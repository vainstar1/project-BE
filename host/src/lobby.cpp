// Custom-game lobbies. The game ships a complete (dormant) Custom Game screen driven by MBCustomGameManager, which used
// Xbox multiplayer sessions. We keep the screen and the manager, and replace the session underneath with a Steam lobby:
// - the host's UI edits the manager's own fields (team slots, map roster, privacy, names); we watch them and publish
//   them as lobby data;
// - members mirror the lobby data back into their manager, so their screen shows the same thing;
// - Start makes the host travel to the map as a listen server and tells members (lobby data) to connect.
#include <windows.h>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <cstdio>
#include <algorithm>
#include "MinHook.h"
#include "uobj.h"
#include "steam.h"
#include "mod.h"

namespace {
// ---- game addresses -------------------------------------------------------------------------------------------
constexpr uintptr_t A_IsInLobby = 0x1411058f0;       // bool MBCustomGameManager::IsInCustomGameLobby()
constexpr uintptr_t A_IsLeader = 0x1411059d0;        // bool MBCustomGameManager::IsLocalPlayerLobbyLeader()
constexpr uintptr_t A_CustomStart = 0x14110cdb0;     // void MBCustomGameManager::StartGame()
constexpr uintptr_t A_CountTeams = 0x141109810;      // void MBCustomGameManager::RecountTeams() (fills Teams[].Num)
constexpr uintptr_t A_SetPlayerTeam = 0x140fcfdc0;   // bool MBFECustomGameMenu::SetPlayerTeamId(const FString& NetId, int TeamId)
constexpr uintptr_t A_SetLocalTeam = 0x140fcf9e0;    // void MBFECustomGameMenu::SetLocalTeamId(int TeamId)
constexpr uintptr_t A_CanStart = 0x140fbd490;        // bool MBFECustomGameMenu::CanStartGame()
constexpr uintptr_t A_TryStart = 0x140fd8650;        // bool MBFECustomGameMenu::TryStartGame()
constexpr uintptr_t A_InviteFriend = 0x141105390;    // void MBCustomGameManager::InviteFriend(const FString&)
constexpr uintptr_t A_GetLocalTeam = 0x14110fd30;    // bool MBCustomGameManager::TryGetLocalTeam(int& Out)
constexpr uintptr_t A_RequestTeam = 0x141110290;     // void MBCustomGameManager::RequestLocalTeamChange(int TeamId)
constexpr uintptr_t A_ExecLeaveLobby = 0x1412f6250;  // exec MBCustomGameManager::LeaveLobby
constexpr uintptr_t A_ExecLeaveGame = 0x141309e10;   // exec MBFECustomGameMenu::LeaveGame
constexpr uintptr_t A_GetMapList = 0x141010c40;      // void GetMapList(UObject* ctx, TArray<FMBMapInfo>& out, bool bIncludeDev)
constexpr uintptr_t A_GameSettings = 0x140fdb010;    // UMBGameSettings* (MapList at +0x88)
constexpr uintptr_t A_MapInfoCopy = 0x1410032a0;     // FMBMapInfo copy constructor (dst, src)
constexpr uintptr_t A_ArrayGrow = 0x1403add20;       // TArray<FMBMapInfo>::ResizeGrow(arr, oldNum)
constexpr uintptr_t A_MinPlayers = 0x144f357b8;      // int, players needed before the match starts

// MBCustomGameManager fields
constexpr size_t CGM_MemberList = 0x80, CGM_Teams = 0xe0, CGM_Spectators = 0x110, CGM_MapRoster = 0x128,
                 CGM_CurrentMap = 0x138, CGM_GameName = 0x160, CGM_Privacy = 0x170, CGM_MaxRoster = 0x174,
                 CGM_TeamsLocked = 0x178, CGM_IsLeader = 0x179;
// MBFECustomGameMenu fields
constexpr size_t Menu_Manager = 0x4a8, Menu_LocalTeam = 0x4c0, Menu_LocalTeamSet = 0x4c4;
constexpr size_t MapInfoSize = 0x90, MI_Name = 0x0, MI_Text = 0x8, MI_Mode = 0x20, MI_Path = 0x28;

struct Member { void* NetIdObj; void* NetIdRef; FString NetId; FString Nickname; int32_t TeamId; bool bLeader; bool bLocal; uint8_t pad[2]; };
static_assert(sizeof(Member) == 0x38, "Member");
struct Team { FString Name; int32_t Num; int32_t Max; };
static_assert(sizeof(Team) == 0x18, "Team");

DWORD gBrowseWait;
std::function<void()> gBrowseDone;

std::wstring W(const std::string& s) { return Utf8ToWide(s); }
std::string N(const std::wstring& s) { return WideToUtf8(s); }
std::string I(long long v) { return std::to_string(v); }
long long ToI(const std::string& s, long long def = 0) { if (s.empty()) return def; char* e; long long v = strtoll(s.c_str(), &e, 10); return e == s.c_str() ? def : v; }

// ---- backends ---------------------------------------------------------------------------------------------------
struct Backend {
    virtual ~Backend() {}
    virtual bool Ready() = 0;
    virtual uint64_t Me() = 0;
    virtual std::wstring NameOf(uint64_t id) = 0;
    virtual void Create(int privacy, int maxMembers, std::function<void(bool, uint64_t)> done) = 0;
    virtual void Join(uint64_t id, std::function<void(bool, int)> done) = 0;   // (ok, Steam chat-room enter response)
    virtual void Leave(uint64_t id) = 0;
    virtual void Set(uint64_t id, const char* k, const std::string& v) = 0;
    virtual std::string Get(uint64_t id, const char* k) = 0;
    virtual void SetMine(uint64_t id, const char* k, const std::string& v) = 0;
    virtual std::string GetMember(uint64_t id, uint64_t m, const char* k) = 0;
    virtual std::vector<uint64_t> Members(uint64_t id) = 0;
    virtual uint64_t Owner(uint64_t id) = 0;
    virtual void SetPrivacy(uint64_t, int) {}
    virtual void SetLimit(uint64_t, int) {}
    virtual std::wstring HostAddress() = 0;     // what members travel to
    // Joinable lobbies of this mod: friends' games first, then public ones. Data must be readable with Get().
    virtual void Browse(std::function<void(std::vector<uint64_t>)> done) = 0;
    virtual std::wstring ListenOptions() { return L"?listen"; }
    virtual void Tick() {}
};

struct SteamBackend : Backend {
    bool Ready() override { return steam::Ready(); }
    uint64_t Me() override { return steam::MyId(); }
    std::wstring NameOf(uint64_t id) override { return id == Me() ? steam::MyName() : steam::NameOf(id); }
    static steam::LobbyType Type(int privacy) { return privacy == 0 ? steam::Public : privacy == 1 ? steam::FriendsOnly : steam::Private; }
    void Create(int privacy, int maxMembers, std::function<void(bool, uint64_t)> done) override { steam::CreateLobby(Type(privacy), maxMembers, done); }
    void Join(uint64_t id, std::function<void(bool, int)> done) override { steam::JoinLobby(id, [done](bool ok, uint64_t, int r) { done(ok, r); }); }
    void Leave(uint64_t id) override { steam::LeaveLobby(id); }
    void Set(uint64_t id, const char* k, const std::string& v) override { steam::SetLobbyData(id, k, v); }
    std::string Get(uint64_t id, const char* k) override { return steam::LobbyData(id, k); }
    void SetMine(uint64_t id, const char* k, const std::string& v) override { steam::SetMemberData(id, k, v); }
    std::string GetMember(uint64_t id, uint64_t m, const char* k) override { return steam::MemberData(id, m, k); }
    std::vector<uint64_t> Members(uint64_t id) override { return steam::Members(id); }
    uint64_t Owner(uint64_t id) override { return steam::Owner(id); }
    void SetPrivacy(uint64_t id, int p) override { steam::SetLobbyType(id, Type(p)); }
    void SetLimit(uint64_t id, int n) override { steam::SetMemberLimit(id, n); }
    std::wstring HostAddress() override { return L"steam." + std::to_wstring(Me()); }
    void Browse(std::function<void(std::vector<uint64_t>)> done) override {
        // Friends in this game who sit in a lobby (friends-only lobbies are not listed publicly).
        auto friends = std::make_shared<std::vector<uint64_t>>();
        for (auto& f : steam::Friends()) if (f.inGame && f.lobby) { friends->push_back(f.lobby); steam::RequestLobbyData(f.lobby); }
        steam::RequestLobbyList({ { "be1v1", BE1V1_PROTOCOL } }, [friends, done](std::vector<uint64_t> pub) {
            std::vector<uint64_t> all = *friends;
            for (uint64_t l : pub) if (std::find(all.begin(), all.end(), l) == all.end()) all.push_back(l);
            // Friends' lobby data arrives asynchronously; give it a moment.
            gBrowseWait = GetTickCount() + 1200;
            gBrowseDone = [all, done]() { done(all); };
        });
    }
};

// Local test backend (-be1v1devlobby): two instances on one PC share a folder; transport is 127.0.0.1.
struct DevBackend : Backend {
    std::wstring dir;
    uint64_t me;
    std::map<std::string, std::string> cache;
    DevBackend() {
        wchar_t t[MAX_PATH]; GetTempPathW(MAX_PATH, t);
        dir = std::wstring(t) + L"be1v1-devlobby\\";
        CreateDirectoryW(dir.c_str(), nullptr);
        me = 90000000000ull + GetCurrentProcessId();
    }
    static std::map<std::string, std::string> Read(const std::wstring& p) {
        std::map<std::string, std::string> m;
        FILE* f = _wfopen(p.c_str(), L"rb"); if (!f) return m;
        char line[2048];
        while (fgets(line, sizeof line, f)) {
            std::string s = line; while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
            size_t e = s.find('='); if (e != std::string::npos) m[s.substr(0, e)] = s.substr(e + 1);
        }
        fclose(f); return m;
    }
    static void Write(const std::wstring& p, const std::map<std::string, std::string>& m) {
        std::wstring tmp = p + L".tmp";
        FILE* f = _wfopen(tmp.c_str(), L"wb"); if (!f) return;
        for (auto& kv : m) fprintf(f, "%s=%s\n", kv.first.c_str(), kv.second.c_str());
        fclose(f); MoveFileExW(tmp.c_str(), p.c_str(), MOVEFILE_REPLACE_EXISTING);
    }
    std::wstring MemberFile(uint64_t id) { return dir + L"m_" + std::to_wstring(id) + L".kv"; }
    bool Ready() override { return true; }
    uint64_t Me() override { return me; }
    std::wstring NameOf(uint64_t id) override {
        auto m = Read(MemberFile(id)); auto it = m.find("name");
        return it != m.end() ? W(it->second) : L"Player " + std::to_wstring(id % 100000);
    }
    bool joined = false;
    void Create(int, int, std::function<void(bool, uint64_t)> done) override {
        joined = true;
        cache.clear(); cache["owner"] = I((long long)me);
        Write(dir + L"lobby.kv", cache);
        Touch(); done(true, 1);
    }
    void Join(uint64_t, std::function<void(bool, int)> done) override {
        bool ok = GetFileAttributesW((dir + L"lobby.kv").c_str()) != INVALID_FILE_ATTRIBUTES;
        if (ok) { joined = true; Touch(); }
        done(ok, ok ? 1 : 2);
    }
    void Leave(uint64_t) override {
        joined = false;
        DeleteFileW(MemberFile(me).c_str());
        if (Owner(1) == me) DeleteFileW((dir + L"lobby.kv").c_str());
    }
    void Set(uint64_t, const char* k, const std::string& v) override { cache = Read(dir + L"lobby.kv"); cache[k] = v; Write(dir + L"lobby.kv", cache); }
    std::string Get(uint64_t, const char* k) override { auto it = cache.find(k); return it != cache.end() ? it->second : ""; }
    void SetMine(uint64_t, const char* k, const std::string& v) override { auto m = Read(MemberFile(me)); m[k] = v; Write(MemberFile(me), m); }
    std::string GetMember(uint64_t, uint64_t id, const char* k) override { auto m = Read(MemberFile(id)); auto it = m.find(k); return it != m.end() ? it->second : ""; }
    std::vector<uint64_t> Members(uint64_t) override {
        std::vector<uint64_t> r;
        WIN32_FIND_DATAW fd; HANDLE h = FindFirstFileW((dir + L"m_*.kv").c_str(), &fd);
        if (h == INVALID_HANDLE_VALUE) return r;
        FILETIME now; GetSystemTimeAsFileTime(&now);
        uint64_t n = ((uint64_t)now.dwHighDateTime << 32) | now.dwLowDateTime;
        do {
            uint64_t t = ((uint64_t)fd.ftLastWriteTime.dwHighDateTime << 32) | fd.ftLastWriteTime.dwLowDateTime;
            if (n - t < 50000000ull) r.push_back(_wcstoui64(fd.cFileName + 2, nullptr, 10));   // seen in the last 5 s
        } while (FindNextFileW(h, &fd));
        FindClose(h);
        std::sort(r.begin(), r.end());
        return r;
    }
    uint64_t Owner(uint64_t) override { return (uint64_t)ToI(Get(1, "owner")); }
    std::wstring HostAddress() override { return L"127.0.0.1:7777"; }
    std::wstring ListenOptions() override { return L"?listen?bIsLanMatch"; }
    void Browse(std::function<void(std::vector<uint64_t>)> done) override {
        std::vector<uint64_t> r;
        cache = Read(dir + L"lobby.kv");
        if (!cache.empty()) r.push_back(1);
        done(r);
    }
    DWORD lastTouch = 0;
    void Touch() { auto m = Read(MemberFile(me)); m["name"] = N(steam::Ready() ? steam::MyName() : L"Player " + std::to_wstring(me % 100000)); Write(MemberFile(me), m); }
    void Tick() override {
        cache = Read(dir + L"lobby.kv");
        DWORD now = GetTickCount();
        if (joined && now - lastTouch > 1000) { lastTouch = now; Touch(); }
    }
};

std::unique_ptr<Backend> gB;

// ---- map list -----------------------------------------------------------------------------------------------
// Our map list for the custom-game screen: every arena in both modes (including those rotated out of matchmaking),
// the Dojo and the developers' rollback playground. Indices into this list are what the roster stores.
const wchar_t* kMaps[] = {
    L"/Game/Levels/Map_Train/GameMode_CP/Map_Train_CP_Main",
    L"/Game/Levels/Map_Sewers/GameMode_CP/Map_Sewers_CP_Main",
    L"/Game/Levels/Map_Rooftops/GameMode_CP/Map_Rooftops_CP_Main",
    L"/Game/Levels/Map_Junkyard/GameMode_CP/Map_Junkyard_CP_Main",
    L"/Game/Levels/Map_Facility/GameMode_CP/Map_Facility_CP_Main",
    L"/Game/Levels/Map_Stormdrain/GameMode_CP/Map_Stormdrain_CP_Main",
    L"/Game/Levels/Map_Landslide/GameMode_CP/Map_Landslide_CP_Main",
    L"/Game/Levels/Map_Train/GameMode_Seeds/Map_Train_Seeds_Main",
    L"/Game/Levels/Map_Sewers/GameMode_Seeds/Map_Sewers_Seeds_Main",
    L"/Game/Levels/Map_Rooftops/GameMode_Seeds/Map_Rooftops_Seeds_Main",
    L"/Game/Levels/Map_Junkyard/GameMode_Seeds/Map_Junkyard_Seeds_Main",
    L"/Game/Levels/Map_Facility/GameMode_Seeds/Map_Facility_Seeds_Main",
    L"/Game/Levels/Map_Stormdrain/GameMode_Seeds/Map_Stormdrain_Seeds_Main",
    L"/Game/Levels/Map_Landslide/GameMode_Seeds/Map_Landslide_Seeds_Main",
    L"/Game/Levels/Training/Dojo/New/Map_Dojo_Main",
    L"/Game/Levels/Playgrounds/MB_DefaultRollbackMap",
};
constexpr int kNumMaps = sizeof(kMaps) / sizeof(kMaps[0]);
constexpr int kPlaygroundIdx = kNumMaps - 1, kDojoIdx = kNumMaps - 2;
uint8_t* gPlaygroundRow;   // synthetic FMBMapInfo for the playground (not in the game's MapList asset)

TArray<uint8_t>* MapRows() {
    uint8_t* settings = Fn<uint8_t*(__fastcall*)()>(A_GameSettings)();
    uint8_t* ml = settings ? F<uint8_t*>(settings, 0x88) : nullptr;
    return ml ? &F<TArray<uint8_t>>(ml, 0x30) : nullptr;
}
uint8_t* FindRow(const wchar_t* path) {
    auto* rows = MapRows(); if (!rows) return nullptr;
    for (int i = 0; i < rows->Num; i++) {
        uint8_t* r = rows->Data + i * MapInfoSize;
        if (!_wcsicmp(F<FString>(r, MI_Path).c_str(), path)) return r;
    }
    return nullptr;
}
uint8_t* RowFor(int idx) {
    if (idx < 0 || idx >= kNumMaps) return nullptr;
    if (idx != kPlaygroundIdx) return FindRow(kMaps[idx]);
    if (!gPlaygroundRow) {
        uint8_t* src = FindRow(kMaps[kDojoIdx]);
        if (!src) return nullptr;
        gPlaygroundRow = (uint8_t*)uo::Malloc(MapInfoSize);
        memset(gPlaygroundRow, 0, MapInfoSize);
        Fn<void(__fastcall*)(void*, void*)>(A_MapInfoCopy)(gPlaygroundRow, src);
        F<FName>(gPlaygroundRow, MI_Name) = uo::MakeName(L"Playground");
        uo::MakeText((uo::FText*)(gPlaygroundRow + MI_Text), L"Playground");
        F<FString>(gPlaygroundRow, MI_Path) = FString{};
        uo::SetFString(F<FString>(gPlaygroundRow, MI_Path), kMaps[kPlaygroundIdx]);
        F<uint8_t>(gPlaygroundRow, MI_Mode) = 0;
    }
    return gPlaygroundRow;
}
std::wstring MapName(int idx) {
    uint8_t* row = RowFor(idx);
    return row ? ui::TextToString(row + MI_Text) : L"";
}
std::wstring MapPath(int idx) { return idx >= 0 && idx < kNumMaps ? kMaps[idx] : kMaps[0]; }
bool IsTrainingMap(int idx) { return idx == kDojoIdx || idx == kPlaygroundIdx; }

using GetMapListFn = void(__fastcall*)(void*, TArray<uint8_t>*, bool);
GetMapListFn oGetMapList;
void __fastcall hkGetMapList(void* ctx, TArray<uint8_t>* out, bool includeDev) {
    if (!MapRows()) { oGetMapList(ctx, out, includeDev); return; }
    for (int i = 0; i < kNumMaps; i++) {
        uint8_t* row = RowFor(i);
        if (!row) { Log("maps: missing row %ls", kMaps[i]); continue; }
        int n = out->Num;
        out->Num = n + 1;
        if (out->Max < n + 1) Fn<void(__fastcall*)(void*, int)>(A_ArrayGrow)(out, n);
        Fn<void(__fastcall*)(void*, void*)>(A_MapInfoCopy)(out->Data + n * MapInfoSize, row);
    }
}

// ---- lobby state --------------------------------------------------------------------------------------------
enum class St { Idle, Creating, Joining, Lobby };
St gSt = St::Idle;
uint64_t gId;                       // lobby id
uint64_t gPendingJoin;              // invite accepted while not on the main menu
bool gWantScreen;                   // show the lobby screen as soon as the main menu allows
uint64_t gHostId;                   // the lobby owner we know (to notice a host leaving)
std::wstring gPendingMessage;
std::string gMemberSnap;            // member: last lobby data applied to the screen
uo::UObject* gDecorated;            // lobby screen we added LEAVE to
bool gHost;
std::map<uint64_t, int> gTeam;      // host: authoritative team assignment
std::map<uint64_t, long long> gReqSeen;
long long gMyReq;                   // my team-change request counter
long long gSeq, gSeenSeq;           // match start counter (published by host / last acted on)
int gMyTeamInMatch, gPlayersInMatch;
bool gInMatch;                      // we travelled for the current seq
std::string gLastPublished;         // host: last lobby snapshot we pushed
DWORD gLastSync;
std::wstring gPendingJoinFromCmdline;

uo::UObject* Mgr() {
    static uo::UObject* cached;
    if (cached && uo::IsLive(cached)) return cached;
    cached = uo::FindTransient(uo::FindClass(L"MBCustomGameManager"));
    return cached;
}
// The on-screen Custom Game screen (closed copies linger until garbage collection).
uo::UObject* Screen() {
    uo::UObject* cls = uo::FindClass(L"CustomGameScreen_C");
    // Screens live in the front end's ScreenSlot overlay; closed ones are detached from it.
    for (uo::UObject* s : cls ? uo::FindAllTransient(cls) : std::vector<uo::UObject*>()) {
        uo::Call c(s, L"GetParent");
        if (c.ok() && c.run().get<uo::UObject*>(L"ReturnValue")) return s;
    }
    return nullptr;
}
// A widget of the given class inside the on-screen Custom Game screen.
uo::UObject* InScreen(const wchar_t* clsName) {
    uo::UObject* scr = Screen();
    uo::UObject* c = uo::FindClass(clsName);
    if (!scr || !c) return nullptr;
    for (uo::UObject* w : uo::FindAllTransient(c))
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o))
            if (o == scr) return w;
    return nullptr;
}
uo::UObject* Menu() {
    uo::UObject* m = InScreen(L"MBFECustomGameMenu");
    return m && F<void*>(m, Menu_Manager) ? m : nullptr;
}

bool __fastcall hkIsInLobbyImpl(void*);
bool __fastcall hkIsLeaderImpl(void*);
using BoolFn = bool(__fastcall*)(void*);
BoolFn oIsInLobby, oIsLeader, oCanStart, oTryStart;
// While the player has stepped out to the main menu, the lobby reports "not in a lobby" to the front end: the screen
// then closes itself and the main menu doesn't bring it back. We stay in the Steam lobby all the same.
bool gScreenHidden;
bool __fastcall hkIsInLobbyImpl(void* self) { return gSt == St::Lobby && !gScreenHidden; }
bool __fastcall hkIsLeaderImpl(void* self) { return gSt == St::Lobby && gHost; }

// Fills the manager's (garbage-collected) TArray<FMBCustomGameMember> with our member list.
void WriteMembers(uo::UObject* m, const std::vector<std::pair<uint64_t, int>>& members, uint64_t owner) {
    auto& list = F<TArray<Member>>(m, CGM_MemberList);
    if (list.Max < (int)members.size() || !list.Data) {
        Member* d = (Member*)uo::Malloc(sizeof(Member) * 16);
        memset((void*)d, 0, sizeof(Member) * 16);
        for (int i = 0; i < list.Num && i < 16; i++) d[i] = list.Data[i];
        list.Data = d; list.Max = 16;
    }
    for (int i = list.Num; i < (int)members.size(); i++) memset((void*)&list.Data[i], 0, sizeof(Member));
    list.Num = (int)members.size();
    uint64_t me = gB->Me();
    for (size_t i = 0; i < members.size(); i++) {
        Member& e = list.Data[i];
        uo::SetFString(e.NetId, std::to_wstring(members[i].first));
        std::wstring name = gB->NameOf(members[i].first);
        if (name.empty()) name = L"Player";
        uo::SetFString(e.Nickname, name);
        e.TeamId = members[i].second;
        e.bLeader = members[i].first == owner;
        e.bLocal = members[i].first == me;
    }
    Fn<void(__fastcall*)(void*)>(A_CountTeams)(m);
}

// Team slot widgets (created by the menu with the game instance as outer). The slot Blueprint collapses the local
// player's row when its data changes after construction; occupied rows must stay visible.
std::vector<uo::UObject*> gSlots;
DWORD gSlotFixUntil;
void FixSlotVisibility() {
    for (uo::UObject* s : gSlots) {
        if (!uo::IsLive(s) || !F<bool>(s, 0x4a8 /* bIsOccupied */)) continue;
        uo::Call v(s, L"GetVisibility");
        if (v.ok() && v.run().get<uint8_t>(L"ReturnValue") == 1 /* Collapsed */)
            uo::Call(s, L"SetVisibility").set<uint8_t>(L"InVisibility", 0).run();
    }
}
void RefreshUI() {
    if (!net::MenuSettled()) return;
    uo::UObject* menu = Menu();
    if (menu) { uo::Call(menu, L"NativeOnSessionUpdated").run(); uo::Call(menu, L"RefreshTeamSlotButtons").run(); }
    gSlots = uo::FindAllTransient(uo::FindClass(L"MBFECustomGameTeamSlotButton"));
    gSlotFixUntil = GetTickCount() + 3000;
    FixSlotVisibility();
}

std::vector<int> ParseCsv(const std::string& s) {
    std::vector<int> r; size_t p = 0;
    while (p < s.size()) { size_t e = s.find(',', p); if (e == std::string::npos) e = s.size(); if (e > p) r.push_back((int)ToI(s.substr(p, e - p))); p = e + 1; }
    return r;
}
std::string Csv(const int32_t* d, int n) { std::string s; for (int i = 0; i < n; i++) { if (i) s += ","; s += I(d[i]); } return s; }

int TeamMax(uo::UObject* m, int t) { return t < 0 ? F<Team>(m, CGM_Spectators).Max : (&F<Team>(m, CGM_Teams))[t].Max; }

int AutoTeam(uo::UObject* m) {
    int c[2] = { 0, 0 };
    for (auto& kv : gTeam) if (kv.second == 0 || kv.second == 1) c[kv.second]++;
    (void)m;
    return c[0] <= c[1] ? 0 : 1;
}
int CountTeam(int t) { int n = 0; for (auto& kv : gTeam) if (kv.second == t) n++; return n; }

// ---- host side ----------------------------------------------------------------------------------------------
void HostSync(uo::UObject* m) {
    std::vector<uint64_t> members = gB->Members(gId);
    std::set<uint64_t> present(members.begin(), members.end());
    for (auto it = gTeam.begin(); it != gTeam.end();) it = present.count(it->first) ? std::next(it) : gTeam.erase(it);
    for (uint64_t id : members) {
        if (!gTeam.count(id)) { int t = AutoTeam(m); gTeam[id] = t; }
        // Team-change requests from members: "want" = "<team>:<counter>"
        std::string want = gB->GetMember(gId, id, "want");
        size_t c = want.find(':');
        if (c != std::string::npos) {
            long long n = ToI(want.substr(c + 1));
            if (n > gReqSeen[id]) {
                gReqSeen[id] = n;
                int t = (int)ToI(want.substr(0, c));
                if (!F<bool>(m, CGM_TeamsLocked) && t >= -1 && t <= 1 && gTeam[id] != t && CountTeam(t) < TeamMax(m, t)) gTeam[id] = t;
            }
        }
    }
    std::vector<std::pair<uint64_t, int>> list;
    for (uint64_t id : members) list.push_back({ id, gTeam[id] });
    WriteMembers(m, list, gB->Me());

    // Publish everything members need to rebuild the screen.
    std::string teams;
    for (auto& e : list) { if (!teams.empty()) teams += ";"; teams += I((long long)e.first) + ":" + I(e.second); }
    Team* t = &F<Team>(m, CGM_Teams);
    auto& roster = F<TArray<int32_t>>(m, CGM_MapRoster);
    std::map<std::string, std::string> kv = {
        { "be1v1", BE1V1_PROTOCOL },
        { "name", N(F<FString>(m, CGM_GameName).c_str()) },
        { "priv", I(F<uint8_t>(m, CGM_Privacy)) },
        { "maps", Csv(roster.Data, roster.Num) },
        { "maxr", I(F<int32_t>(m, CGM_MaxRoster)) },
        { "cur", I(F<int32_t>(m, CGM_CurrentMap)) },
        { "tn0", N(t[0].Name.c_str()) }, { "tn1", N(t[1].Name.c_str()) },
        { "tm0", I(t[0].Max) }, { "tm1", I(t[1].Max) }, { "tms", I(F<Team>(m, CGM_Spectators).Max) },
        { "lock", I(F<bool>(m, CGM_TeamsLocked)) },
        { "teams", teams },
        { "n", I((long long)members.size()) },
        { "host", I((long long)gB->Me()) },
        { "hn", N(gB->NameOf(gB->Me())) },
        { "seq", I(gSeq) },
        { "state", gInMatch ? "game" : "lobby" },
        { "addr", N(gB->HostAddress()) },
        { "map", N(MapPath(roster.Num ? roster.Data[F<int32_t>(m, CGM_CurrentMap) % roster.Num] : 0)) },
        { "rules", rules::Encode() },
        { "mapname", N(MapName(roster.Num ? roster.Data[F<int32_t>(m, CGM_CurrentMap) % roster.Num] : 0)) },
        { "max", I(2 * (&F<Team>(m, CGM_Teams))[0].Max) },
    };
    std::string snap;
    for (auto& e : kv) snap += e.first + "=" + e.second + "\n";
    if (snap != gLastPublished) {
        static int lastPriv = -1;
        int priv = F<uint8_t>(m, CGM_Privacy);
        if (priv != lastPriv) { gB->SetPrivacy(gId, priv); lastPriv = priv; }
        for (auto& e : kv) gB->Set(gId, e.first.c_str(), e.second);
        gLastPublished = snap;
        RefreshUI();
    }
}

// ---- member side --------------------------------------------------------------------------------------------
void MemberSync(uo::UObject* m) {
    if (gB->Get(gId, "be1v1").empty()) return;   // data not arrived yet
    std::vector<uint64_t> members = gB->Members(gId);
    std::map<uint64_t, int> assigned;
    std::string teams = gB->Get(gId, "teams");
    size_t p = 0;
    while (p < teams.size()) {
        size_t e = teams.find(';', p); if (e == std::string::npos) e = teams.size();
        std::string item = teams.substr(p, e - p); size_t c = item.find(':');
        if (c != std::string::npos) assigned[(uint64_t)ToI(item.substr(0, c))] = (int)ToI(item.substr(c + 1));
        p = e + 1;
    }
    std::vector<std::pair<uint64_t, int>> list;
    for (uint64_t id : members) list.push_back({ id, assigned.count(id) ? assigned[id] : 0 });

    std::string snap = gB->Get(gId, "name") + "|" + teams + "|" + gB->Get(gId, "maps") + "|" + gB->Get(gId, "cur") + "|" +
                       gB->Get(gId, "priv") + "|" + gB->Get(gId, "lock") + "|" + gB->Get(gId, "tn0") + "|" + gB->Get(gId, "tn1") + "|" +
                       gB->Get(gId, "tm0") + gB->Get(gId, "tm1") + gB->Get(gId, "tms") + "|" + I((long long)members.size()) + "|" +
                       gB->Get(gId, "rules");
    if (snap == gMemberSnap) return;
    gMemberSnap = snap;
    WriteMembers(m, list, gB->Owner(gId));
    rules::Set(rules::Decode(gB->Get(gId, "rules")));
    uo::SetFString(F<FString>(m, CGM_GameName), W(gB->Get(gId, "name")));
    F<uint8_t>(m, CGM_Privacy) = (uint8_t)ToI(gB->Get(gId, "priv"));
    F<bool>(m, CGM_TeamsLocked) = ToI(gB->Get(gId, "lock")) != 0;
    Team* t = &F<Team>(m, CGM_Teams);
    uo::SetFString(t[0].Name, W(gB->Get(gId, "tn0")));
    uo::SetFString(t[1].Name, W(gB->Get(gId, "tn1")));
    t[0].Max = (int)ToI(gB->Get(gId, "tm0"), 4); t[1].Max = (int)ToI(gB->Get(gId, "tm1"), 4);
    F<Team>(m, CGM_Spectators).Max = (int)ToI(gB->Get(gId, "tms"));
    std::vector<int> roster = ParseCsv(gB->Get(gId, "maps"));
    auto& r = F<TArray<int32_t>>(m, CGM_MapRoster);
    if (r.Max < 16 || !r.Data) { r.Data = (int32_t*)uo::Malloc(sizeof(int32_t) * 16); r.Max = 16; }
    r.Num = (int)std::min<size_t>(roster.size(), 16);
    for (int i = 0; i < r.Num; i++) r.Data[i] = roster[i];
    F<int32_t>(m, CGM_MaxRoster) = (int)ToI(gB->Get(gId, "maxr"), 1);
    F<int32_t>(m, CGM_CurrentMap) = (int)ToI(gB->Get(gId, "cur"));
    Fn<void(__fastcall*)(void*)>(A_CountTeams)(m);
    // Our own pending team request stays visible until the host applies it.
    uo::UObject* menu = Menu();
    if (menu) F<bool>(menu, Menu_LocalTeamSet) = false;
    RefreshUI();
}

// Resets the manager to "not in a lobby" defaults.
void ResetManager() {
    uo::UObject* m = Mgr();
    if (!m) return;
    F<TArray<Member>>(m, CGM_MemberList).Num = 0;
    F<TArray<int32_t>>(m, CGM_MapRoster).Num = 0;
    F<bool>(m, CGM_IsLeader) = false;
    Fn<void(__fastcall*)(void*)>(A_CountTeams)(m);
}

void InitManagerAsHost(uo::UObject* m) {
    Team* t = &F<Team>(m, CGM_Teams);
    t[0].Max = t[1].Max = rules::Current().teamSize;
    uo::SetFString(t[0].Name, L""); uo::SetFString(t[1].Name, L"");
    F<Team>(m, CGM_Spectators).Max = 4;
    F<bool>(m, CGM_IsLeader) = true;
    F<bool>(m, CGM_TeamsLocked) = false;
    F<uint8_t>(m, CGM_Privacy) = 1;   // friends
    uo::SetFString(F<FString>(m, CGM_GameName), gB->NameOf(gB->Me()) + L"'s Game");
    auto& r = F<TArray<int32_t>>(m, CGM_MapRoster);
    if (r.Max < 16 || !r.Data) { r.Data = (int32_t*)uo::Malloc(sizeof(int32_t) * 16); r.Max = 16; }
    r.Num = 1; r.Data[0] = 0;
    F<int32_t>(m, CGM_MaxRoster) = 5;
    F<int32_t>(m, CGM_CurrentMap) = 0;
}

void Enter(uint64_t id, bool host) {
    gId = id; gHost = host; gSt = St::Lobby;
    gTeam.clear(); gReqSeen.clear(); gLastPublished.clear(); gInMatch = false; gMemberSnap.clear(); gDecorated = nullptr;
    gSeq = host ? 0 : ToI(gB->Get(id, "seq"));
    gSeenSeq = gSeq;
    if (!host && gB->Get(id, "state") == "game") gSeenSeq = -1;   // a match is running: join it
    uo::UObject* m = Mgr();
    if (m && host) InitManagerAsHost(m);
    if (m && !host) F<bool>(m, CGM_IsLeader) = false;
    gB->SetMine(id, "ver", BE1V1_VERSION);
    gHostId = gB->Owner(id);
    steam::SetRichPresence("connect", ("+connect_lobby " + I((long long)id)).c_str());
    steam::SetRichPresence("status", "In a custom game lobby");
    Log("lobby: entered %llu as %s", (unsigned long long)id, host ? "host" : "member");
}

void ShowLobbyScreen() {
    gScreenHidden = false;
    uo::UObject* cls = uo::FindObjectPath(L"/Game/UI/FrontEnd/CustomGame/CustomGameScreen.CustomGameScreen_C");
    if (!cls) return;
    if (Screen()) return;   // already up
    Log("lobby: showing the lobby screen");
    uo::UObject* fe = uo::FindFirst(uo::FindClass(L"MBFrontEnd"));
    if (!fe) return;
    uo::Call(fe, L"PushScreen").set<uo::UObject*>(L"ScreenClass", cls).set<uo::UObject*>(L"PlayerController", nullptr).run();
}

// "?Name=<Steam name>": the player name the engine gives our PlayerState (shown in fighter select, scoreboard, kill feed).
std::wstring NameOption() {
    std::wstring n = gB->NameOf(gB->Me()), clean;
    for (wchar_t c : n) if (c != L'?' && c != L'=' && c != L'#' && c >= 32) clean += c;
    if (clean.empty()) return L"";
    if (clean.size() > 20) clean.resize(20);
    return L"?Name=" + clean;
}

// The lobby screen has two hidden debug buttons; they become LEAVE in the host's and the members' button column,
// styled like INVITE.
uo::UObject* ScreenWidget(uo::UObject* scr, const wchar_t* cls, const wchar_t* name) {
    FName want = uo::MakeName(name);
    for (uo::UObject* w : uo::FindAll(uo::FindClass(cls))) {
        if (!uo::NameIs(w, want)) continue;
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o)) if (o == scr) return w;
    }
    return nullptr;
}
void DecorateScreen() {
    uo::UObject* scr = Screen();
    if (!scr || scr == gDecorated) return;
    uo::UObject* invite = ScreenWidget(scr, L"PromptListButtonTemplate_C", L"Button_Invite");
    uo::UObject* hostView = ScreenWidget(scr, L"VerticalBox", L"HostView");
    uo::UObject* clientView = ScreenWidget(scr, L"VerticalBox", L"ClientView");
    if (!invite || !hostView || !clientView) return;
    gDecorated = scr;
    int fontOff = uo::PropOffset(uo::FindClass(L"TextBlock"), L"Font");
    uo::UObject* inviteText = F<uo::UObject*>(invite, 0x4b0);
    std::pair<const wchar_t*, uo::UObject*> moves[] = { { L"Debug_FetchSessionData", hostView }, { L"Debug_UpdateSessionData", clientView } };
    for (auto& mv : moves) {
        uo::UObject* b = ScreenWidget(scr, L"PromptListButtonTemplate_C", mv.first);
        if (!b) continue;
        uo::Call(b, L"RemoveFromParent").run();
        uo::Call add(mv.second, L"AddChild");
        uo::UObject* slot = add.set<uo::UObject*>(L"Content", b).run().get<uo::UObject*>(L"ReturnValue");
        uo::UObject* invSlot = F<uo::UObject*>(invite, uo::PropOffset(uo::FindClass(L"Widget"), L"Slot"));
        if (slot && invSlot) {
            uo::UObject* sc = uo::ClassOf(invSlot);
            int ha = uo::PropOffset(sc, L"HorizontalAlignment"), pad = uo::PropOffset(sc, L"Padding");
            if (ha >= 0) uo::Call(slot, L"SetHorizontalAlignment").set<uint8_t>(L"InHorizontalAlignment", F<uint8_t>(invSlot, ha)).run();
            if (pad >= 0) { uo::Call c(slot, L"SetPadding"); int o = c.off(L"InPadding"); if (o >= 0) { memcpy(c.buf.data() + o, invSlot + pad, 16); c.run(); } }
        }
        F<int32_t>(b, 0x760) = F<int32_t>(invite, 0x760);   // TextSize
        F<uint8_t>(b, 0x75c) = F<uint8_t>(invite, 0x75c);   // Justification
        F<uint8_t>(b, 0x75d) = F<uint8_t>(invite, 0x75d);   // TextSlotAlignment
        uo::UObject* tb = F<uo::UObject*>(b, 0x4b0);        // ButtonText
        if (tb && inviteText && fontOff >= 0) {
            uo::Call f(tb, L"SetFont");
            int a = f.off(L"InFontInfo");
            if (a >= 0) { memcpy(f.buf.data() + a, inviteText + fontOff, 0x50); f.run(); }
            uo::Call(tb, L"SetJustification").set<uint8_t>(L"Justification", F<uint8_t>(invite, 0x75c)).run();
        }
        if (tb) { uo::FText t; uo::MakeText(&t, L"LEAVE"); uo::Call(tb, L"SetText").set(L"InText", t).run(); }
        uo::Call(b, L"SetVisibility").set<uint8_t>(L"InVisibility", 0).run();
    }
    Log("lobby: screen decorated");
}

// ---- hooks ----------------------------------------------------------------------------------------------------
using VoidFn = void(__fastcall*)(void*);
VoidFn oCustomStart;
void __fastcall hkCustomStart(void* mgr) {
    if (gSt != St::Lobby) { oCustomStart(mgr); return; }
    if (!gHost) return;
    uo::UObject* m = (uo::UObject*)mgr;
    auto& roster = F<TArray<int32_t>>(m, CGM_MapRoster);
    int cur = F<int32_t>(m, CGM_CurrentMap);
    int idx = roster.Num ? roster.Data[cur % roster.Num] : 0;
    gPlayersInMatch = CountTeam(0) + CountTeam(1);
    // Training maps (Dojo, Playground) start with the host alone and friends drop in; matches wait for everyone.
    int32_t minPlayers = IsTrainingMap(idx) ? 1 : std::max(1, gPlayersInMatch);
    PatchBytes((void*)VA(A_MinPlayers), &minPlayers, sizeof minPlayers);
    gMyTeamInMatch = gTeam.count(gB->Me()) ? gTeam[gB->Me()] : 0;
    gSeq++; gSeenSeq = gSeq; gInMatch = true;
    std::wstring url = MapPath(idx) + gB->ListenOptions() + NameOption();
    Log("lobby: start #%lld map=%ls players=%d", gSeq, url.c_str(), gPlayersInMatch);
    HostSync(m);   // publish state=game before we leave the menu
    net::Travel(url);
}

using SetPlayerTeamFn = bool(__fastcall*)(void*, FString*, int);
SetPlayerTeamFn oSetPlayerTeam;
bool __fastcall hkSetPlayerTeam(void* menu, FString* netId, int team) {
    if (gSt != St::Lobby) return oSetPlayerTeam(menu, netId, team);
    if (!gHost || !netId) return false;
    uint64_t id = _wcstoui64(netId->c_str(), nullptr, 10);
    uo::UObject* m = Mgr();
    if (!m || !gTeam.count(id) || gTeam[id] == team) return gTeam.count(id) != 0;
    if (team < -1 || team > 1 || CountTeam(team) >= TeamMax(m, team)) return false;
    gTeam[id] = team;
    Log("lobby: host moved %llu to team %d", (unsigned long long)id, team);
    HostSync(m);
    return true;
}

using SetLocalTeamFn = void(__fastcall*)(void*, int);
SetLocalTeamFn oSetLocalTeam;
void __fastcall hkSetLocalTeam(void* menu, int team) {
    if (gSt != St::Lobby) { oSetLocalTeam(menu, team); return; }
    uo::UObject* m = Mgr();
    if (gHost) {
        FString id{}; std::wstring s = std::to_wstring(gB->Me());
        id.Data = (wchar_t*)s.c_str(); id.Num = id.Max = (int)s.size() + 1;
        hkSetPlayerTeam(menu, &id, team);
        return;
    }
    F<int32_t>((uo::UObject*)menu, Menu_LocalTeam) = team;
    F<bool>((uo::UObject*)menu, Menu_LocalTeamSet) = true;
    gB->SetMine(gId, "want", I(team) + ":" + I(++gMyReq));
    Log("lobby: requested team %d", team);
    (void)m;
    RefreshUI();
}

// Start is allowed with at least one player on a team (practice alone, dojo), within team limits.
bool CanStartNow() {
    uo::UObject* m = Mgr();
    if (!m || !gHost) return false;
    int a = CountTeam(0), b = CountTeam(1);
    return a + b >= 1 && a <= TeamMax(m, 0) && b <= TeamMax(m, 1);
}
bool __fastcall hkCanStart(void* menu) { return gSt == St::Lobby ? CanStartNow() : oCanStart(menu); }
bool __fastcall hkTryStart(void* menu) {
    if (gSt != St::Lobby) return oTryStart(menu);
    if (!CanStartNow()) return false;
    hkCustomStart(Mgr());
    return true;
}

// The local player's team and team-change requests (the menu's prev/next team buttons).
using GetLocalTeamFn = bool(__fastcall*)(void*, int*);
GetLocalTeamFn oGetLocalTeam;
bool __fastcall hkGetLocalTeam(void* mgr, int* out) {
    if (gSt != St::Lobby) return oGetLocalTeam(mgr, out);
    auto& list = F<TArray<Member>>((uo::UObject*)mgr, CGM_MemberList);
    for (int i = 0; i < list.Num; i++) if (list.Data[i].bLocal) { *out = list.Data[i].TeamId; return true; }
    return false;
}
using RequestTeamFn = void(__fastcall*)(void*, int);
RequestTeamFn oRequestTeam;
void RequestTeam(int team) {
    uo::UObject* m = Mgr();
    if (!m) return;
    if (gHost) {
        uint64_t me = gB->Me();
        if (team >= -1 && team <= 1 && gTeam[me] != team && CountTeam(team) < TeamMax(m, team)) gTeam[me] = team;
        HostSync(m);
    } else {
        gB->SetMine(gId, "want", I(team) + ":" + I(++gMyReq));
    }
    Log("lobby: requested team %d", team);
}
void __fastcall hkRequestTeam(void* mgr, int team) {
    if (gSt != St::Lobby) { oRequestTeam(mgr, team); return; }
    RequestTeam(team);
}

using InviteFn = void(__fastcall*)(void*, FString*);
InviteFn oInvite;
void __fastcall hkInvite(void* mgr, FString* id) {
    if (gSt != St::Lobby) { oInvite(mgr, id); return; }
    uint64_t user = id ? _wcstoui64(id->c_str(), nullptr, 10) : 0;
    if (user) steam::InviteUser(gId, user);
    Log("lobby: invited %llu", (unsigned long long)user);
}

// UFunction exec thunks for LeaveLobby (manager) and LeaveGame (menu): no parameters.
struct FFrameHead { uint8_t pad[0x20]; uint8_t* Code; };
using ExecFn = void(__fastcall*)(void*, FFrameHead*, void*);
ExecFn oExecLeaveLobby, oExecLeaveGame;
void __fastcall hkExecLeaveLobby(void* ctx, FFrameHead* st, void* res) {
    if (gSt == St::Idle) { oExecLeaveLobby(ctx, st, res); return; }
    if (st->Code) st->Code++;
    lobby::Leave();
}
void __fastcall hkExecLeaveGame(void* ctx, FFrameHead* st, void* res) {
    if (gSt == St::Idle) { oExecLeaveGame(ctx, st, res); return; }
    if (st->Code) st->Code++;
    lobby::Leave();
}

void Hook(uintptr_t va, void* det, void** orig, const char* name) {
    if (MH_CreateHook((void*)VA(va), det, orig) != MH_OK) Log("lobby: hook %s failed", name);
}
}  // namespace

namespace lobby {
bool Active() { return gSt == St::Lobby; }
bool IsHost() { return gSt == St::Lobby && gHost; }
int MyTeam() { return gMyTeamInMatch; }
int PlayersInMatch() { return gPlayersInMatch; }
std::wstring StatusLine() {
    const wchar_t* s[] = { L"idle", L"creating", L"joining", L"lobby" };
    return std::wstring(s[(int)gSt]) + L" id=" + std::to_wstring(gId) + (gHost ? L" host" : L"");
}

std::wstring LobbyCode() {
    // The lower 32 bits identify a Steam lobby; show them in base 32 (no 0/O/1/I confusion).
    static const char* A = "23456789ABCDEFGHJKLMNPQRSTUVWXYZ";
    uint32_t v = (uint32_t)gId; std::wstring s;
    for (int i = 0; i < 7; i++) { s = (wchar_t)A[v % 32] + s; v /= 32; }
    return s;
}

void CreateAsHost() {
    if (!gB || gSt != St::Idle) return;
    if (!gB->Ready()) { ui::ShowMessage(L"Custom Game", L"Steam isn't available. Make sure Steam is running."); return; }
    gSt = St::Creating;
    ui::ShowBusy(true);
    gB->Create(1, 16, [](bool ok, uint64_t id) {
        ui::ShowBusy(false);
        if (!ok) { gSt = St::Idle; ui::ShowMessage(L"Custom Game", L"Couldn't create the lobby. Check your connection to Steam."); return; }
        Enter(id, true);
        if (Mgr()) HostSync(Mgr());
        gWantScreen = true;
    });
}

void JoinById(uint64_t id) {
    if (!gB || !id) return;
    // Invites can arrive on the title screen or during a match: join once the main menu is up.
    if (!net::MenuSettled() && !(gSt == St::Lobby && gId == id)) { gPendingJoin = id; Log("lobby: join %llu queued", (unsigned long long)id); return; }
    if (gSt == St::Lobby && gId == id) { ShowLobbyScreen(); return; }
    if (gSt == St::Lobby) Leave();
    if (gSt != St::Idle) return;
    gSt = St::Joining;
    ui::ShowBusy(true);
    gB->Join(id, [id](bool ok, int response) {
        ui::ShowBusy(false);
        if (!ok) {
            gSt = St::Idle;
            Log("lobby: join %llu failed, response %d", (unsigned long long)id, response);
            const wchar_t* why = response == 4 ? L"That game is full."
                               : response == 3 ? L"That game is invite only. Ask the host for an invite."
                               : response == 2 ? L"That game no longer exists."
                               : response == 10 || response == 11 ? L"You can't join this player's game."
                               : L"Couldn't join that game. Check your connection to Steam and try again.";
            ui::ShowMessage(L"", why);
            return;
        }
        Enter(id, gB->Owner(id) == gB->Me());
        gWantScreen = true;
    });
}

void Leave() {
    if (gSt == St::Idle) return;
    Log("lobby: leaving %llu", (unsigned long long)gId);
    if (gId) gB->Leave(gId);
    gSt = St::Idle; gId = 0; gHost = false; gInMatch = false; gWantScreen = false; gHostId = 0;
    net::CancelJoin();
    ResetManager();
    steam::ClearRichPresence();
}

void ShowScreen() { if (gSt == St::Lobby) ShowLobbyScreen(); }

void SetTeamSize(int perTeam) {
    uo::UObject* m = Mgr();
    if (!m || !gHost) return;
    Team* t = &F<Team>(m, CGM_Teams);
    t[0].Max = t[1].Max = perTeam;
    // Players beyond the new size move to the other team when it has room.
    for (auto& kv : gTeam)
        if ((kv.second == 0 || kv.second == 1) && CountTeam(kv.second) > perTeam && CountTeam(1 - kv.second) < perTeam) kv.second = 1 - kv.second;
    Log("lobby: team size %d", perTeam);
    HostSync(m);
}

// CUSTOM GAME on the main menu: friends' and public games, plus CREATE GAME.
void OpenBrowser() {
    if (!gB) return;
    if (!gB->Ready()) { ui::ShowMessage(L"", L"Steam isn't available. Make sure Steam is running."); return; }
    ui::ShowBusy(true);
    gB->Browse([](std::vector<uint64_t> ids) {
        ui::ShowBusy(false);
        std::vector<std::wstring> rows = { L"CREATE GAME" };
        std::vector<uint64_t> ok;
        for (uint64_t id : ids) {
            if (gB->Get(id, "be1v1") != BE1V1_PROTOCOL) continue;
            std::wstring name = W(gB->Get(id, "name")), map = W(gB->Get(id, "mapname"));
            long long n = ToI(gB->Get(id, "n")), max = ToI(gB->Get(id, "max"), 8);
            if (name.empty()) continue;
            std::wstring row = name;
            if (!map.empty()) row += L"   " + map;
            row += L"   " + std::to_wstring(n) + L"/" + std::to_wstring(max);
            if (gB->Get(id, "state") == "game") row += L"   IN MATCH";
            rows.push_back(row);
            ok.push_back(id);
        }
        Log("lobby: browser shows %d game(s)", (int)ok.size());
        rows.push_back(L"REFRESH");
        int refresh = (int)rows.size() - 1;
        ui::List(L"", rows, L"", L"", [ok, refresh](int c) {
            if (c == 0) CreateAsHost();
            else if (c == refresh) OpenBrowser();
            else if (c > 0 && c - 1 < (int)ok.size()) JoinById(ok[c - 1]);
        });
    });
}

// Lobby screen BACK: keep the lobby and return to the main menu (LEAVE is the way out).
bool gLeaving;
bool OnBackPressed() {
    if (gSt != St::Lobby) return false;
    if (gLeaving) { gLeaving = false; return false; }   // our LEAVE button: let the game ask "Leaving so soon?"
    gScreenHidden = true;
    Log("lobby: back to the main menu (still in the lobby)");
    return true;
}

// The lobby screen's hidden debug button becomes LEAVE.
bool OnListButton(void* btn) {
    uo::UObject* b = (uo::UObject*)btn;
    std::wstring bn = uo::Name(b);
    Log("lobby: list button %ls", bn.c_str());
    if (gSt != St::Lobby || (bn != L"Debug_FetchSessionData" && bn != L"Debug_UpdateSessionData")) return false;
    uo::UObject* scr = Screen();
    if (!scr) return false;
    gLeaving = true;
    uo::Call(scr, L"BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_55_OnLeaveGamePressed__DelegateSignature").run();
    gLeaving = false;
    return true;
}

// Team slot clicked (mouse): your own slot or an empty slot moves you; the host's click on someone moves them.
bool OnSlotPressed(void* slotPtr) {
    if (gSt != St::Lobby) return false;
    uo::UObject* slot = (uo::UObject*)slotPtr;
    int team = F<int32_t>(slot, 0x480);
    bool occupied = F<bool>(slot, 0x4a8), local = F<bool>(slot, 0x4aa);
    Log("lobby: slot pressed team=%d occupied=%d local=%d", team, occupied, local);
    uo::UObject* m = Mgr();
    if (!m) return true;
    if (!occupied) { if (team >= -1 && team <= 1) RequestTeam(team); return true; }
    uint64_t id = _wcstoui64(F<FString>(slot, 0x4b0).c_str(), nullptr, 10);
    if (local || id == gB->Me()) { int cur = gHost ? gTeam[gB->Me()] : team; RequestTeam(cur == 0 ? 1 : 0); return true; }
    if (gHost && id && gTeam.count(id)) {
        int to = gTeam[id] == 0 ? 1 : 0;
        if (CountTeam(to) < TeamMax(m, to)) { gTeam[id] = to; Log("lobby: host moved %llu to team %d", (unsigned long long)id, to); HostSync(m); }
    }
    return true;
}

void OpenInvite() {
    if (gSt != St::Lobby) return;
    Log("lobby: invite dialog");
    steam::OpenInviteOverlay(gId);
}

void OnMatchEnded() {
    if (gSt != St::Lobby) return;
    gInMatch = false;
    if (gHost) {
        uo::UObject* m = Mgr();
        if (m) {
            auto& roster = F<TArray<int32_t>>(m, CGM_MapRoster);
            if (roster.Num > 1) F<int32_t>(m, CGM_CurrentMap) = (F<int32_t>(m, CGM_CurrentMap) + 1) % roster.Num;
        }
    }
}

void Tick(float dt) {
    if (!gB) return;
    steam::Tick();
    DWORD now = GetTickCount();
    if (now - gLastSync < 250) return;
    gLastSync = now;
    gB->Tick();
    if (gBrowseDone && now > gBrowseWait) { auto f = gBrowseDone; gBrowseDone = nullptr; f(); }
    if (!gPendingJoinFromCmdline.empty()) {
        gPendingJoin = _wcstoui64(gPendingJoinFromCmdline.c_str(), nullptr, 10);
        gPendingJoinFromCmdline.clear();
    }
    bool menuReady = ui::MainMenuReady();
    if (gPendingJoin && net::MenuSettled() && (gSt == St::Idle || gSt == St::Lobby)) { uint64_t id = gPendingJoin; gPendingJoin = 0; JoinById(id); return; }
    if (gSt != St::Lobby) return;
    // The lobby screen: shown after creating/joining, and whenever the main menu comes back while a match is
    // not running (e.g. after a match). Closing it with BACK keeps the lobby.
    // (The main menu itself opens the screen as soon as it sees we're in a lobby; then there's nothing left to do.)
    if (gWantScreen && Screen()) gWantScreen = false;
    if (gWantScreen && menuReady) { gWantScreen = false; ShowLobbyScreen(); }
    DecorateScreen();
    // Ownership can move (Steam picks a new owner when the host leaves): the lobby carries on with the new owner.
    // Members who were playing on the old host's server go back to the menu.
    uint64_t owner = gB->Owner(gId);
    if (!gHost && gHostId && owner && owner != gHostId) {
        Log("lobby: host left");
        if (net::InNetGame() || net::Joining()) {
            net::Travel(L"/Game/Levels/FrontEnd/Map_FrontEnd_3D");
            gInMatch = false;
            gPendingMessage = L"The host left the game.";
        }
        gHostId = owner;
    }
    if (!gHostId) gHostId = owner;
    if (!gPendingMessage.empty() && menuReady) { ui::ShowMessage(L"", gPendingMessage); gPendingMessage.clear(); gWantScreen = true; }
    bool host = owner == gB->Me();
    if (host != gHost) {
        Log("lobby: host role %d -> %d", gHost, host);
        gHost = host;
        if (uo::UObject* m = Mgr()) { F<bool>(m, CGM_IsLeader) = host; if (host) gLastPublished.clear(); }
        if (host) { gSeq = ToI(gB->Get(gId, "seq")); gSeenSeq = gSeq; }
    }
    bool inMenu = net::MenuSettled();
    if (gInMatch && inMenu && !net::Joining()) {
        static DWORD backSince; if (!backSince) backSince = now;
        if (now - backSince > 3000) { backSince = 0; Log("lobby: back in the menu"); OnMatchEnded(); gWantScreen = true; }
    }
    if (inMenu && now < gSlotFixUntil) FixSlotVisibility();
    uo::UObject* m = Mgr();
    if (!m) return;
    if (gHost) { if (inMenu || gInMatch) HostSync(m); return; }

    MemberSync(m);
    long long seq = ToI(gB->Get(gId, "seq"));
    std::string teams = gB->Get(gId, "teams");
    std::string me = I((long long)gB->Me()) + ":";
    size_t p = teams.find(me);
    // Join a running match once the host has given us a team (it does within a second of us joining the lobby).
    if (gB->Get(gId, "state") == "game" && seq != gSeenSeq && inMenu && p != std::string::npos) {
        gSeenSeq = seq;
        gMyTeamInMatch = p == std::string::npos ? 0 : (int)ToI(teams.substr(p + me.size()));
        gInMatch = true;
        std::wstring addr = W(gB->Get(gId, "addr"));
        Log("lobby: match #%lld started, joining %ls as %s %d", seq, addr.c_str(), gMyTeamInMatch < 0 ? "spectator" : "team", gMyTeamInMatch);
        net::JoinHost(addr + NameOption() + L"?BETeam=" + std::to_wstring(gMyTeamInMatch));
    }
    if (gB->Get(gId, "state") == "lobby" && gInMatch && inMenu) gInMatch = false;
}

void Install() {
    std::wstring cmd = GetCommandLineW();
    if (cmd.find(L"-be1v1devlobby") != std::wstring::npos) { gB.reset(new DevBackend()); Log("lobby: dev backend"); }
    else gB.reset(new SteamBackend());
    size_t p = cmd.find(L"+connect_lobby");
    if (p != std::wstring::npos) {
        size_t s = cmd.find_first_of(L"0123456789", p);
        if (s != std::wstring::npos) gPendingJoinFromCmdline = cmd.substr(s, cmd.find_first_not_of(L"0123456789", s) - s);
        Log("lobby: will join %ls from the command line", gPendingJoinFromCmdline.c_str());
    }
    steam::OnJoinRequested([](uint64_t id) { JoinById(id); });
    Hook(A_IsInLobby, (void*)&hkIsInLobbyImpl, (void**)&oIsInLobby, "IsInLobby");
    Hook(A_IsLeader, (void*)&hkIsLeaderImpl, (void**)&oIsLeader, "IsLeader");
    Hook(A_CustomStart, (void*)&hkCustomStart, (void**)&oCustomStart, "CustomStart");
    Hook(A_SetPlayerTeam, (void*)&hkSetPlayerTeam, (void**)&oSetPlayerTeam, "SetPlayerTeam");
    Hook(A_SetLocalTeam, (void*)&hkSetLocalTeam, (void**)&oSetLocalTeam, "SetLocalTeam");
    Hook(A_CanStart, (void*)&hkCanStart, (void**)&oCanStart, "CanStart");
    Hook(A_TryStart, (void*)&hkTryStart, (void**)&oTryStart, "TryStart");
    Hook(A_InviteFriend, (void*)&hkInvite, (void**)&oInvite, "InviteFriend");
    Hook(A_GetLocalTeam, (void*)&hkGetLocalTeam, (void**)&oGetLocalTeam, "GetLocalTeam");
    Hook(A_RequestTeam, (void*)&hkRequestTeam, (void**)&oRequestTeam, "RequestTeam");
    Hook(A_ExecLeaveLobby, (void*)&hkExecLeaveLobby, (void**)&oExecLeaveLobby, "LeaveLobby");
    Hook(A_ExecLeaveGame, (void*)&hkExecLeaveGame, (void**)&oExecLeaveGame, "LeaveGame");
    Hook(A_GetMapList, (void*)&hkGetMapList, (void**)&oGetMapList, "GetMapList");
    Log("lobby: hooks installed");
}
}  // namespace lobby

// Developer shortcuts from the dev command channel.
void LobbyDevCommand(const char* cmd) {
    unsigned long long id = 0; int t = 0;
    if (!strcmp(cmd, "create")) lobby::CreateAsHost();
    else if (!strcmp(cmd, "leave")) lobby::Leave();
    else if (sscanf(cmd, "join %llu", &id) == 1) lobby::JoinById(id);
    else if (!strcmp(cmd, "start")) { if (uo::UObject* m = Mgr()) hkCustomStart(m); }
    else if (sscanf(cmd, "team %d", &t) == 1) RequestTeam(t);
    else if (!strcmp(cmd, "status")) Log("lobby: %ls", lobby::StatusLine().c_str());
    else if (!strcmp(cmd, "tomenu")) net::Travel(L"/Game/Levels/FrontEnd/Map_FrontEnd_3D");
}
