// Gameplay-rule patches for private matches (no PlayFab, no matchmaking).
#include <windows.h>
#include "MinHook.h"
#include "ue.h"
#include "mod.h"
#include "uobj.h"
#include <cwchar>

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
void SpectateTick(bool request) {
    // Steps: StartSpectating on the local controller (puts the world into spectator mode), then close fighter
    // select once the match has left WaitingForPlayers, which reveals the spectator HUD.
    static bool want; static DWORD since; static void* started; static int closed;
    if (request && !want) { want = true; since = GetTickCount(); started = nullptr; closed = 0; }
    if (!want) return;
    if (!lobby::Active() || lobby::MyTeam() >= 0 || !net::IsConnectedClient()) { want = false; return; }
    DWORD now = GetTickCount();
    if (now - since < 1000) return;
    since = now;
    uo::UObject* pc = nullptr;
    for (uo::UObject* p : uo::FindAll(uo::FindClass(L"MBPlayerControllerBase"))) {
        uo::Call loc(p, L"IsLocalController");
        if (loc.ok() && loc.run().get<bool>(L"ReturnValue")) { pc = p; break; }
    }
    if (!pc) return;
    if (started != pc) {
        Log("spectate: starting spectator mode");
        uo::Call(pc, L"StartSpectating").run();
        uo::Call(pc, L"ServerStartSpectating").run();
        started = pc;
        return;
    }
    uo::UObject* hs = uo::FindClass(L"FE_HeroSelectScreen_C");
    uo::UObject* fe = uo::FindFirst(uo::FindClass(L"MBFrontEnd"));
    bool open = false;
    for (uo::UObject* s : hs ? uo::FindAll(hs) : std::vector<uo::UObject*>()) {
        uo::Call par(s, L"GetParent");
        if (par.ok() && par.run().get<uo::UObject*>(L"ReturnValue")) open = true;
    }
    if (open && fe) { uo::Call(fe, L"PopScreen").run(); Log("spectate: closed fighter select"); closed++; }
    // Keep watching for a while: fighter select can be pushed again when the match state changes.
    if (closed > 4) want = false;
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
    // Scan the connection object for the request URL (an FString containing our option).
    for (size_t off = 0x60; off < 0x2000; off += 8) {
        FString* s = (FString*)(conn + off);
        if (!ReadableString(s)) continue;
        const wchar_t* t = wcsstr(s->Data, L"BETeam=");
        if (t) return _wtoi(t + 7);
    }
    return -2;
}
int gCtrlPSOff = -1;
void SyncTeamsOnHost() {
    if (!lobby::Active() || !net::IsHosting()) return;
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 500) return;
    last = now;
    void* world = net::World();
    void* nd = world ? F<void*>(world, Off::World_NetDriver) : nullptr;
    if (!nd) return;
    if (gCtrlPSOff < 0) gCtrlPSOff = uo::PropOffset(uo::FindClass(L"Controller"), L"PlayerState");
    if (gCtrlPSOff < 0) return;
    auto setTeam = [](uint8_t* pc, int team) {
        uint8_t* ps = pc ? F<uint8_t*>(pc, gCtrlPSOff) : nullptr;
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
    };
    auto& conns = F<TArray<uint8_t*>>(nd, Off::ND_ClientConnections);
    for (int i = 0; i < conns.Num; i++) {
        uint8_t* c = conns.Data[i];
        uint8_t* pc = c ? F<uint8_t*>(c, Off::Conn_PlayerController) : nullptr;
        if (!pc) continue;
        int t = TeamFromConnection(c);
        if (t >= -1) setTeam(pc, t);
    }
    // The host's own player
    for (uo::UObject* pc : uo::FindAll(uo::FindClass(L"MBPlayerController"))) {
        uo::Call c(pc, L"IsLocalController");
        if (c.ok() && c.run().get<bool>(L"ReturnValue")) setTeam(pc, lobby::MyTeam());
    }
}
}  // namespace

void GameTeamsTick() { SyncTeamsOnHost(); SpectateTick(false); }

void InstallGame() {
    if (MH_CreateHook((void*)VA(BuildLocalAddPlayer), (void*)&hkBuildLocalAddPlayer, (void**)&oBuildLocalAddPlayer) == MH_OK)
        Log("team patch installed");
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
