// Gameplay-rule patches for private matches (no PlayFab, no matchmaking).
#include <windows.h>
#include "MinHook.h"
#include "ue.h"
#include "mod.h"
#include "uobj.h"
#include <cwchar>
#include <map>
#include <vector>

namespace {
constexpr uintptr_t VT_MBPlayerController = 0x1438a5b20;
constexpr uintptr_t ReturnTrue = 0x1402ec6d0;                  // mov al,1; ret
constexpr uintptr_t MinPlayersToStart = 0x144f357b8;           // int, 8 in retail (full 4v4)

void SpectateTick(bool request);

// True when this process is a client connected to a host (its world's net driver has a server connection).
bool IsJoinedClient() {
    void* engine = *(void**)VA(Addr::GEngine);
    auto& list = F<TArray<uint8_t*>>(engine, Off::Engine_WorldList);
    for (int i = 0; i < list.Num; i++) {
        void* w = list.Data[i] ? F<void*>(list.Data[i], Off::Ctx_World) : nullptr;
        void* nd = w ? F<void*>(w, Off::World_NetDriver) : nullptr;
        if (nd && F<void*>(nd, Off::ND_ServerConnection)) return true;
    }
    return false;
}

// Builds the MBInputEventAddPlayer for a local player; TeamId (+0xd8) is copied from the replicated PlayerState,
// which is 0 for everyone without matchmaking. Each player puts in the team the lobby gave them (without a lobby,
// e.g. the developer shortcuts, the joining player takes team 1 so the match is a real 1v1).
// (Injecting MBInputEventChangeTeam from the host afterwards is ignored by the sim.)
constexpr uintptr_t BuildLocalAddPlayer = 0x1410f9640;
constexpr size_t AddPlayer_TeamId = 0xd8;
using BuildAddPlayerFn = void*(__fastcall*)(void*, void*);
BuildAddPlayerFn oBuildLocalAddPlayer;
void* __fastcall hkBuildLocalAddPlayer(void* self, void* pc) {
    int team = lobby::Active() ? lobby::MyTeam() : (IsJoinedClient() ? 1 : 0);
    // Spectators never join the simulation as fighters; they watch through the game's spectator mode.
    if (team < 0) { SpectateTick(true); return nullptr; }
    void* ev = oBuildLocalAddPlayer(self, pc);
    if (!ev) return ev;
    Log("adding local player to team %d (was %d)", team, F<int32_t>(ev, AddPlayer_TeamId));
    F<int32_t>(ev, AddPlayer_TeamId) = team;
    return ev;
}
// ---- spectators -------------------------------------------------------------------------------------------
// A spectator's local controller is switched into the game's spectator mode once its pawn-less controller exists.
// Spectator mode is confirmed (not assumed) before fighter select is closed: started too early (a slow join), the
// request is lost and the player is left with an empty fighter HUD and a camera stuck at the spawn.
constexpr size_t World_WorldSingleton = 0x8d8, WS_bIsInSpectatorMode = 0x98d;
bool Visible(uo::UObject* w) { uo::Call c(w, L"IsVisible"); return c.ok() && c.run().get<bool>(L"ReturnValue"); }
bool OnScreen(uo::UObject* w) { uo::Call c(w, L"GetParent"); return c.ok() && c.run().get<uo::UObject*>(L"ReturnValue"); }
void SpectateTick(bool request) {
    static bool want; static DWORD next, lastAttempt, lastCycle; static int attempts; static bool logged;
    DWORD now = GetTickCount();
    if (request && !want) { want = true; next = now + 500; lastAttempt = 0; attempts = 0; logged = false; }
    if (!want) return;
    if (!lobby::Active() || lobby::MyTeam() >= 0 || !net::IsConnectedClient()) { want = false; return; }
    if (now < next) return;
    next = now + 500;
    uo::UObject* pc = nullptr;
    for (uo::UObject* p : uo::FindAll(uo::FindClass(L"MBPlayerControllerBase"))) {
        uo::Call loc(p, L"IsLocalController");
        if (loc.ok() && loc.run().get<bool>(L"ReturnValue")) { pc = p; break; }
    }
    if (!pc) return;
    uint8_t* world = (uint8_t*)net::World();
    uint8_t* ws = world ? F<uint8_t*>(world, World_WorldSingleton) : nullptr;
    uo::Call isSpec(pc, L"IsSpectator");
    bool spectating = ws && F<bool>(ws, WS_bIsInSpectatorMode) && isSpec.ok() && isSpec.run().get<bool>(L"ReturnValue");
    if (!spectating) {
        if (now - lastAttempt < 1500) return;
        lastAttempt = now; attempts++; logged = false;
        Log("spectate: starting spectator mode (attempt %d)", attempts);
        uo::Call(pc, L"StartSpectating").run();
        uo::Call(pc, L"ServerStartSpectating").run();
        return;
    }
    if (!logged) { logged = true; Log("spectate: spectator mode is on"); }
    // Fighter select can be pushed again when the match state changes: keep it closed.
    if (uo::UObject* hs = uo::FindClass(L"FE_HeroSelectScreen_C")) {
        uo::UObject* fe = uo::FindFirst(uo::FindClass(L"MBFrontEnd"));
        for (uo::UObject* s : uo::FindAll(hs))
            if (fe && OnScreen(s)) { uo::Call(fe, L"PopScreen").run(); Log("spectate: closed fighter select"); break; }
    }
    // Live spectating has nothing to rewind: hide the replay controls and the replay progress bar.
    for (const wchar_t* c : { L"Widget_SpectatorPlaybackControls_C", L"Widget_SpectatorReplayProgressBar_C" })
        for (uo::UObject* w : uo::FindAll(uo::FindClass(c)))
            if (Visible(w)) uo::Call(w, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    static FName progressInfo = uo::MakeName(L"VerticalBox_ReplayProgressInfo");
    for (uo::UObject* w : uo::FindAll(uo::FindClass(L"VerticalBox")))
        if (uo::NameIs(w, progressInfo) && Visible(w)) uo::Call(w, L"SetVisibility").set<uint8_t>(L"InVisibility", 1).run();
    // Follow camera without anyone to follow (start of the match, or the player left): pick the next player.
    static int smOff = -2;
    if (smOff == -2) smOff = uo::PropOffset(uo::ClassOf(pc), L"SpectatorManager");
    uint8_t* sm = smOff >= 0 ? F<uint8_t*>(pc, smOff) : nullptr;
    if (sm && F<uint8_t>(sm, 0x141 /* CameraMode */) == 1 && !F<void*>(sm, 0x128 /* FollowingPawn */) && now - lastCycle > 2000) {
        lastCycle = now;
        for (uo::UObject* ov : uo::FindAll(uo::FindClass(L"MBSpectatorOverlayWidget")))
            if (Visible(ov)) { uo::Call(ov, L"SpectatorSelectNextPlayer").run(); Log("spectate: following the next player"); break; }
    }
}

// ---- teams on the host ---------------------------------------------------------------------------------------
// Character select (which heroes a team has picked, the team rosters) reads PlayerState.TeamId, which nothing sets
// without matchmaking. Joiners put "?BETeam=<n>" in their join URL; the host finds it in each connection's request
// URL and sets the replicated TeamId on that player's PlayerState as soon as it exists.
constexpr size_t PS_TeamId = 0x5d4;
bool ReadableString(const FString* s) {
    if (!s->Data || s->Num < 8 || s->Num > 2048 || s->Max < s->Num) return false;
    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery(s->Data, &mbi, sizeof mbi) || mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))) return false;
    return (uint8_t*)s->Data + s->Num * 2 <= (uint8_t*)mbi.BaseAddress + mbi.RegionSize;
}
int TeamFromConnection(uint8_t* conn) {
    // Scan the connection object for the request URL (an FString containing our option). The answer never changes
    // for a connection, so it is looked up once.
    struct Known { int team; DWORD at; };
    static std::map<uint8_t*, Known> known;
    DWORD now = GetTickCount();
    auto k = known.find(conn);
    if (k != known.end() && (k->second.team != -2 || now - k->second.at < 2000)) return k->second.team;   // misses retried every 2 s
    if (known.size() > 64) known.clear();
    for (size_t off = 0x60; off < 0x2000; off += 8) {
        FString* s = (FString*)(conn + off);
        if (!ReadableString(s)) continue;
        const wchar_t* t = wcsstr(s->Data, L"BETeam=");
        if (t) { known[conn] = { _wtoi(t + 7), now }; return known[conn].team; }
    }
    known[conn] = { -2, now };
    return -2;
}
int gCtrlPSOff = -1;
void SetTeam(uint8_t* pc, int team) {
    if (gCtrlPSOff < 0) gCtrlPSOff = uo::PropOffset(uo::FindClass(L"Controller"), L"PlayerState");
    uint8_t* ps = pc && gCtrlPSOff >= 0 ? F<uint8_t*>(pc, gCtrlPSOff) : nullptr;
    if (!ps) return;
    // Spectators: the game mode doesn't count them as players (so the match starts without them).
    if (team < 0) {
        if (!uo::GetBool(ps, L"bOnlySpectator")) {
            uo::SetBool(ps, L"bOnlySpectator", true);
            uo::SetBool(ps, L"bIsSpectator", true);
            Log("teams: %ls is a spectator", uo::Name((uo::UObject*)ps).c_str());
        }
        return;
    }
    if (F<int32_t>(ps, PS_TeamId) == team) return;
    Log("teams: %ls -> team %d", uo::Name((uo::UObject*)ps).c_str(), team);
    F<int32_t>(ps, PS_TeamId) = team;
}
// Joined players get their team the moment their PlayerState exists, before it is first sent to anyone: fighter
// select builds each player's view of "my team" from the first values it receives.
void HostConnectionTeams(void* nd) {
    auto& conns = F<TArray<uint8_t*>>(nd, Off::ND_ClientConnections);
    for (int i = 0; i < conns.Num; i++) {
        uint8_t* c = conns.Data[i];
        uint8_t* pc = c ? F<uint8_t*>(c, Off::Conn_PlayerController) : nullptr;
        if (!pc) continue;
        int t = TeamFromConnection(c);
        if (t >= -1) SetTeam(pc, t);
    }
}
void SyncTeamsOnHost() {
    if (!lobby::Active() || !net::IsHosting()) return;
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 500) return;
    last = now;
    void* world = net::World();
    void* nd = world ? F<void*>(world, Off::World_NetDriver) : nullptr;
    if (!nd) return;
    LARGE_INTEGER f, a, b; QueryPerformanceFrequency(&f); QueryPerformanceCounter(&a);
    HostConnectionTeams(nd);
    QueryPerformanceCounter(&b);
    if ((b.QuadPart - a.QuadPart) * 1000.0 / f.QuadPart > 20) Log("perf: connection teams %.1f ms", (b.QuadPart - a.QuadPart) * 1000.0 / f.QuadPart);
    // The host's own player
    for (uo::UObject* pc : uo::FindAll(uo::FindClass(L"MBPlayerController"))) {
        uo::Call c(pc, L"IsLocalController");
        if (c.ok() && c.run().get<bool>(L"ReturnValue")) SetTeam(pc, lobby::MyTeam());
    }
}
}  // namespace

namespace {
// ---- text chat ------------------------------------------------------------------------------------------------
// nt.usePlayfabTextChat (default 1) routes text chat through PlayFab Party, which player-hosted games don't have:
// the host's ServerBroadcastChat then never relays the message and only the sender sees it. With 0 the host sends
// it to the other players with the game's own ClientReceiveChat RPC (team/all/whisper filtering included).
constexpr uintptr_t A_CVarUsePlayfabTextChat = 0x145341e20;   // int* (game-thread and render-thread values)
void ChatTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 2000) return;
    last = now;
    int32_t* v = *(int32_t**)VA(A_CVarUsePlayfabTextChat);
    if (!v || (v[0] == 0 && v[1] == 0)) return;
    Log("chat: nt.usePlayfabTextChat %d -> 0", v[0]);
    v[0] = v[1] = 0;
}
// In custom games every text message goes to everyone in the match (both teams and spectators): team chat would
// reach nobody in a 1v1. The host relays; the channel it relays on is what everyone sees.
constexpr uintptr_t A_ServerBroadcastChatImpl = 0x1410c7910;   // void (PC*, const FText&, EMBChatChannel, int TargetPlayerId)
using BroadcastChatFn = void(__fastcall*)(void*, void*, uint8_t, int32_t);
BroadcastChatFn oBroadcastChat;
void __fastcall hkBroadcastChat(void* pc, void* text, uint8_t channel, int32_t target) {
    if (lobby::Active() && (channel == 0 || channel == 7)) channel = 1;   // team -> match
    oBroadcastChat(pc, text, channel, target);
}
// Leaving a match early is reported to the official backend (PlayFab "Account_AddLeaveReasonSingle_Leave"), which
// gives the account an official leaver penalty: backfill with other leavers and no rewards until 3 games are finished.
// Player-hosted games must never count: the report is dropped when the match was one of ours.
constexpr uintptr_t A_AddLocalPlayerLeaveReason = 0x14110b830;
using LeaveReasonFn = void(__fastcall*)(void*, void*, void*, void*);
LeaveReasonFn oLeaveReason;
void __fastcall hkLeaveReason(void* a, void* b, void* c, void* d) {
    if (lobby::Active() || net::CustomMatch()) { Log("leaver: not reporting a leave from a custom game to the official servers"); return; }
    oLeaveReason(a, b, c, d);
}
// The official "you have a leaver penalty" message is about official matchmaking; it isn't shown in custom games.
// (A native function called from Blueprint script: hooked natively, not through its UFunction.)
constexpr uintptr_t A_CheckAndShowLeaverMessage = 0x1410fbb60;   // void (UObject* WorldContextObject)
using CtxFn = void(__fastcall*)(void*);
CtxFn oLeaverMessage;
void __fastcall hkLeaverMessage(void* ctx) {
    if (lobby::Active() || net::CustomMatch()) { Log("leaver: official penalty message skipped in a custom game"); return; }
    oLeaverMessage(ctx);
}
// ---- unlocked frame rate --------------------------------------------------------------------------------------
// Bleeding Edge has an "unlock frame rate" option (RollbackEngine.ThrottleEngineTickRate = 0, saved as
// ThrottleEngineTickRate in GameUserSettings) that shipped hidden: video.AllowThrottleEngineTickRate is 0 in the
// game's config, so the option is not shown and applying the video settings forces the throttle back on (60 fps).
// The mod keeps the allow flag on, so the option shows and is respected.
constexpr uintptr_t A_CVarAllowThrottle = 0x145341a98;      // int* video.AllowThrottleEngineTickRate
constexpr uintptr_t A_ThrottleEngineTickRate = 0x144e14d30; // int  RollbackEngine.ThrottleEngineTickRate (1 = 60 fps)
constexpr uintptr_t A_SmoothMax = 0x14534137c, A_SmoothMin = 0x144f352e4, A_SmoothOn = 0x144f352e0;
// The rollback engine's tick-rate limit: when unlocked it normally returns 0 (no limit), but in online matches it
// first takes a time-sync branch that returns a ~60 fps limit whenever it nudges the timing toward the other
// players, without looking at the setting. Unlocked, the simulation steps on real elapsed time, so that limit
// doesn't help the sync at all - it only drops the frame rate to 60 every now and then.
constexpr uintptr_t A_RollbackMaxTickRate = 0x140403650;    // float (NTRollbackEngine*, float)
using MaxTickFn = float(__fastcall*)(void*, float);
MaxTickFn oRollbackMaxTick;
float __fastcall hkRollbackMaxTick(void* engine, float x) {
    float r = oRollbackMaxTick(engine, x);   // keeps its bookkeeping
    return *(int32_t*)VA(A_ThrottleEngineTickRate) == 0 ? 0.0f : r;
}
// The engine's own limiter (UMBGameEngine::GetMaxTickRate). With the throttle off it applies Ninja Theory's frame
// rate smoothing: the next frame is limited to the recent average frame rate. That feeds back on itself: once the
// game ran at 60 for a moment (a loading screen, a busy scene) it stays at 60, until something disturbs the
// average (changing a video setting, switching fullscreen/borderless) and it climbs again. Unlocked means unlocked:
// no smoothing. The player's frame rate limit and V-Sync (Options > Video) still apply.
constexpr uintptr_t A_EngineMaxTickRate = 0x141041d80;   // float UMBGameEngine::GetMaxTickRate(float DeltaTime, bool bAllowSmoothing)
using EngineMaxFn = float(__fastcall*)(void*, float, bool);
EngineMaxFn oEngineMaxTick;
float __fastcall hkEngineMaxTick(void* engine, float dt, bool smooth) {
    if (*(int32_t*)VA(A_ThrottleEngineTickRate) == 0) smooth = false;
    return oEngineMaxTick(engine, dt, smooth);
}
// t.MaxFPS (the engine's FPS cap) is set from the player's Frame Rate Limit when the video settings are applied,
// but it also turns up at 60 on its own now and then (it then stays there until a setting is changed). While the
// frame rate is unlocked it is held at the player's own limit (0 = none).
constexpr uintptr_t A_CVarMaxFPS = 0x14558fc80;   // float* t.MaxFPS (game-thread and render-thread values)
void FrameRateTick() {
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 1000) return;
    last = now;
    int32_t* allow = *(int32_t**)VA(A_CVarAllowThrottle);
    if (allow && (allow[0] <= 0 || allow[1] <= 0)) {
        Log("fps: video.AllowThrottleEngineTickRate %d -> 1 (unlock frame rate option available)", allow[0]);
        allow[0] = allow[1] = 1;
    }
    // The throttle follows the player's own choice (Options > Video > Unlock Frame Rate) and nothing else: anything
    // that switches it back on behind their back (a settings re-apply while the option was disallowed, settings
    // pushed by the game's servers) is undone within a second.
    static uo::UObject* gus;
    if (!gus || !uo::IsLive(gus)) gus = uo::FindFirst(uo::FindClass(L"GameUserSettings"));
    uo::Call get(gus, L"GetThrottleEngineTickRate");
    if (gus && get.ok()) {
        int want = get.run().get<bool>(L"ReturnValue") ? 1 : 0;
        int32_t& cur = *(int32_t*)VA(A_ThrottleEngineTickRate);
        if (cur != want) { Log("fps: frame rate lock was %d, the player's setting is %d: restored", cur, want); cur = want; }
    }
    float* maxFps = *(float**)VA(A_CVarMaxFPS);
    uo::Call lim(gus, L"GetFrameRateLimit");
    if (maxFps && gus && lim.ok() && *(int32_t*)VA(A_ThrottleEngineTickRate) == 0) {
        float want = lim.run().get<float>(L"ReturnValue");
        if (want < 0) want = 0;
        if (maxFps[0] != want || maxFps[1] != want) {
            Log("fps: t.MaxFPS was %.0f, the player's frame rate limit is %.0f: restored", maxFps[0], want);
            maxFps[0] = maxFps[1] = want;
        }
    }
    static int lastThrottle = -1;
    int t = *(int32_t*)VA(A_ThrottleEngineTickRate);
    if (t != lastThrottle) { lastThrottle = t; Log("fps: frame rate %s", t ? "locked to the simulation (60)" : "unlocked"); }
}
}  // namespace

void FpsDevReport() {
    int32_t* allow = *(int32_t**)VA(A_CVarAllowThrottle);
    Log("fps: allow=%d throttle=%d smoothing=%d min=%.1f max=%.1f", allow ? allow[0] : -1, *(int32_t*)VA(A_ThrottleEngineTickRate),
        *(uint8_t*)VA(A_SmoothOn), *(float*)VA(A_SmoothMin), *(float*)VA(A_SmoothMax));
    uo::UObject* gus = uo::FindFirst(uo::FindClass(L"GameUserSettings"));
    for (const wchar_t* f : { L"IsAllowedThrottleEngineTickRate", L"GetThrottleEngineTickRate", L"GetDefaultThrottleEngineTickRate", L"GetFrameRateLimit", L"IsVSyncEnabled" }) {
        uo::Call c(gus, f);
        if (!c.ok()) continue;
        c.run();
        void* native = F<void*>(c.fn, uo::Func_Native);
        Log("fps: %ls -> %d (as float %.1f) native=%llx", f, c.buf[0], *(float*)c.buf.data(), (unsigned long long)((uintptr_t)native - gBase + 0x140000000ull));
    }
    if (gus) Log("fps: settings object %ls byte186=%d", uo::Name(uo::ClassOf(gus)).c_str(), gus[0x186]);
}

void GameTeamsTick() {
    FrameRateTick();
    LARGE_INTEGER f, t0, t1, t2, t3;
    QueryPerformanceFrequency(&f); QueryPerformanceCounter(&t0);
    SyncTeamsOnHost(); QueryPerformanceCounter(&t1);
    SpectateTick(false); QueryPerformanceCounter(&t2);
    ChatTick(); QueryPerformanceCounter(&t3);
    double ms = (t3.QuadPart - t0.QuadPart) * 1000.0 / f.QuadPart;
    if (ms > 20) Log("perf: teams %.1f ms (sync %.1f spectate %.1f chat %.1f)", ms, (t1.QuadPart - t0.QuadPart) * 1000.0 / f.QuadPart,
                     (t2.QuadPart - t1.QuadPart) * 1000.0 / f.QuadPart, (t3.QuadPart - t2.QuadPart) * 1000.0 / f.QuadPart);
}
// Called by the replication pass (repl.cpp) right before actors are sent to the clients.
void GameBeforeReplication(void* nd) { if (lobby::Active()) HostConnectionTeams(nd); }

void InstallGame() {
    if (MH_CreateHook((void*)VA(BuildLocalAddPlayer), (void*)&hkBuildLocalAddPlayer, (void**)&oBuildLocalAddPlayer) == MH_OK)
        Log("team patch installed");
    MH_CreateHook((void*)VA(A_ServerBroadcastChatImpl), (void*)&hkBroadcastChat, (void**)&oBroadcastChat);
    MH_CreateHook((void*)VA(A_RollbackMaxTickRate), (void*)&hkRollbackMaxTick, (void**)&oRollbackMaxTick);
    MH_CreateHook((void*)VA(A_EngineMaxTickRate), (void*)&hkEngineMaxTick, (void**)&oEngineMaxTick);
    MH_CreateHook((void*)VA(A_AddLocalPlayerLeaveReason), (void*)&hkLeaveReason, (void**)&oLeaveReason);
    MH_CreateHook((void*)VA(A_CheckAndShowLeaverMessage), (void*)&hkLeaverMessage, (void**)&oLeaverMessage);
    // SubmitChangePlayerClassInputEventOnServer_Validate checks the player's PlayFab inventory (owned skins etc.).
    // With the backend gone the inventory never loads, so "Fight" failed validation: the host's own request was
    // dropped and a remote player was disconnected. Accept the request.
    void* prev = nullptr;
    PatchVtable(VT_MBPlayerController, 0xe20 / 8, (void*)VA(ReturnTrue), &prev);
    Log("fight-validate patch: was %p", prev);

    // The game mode waits in WaitingForPlayers until this many players joined, else ends with NotEnoughPlayers.
    int32_t two = 2;
    PatchBytes((void*)VA(MinPlayersToStart), &two, sizeof two);
    Log("min-players patch: 2");
}
