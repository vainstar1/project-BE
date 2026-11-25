# P2P / custom-match feasibility (2026-11-24)

Question: can Bleeding Edge be modded so players host their own matches with custom rules (any player count, custom objectives, mid-game changes), and keep playing after the official servers shut down?

**Verdict: yes, it's technically feasible.** The retail client already contains the full authoritative game logic and the rollback-netcode server role. What's missing is a thin layer of Unreal Engine "listen server" plumbing that the Client build compiled out. That gap can be filled with a native mod. No component is missing that would require rewriting game logic. The work is substantial reverse-engineering and C++, not a config tweak.

Executable for all results: `MobladeClient-Win64-Shipping.exe`, SHA-256 `41ab697b…bfd306`, unchanged after testing.

## What was proven by running the game

| Test | Result |
|---|---|
| Load a real PvP map with no server (Train CP, from the main menu) | Works. `MB_RollbackGameMode` (the server-side game mode) runs locally, the rollback engine ticks at full rate, character select appears, match state goes `PreMatchCountdown` → `InProgress`. |
| Same, from the **title screen** (before "Press Enter", before the PlayFab sign-in step), on Sewers CP | Works. The match world boots identically. The game's front-end login flow is not a hard gate for gameplay. |
| Drive match rules from a mod | `MBRollbackGameMode.Debug_EndGame()` moved the match to `PostMatchCountdown` with `MatchEndReason=TeamWon`; the full post-match flow (Final Play / Progression / Highlights / Stats) ran. `SelectCharacterOnServer` RPC advanced character select. |
| Two game instances on one PC | Blocked by a process-name check (window creation → `0x14153EE70` counts processes with the same exe name → `TerminateProcess`). **Bypassed** by running the second copy through a renamed hard link. Both instances then ran fine. Local two-client testing is possible. |

## What static analysis established

1. **Gameplay doesn't use normal Unreal replication.** The game runs on Ninja Theory's own rollback engine (`NTRollbackEngine`, `NTRollbackMachine`, `NTRollbackChannel`), a deterministic simulation with per-frame hash checks between client and server. Of 185 reflected network RPCs, **none carry gameplay input**. They cover character select, chat, voice, reports and replay transfer. Combat, movement and objectives all flow through `NTRollbackChannel`.
2. **Match rules are events inside the deterministic simulation.** There are `MBInputEvent*` classes for `SetPointsToWin`, `SetTeams`, `StartGame`, `EndGame`, `StartOvertime`, `ChangeSettings`, `SetObjectivesToActivate`, `SetObjectivesCycleActiveTime`, `TeleportPlayer`, `SetPlayerAttribute`, `SetEnabledCheats`, `AddPlayer`/`RemovePlayer`, `RespawnPlayers`, `ChangeTeam`, and more. A host that injects these gets synchronized rule changes on every client for free. `MBSessionOptions` already has `AllowCheats`, `InfiniteStamina`, `InfiniteSuper`, `IgnoreCooldowns`, `PlayerMods` and `ActiveMapModIds`.
3. **The rollback *server* role is compiled into the client.**
   - `NTRollbackNetworkInterface::ParsePacket` (`0x140409EE0`) has a 22-way switch, and **all 22 packet types have real handlers** (none fall to "unhandled"). That includes client→server packets such as ClientReady, ClientAddPlayers and RequestGameState.
   - All 17 packet classes (`FNTRollbackPacket` subclass vtables `0x14341ED28`…`0x14341EFA8`, type IDs 6–22) have send-side constructor sites in addition to the receive factory.
   - Also present: `ENTRollbackEngineEvaluationMode::DedicatedServer`, the reflected `MBHostMigrationManager` (`bIsClient`, `bHostMigrationInProgress`, `OldRollbackEngine`, `WaitingForPlayerIDs`) inside `MBWorldSingleton`, and "Can't become server…" strings. Ninja Theory designed clients to be able to take over as host.
4. **Unreal's listen-server pieces were compiled out (Client target ⇒ `WITH_SERVER_CODE=0`, verified in UE 4.20 UBT `TargetRules.cs:1298`):**
   - `UWorld::Listen` returns false. The "Failed to listen" literal is absent, and earlier `open map?listen` attempts created no NetDriver.
   - `UNetDriver::ServerReplicateActors` (vtable slot 85) is literally `xor eax,eax; ret` in all three net drivers. Slot layout was matched against the UE 4.20 header.
   - `ServerTravel` / `ProcessServerTravel` are removed.
5. **Still present and usable:** `UIpNetDriver::InitListen` (`0x1404CBE50`), `USteamNetDriver::InitListen` (`0x140804110`), the server-side login/join handshake in `UWorld::NotifyControlMessage`, `TickDispatch`, `ProcessRemoteFunction`, and per-actor `UActorChannel::ReplicateActor` (kept because the replay recorder uses it).
6. **NAT traversal comes for free.** The configured `GameNetDriver` is `SteamNetDriver` (fallback `IpNetDriver`) with `bAllowP2PPacketRelay=true`, so Steam P2P with Valve relay is already in the shipped client.
7. **Custom assets are blocked by pak signing.** The prior model-swap test showed the signed build rejects an unsigned pak and loose files. Rule/gameplay mods don't need new assets. New maps or models would need a signature-check bypass (a known UE4 technique) or reuse of existing assets.

## What a P2P mod has to build

**Route A, recommended: "client becomes host".** One player's game acts as the server, using the game's own rollback server code.

1. Re-implement `UWorld::Listen` in a native DLL: create the named `GameNetDriver`, set it on the world, call `InitListen`. Six engine calls; addresses come from vtables and signatures.
2. Replace the stubbed `ServerReplicateActors` with a minimal loop that replicates the few Unreal actors the game still relies on (GameState, PlayerControllers, PlayerStates) using the surviving `ReplicateActor`. This is the biggest engine-level job.
3. Put the host's rollback engine into server mode and open `NTRollbackChannel`s for joining clients. `MBRollbackGameMode` login/PostLogin logic is present. Exactly how it attaches the rollback server needs runtime tracing.
4. Lobby/session: skip PlayFab/Xbox session creation (the custom-lobby service already returns HTTP 404). Use Steam lobbies (the `CreateLobby` implementation exists) or plain IP/Steam-ID join. Also skip PlayFab server allocation, XP and stat uploads.
5. Rules: inject `MBInputEvent*` on the host for score thresholds, teams, objectives and respawns. Player count follows from slot/roster logic that already uses dynamic counts.
6. Mid-game map change: `ServerTravel` is compiled out. Instead the host sends a "load map" message (the custom-game lobby already has a `LoadMap`/`LoadMapServerAddress` peer message) and everyone reconnects, or the travel is implemented natively.

**Route B, fallback: lockstep overlay.** Every peer runs the match standalone (already proven to work), and a mod exchanges player inputs over its own UDP/Steam socket, injecting remote players into each local rollback engine. This avoids all Unreal server plumbing but means re-implementing what NT's network interface already does. Consider it only if Route A stalls on step 2 or 3.

## Risks and unknowns

- **Desync:** the simulation is deterministic by design (hash-checked against the official server), but cross-machine determinism of this client-only build hasn't been tested between two PCs yet.
- **Rollback server activation path:** the code exists, but the call sequence that turns a client's engine into the server isn't traced yet. That's the next runtime target, either by tracing a Dojo/kiosk local machine group or hooking `ParsePacket` server cases.
- **Backend shutdown:** the title screen signs in to Xbox Live (GRDK) and PlayFab. Gameplay boots without the PlayFab front-end step, but behaviour when those services are completely gone (e.g. a startup hang or error loop) can't be simulated without admin rights to firewall the game. A launcher/mod that skips straight to a map is the mitigation, and that path is already proven.
- **Pak signing** blocks new assets until bypassed.
- **Never use these mods on the official servers.** EAC components exist and official servers can kick or ban.

## Tooling left in place (local, gitignored)

- `local/runtime/feasibility/` is a UE4SS probe with a file command channel: write Lua to `cmd.txt`, results appear in `probe.log`, and calls run on the game thread. `ctl.ps1` handles launch, inject (`-TargetPid`, `-Dll`), game-window-only screenshots, posted keys and kill. `vtables.ps1` dumps live vtables and `readconsole.ps1` reads the UE4SS console.
- `local/runtime/feasibility2/` is a second probe copy for a second instance.
- Second instance: create a hard link with a different exe name in `Binaries/Win64` (e.g. `BEInstance2-Win64-Shipping.exe`), launch it, and delete it afterwards.
- UE4SS silently falls back to defaults if `UE4SS-settings.ini` has a parse error. The console then shows "IniParser failed to parse" and no mods load.
