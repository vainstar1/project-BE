# v1 implementation notes (2026-11-25)

How the 1v1 build works, what was verified, and the addresses it depends on (exe SHA-256 `41ab697b…bfd306`).

## Pieces

- `build/BE1v1.exe` (`launcher/src/main.cpp`): friend-facing window. Finds the game via Steam (`libraryfolders.vdf` + `appmanifest_1189800.acf`), checks Steam is running, starts the game suspended and loads `be1v1.dll` with an early-bird APC (`launcher/src/inject.cpp`) so hooks are in place before the game's entry point. Host passes `-be1v1host` (plus `-be1v1lan` for IP mode), join passes `-be1v1join=<steam.SteamID64 | ip:port>`. Invite code = Steam account id (`HKCU\Software\Valve\Steam\ActiveProcess\ActiveUser`); SteamID64 = code + 76561197960265728. Switches `--host`, `--join <code>`, `--lan` drive the window from the command line.
- `build/be1v1.dll` (`host/src`): all patches, applied in `DllMain`. Logs to `be1v1-<pid>.log` next to the DLL, including a first-chance crash logger.
- `build/devlaunch.exe`: same injector for the harness.

## Patches (host/src)

| What | Where | Why |
|---|---|---|
| No Steam relaunch | `sys.cpp`: byte `0x1408043bb` `je`→`jmp` in `FOnlineSubsystemSteam::InitSteamworksClient` (skips `SteamAPI_RestartAppIfNecessary`); launcher sets `SteamAppId`/`SteamGameId`=1189800 for the child and creates `steam_appid.txt` if missing | Without an app id Steam killed our process and relaunched the game through Steam (+EAC) with a "Launch Game with custom arguments" prompt, without the DLL. Found in the first real test (friend's PC had no `steam_appid.txt`; the dev PC had a leftover one) |
| Skip intro movies | `sys.cpp`: CreateFileW/CreateFile2 fail for NT/Xbox/PlayFab/UE4 logo mp4s and OpeningCine | Faster boot (~15 s to title) |
| Auto-accept EAC box | `sys.cpp`: MessageBoxW/A return IDOK when text contains "EasyAntiCheat" | Launching without EAC shows "Failed to create IGameClient instance" |
| `UWorld::Listen` | `net.cpp`: call at `0x1425e0537` in `UEngine::LoadMap` (target was the shared "return false" stub `0x1402ec800`) | Reimplemented: `CreateNamedNetDriver(World)` `0x1425c8550`, `World->NetDriver` (+0x38), `SetWorld` `0x14237e2f0`, level collections 0 and 2 via `0x1426262f0` (+0x10), `InitListen` (vtable slot 75) with `World+0x28` as FNetworkNotify |
| Encryption token | `net.cpp`: byte `0x14262d02c` `je`→`jmp` in `UWorld::NotifyControlMessage(NMT_Hello)` | `[PacketHandlerComponents] bForcePacketEncryptionInShipping=true` rejects joins without a PlayFab token ("Encryption token failure") |
| Auto-travel | `net.cpp`: hook `UEngine::TickWorldTravel` `0x1425ee300`; writes `Context.TravelURL` (+0xd0) / `TravelType` (+0xe0) with `FMemory::Realloc` `0x141440950` | The command-line map URL is ignored (always boots to the title); joins retry every 8 s |
| Actor replication | `repl.cpp`: vtable slot 88 (`TickFlush`) of Ip/SteamNetDriver; per tick `ReplicationFrame` (+0x348)++, then for every `bReplicates` actor in `World->Levels[*]->Actors` (+0xa0): `CallPreReplication` `0x142041450` and the replay recorder's per-actor routine `0x142204330(driver, actor, conn, false)` | `ServerReplicateActors` is `return 0` and `TickFlush` never calls it in the Client build |
| Fight validation | `game.cpp`: `MBPlayerController` vtable `0x1438a5b20` +0xe20 → `return true` | `SubmitChangePlayerClassInputEventOnServer_Validate` checks the PlayFab inventory; failure dropped the host's request and **disconnected** remote players (the "press FIGHT, never spawn" bug) |
| Min players | `game.cpp`: int `0x144f357b8` 8 → 2 | Game mode waits in WaitingForPlayers for 8, then ends with NotEnoughPlayers |
| Teams | `game.cpp`: hook `0x1410f9640` (builds the local `MBInputEventAddPlayer`); on a joined client set TeamId (+0xd8) = 1 | TeamId is copied from the replicated PlayerState (0 for all). Host-injected `MBInputEventChangeTeam`/`TeleportPlayer` events are ignored by the sim |

## Things that just worked once the above was in place

- The rollback engine picks its role from its net driver (`+0x140`): server if no `ServerConnection`, client if it has one, standalone if none. With the listen driver present at map load, the host's engine is a server and opens an `NTRollbackChannel` (channel type 5) to each client that has a PlayerController.
- Character select RPCs, spawn, rollback input sync (identical positions on both sides), match end (`PostMatchCountdown`/`TeamWon` on both, then both return to the title), and then the launcher's auto-travel starts the next match.
- `UWorld::GetNetMode()` reports NM_Client on the host (client build); no visible problem so far.

## Not verified

- Steam P2P between two different Steam accounts. On one account only the first game process gets Steam sockets, so local tests use `-be1v1lan` over 127.0.0.1. Verified: the host's SteamNetDriver listens with a Steam socket (`+0x550` set, passthrough `+0x568` = 0) and a Steam-capable joiner uses `SteamNetDriver::InitConnect` for `steam.<id>`.
- Damage between players (couldn't navigate the fighters together with posted keys).

## Harness additions

`ctl.ps1 -Action boot [-Instance 2] [-NoNative] [-ExtraArgs ...]` (launches through devlaunch with a fresh DLL copy, injects the UE4SS probe, auto-dismisses dialogs), `duo.ps1` (host + join over 127.0.0.1), `pick.ps1 -Instance N -Hero Ninja` (select + FIGHT via posted Space), `ctl.ps1 -Action hold -Keys "57,2500"`, `trace.ps1 -Agent x.js` (Frida agents in `tools/re/frida`), `tools/re/decomp.py OUTDIR addr:label…` (headless Ghidra; OUTDIR must not contain `!`).
