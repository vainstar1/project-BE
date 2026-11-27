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
constexpr size_t Menu_Manager = 0x4a8, Menu_LocalTeam = 0x4c0, Menu_LocalTeamSet = 0x4c4, Menu_NumQueueSlots = 0x458;
// MBFECustomGameTeamSlotButton fields
constexpr size_t Slot_TeamId = 0x480, Slot_Name = 0x488, Slot_Occupied = 0x4a8, Slot_IsLocal = 0x4aa, Slot_NetId = 0x4b0;
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
        // Several friends in one lobby report the same lobby id: list each lobby once.
        auto friends = std::make_shared<std::vector<uint64_t>>();
        for (auto& f : steam::Friends())
            if (f.inGame && f.lobby && std::find(friends->begin(), friends->end(), f.lobby) == friends->end()) {
                friends->push_back(f.lobby);
                steam::RequestLobbyData(f.lobby);
            }
        steam::RequestLobbyList({ { "be1v1", BE1V1_PROTOCOL } }, [friends, done](std::vector<uint64_t> pub) {
            std::vector<uint64_t> all = *friends;
            for (uint64_t l : pub) if (std::find(all.begin(), all.end(), l) == all.end()) all.push_back(l);
            done(all);
            // Friends' lobby data arrives asynchronously: report again once it had a moment.
            gBrowseWait = GetTickCount() + 1500;
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
            if (n - t < 300000000ull) r.push_back(_wcstoui64(fd.cFileName + 2, nullptr, 10));   // seen in the last 30 s (loading a map stalls the game thread)
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
std::wstring MapPath(int idx);
std::wstring ModeName(int idx) {
    if (idx == kDojoIdx) return L"Training";
    if (idx == kPlaygroundIdx) return L"Playground";
    return wcsstr(MapPath(idx).c_str(), L"GameMode_Seeds") ? L"Power Collection" : L"Objective Control";
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

// The member shown in a team slot. The slot's NetId is the string of the member's online id object, which our
// members don't have, so the slot is matched by the shown name (and team) against the member list.
uint64_t SlotMember(uo::UObject* slot) {
    uint64_t id = _wcstoui64(F<FString>(slot, Slot_NetId).c_str(), nullptr, 10);
    if (id) return id;
    uo::UObject* m = Mgr();
    if (!m || !F<bool>(slot, Slot_Occupied)) return 0;
    const wchar_t* name = F<FString>(slot, Slot_Name).c_str();
    int team = F<int32_t>(slot, Slot_TeamId);
    auto& list = F<TArray<Member>>(m, CGM_MemberList);
    for (int pass = 0; pass < 2; pass++)
        for (int i = 0; i < list.Num; i++)
            if (!wcscmp(list.Data[i].Nickname.c_str(), name) && (pass == 1 || list.Data[i].TeamId == team))
                return _wcstoui64(list.Data[i].NetId.c_str(), nullptr, 10);
    return 0;
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
    // The screen was built for the official queue: "team max - NumQueueSlots" real team slots and 4 queue slots per
    // team, which shows no empty places at all. Without queue slots every place is a real (clickable) team slot.
    if (menu) F<int32_t>(menu, Menu_NumQueueSlots) = 0;
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

// Teams in this lobby (2-4, the host's "Teams" setting) and their size (the same for every team).
int NumTeams() { return std::max(2, std::min(4, rules::Current().teams)); }
bool ValidTeam(int t) { return t >= -1 && t < NumTeams(); }
int TeamMax(uo::UObject* m, int t) { return t < 0 ? F<Team>(m, CGM_Spectators).Max : t < NumTeams() ? (&F<Team>(m, CGM_Teams))[0].Max : 0; }

int CountTeam(int t) { int n = 0; for (auto& kv : gTeam) if (kv.second == t) n++; return n; }
int CountPlayers() { int n = 0; for (auto& kv : gTeam) if (kv.second >= 0) n++; return n; }
// New members go to the smallest team with room (the first of equals); when every team is full they watch.
int AutoTeam(uo::UObject* m) {
    int best = -1;
    for (int t = 0; t < NumTeams(); t++)
        if (CountTeam(t) < TeamMax(m, t) && (best < 0 || CountTeam(t) < CountTeam(best))) best = t;
    return best;
}
// Players on teams that no longer exist, or beyond a team's size, move to a team with room (else they watch).
void FitTeams(uo::UObject* m) {
    for (auto& kv : gTeam) {
        int t = kv.second;
        if (t < 0) continue;
        if (t < NumTeams() && CountTeam(t) <= TeamMax(m, t)) continue;
        kv.second = -2;
        kv.second = AutoTeam(m);
    }
}

// ---- host side ----------------------------------------------------------------------------------------------
void HostSync(uo::UObject* m) {
    std::vector<uint64_t> members = gB->Members(gId);
    std::set<uint64_t> present(members.begin(), members.end());
    for (auto it = gTeam.begin(); it != gTeam.end();) it = present.count(it->first) ? std::next(it) : gTeam.erase(it);
    for (uint64_t id : members) {
        // Team-change requests from members: "want" = "<team>:<counter>". A member who (re)appears gets the team
        // they asked for last, if it has room; otherwise the smaller team, or spectating when both are full.
        std::string want = gB->GetMember(gId, id, "want");
        size_t c = want.find(':');
        bool isNew = !gTeam.count(id);
        if (isNew) gTeam[id] = -2;   // not counted while we pick
        if (c != std::string::npos) {
            long long n = ToI(want.substr(c + 1));
            if (n > gReqSeen[id] || isNew) {
                gReqSeen[id] = std::max(n, gReqSeen[id]);
                int t = (int)ToI(want.substr(0, c));
                if ((!F<bool>(m, CGM_TeamsLocked) || isNew) && ValidTeam(t) && gTeam[id] != t && CountTeam(t) < TeamMax(m, t)) {
                    gTeam[id] = t;
                    Log("lobby: %llu -> team %d (asked)", (unsigned long long)id, t);
                }
            }
        }
        if (gTeam[id] == -2) gTeam[id] = AutoTeam(m);
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
        { "max", I(NumTeams() * (&F<Team>(m, CGM_Teams))[0].Max) },
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

// ---- lobby screen decoration ---------------------------------------------------------------------------------
uo::UObject* ScreenWidget(uo::UObject* scr, const wchar_t* cls, const wchar_t* name) {
    FName want = uo::MakeName(name);
    for (uo::UObject* w : uo::FindAll(uo::FindClass(cls))) {
        if (!uo::NameIs(w, want)) continue;
        for (uo::UObject* o = uo::OuterOf(w); o; o = uo::OuterOf(o)) if (o == scr) return w;
    }
    return nullptr;
}
// A named widget inside a user widget: its Blueprint variable, else a search of its widget tree (cached).
uo::UObject* Named(uo::UObject* userWidget, const wchar_t* name) {
    if (!userWidget) return nullptr;
    int off = uo::PropOffset(uo::ClassOf(userWidget), name);
    if (off >= 0) return F<uo::UObject*>(userWidget, off);
    // The engine's own lookup in the widget's tree (searching all widgets instead froze the lobby screen in v2.3.0).
    uo::Call c(userWidget, L"GetWidgetFromName");
    if (!c.ok()) return nullptr;
    return c.set<FName>(L"Name", uo::MakeName(name)).run().get<uo::UObject*>(L"ReturnValue");
}
uo::UObject* SlotOf(uo::UObject* w) {
    static int off = -2;
    if (off == -2) off = uo::PropOffset(uo::FindClass(L"Widget"), L"Slot");
    return w && off >= 0 ? F<uo::UObject*>(w, off) : nullptr;
}
// Layout of a panel slot (padding, size, alignment), kept by value so it survives removing the widget.
struct SlotLayout {
    uint8_t padding[16] = {}, size[8] = {}, ha = 0, va = 0;
    bool hasPad = false, hasSize = false, hasHa = false, hasVa = false;
    void Read(uo::UObject* slot) {
        if (!slot) return;
        uo::UObject* sc = uo::ClassOf(slot);
        int o;
        if ((o = uo::PropOffset(sc, L"Padding")) >= 0) { memcpy(padding, slot + o, 16); hasPad = true; }
        if ((o = uo::PropOffset(sc, L"Size")) >= 0) { memcpy(size, slot + o, 8); hasSize = true; }
        if ((o = uo::PropOffset(sc, L"HorizontalAlignment")) >= 0) { ha = slot[o]; hasHa = true; }
        if ((o = uo::PropOffset(sc, L"VerticalAlignment")) >= 0) { va = slot[o]; hasVa = true; }
    }
    void Apply(uo::UObject* slot) const {
        if (!slot) return;
        auto raw = [&](const wchar_t* fn, const wchar_t* arg, const void* v, size_t n) {
            uo::Call c(slot, fn); int a = c.off(arg);
            if (c.ok() && a >= 0) { memcpy(c.buf.data() + a, v, n); c.run(); }
        };
        if (hasPad) raw(L"SetPadding", L"InPadding", padding, 16);
        if (hasSize) raw(L"SetSize", L"InSize", size, 8);
        if (hasHa) raw(L"SetHorizontalAlignment", L"InHorizontalAlignment", &ha, 1);
        if (hasVa) raw(L"SetVerticalAlignment", L"InVerticalAlignment", &va, 1);
    }
};
uo::UObject* AddTo(uo::UObject* panel, uo::UObject* w, const SlotLayout* layout) {
    uo::Call add(panel, L"AddChild");
    uo::UObject* slot = add.set<uo::UObject*>(L"Content", w).run().get<uo::UObject*>(L"ReturnValue");
    if (layout) layout->Apply(slot);
    return slot;
}
// A new side-menu button styled exactly like `like` (the game's PromptListButtonTemplate, as INVITE).
uo::UObject* MakeMenuButton(uo::UObject* like, const wchar_t* text) {
    uo::UObject* lib = uo::FindFirst(uo::FindClass(L"WidgetBlueprintLibrary"), true);
    uo::UObject* cls = uo::ClassOf(like);
    if (!lib || !cls) return nullptr;
    uo::Call c(lib, L"Create");
    c.set<uo::UObject*>(L"WorldContextObject", (uo::UObject*)net::World()).set<uo::UObject*>(L"WidgetType", cls).set<uo::UObject*>(L"OwningPlayer", nullptr).run();
    uo::UObject* w = c.get<uo::UObject*>(L"ReturnValue");
    if (!w) return nullptr;
    // Plain style fields (colours, sizes, textures, alignment) as designed for INVITE; read when it is constructed.
    const std::pair<size_t, size_t> ranges[] = { { 0x558, 0x6c8 }, { 0x6d8, 0x6dc }, { 0x75c, 0x764 }, { 0x76c, 0x77c } };
    for (auto& r : ranges) memcpy(w + r.first, like + r.first, r.second - r.first);
    uo::MakeText((uo::FText*)(w + 0x4e0), text);
    return w;
}
uo::UObject* gLeaveBtn[2];          // LEAVE in the host's and the members' button column
uo::UObject* gJoinBtn;              // members: JOIN MATCH while a match runs without them
uo::UObject* gInfoText;             // the line under the game name
bool Animating(uo::UObject* w) {
    uo::Call c(w, L"IsAnyAnimationPlaying");
    return w && c.ok() && c.run().get<bool>(L"ReturnValue");
}
// ---- teams 3 and 4 on the lobby screen ------------------------------------------------------------------------
// The menu builds its team columns from TeamOrder (0, 1, -1) and one slot container per entry. Teams 2 and 3 get
// their own containers below the columns of teams 0 and 1 (a 2x2 grid: blue and red on top, yellow and green below),
// so the game's own slot builder fills them with real team slots. Their size comes from the hooked team-size lookup
// (0 when the lobby has fewer teams, which leaves the containers empty).
constexpr size_t Menu_TeamOrder = 0x448, Menu_Containers = 0x480, Menu_QueuedContainers = 0x490, Menu_SlotLists = 0x4b0;
constexpr uintptr_t A_StaticConstructObject = 0x1416aac50;
constexpr uintptr_t A_GetTeamMaxPlayers = 0x141100bb0;   // int UMBCustomGameManager::GetTeamMaxPlayers(int TeamId)
using IntTeamFn = int(__fastcall*)(void*, int);
IntTeamFn oGetTeamMaxPlayers;
int __fastcall hkGetTeamMaxPlayers(void* mgr, int team) {
    if (gSt == St::Lobby && team >= 2) return team < NumTeams() ? (&F<Team>((uo::UObject*)mgr, CGM_Teams))[0].Max : 0;
    return oGetTeamMaxPlayers(mgr, team);
}
// The members of one team (the menu fills each team's slots from it); the game's version only knows teams -1, 0, 1.
constexpr uintptr_t A_GetTeamMembers = 0x141100be0;   // TArray<FMBCustomGameMember>* (Mgr*, TArray* Out, int TeamId)
constexpr uintptr_t A_MembersGrow = 0x140356770, A_MemberCopy = 0x140fb8980;
using TeamMembersFn = TArray<Member>*(__fastcall*)(void*, TArray<Member>*, int);
TeamMembersFn oGetTeamMembers;
TArray<Member>* __fastcall hkGetTeamMembers(void* mgr, TArray<Member>* out, int team) {
    if (gSt != St::Lobby || team < 2) return oGetTeamMembers(mgr, out, team);
    out->Data = nullptr; out->Num = out->Max = 0;
    auto& list = F<TArray<Member>>((uo::UObject*)mgr, CGM_MemberList);
    for (int i = 0; i < list.Num; i++) {
        if (list.Data[i].TeamId != team) continue;
        int n = out->Num++;
        if (out->Num > out->Max) Fn<void(__fastcall*)(void*, int)>(A_MembersGrow)(out, n);
        Fn<void(__fastcall*)(void*, void*)>(A_MemberCopy)(&out->Data[n], &list.Data[i]);
    }
    return out;
}
uo::UObject* NewWidget(const wchar_t* cls, uo::UObject* outer, const wchar_t* name) {
    uo::UObject* c = uo::FindClass(cls);
    if (!c || !outer) return nullptr;
    using SCO = uo::UObject*(__fastcall*)(uo::UObject*, uo::UObject*, FName, uint32_t, uint32_t, uo::UObject*, bool, void*, bool);
    return Fn<SCO>(A_StaticConstructObject)(c, outer, uo::MakeName(name), 0, 0, nullptr, false, nullptr, false);
}
template <class T> void Append(TArray<T>& a, const T& v) {
    if (a.Num >= a.Max) {
        int max = a.Max ? a.Max * 2 : 4;
        T* d = (T*)uo::Malloc(sizeof(T) * max);
        memset((void*)d, 0, sizeof(T) * max);
        if (a.Num) memcpy((void*)d, (void*)a.Data, sizeof(T) * a.Num);
        a.Data = d; a.Max = max;
    }
    a.Data[a.Num++] = v;
}
struct SlotList { uint8_t raw[0x20]; };
uo::UObject* gExtraBox[4];          // containers of teams 2 and 3 (index = team)
uo::UObject* gExtraMenu;            // the menu they were added to
void AddTeamColumns(uo::UObject* menu) {
    if (!menu || menu == gExtraMenu) return;
    auto& order = F<TArray<int32_t>>(menu, Menu_TeamOrder);
    auto& boxes = F<TArray<uo::UObject*>>(menu, Menu_Containers);
    auto& queued = F<TArray<uo::UObject*>>(menu, Menu_QueuedContainers);
    auto& lists = F<TArray<SlotList>>(menu, Menu_SlotLists);
    for (int i = 0; i < order.Num; i++) if (order.Data[i] >= 2) { gExtraMenu = menu; return; }   // already there
    if (order.Num != 3 || boxes.Num != 3 || queued.Num != 3 || lists.Num != 3) {
        Log("lobby: unexpected team layout (%d %d %d %d)", order.Num, boxes.Num, queued.Num, lists.Num);
        gExtraMenu = menu;
        return;
    }
    for (int team = 2; team <= 3; team++) {
        uo::UObject* under = boxes.Data[team - 2];          // the slot container of team 0 / team 1
        uo::Call par(under, L"GetParent");
        uo::UObject* column = par.ok() ? par.run().get<uo::UObject*>(L"ReturnValue") : nullptr;
        uo::UObject* tree = uo::OuterOf(under);
        uo::UObject* box = NewWidget(L"VerticalBox", tree, team == 2 ? L"VerticalBox_Team3Slots" : L"VerticalBox_Team4Slots");
        uo::UObject* dummy = NewWidget(L"VerticalBox", tree, team == 2 ? L"VerticalBox_Team3Queue" : L"VerticalBox_Team4Queue");
        if (!column || !box || !dummy) { Log("lobby: couldn't add the columns of team %d", team + 1); gExtraMenu = menu; return; }
        // A gap between the two teams of a column, the size of one slot's padding.
        SlotLayout gap; gap.Read(SlotOf(under));
        gap.hasPad = true; float pad[4] = { 0, 24, 0, 0 }; memcpy(gap.padding, pad, 16);
        AddTo(column, box, &gap);
        Append(order, (int32_t)team);
        Append(boxes, box);
        Append(queued, dummy);
        Append(lists, SlotList{});
        gExtraBox[team] = box;
    }
    gExtraMenu = menu;
    Log("lobby: team columns 3 and 4 added");
    uo::Call(menu, L"RefreshTeamSlotButtons").run();
    uo::Call(menu, L"NativeOnSessionUpdated").run();
}

void DecorateScreen() {
    uo::UObject* scr = Screen();
    if (!scr) return;
    // Real team slots right away (the field only matters when slots are rebuilt).
    uo::UObject* menu = Menu();
    if (menu && F<int32_t>(menu, Menu_NumQueueSlots) != 0) {
        F<int32_t>(menu, Menu_NumQueueSlots) = 0;
        uo::Call(menu, L"RefreshTeamSlotButtons").run();
        uo::Call(menu, L"NativeOnSessionUpdated").run();
    }
    AddTeamColumns(menu);
    if (scr == gDecorated) return;
    // Moving buttons while the screen slides in freezes its intro animation half-way (the side columns then sit
    // off their places): wait until it has finished.
    if (Animating(scr) || (menu && Animating(menu))) return;
    uo::UObject* invite = ScreenWidget(scr, L"PromptListButtonTemplate_C", L"Button_Invite");
    uo::UObject* start = ScreenWidget(scr, L"PromptListButtonTemplate_C", L"Button_Start");
    uo::UObject* hostView = ScreenWidget(scr, L"VerticalBox", L"HostView");
    uo::UObject* clientView = ScreenWidget(scr, L"VerticalBox", L"ClientView");
    gInfoText = ScreenWidget(scr, L"TextBlock", L"BasicGameInfo");
    // Widgets of a screen that was just created show up in searches within a second: try again next tick.
    if (!invite || !start || !hostView || !clientView || !gInfoText) return;
    gDecorated = scr;
    SlotLayout inviteLayout, startLayout;
    inviteLayout.Read(SlotOf(invite));
    startLayout.Read(SlotOf(start));
    // Host: SETTINGS, MAPS, INVITE, LEAVE, then START. Members: the map list, then LEAVE.
    for (auto& b : gLeaveBtn) if (b && uo::IsLive(b)) uo::Call(b, L"RemoveFromParent").run();
    if (gJoinBtn && uo::IsLive(gJoinBtn)) uo::Call(gJoinBtn, L"RemoveFromParent").run();
    gLeaveBtn[0] = MakeMenuButton(invite, L"LEAVE");
    gLeaveBtn[1] = MakeMenuButton(invite, L"LEAVE");
    gJoinBtn = MakeMenuButton(invite, L"JOIN MATCH");
    if (gJoinBtn) { AddTo(clientView, gJoinBtn, &inviteLayout); uo::Call(gJoinBtn, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run(); }
    if (gLeaveBtn[0]) {
        uo::Call(start, L"RemoveFromParent").run();
        AddTo(hostView, gLeaveBtn[0], &inviteLayout);
        AddTo(hostView, start, &startLayout);
    }
    if (gLeaveBtn[1]) AddTo(clientView, gLeaveBtn[1], &inviteLayout);
    // The LEAVE of earlier versions (moved debug buttons) stays hidden.
    for (const wchar_t* n : { L"Debug_FetchSessionData", L"Debug_UpdateSessionData" })
        if (uo::UObject* b = ScreenWidget(scr, L"PromptListButtonTemplate_C", n)) uo::Call(b, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    Log("lobby: screen decorated");
}

int LocalTeamInLobby() {
    uo::UObject* m = Mgr();
    if (!m) return 0;
    auto& list = F<TArray<Member>>(m, CGM_MemberList);
    for (int i = 0; i < list.Num; i++) if (list.Data[i].bLocal) return list.Data[i].TeamId;
    return 0;
}
void SetTextIfDifferent(uo::UObject* tb, const std::wstring& text) {
    static int textOff = -2;
    if (textOff == -2) textOff = uo::PropOffset(uo::FindClass(L"TextBlock"), L"Text");
    if (!tb || textOff < 0) return;
    if (ui::TextToString(tb + textOff) == text) return;
    uo::FText t; uo::MakeText(&t, text.c_str());
    uo::Call(tb, L"SetText").set(L"InText", t).run();
}
std::wstring Upper(std::wstring s) { for (auto& c : s) c = towupper(c); return s; }
// Empty places say what clicking them does ("Join" / "Spectate"); the line under the game name says what will be
// played. Runs a few times a second while the screen is up (the Blueprint rewrites its texts on every update).
void LabelScreen() {
    static bool wasUp, focusDone;
    uo::UObject* scr = Screen();
    if (!scr) { wasUp = false; return; }
    if (!wasUp) { wasUp = true; focusDone = false; }
    int mine = LocalTeamInLobby();
    // Members can't rename the game or the teams: no pencils, and keyboard/controller focus starts on their own place
    // (left/right or LT/RT then switch teams) instead of inside the game name.
    if (!gHost) {
        for (uo::UObject* e : uo::FindAllTransient(uo::FindClass(L"FE_EditButton_C"))) {
            bool inside = false;
            for (uo::UObject* o = uo::OuterOf(e); o && !inside; o = uo::OuterOf(o)) inside = o == scr;
            if (!inside) continue;
            uo::Call v(e, L"GetVisibility");
            if (v.ok() && v.run().get<uint8_t>(L"ReturnValue") != 1) uo::Call(e, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
        }
        // A match is running without us (we came back to the menu, or lost the connection): offer to drop back in.
        if (gJoinBtn && uo::IsLive(gJoinBtn)) {
            bool show = gB->Get(gId, "state") == "game" && !gInMatch && !net::Joining();
            uo::Call v(gJoinBtn, L"GetVisibility");
            uint8_t want = show ? 0 : 1;
            if (v.ok() && v.run().get<uint8_t>(L"ReturnValue") != want) uo::Call(gJoinBtn, L"SetVisibility").set<uint8_t>(L"InVisibility", want).run();
        }
        if (!focusDone)
            for (uo::UObject* sl : uo::FindAllTransient(uo::FindClass(L"MBFECustomGameTeamSlotButton"))) {
                if (!F<bool>(sl, Slot_IsLocal)) continue;
                uo::Call par(sl, L"GetParent");
                if (!par.ok() || !par.run().get<uo::UObject*>(L"ReturnValue")) continue;
                if (uo::UObject* b = Named(sl, L"TheButton")) { uo::Call(b, L"SetKeyboardFocus").run(); focusDone = true; Log("lobby: focus on my place"); }
                break;
            }
    }
    static uo::UObject* queueCls;
    if (!queueCls || !uo::IsLive(queueCls)) queueCls = uo::FindClass(L"CustomGame_PlayerSlot_Queue_C");
    for (uo::UObject* s : uo::FindAllTransient(uo::FindClass(L"MBFECustomGameTeamSlotButton"))) {
        // The official queue's slots (never shown in custom games) have none of the texts or pictures below:
        // looking for them searched every widget, for every slot, on every refresh.
        if (queueCls && uo::ClassOf(s) == queueCls) continue;
        // Occupied places show the player's Steam profile picture (the game asked Xbox Live, which is gone).
        if (F<bool>(s, Slot_Occupied)) {
            // (team slots only: the hidden queue slots have no picture)
            static int iconOff = -2, icon1Off = -2;
            static uo::UObject* teamSlotCls;
            if (!teamSlotCls || !uo::IsLive(teamSlotCls)) {
                teamSlotCls = uo::FindClass(L"CustomGame_PlayerSlot_Team_C");
                iconOff = teamSlotCls ? uo::PropOffset(teamSlotCls, L"Icon") : -1;
                icon1Off = teamSlotCls ? uo::PropOffset(teamSlotCls, L"Icon1") : -1;
            }
            if (!teamSlotCls || uo::ClassOf(s) != teamSlotCls || iconOff < 0) continue;
            uint64_t id = SlotMember(s);
            if (uo::UObject* tex = id ? avatars::Texture(id) : nullptr) {
                avatars::Show(F<uo::UObject*>(s, iconOff), tex);
                if (icon1Off >= 0) avatars::Show(F<uo::UObject*>(s, icon1Off), tex);
            }
            continue;
        }
        uo::Call par(s, L"GetParent");
        if (!par.ok() || !par.run().get<uo::UObject*>(L"ReturnValue")) continue;
        int team = F<int32_t>(s, Slot_TeamId);
        bool spec = team < 0;
        // Your own team's empty places: the host invites friends into them (the game's invite icon), members see "Open".
        std::wstring label = team == mine ? (gHost ? L"Invite" : L"Open") : spec ? L"+ Spectate" : L"Join";
        const wchar_t* specNames[] = { L"TextBlock_0", L"TextBlock_4" };
        const wchar_t* teamNames[] = { L"PlayerName1", L"NameText" };
        for (const wchar_t* n : spec ? specNames : teamNames) SetTextIfDifferent(Named(s, n), label);
    }
    if (gInfoText && uo::IsLive(gInfoText)) {
        uo::UObject* m = Mgr();
        if (!m) return;
        auto& roster = F<TArray<int32_t>>(m, CGM_MapRoster);
        int idx = roster.Num ? roster.Data[F<int32_t>(m, CGM_CurrentMap) % roster.Num] : 0;
        int size = (&F<Team>(m, CGM_Teams))[0].Max;
        const wchar_t* priv[] = { L"Public", L"Friends only", L"Invite only" };
        int p = F<uint8_t>(m, CGM_Privacy);
        // Two short lines: a wider line under the title pushes the side columns outward.
        if (NumTeams() > 2 && idx >= 7 && idx <= 13) idx -= 7;   // 3-4 teams play the arena's Objective Control version
        std::wstring mode = rules::Current().koOnly && !IsTrainingMap(idx) ? L"Team Brawl" : ModeName(idx);
        auto sizes = rules::TeamSizeLabels(NumTeams());
        std::wstring info = MapName(idx) + L" / " + mode + L"\n" + (size >= 1 && size <= 4 ? sizes[size - 1] : L"");
        if (roster.Num > 1) info += L" / " + std::to_wstring(roster.Num) + L" maps";
        info += std::wstring(L" / ") + (p >= 0 && p < 3 ? priv[p] : L"");
        SetTextIfDifferent(gInfoText, Upper(info));
    }
}

// ---- loading screen ---------------------------------------------------------------------------------------------
// In custom games the loading screen lists the lobby's members: team 0 on one side, team 1 on the other, the local
// player's team on the left. With 3-4 teams it shows "your team" against everyone else (grouped by team), and every
// name plate gets the player's Steam picture (the game asked Xbox Live).
constexpr uintptr_t A_LoadingFromLobby = 0x141086330;   // void UMBLoadingScreenManager::(build runtime data from the lobby)
constexpr uintptr_t A_LoadingSetData = 0x141084af0;     // void UMBLoadingScreenWidget::(set runtime data)(Widget*, Data*)
constexpr size_t LSM_Widget = 0x90, LSM_Team0 = 0x180, LSM_Team1 = 0x190, LSPI_Size = 0x40, LSPI_Name = 0x0, LSPI_Avatar = 0x10;
using LoadingFn = void(__fastcall*)(uint8_t*);
LoadingFn oLoadingFromLobby;
uint64_t MemberIdByName(const wchar_t* name) {
    uo::UObject* m = Mgr();
    if (!m) return 0;
    auto& list = F<TArray<Member>>(m, CGM_MemberList);
    for (int i = 0; i < list.Num; i++) if (!wcscmp(list.Data[i].Nickname.c_str(), name)) return _wcstoui64(list.Data[i].NetId.c_str(), nullptr, 10);
    return 0;
}
void __fastcall hkLoadingFromLobby(uint8_t* lsm) {
    uo::UObject* m = Mgr();
    if (gSt != St::Lobby || !m) { oLoadingFromLobby(lsm); return; }
    auto& list = F<TArray<Member>>(m, CGM_MemberList);
    std::vector<Member> keep(list.Data, list.Data + list.Num);
    if (NumTeams() > 2) {
        int mine = LocalTeamInLobby();
        std::vector<Member> view = keep;
        std::stable_sort(view.begin(), view.end(), [&](const Member& a, const Member& b) {
            auto key = [&](const Member& x) { return x.TeamId < 0 ? 99 : x.TeamId == mine ? -1 : x.TeamId; };
            return key(a) < key(b);
        });
        for (auto& v : view) if (v.TeamId >= 0) v.TeamId = v.TeamId == mine ? 0 : 1;
        memcpy((void*)list.Data, (void*)view.data(), sizeof(Member) * view.size());
    }
    oLoadingFromLobby(lsm);
    memcpy((void*)list.Data, (void*)keep.data(), sizeof(Member) * keep.size());
    int shown = 0;
    for (size_t side : { LSM_Team0, LSM_Team1 }) {
        auto& arr = F<TArray<uint8_t>>(lsm, side);
        for (int i = 0; i < arr.Num; i++) {
            uint8_t* e = arr.Data + (size_t)i * LSPI_Size;
            uint64_t id = MemberIdByName(F<FString>(e, LSPI_Name).c_str());
            uo::UObject* tex = id ? avatars::Texture(id) : nullptr;
            if (tex) { F<uo::UObject*>(e, LSPI_Avatar) = tex; shown++; }
        }
    }
    if (uint8_t* w = F<uint8_t*>(lsm, LSM_Widget)) Fn<void(__fastcall*)(void*, void*)>(A_LoadingSetData)(w, lsm + LSM_Team0);
    ui::ResolveInMatch();   // the loading screen's Blueprint events (its class is loaded by now)
    teams::Relabel(F<uint8_t*>(lsm, LSM_Widget));
    Log("lobby: loading screen lists %d + %d players (%d Steam pictures)", F<TArray<uint8_t>>(lsm, LSM_Team0).Num, F<TArray<uint8_t>>(lsm, LSM_Team1).Num, shown);
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
    // 3-4 teams play Objective Control (Power Collection's cells exist for two teams only): a Power Collection pick
    // plays the same arena's Objective Control version. Knockouts Only scoring also runs on Objective Control rules.
    if ((teams::Active() || teams::KoOnly()) && idx >= 7 && idx <= 13) idx -= 7;
    gPlayersInMatch = CountPlayers();
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
    if (!ValidTeam(team) || CountTeam(team) >= TeamMax(m, team)) return false;
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
    if (CountPlayers() < 1) return false;
    for (int t = 0; t < NumTeams(); t++) if (CountTeam(t) > TeamMax(m, t)) return false;
    return true;
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
        if (ValidTeam(team) && gTeam[me] != team && CountTeam(team) < TeamMax(m, team)) gTeam[me] = team;
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
int gForceTeam = -99;   // dev override
int MyTeam() { return gForceTeam != -99 ? gForceTeam : gMyTeamInMatch; }
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
    // Players beyond the new size (or on a team that was removed) move to a team with room.
    FitTeams(m);
    Log("lobby: %d teams of %d", NumTeams(), perTeam);
    HostSync(m);
}

int NextTeamWithRoom(uo::UObject* m, int from);
int SpectatorPlaces() { uo::UObject* m = Mgr(); return m ? F<Team>(m, CGM_Spectators).Max : 0; }
void SetSpectatorPlaces(int n) {
    uo::UObject* m = Mgr();
    if (!m || !gHost || n < 0 || n > 8) return;
    F<Team>(m, CGM_Spectators).Max = n;
    // Spectators beyond the new number go to a team with room (or stay, if there is none).
    for (auto& kv : gTeam)
        if (kv.second == -1 && CountTeam(-1) > n) { int t = NextTeamWithRoom(m, -1); if (t != -1) kv.second = t; }
    Log("lobby: %d spectator places", n);
    HostSync(m);
}

// ---- lobby browser (CUSTOM GAMES on the main menu) ---------------------------------------------------------------
// The list opens at once from a cache that is refreshed in the background while the main menu is up, and its rows
// update in place when fresh results arrive.
struct BrowseEntry { uint64_t id; std::wstring label; };
std::vector<BrowseEntry> gCache;
DWORD gCacheAt;
bool gFetching, gFetchedOnce;
int gBrowserList;                                   // id of the open browser list (ui::List)
std::vector<uint64_t> gBrowserIds;                  // lobby of each game row, in row order
bool gBrowserSearchingRow;

std::vector<BrowseEntry> Describe(const std::vector<uint64_t>& ids) {
    std::vector<BrowseEntry> out;
    for (uint64_t id : ids) {
        if (gB->Get(id, "be1v1") != BE1V1_PROTOCOL) continue;
        std::wstring name = W(gB->Get(id, "name")), map = W(gB->Get(id, "mapname"));
        long long n = ToI(gB->Get(id, "n")), max = ToI(gB->Get(id, "max"), 8);
        if (name.empty() || n <= 0) continue;
        std::wstring row = name;
        if (!map.empty()) row += L"   -   " + map;
        rules::Values rv = rules::Decode(gB->Get(id, "rules"));
        if (rv.teams > 2 || rv.koOnly)
            row += std::wstring(L"   -   ") + (rv.koOnly ? L"TEAM BRAWL " : L"") + rules::TeamSizeLabels(rv.teams)[std::max(1, std::min(4, rv.teamSize)) - 1];
        row += L"   -   " + std::to_wstring(n) + L"/" + std::to_wstring(max);
        if (gB->Get(id, "state") == "game") row += L"   -   IN MATCH";
        out.push_back({ id, row });
    }
    return out;
}
std::vector<std::wstring> BrowserRows() {
    std::vector<std::wstring> rows = { L"CREATE GAME" };
    gBrowserIds.clear();
    for (auto& e : gCache) { rows.push_back(e.label); gBrowserIds.push_back(e.id); }
    gBrowserSearchingRow = gCache.empty() && (gFetching || !gFetchedOnce);
    if (gBrowserSearchingRow) rows.push_back(L"SEARCHING FOR GAMES...");
    else if (gCache.empty()) rows.push_back(L"NO GAMES FOUND");
    rows.push_back(L"REFRESH");
    rows.push_back(L"OFFICIAL CUSTOM QUEUE");
    return rows;
}
void Fetch() {
    if (gFetching || !gB || !gB->Ready()) return;
    gFetching = true;
    gB->Browse([](std::vector<uint64_t> ids) {
        gFetching = false; gFetchedOnce = true;
        gCache = Describe(ids);
        gCacheAt = GetTickCount();
        if (gBrowserList && ui::ListOpen(gBrowserList)) ui::UpdateList(gBrowserList, BrowserRows());
    });
}

void OpenBrowser() {
    if (!gB) return;
    if (!gB->Ready()) { ui::ShowMessage(L"", L"Steam isn't available. Make sure Steam is running."); return; }
    if (gBrowserList && ui::ListOpen(gBrowserList)) return;   // already showing (double click)
    Fetch();
    Log("lobby: browser opens with %d cached game(s)", (int)gCache.size());
    gBrowserList = ui::List(L"", BrowserRows(), L"", L"", [](int c) {
        gBrowserList = 0;
        int games = (int)gBrowserIds.size();
        int extra = 1 + games + ((gBrowserSearchingRow || games == 0) ? 1 : 0);   // index of REFRESH
        if (c == 0) CreateAsHost();
        else if (c >= 1 && c <= games) JoinById(gBrowserIds[c - 1]);
        else if (c == extra || (c == extra - 1 && games == 0)) { gCacheAt = 0; OpenBrowser(); }
        else if (c == extra + 1) ui::OpenOfficialCustomQueue();
    });
}
// Keeps the browser cache fresh while the player is on the main menu (cheap: one Steam lobby query).
void BrowserTick() {
    if (gSt != St::Idle || gFetching) return;
    DWORD now = GetTickCount();
    bool open = gBrowserList && ui::ListOpen(gBrowserList);
    if (now - gCacheAt < (open ? 6000u : 20000u)) return;
    if (!open && !ui::MainMenuReady()) return;
    Fetch();
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

// Our LEAVE buttons (and the moved debug buttons of earlier versions).
bool OnListButton(void* btn) {
    uo::UObject* b = (uo::UObject*)btn;
    std::wstring bn = uo::Name(b);
    Log("lobby: list button %ls", bn.c_str());
    if (gSt == St::Lobby && gJoinBtn && b == gJoinBtn) { Log("lobby: join the running match"); gSeenSeq = -1; return true; }
    bool leave = (gLeaveBtn[0] && b == gLeaveBtn[0]) || (gLeaveBtn[1] && b == gLeaveBtn[1]) ||
                 bn == L"Debug_FetchSessionData" || bn == L"Debug_UpdateSessionData";
    if (gSt != St::Lobby || !leave) return false;
    uo::UObject* scr = Screen();
    if (!scr) return false;
    gLeaving = true;
    uo::Call(scr, L"BndEvt__FE_CustomGameMenu_K2Node_ComponentBoundEvent_55_OnLeaveGamePressed__DelegateSignature").run();
    gLeaving = false;
    return true;
}

// A team or spectator place was clicked (mouse, Enter, controller A): an empty place moves you there, your own
// place moves you to the other team, and the host's click on someone else moves that player.
int NextTeamWithRoom(uo::UObject* m, int from) {
    int n = NumTeams();
    for (int k = 1; k <= n; k++) {
        int t = ((from < 0 ? -1 : from) + k) % n;
        if (t != from && CountTeam(t) < TeamMax(m, t)) return t;
    }
    return from;
}
void OpenInvite();
bool OnSlotPressed(void* slotPtr) {
    if (gSt != St::Lobby) return false;
    uo::UObject* slot = (uo::UObject*)slotPtr;
    // One click can arrive as both "Pressed" and "OnPressed_Event": act once.
    static uo::UObject* lastSlot; static DWORD lastAt;
    DWORD now = GetTickCount();
    if (slot == lastSlot && now - lastAt < 300) return true;
    lastSlot = slot; lastAt = now;
    int team = F<int32_t>(slot, Slot_TeamId);
    bool occupied = F<bool>(slot, Slot_Occupied), local = F<bool>(slot, Slot_IsLocal);
    Log("lobby: slot pressed team=%d occupied=%d local=%d", team, occupied, local);
    uo::UObject* m = Mgr();
    if (!m) return true;
    if (!occupied) {
        if (team == LocalTeamInLobby()) { if (gHost) OpenInvite(); }
        else if (ValidTeam(team)) RequestTeam(team);
        return true;
    }
    uint64_t id = SlotMember(slot);
    if (local || id == gB->Me()) {
        int cur = LocalTeamInLobby();
        int to = NextTeamWithRoom(m, cur);
        if (to != cur) RequestTeam(to);
        return true;
    }
    if (gHost && id && gTeam.count(id)) {
        int to = NextTeamWithRoom(m, gTeam[id]);
        if (to != gTeam[id]) { gTeam[id] = to; Log("lobby: host moved %llu to team %d", (unsigned long long)id, to); HostSync(m); }
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
    BrowserTick();
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
    if (net::MenuSettled()) LabelScreen();
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
        net::JoinHost(addr + NameOption() + L"?BETeam=" + std::to_wstring(lobby::MyTeam()));
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
    // Team 3 sits in the left column (under team 1) and takes that column's layout (name, then the picture on the
    // right). The slot Blueprint picks the layout from the team on every tick.
    ui::OnEventAfter(L"CustomGame_PlayerSlot_Team_C", L"Tick", [](uint8_t* slot, void*, uint8_t*) {
        if (F<int32_t>(slot, Slot_TeamId) != 2) return;
        static int off = -2;
        if (off == -2) off = uo::PropOffset(uo::ClassOf(slot), L"WidgetSwitcher_0");
        uo::UObject* sw = off >= 0 ? F<uo::UObject*>(slot, off) : nullptr;
        if (!sw) return;
        uo::Call g(sw, L"GetActiveWidgetIndex");
        if (g.ok() && g.run().get<int32_t>(L"ReturnValue") != 0) uo::Call(sw, L"SetActiveWidgetIndex").set<int32_t>(L"Index", 0).run();
    });
    // Team slot backgrounds: the slot Blueprint colours teams 0 and 1 (blue / red); teams 2 and 3 get yellow / green.
    ui::OnEventAfter(L"CustomGame_PlayerSlot_Base_C", L"Get_Background_ColorAndOpacity", [](uint8_t* slot, void*, uint8_t* ret) {
        int team = F<int32_t>(slot, Slot_TeamId);
        float* c = (float*)ret;
        static float alpha = 0.5f;
        if ((team == 0 || team == 1) && c[3] > 0) alpha = c[3];   // the Blueprint's own strength (0.5) and fades
        if (team >= 2 && team <= 3) { const float* tc = teams::Colour(team); c[0] = tc[0]; c[1] = tc[1]; c[2] = tc[2]; c[3] = alpha; }
    });
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
    Hook(A_GetTeamMaxPlayers, (void*)&hkGetTeamMaxPlayers, (void**)&oGetTeamMaxPlayers, "GetTeamMaxPlayers");
    Hook(A_GetTeamMembers, (void*)&hkGetTeamMembers, (void**)&oGetTeamMembers, "GetTeamMembers");
    Hook(A_LoadingFromLobby, (void*)&hkLoadingFromLobby, (void**)&oLoadingFromLobby, "LoadingFromLobby");
    Log("lobby: hooks installed");
}
}  // namespace lobby

// Developer shortcuts from the dev command channel.
void LobbyDevCommand(const char* cmd) {
    unsigned long long id = 0; int t = 0, n2 = 0;
    if (!strcmp(cmd, "create")) lobby::CreateAsHost();
    else if (!strcmp(cmd, "leave")) lobby::Leave();
    else if (sscanf(cmd, "join %llu", &id) == 1) lobby::JoinById(id);
    else if (!strcmp(cmd, "start")) { if (uo::UObject* m = Mgr()) hkCustomStart(m); }
    else if (sscanf(cmd, "team %d", &t) == 1) RequestTeam(t);
    else if (!strcmp(cmd, "status")) Log("lobby: %ls", lobby::StatusLine().c_str());
    else if (!strcmp(cmd, "tomenu")) net::Travel(L"/Game/Levels/FrontEnd/Map_FrontEnd_3D");
    else if (!strcmp(cmd, "rejoin")) gSeenSeq = -1;
    else if (!strcmp(cmd, "leavebtn")) lobby::OnListButton(gLeaveBtn[gHost ? 0 : 1]);
    else if (sscanf(cmd, "teams %d %d", &t, &n2) == 2) { rules::Values v = rules::Current(); v.teams = t; v.teamSize = n2; rules::Set(v); lobby::SetTeamSize(n2); }
    else if (sscanf(cmd, "forceteam %d", &t) == 1) { lobby::gForceTeam = t; Log("lobby: forced team %d", t); }
    else if (!strncmp(cmd, "rules ", 6)) rules::Set(rules::Decode(cmd + 6));
}
