# Next session: from working 1v1 to a polished custom multiplayer experience

**Ground rule: nothing is off limits.** Write, use, download or install any tool, library, SDK, server or cloud service needed. Work autonomously per CLAUDE.md: launch, inject, trace, reverse engineer and test yourself, explain results in plain language, and never hand the user test steps.

Read first: `CLAUDE.md` (harness), `docs/v1-implementation.md` (every patch, with addresses), `docs/p2p-feasibility.md` (architecture), memory `v1-status`.

## Vision

Bleeding Edge's servers are gone. This mod should bring back **custom multiplayer that feels like an official feature of the game**: a player launches Bleeding Edge, sees new options in the game's own menus, hosts or browses matches, picks a map and rules, invites Steam friends, and plays. No tools, no config files, no ports, no IP addresses, no "modded" look. Everything the old online backend did for the player should work, or quietly fall back to something sensible: profile, loadouts, settings, names.

**The game boots and plays exactly like normal.** No forced jump into a custom-match screen and no auto-travel straight into a map (v1's `-be1v1host`/`-be1v1join` auto-travel is a stopgap to replace). The player reaches the usual title and main menu, can do anything they normally would (dojo, settings, customisation), and finds custom multiplayer as extra options *inside* the main menu, next to the normal modes. Custom matches are something you choose from the menu, not where the game starts.

Principles:
1. **Seamless.** Zero setup beyond "Steam running". Defaults just work, and failures recover by themselves (retry, fall back, explain in plain words).
2. **Native.** Reuse the game's own UI widgets, menus, fonts, sounds and controller navigation. It should look like Ninja Theory built it (see goal 2).
3. **Authoritative and deterministic.** Rule changes (cheats, dojo settings, teams) go through the rollback sim on the host, never as local hacks, so clients can't desync.
4. **Robust.** Signature-scan instead of hardcoded addresses, check each patch at startup and degrade gracefully, and log everything to `be1v1-<pid>.log`.
5. **Quality of life first.** Every feature should remove a step or a confusion for players.

## State at handoff (2026-11-25)

- **Works:** `BE1v1.exe` launcher, Host/Join with an invite code (Steam account id), **Steam P2P between two accounts (confirmed flawless by the user)**, auto host/join/retry, Train CP lobby, teams 0/1, character select and spawn, rollback input sync, match end, auto-rematch, intro videos skipped, EAC box auto-accepted, Steam relaunch blocked.
- **Unverified:** PvP damage (very likely fine: same deterministic sim).
- **Known limitation:** input events the host injects from outside the normal flow (`MBInputEventChangeTeam`, `MBInputEventTeleportPlayer`) are ignored by the sim, even on the game thread. Goals 1 and 3 probably need a working injection path, so solve this early (see "Open RE questions").
- **Package:** `dist/BE1v1.zip` = `BE1v1.exe` + `be1v1.dll` + `README.txt`. Build with `sh host/build.sh` and `sh launcher/build.sh` (winlibs MinGW g++ 14, MinHook vendored in `host/third_party`).

## Architecture reference (what exists)

| Layer | Mechanism | Key addresses (Steam exe, image base 0x140000000) |
|---|---|---|
| Loading | Launcher starts the game suspended and queues `LoadLibraryW(be1v1.dll)` as an APC before the entry point. Sets `SteamAppId`/`SteamGameId`=1189800 and creates `steam_appid.txt` | — |
| Steam | Skip `SteamAPI_RestartAppIfNecessary` | `0x1408043bb` je→jmp |
| Listen server | `UWorld::Listen` reimplemented, hooked at the `LoadMap` call site | call `0x1425e0537`, `CreateNamedNetDriver(World)` `0x1425c8550`, `SetWorld` `0x14237e2f0`, `FindOrAddCollectionByType` `0x1426262f0`, `InitListen` = vtable slot 75 |
| Handshake | Accept joins without a PlayFab encryption token | `0x14262d02c` je→jmp |
| Replication | `TickFlush` (slot 88) hook: `ReplicationFrame` (+0x348)++, then `CallPreReplication` `0x142041450` and per-actor replicate `0x142204330` for every `bReplicates` actor in `Levels[*]->Actors` (+0xa0) | Ip/Steam NetDriver vtables `0x143489140` / `0x1436BF3F0` |
| Rollback | Engine role comes from its NetDriver (+0x140): server if no ServerConnection. Server opens `NTRollbackChannel` (type 5) to connections with a PC (`0x140418110`) | Role predicates on the interface vtable `0x143420028` (+0x48 server, +0x50 client, +0x58 standalone); AddInputEvent = interface slot 6 (`0x1403f66d0`) |
| Travel | `TickWorldTravel` hook writes `Context.TravelURL` (+0xd0) and `TravelType` (+0xe0) | `0x1425ee300`, `FMemory::Realloc` `0x141440950`, `Browse` `0x1425c4570` |
| Rules | Min players 8→2; Fight validate → true; joiner TeamId=1 in AddPlayer | `0x144f357b8`; `MBPlayerController` vtable `0x1438a5b20`+0xe20; hook `0x1410f9640` (event +0xd8) |
| Convenience | Block intro mp4s (CreateFileW/CreateFile2); MessageBox hook for EAC | `host/src/sys.cpp` |

Useful engine facts: `GEngine` `0x14558F8B0`; `GEngine+0xbb8` world contexts; `FWorldContext`: PendingNetGame +0x1c8, ActiveNetDrivers +0x248, World +0x288; `UWorld`: NetDriver +0x38, AuthorityGameMode +0x140, GameState +0x148, Levels +0x160, WorldSingleton +0x8d8; `MBWorldSingleton.RollbackEngine` +0x3e8; `UNetDriver`: ServerConnection +0x88, ClientConnections +0x90, World +0xc8; `UNetConnection.PlayerController` +0x30; `PlayerState`: PlayerId +0x3c0, TeamId +0x5d4; `StaticConstructObject` `0x1416aac50`. The game mode state machine is in `0x1410f1250` (WaitingForPlayers → PreMatchCountdown → InProgress → PostMatchCountdown). Reflection dumps: `docs/research/*`, full index in `..\bleeding-edge-revival\local\research\reflection\reflection-full.json` (use `tools/re/dumpcls.py`).

## Goals

### 1. Players spawn with their real settings, skins and keybinds (bug fix)
Symptom: players load in before their preferences apply, so keybinds, skins and some graphics settings fall back to defaults. **Only ship a fix if the real values can be retrieved without breaking anything.**
- Find the source of each setting category:
  - local ini (`%LOCALAPPDATA%\Moblade\Saved\Config\WindowsClient\{GameUserSettings,Input}.ini`)
  - the Xbox Live/GRDK profile (title prints "LIVE: Added default user")
  - PlayFab player data/inventory (dead)
  Trace the reads with Frida (`tools/re/frida/attach.js` + agent) during a normal boot. Hook file reads and the profile/settings loader in `MBGameInstance`.
- Timing: the auto-travel fires ~2 s after the title world is idle (`net.cpp`, `gReady > 2.0f`), possibly before the async profile load finishes. Gate the travel on "profile/settings loaded" instead of a timer.
- Loadout: `MBInputEventAddPlayer` (built in `0x1410f9640`, already hooked) carries `SkinDefAssetPath` (+0x118), `CustomisationDefs` (+0xe8), `TauntDefs` (+0x108), `TargetingSettings_{KeyboardAndMouse,Controller}` (+0x130/+0x138), `SuperAbilityIndex` (+0xdc), `ActiveMods` (+0xc8). The change-class event built in `0x1410af1f0` carries the selected loadout. If ownership/inventory came from PlayFab, persist the player's choices locally (capture them on menu change) and fill these fields. Validation is already bypassed.
- Consider "unlock everything" for skins and mods, since there's no backend to earn them anymore (user decision; ask).

### 2. Native in-game UI: host, join, server browser, invites
**User requirement: as native as possible, an extension of the game.** Reuse the game's own UMG widgets, menus, buttons, fonts, styling, sounds and controller/keyboard navigation. New screens are built from or copied off existing game widgets so they're indistinguishable from Ninja Theory's. An overlay (ImGui via D3D11 Present hook) is a last resort, only for something the game's UI truly can't express.
- Entry point: the main menu's existing **Custom Game** flow: `MBCustomGameManager`, custom-lobby widgets, the `TryStartCustomGame` area (`0x140FD8650`), and the `LoadMap`/`LoadMapServerAddress` peer messages. It's backed by Xbox MPSD sessions (HTTP 404 now). Redirect its backend calls to the mod: create lobby, list lobbies, set map/rules, start. The old research in `..\bleeding-edge-revival\docs\findings\two-player-*.md` maps much of this flow.
- Driving UMG from native code: `ProcessEvent` on widget objects, `StaticFindObject`/`StaticConstructObject`, `CreateWidget` (find the addresses). UE4SS can prototype widget manipulation fast (Lua), then port it to native.
- Backend: **Steam lobbies** via `steam_api64.dll` v139 (`Engine\Binaries\ThirdParty\Steamworks\Steamv139`), using the flat API or `SteamMatchmaking()` interface pointers resolved at runtime.
  - Host: `CreateLobby` with metadata (map, mode, rules, version, host SteamID, player count).
  - Browser: `RequestLobbyList` (friends + public, filter by version).
  - Join: travel to `steam.<owner SteamID64>`.
- Steam friends integration: rich presence `connect` and `steam_gameserver`/invite handling, so "Join Game"/"Invite to Game" in the Steam overlay and friends list work. Handle the `+connect` / `GameLobbyJoinRequested_t` callbacks.
- Map/mode picker: list the maps and modes the client already has (`/Game/Levels/*/GameMode_*`, e.g. Train CP). Check each with a two-instance load.
- Hosting and joining are started from these menus, and the travel happens then (reuse the `TickWorldTravel`/`SetTravel` code in `net.cpp`, triggered by UI actions instead of command-line flags).
- Once in-game UI exists, fold `BE1v1.exe` into an auto-loader: a proxy DLL in `Win64` (e.g. `dwmapi.dll`, `version.dll`, `xinput1_3.dll`; old research tried a dwmapi proxy) so players launch from Steam's Play button normally. Keep the early hooks (Steam relaunch, movies) working under proxy loading.

### 3. Dojo multiplayer with persistent dojo settings
- Assets: `MB_RollbackGameMode_Dojo_C` (`bManualMatchStart=true`, no countdowns, `WaitingForPlayersTimeout=0`) and kiosk dojo variants (`docs/findings/mode-selection-assets.md` in the old workspace). Find the dojo map path and host it with `?listen` through the same patches. Check that the min-players and WaitingForPlayers logic still behave.
- Settings: `MBSessionOptions` (`AllowCheats` +0x3b, `InfiniteStamina` +0x3a, `InfiniteSuper` +0x39, `IgnoreCooldowns` +0x38, `PlayerMods` +0x40, `ActiveMapModIds` +0x50) via `NTRollbackWorldSettings.LevelSessionOptions` (+0x5a0). Set them on the host before or at map load so they enter the deterministic sim for everyone. Also investigate `MBInputEventSetEnabledCheats`, `MBInputEventChangeSettings`, `MBInputEventSetPlayerAttribute` (Attribute/Value/bPercent) and the dojo's own menu widgets (reuse them for the toggles, per goal 2).
- "Persist" means settings survive respawns and rematches. Store them in the lobby/session config and reapply on each map load.
- God mode, cooldowns and the like must go through the sim (session options or input events), never as client-side memory pokes.

### 4. Xbox app (Microsoft Store / Game Pass) PC players: hardest, do last
- Get the build (install via the Xbox app). Expect a different exe and hash, a GDK/WinGDK target, a protected `WindowsApps` install, and possibly no Steam.
- **Signature scanning first:** convert every address above into byte patterns (the `tools/re` scripts can generate and verify them), so one DLL supports both builds and survives updates.
- Injection into a Store app: modifiable installs (Xbox app "advanced management") allow a proxy DLL. Otherwise start the exe directly with the early-bird launcher, or attach after launch.
- Transport: Xbox players have no Steam P2P, so add a non-Steam path:
  - UDP hole punching with a small rendezvous server (free cloud VM, a few hundred lines)
  - UPnP port mapping (miniupnpc)
  - an embedded ICE/TURN library (libjuice/libnice)
  Mixed Steam+Xbox lobbies need a common transport, so the lobby list then lives on our own rendezvous server rather than Steam.
- Check network compatibility early: both builds must agree on the engine/game network version (Hello handshake) and the rollback packet format and sim determinism.

## More quality-of-life ideas (pick freely)
- Show real player names (Steam persona) instead of numeric IDs in PlayerStates, the scoreboard and kill feed.
- In-game invite code display and a "copy code" button. Clear connection-status and error messages ("host not found, retrying…", "host left").
- Host migration or graceful "host left": return the client to the menu with a message instead of hanging. The game has unused host-migration strings and `MBHostMigrationManager`.
- More players than 1v1 (2v2, 4v4). Team balancing: alternate TeamId in the AddPlayer hook, and min players becomes configurable.
- Custom rules: points to win, objective timers, respawn times, map rotation (`MBInputEventSetPointsToWin`, `SetObjectivesToActivate`, `SetObjectivesCycleActiveTime`, `StartOvertime`).
- Optional: a setting to skip intro videos/splashes for faster boots (still ending at the normal title and main menu).
- A ping/latency display (`NTRollbackNetworkInterface.AvgLag`).
- An auto-updater for the mod (check GitHub releases on launch).

## Open RE questions
1. **Why are host-injected input events ignored?** Compare with working paths: `SubmitChangePlayerClassInputEventOnServer` → `0x1410af1f0` submits via `(engine+0x30)->vfunc 0x30` and works. Mine (ChangeTeam from the TickFlush hook, Teleport from a Frida thread) didn't. Suspects:
   - the frame-number/time fields on the event
   - a player-ownership check (server-local vs remote player)
   - the "prep" call `0x141696290`
   - submitting outside the engine's input-gather phase
   Trace `PUC_ChangeTeam` (`0x142a909e0`) to see whether it's reached at all.
2. Where player settings, skins and keybinds load from, and when (goal 1).
3. The Custom Game/lobby UI's backend calls and how to feed them (goal 2).
4. Whether the dojo game mode honours `MBSessionOptions` from `LevelSessionOptions` in multiplayer (goal 3).

## Testing strategy
- Two local instances: `tools/harness/duo.ps1`, `pick.ps1`, `ctl.ps1 -Action hold` (posted keys work; posted mouse clicks don't reach Slate, so drive UI via keyboard or `ProcessEvent`). One Steam account means only instance 1 has Steam sockets, so local multiplayer tests use `-be1v1lan` over 127.0.0.1. Steam lobbies and invites need the user plus a friend; batch those checks and ask once.
- Watch logs (`build/run/be1v1-<pid>.log`), Frida traces (`tools/harness/trace.ps1`), and Ghidra decompiles (`tools/re/decomp.py`; the output dir must not contain `!`).
- To test the friend scenario, temporarily move `Win64\steam_appid.txt` aside (the dev PC has a leftover one that hides launch bugs).
- Regression list after every change: auto host/join, teams 0/1, spawn after FIGHT, input sync (same positions on both sides), match end and rematch, intro skip, no EAC box, no Steam relaunch.
