// Steamworks access through the game's steam_api64.dll (flat API, SDK 1.39).
#include <windows.h>
#include <cstring>
#include <list>
#include "steam.h"
#include "ue.h"

namespace steam {
namespace {
using u64 = uint64_t;
using SteamAPICall = u64;
HMODULE gDll;
void *gClient, *gMM, *gFriends, *gUser, *gUtils;
bool gTried, gOk;

template <class T> T P(const char* name) { return gDll ? (T)GetProcAddress(gDll, name) : nullptr; }
#define SF(ret, name, ...) using name##_t = ret(__cdecl*)(__VA_ARGS__); name##_t name;
SF(void*, SteamClient)
SF(int, SteamAPI_GetHSteamUser)
SF(int, SteamAPI_GetHSteamPipe)
SF(void*, SteamAPI_ISteamClient_GetISteamMatchmaking, void*, int, int, const char*)
SF(void*, SteamAPI_ISteamClient_GetISteamFriends, void*, int, int, const char*)
SF(void*, SteamAPI_ISteamClient_GetISteamUser, void*, int, int, const char*)
SF(void*, SteamAPI_ISteamClient_GetISteamUtils, void*, int, const char*)
SF(u64, SteamAPI_ISteamUser_GetSteamID, void*)
SF(const char*, SteamAPI_ISteamFriends_GetPersonaName, void*)
SF(const char*, SteamAPI_ISteamFriends_GetFriendPersonaName, void*, u64)
SF(bool, SteamAPI_ISteamFriends_RequestUserInformation, void*, u64, bool)
SF(int, SteamAPI_ISteamFriends_GetFriendCount, void*, int)
SF(u64, SteamAPI_ISteamFriends_GetFriendByIndex, void*, int, int)
SF(bool, SteamAPI_ISteamFriends_GetFriendGamePlayed, void*, u64, void*)
SF(void, SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog, void*, u64)
SF(void, SteamAPI_ISteamFriends_ActivateGameOverlayToUser, void*, const char*, u64)
SF(bool, SteamAPI_ISteamFriends_SetRichPresence, void*, const char*, const char*)
SF(void, SteamAPI_ISteamFriends_ClearRichPresence, void*)
SF(SteamAPICall, SteamAPI_ISteamMatchmaking_CreateLobby, void*, int, int)
SF(SteamAPICall, SteamAPI_ISteamMatchmaking_JoinLobby, void*, u64)
SF(void, SteamAPI_ISteamMatchmaking_LeaveLobby, void*, u64)
SF(SteamAPICall, SteamAPI_ISteamMatchmaking_RequestLobbyList, void*)
SF(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter, void*, const char*, const char*, int)
SF(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter, void*, int)
SF(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter, void*, int)
SF(u64, SteamAPI_ISteamMatchmaking_GetLobbyByIndex, void*, int)
SF(bool, SteamAPI_ISteamMatchmaking_SetLobbyData, void*, u64, const char*, const char*)
SF(const char*, SteamAPI_ISteamMatchmaking_GetLobbyData, void*, u64, const char*)
SF(void, SteamAPI_ISteamMatchmaking_SetLobbyMemberData, void*, u64, const char*, const char*)
SF(const char*, SteamAPI_ISteamMatchmaking_GetLobbyMemberData, void*, u64, u64, const char*)
SF(int, SteamAPI_ISteamMatchmaking_GetNumLobbyMembers, void*, u64)
SF(u64, SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex, void*, u64, int)
SF(u64, SteamAPI_ISteamMatchmaking_GetLobbyOwner, void*, u64)
SF(bool, SteamAPI_ISteamMatchmaking_SetLobbyOwner, void*, u64, u64)
SF(bool, SteamAPI_ISteamMatchmaking_SetLobbyType, void*, u64, int)
SF(bool, SteamAPI_ISteamMatchmaking_SetLobbyJoinable, void*, u64, bool)
SF(bool, SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit, void*, u64, int)
SF(int, SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit, void*, u64)
SF(bool, SteamAPI_ISteamMatchmaking_RequestLobbyData, void*, u64)
SF(bool, SteamAPI_ISteamMatchmaking_InviteUserToLobby, void*, u64, u64)
SF(bool, SteamAPI_ISteamUtils_GetAPICallResult, void*, SteamAPICall, void*, int, int, bool*)
SF(bool, SteamAPI_ISteamUtils_IsAPICallCompleted, void*, SteamAPICall, bool*)
SF(void, SteamAPI_RegisterCallback, void*, int)
#undef SF

// Steam callback object with the MSVC vtable layout of CCallbackBase
// (overloaded virtuals are laid out in reverse: Run(p, bIOFailure, call), Run(p), GetCallbackSizeBytes).
struct CallbackObj {
    void** vt; uint8_t flags; int32_t id;
    int size; void (*fn)(void*);
};
void __fastcall CbRun3(CallbackObj* self, void* p, bool, u64) { self->fn(p); }
void __fastcall CbRun1(CallbackObj* self, void* p) { self->fn(p); }
int __fastcall CbSize(CallbackObj* self) { return self->size; }
void* gCbVt[3] = { (void*)&CbRun3, (void*)&CbRun1, (void*)&CbSize };
std::list<CallbackObj> gCallbacks;
void Register(int id, int size, void (*fn)(void*)) {
    gCallbacks.push_back(CallbackObj{ gCbVt, 0, id, size, fn });
    SteamAPI_RegisterCallback(&gCallbacks.back(), id);
}

#pragma pack(push, 8)
struct LobbyCreated_t { int32_t result; u64 lobby; };                                         // 513
struct LobbyEnter_t { u64 lobby; uint32_t perms; bool locked; uint32_t response; };            // 504
struct LobbyMatchList_t { uint32_t count; };                                                  // 510
struct GameLobbyJoinRequested_t { u64 lobby; u64 friendId; };                                 // 333
struct GameRichPresenceJoinRequested_t { u64 friendId; char connect[256]; };                  // 337
struct FriendGameInfo_t { u64 game; uint32_t ip; uint16_t port, qport; u64 lobby; };
#pragma pack(pop)

struct Pending { SteamAPICall call; int id; int size; std::function<void(bool, void*)> done; };
std::list<Pending> gPending;
std::function<void(uint64_t)> gJoinCb;

void OnLobbyJoinRequested(void* p) {
    auto* e = (GameLobbyJoinRequested_t*)p;
    Log("steam: join requested lobby=%llu from=%llu", (unsigned long long)e->lobby, (unsigned long long)e->friendId);
    if (gJoinCb) gJoinCb(e->lobby);
}
void OnRichPresenceJoin(void* p) {
    auto* e = (GameRichPresenceJoinRequested_t*)p;
    Log("steam: rich presence join '%s'", e->connect);
    const char* s = strstr(e->connect, "+connect_lobby ");
    if (s && gJoinCb) gJoinCb(_strtoui64(s + 15, nullptr, 10));
}

std::wstring Wide(const char* s) {
    if (!s) return L"";
    int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
    std::wstring w(n > 0 ? n - 1 : 0, L'\0');
    if (n > 1) MultiByteToWideChar(CP_UTF8, 0, s, -1, &w[0], n);
    return w;
}

bool Resolve() {
    gDll = GetModuleHandleW(L"steam_api64.dll");
    if (!gDll) return false;
#define R(name) name = P<name##_t>(#name); if (!name) { Log("steam: missing %s", #name); return false; }
    R(SteamClient) R(SteamAPI_GetHSteamUser) R(SteamAPI_GetHSteamPipe)
    R(SteamAPI_ISteamClient_GetISteamMatchmaking) R(SteamAPI_ISteamClient_GetISteamFriends) R(SteamAPI_ISteamClient_GetISteamUser)
    R(SteamAPI_ISteamClient_GetISteamUtils) R(SteamAPI_ISteamUser_GetSteamID) R(SteamAPI_ISteamFriends_GetPersonaName)
    R(SteamAPI_ISteamFriends_GetFriendPersonaName) R(SteamAPI_ISteamFriends_RequestUserInformation) R(SteamAPI_ISteamFriends_GetFriendCount)
    R(SteamAPI_ISteamFriends_GetFriendByIndex) R(SteamAPI_ISteamFriends_GetFriendGamePlayed) R(SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog)
    R(SteamAPI_ISteamFriends_ActivateGameOverlayToUser) R(SteamAPI_ISteamFriends_SetRichPresence) R(SteamAPI_ISteamFriends_ClearRichPresence)
    R(SteamAPI_ISteamMatchmaking_CreateLobby) R(SteamAPI_ISteamMatchmaking_JoinLobby) R(SteamAPI_ISteamMatchmaking_LeaveLobby)
    R(SteamAPI_ISteamMatchmaking_RequestLobbyList) R(SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter)
    R(SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter) R(SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter)
    R(SteamAPI_ISteamMatchmaking_GetLobbyByIndex) R(SteamAPI_ISteamMatchmaking_SetLobbyData) R(SteamAPI_ISteamMatchmaking_GetLobbyData)
    R(SteamAPI_ISteamMatchmaking_SetLobbyMemberData) R(SteamAPI_ISteamMatchmaking_GetLobbyMemberData) R(SteamAPI_ISteamMatchmaking_GetNumLobbyMembers)
    R(SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex) R(SteamAPI_ISteamMatchmaking_GetLobbyOwner) R(SteamAPI_ISteamMatchmaking_SetLobbyOwner)
    R(SteamAPI_ISteamMatchmaking_SetLobbyType) R(SteamAPI_ISteamMatchmaking_SetLobbyJoinable) R(SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit)
    R(SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit) R(SteamAPI_ISteamMatchmaking_RequestLobbyData) R(SteamAPI_ISteamMatchmaking_InviteUserToLobby)
    R(SteamAPI_ISteamUtils_GetAPICallResult) R(SteamAPI_ISteamUtils_IsAPICallCompleted) R(SteamAPI_RegisterCallback)
#undef R
    gClient = SteamClient();
    int user = SteamAPI_GetHSteamUser(), pipe = SteamAPI_GetHSteamPipe();
    if (!gClient || !user || !pipe) return false;
    gMM = SteamAPI_ISteamClient_GetISteamMatchmaking(gClient, user, pipe, "SteamMatchMaking009");
    gFriends = SteamAPI_ISteamClient_GetISteamFriends(gClient, user, pipe, "SteamFriends015");
    gUser = SteamAPI_ISteamClient_GetISteamUser(gClient, user, pipe, "SteamUser019");
    gUtils = SteamAPI_ISteamClient_GetISteamUtils(gClient, pipe, "SteamUtils008");
    if (!gMM || !gFriends || !gUser || !gUtils) { Log("steam: interface missing"); return false; }
    Register(333, sizeof(GameLobbyJoinRequested_t), &OnLobbyJoinRequested);
    Register(337, sizeof(GameRichPresenceJoinRequested_t), &OnRichPresenceJoin);
    Register(505, 24, [](void* p) {   // LobbyDataUpdate_t: proves callback delivery works (logged a few times)
        static int n; if (n++ < 3) Log("steam: callback LobbyDataUpdate lobby=%llu", (unsigned long long)*(u64*)p);
    });
    Log("steam: ready, me=%llu (%ls)", (unsigned long long)MyId(), MyName().c_str());
    return true;
}

void Track(SteamAPICall call, int id, int size, std::function<void(bool, void*)> done) {
    if (!call) { done(false, nullptr); return; }
    gPending.push_back(Pending{ call, id, size, std::move(done) });
}
}  // namespace

bool Ready() {
    if (gOk) return true;
    static DWORD last;
    DWORD now = GetTickCount();
    if (gTried && now - last < 2000) return false;
    gTried = true; last = now;
    gOk = Resolve();
    return gOk;
}
uint64_t MyId() { return gUser ? SteamAPI_ISteamUser_GetSteamID(gUser) : 0; }
std::wstring MyName() { return gFriends ? Wide(SteamAPI_ISteamFriends_GetPersonaName(gFriends)) : L""; }
std::wstring NameOf(uint64_t id) { return gFriends ? Wide(SteamAPI_ISteamFriends_GetFriendPersonaName(gFriends, id)) : L""; }
void RequestInfo(uint64_t id) { if (gFriends) SteamAPI_ISteamFriends_RequestUserInformation(gFriends, id, true); }

void CreateLobby(LobbyType type, int maxMembers, std::function<void(bool, uint64_t)> done) {
    if (!Ready()) { done(false, 0); return; }
    Track(SteamAPI_ISteamMatchmaking_CreateLobby(gMM, type, maxMembers), 513, sizeof(LobbyCreated_t), [done](bool ok, void* p) {
        auto* r = (LobbyCreated_t*)p;
        done(ok && r && r->result == 1, r ? r->lobby : 0);
    });
}
void JoinLobby(uint64_t lobby, std::function<void(bool, uint64_t, int)> done) {
    if (!Ready()) { done(false, lobby, 0); return; }
    Track(SteamAPI_ISteamMatchmaking_JoinLobby(gMM, lobby), 504, sizeof(LobbyEnter_t), [done, lobby](bool ok, void* p) {
        auto* r = (LobbyEnter_t*)p;
        done(ok && r && r->response == 1, lobby, r ? (int)r->response : 0);
    });
}
void RequestLobbyList(const std::vector<std::pair<std::string, std::string>>& filters, std::function<void(std::vector<uint64_t>)> done) {
    if (!Ready()) { done({}); return; }
    for (auto& f : filters) SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter(gMM, f.first.c_str(), f.second.c_str(), 0);
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter(gMM, 3);   // worldwide
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter(gMM, 50);
    Track(SteamAPI_ISteamMatchmaking_RequestLobbyList(gMM), 510, sizeof(LobbyMatchList_t), [done](bool ok, void* p) {
        std::vector<uint64_t> out;
        if (ok && p) for (uint32_t i = 0; i < ((LobbyMatchList_t*)p)->count; i++) out.push_back(SteamAPI_ISteamMatchmaking_GetLobbyByIndex(gMM, (int)i));
        done(out);
    });
}
void LeaveLobby(uint64_t lobby) { if (gMM && lobby) SteamAPI_ISteamMatchmaking_LeaveLobby(gMM, lobby); }
bool SetLobbyData(uint64_t lobby, const char* key, const std::string& v) { return gMM && SteamAPI_ISteamMatchmaking_SetLobbyData(gMM, lobby, key, v.c_str()); }
std::string LobbyData(uint64_t lobby, const char* key) { const char* s = gMM ? SteamAPI_ISteamMatchmaking_GetLobbyData(gMM, lobby, key) : nullptr; return s ? s : ""; }
void SetMemberData(uint64_t lobby, const char* key, const std::string& v) { if (gMM) SteamAPI_ISteamMatchmaking_SetLobbyMemberData(gMM, lobby, key, v.c_str()); }
std::string MemberData(uint64_t lobby, uint64_t m, const char* key) { const char* s = gMM ? SteamAPI_ISteamMatchmaking_GetLobbyMemberData(gMM, lobby, m, key) : nullptr; return s ? s : ""; }
std::vector<uint64_t> Members(uint64_t lobby) {
    std::vector<uint64_t> r;
    if (!gMM) return r;
    int n = SteamAPI_ISteamMatchmaking_GetNumLobbyMembers(gMM, lobby);
    for (int i = 0; i < n; i++) r.push_back(SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex(gMM, lobby, i));
    return r;
}
uint64_t Owner(uint64_t lobby) { return gMM ? SteamAPI_ISteamMatchmaking_GetLobbyOwner(gMM, lobby) : 0; }
bool SetOwner(uint64_t lobby, uint64_t m) { return gMM && SteamAPI_ISteamMatchmaking_SetLobbyOwner(gMM, lobby, m); }
void SetLobbyType(uint64_t lobby, LobbyType t) { if (gMM) SteamAPI_ISteamMatchmaking_SetLobbyType(gMM, lobby, t); }
void SetJoinable(uint64_t lobby, bool j) { if (gMM) SteamAPI_ISteamMatchmaking_SetLobbyJoinable(gMM, lobby, j); }
void SetMemberLimit(uint64_t lobby, int n) { if (gMM) SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit(gMM, lobby, n); }
int MemberLimit(uint64_t lobby) { return gMM ? SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit(gMM, lobby) : 0; }
void RequestLobbyData(uint64_t lobby) { if (gMM) SteamAPI_ISteamMatchmaking_RequestLobbyData(gMM, lobby); }
bool InviteUser(uint64_t lobby, uint64_t user) { return gMM && SteamAPI_ISteamMatchmaking_InviteUserToLobby(gMM, lobby, user); }
void OpenInviteOverlay(uint64_t lobby) { if (gFriends) SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog(gFriends, lobby); }
void OpenOverlayToUser(const char* dialog, uint64_t user) { if (gFriends) SteamAPI_ISteamFriends_ActivateGameOverlayToUser(gFriends, dialog, user); }
void SetRichPresence(const char* k, const char* v) { if (gFriends) SteamAPI_ISteamFriends_SetRichPresence(gFriends, k, v); }
void ClearRichPresence() { if (gFriends) SteamAPI_ISteamFriends_ClearRichPresence(gFriends); }

std::vector<Friend> Friends() {
    std::vector<Friend> r;
    if (!Ready()) return r;
    int n = SteamAPI_ISteamFriends_GetFriendCount(gFriends, 4 /* k_EFriendFlagImmediate */);
    for (int i = 0; i < n; i++) {
        u64 id = SteamAPI_ISteamFriends_GetFriendByIndex(gFriends, i, 4);
        FriendGameInfo_t g{};
        bool playing = SteamAPI_ISteamFriends_GetFriendGamePlayed(gFriends, id, &g);
        Friend f{ id, NameOf(id), playing && (g.game & 0xFFFFFF) == 1189800, playing ? g.lobby : 0 };
        r.push_back(f);
    }
    return r;
}

void OnJoinRequested(std::function<void(uint64_t)> cb) { gJoinCb = std::move(cb); }

void Tick() {
    if (!gOk) return;
    for (auto it = gPending.begin(); it != gPending.end();) {
        bool failed = false;
        if (!SteamAPI_ISteamUtils_IsAPICallCompleted(gUtils, it->call, &failed)) { ++it; continue; }
        std::vector<uint8_t> buf(it->size + 16, 0);
        bool ok = SteamAPI_ISteamUtils_GetAPICallResult(gUtils, it->call, buf.data(), it->size, it->id, &failed) && !failed;
        auto done = std::move(it->done);
        it = gPending.erase(it);
        done(ok, buf.data());
    }
}
}  // namespace steam
