// Gameplay-rule patches for private matches (no PlayFab, no matchmaking).
#include <windows.h>
#include "MinHook.h"
#include "ue.h"
#include "mod.h"

namespace {
constexpr uintptr_t VT_MBPlayerController = 0x1438a5b20;
constexpr uintptr_t ReturnTrue = 0x1402ec6d0;                  // mov al,1; ret
constexpr uintptr_t MinPlayersToStart = 0x144f357b8;           // int, 8 in retail (full 4v4)

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
    void* ev = oBuildLocalAddPlayer(self, pc);
    if (!ev) return ev;
    int team = lobby::Active() ? lobby::MyTeam() : (IsJoinedClient() ? 1 : 0);
    if (team < 0) team = 0;
    Log("adding local player to team %d (was %d)", team, F<int32_t>(ev, AddPlayer_TeamId));
    F<int32_t>(ev, AddPlayer_TeamId) = team;
    return ev;
}
}  // namespace

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
