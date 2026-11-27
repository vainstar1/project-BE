# BE 1v1s: peer-hosted Bleeding Edge matches

## Goal (v1, nothing more)
The user hosts, a friend joins, and they 1v1 on a normal map: load in like normal, fight, match ends. Quality-of-life comes later.
**Top priority: seamless for the friend.** Target experience: download one zip, run one exe, click Join (or paste a code). No UE4SS install, no config editing, no port forwarding.

## The user
Not a programmer. Wants Claude fully autonomous: launch the game, inject, test and reverse engineer yourself, and never hand them test steps. They may be using the PC at the same time, so use game-window-only screenshots, posted keys, and no focus stealing. Explain in plain language.

## Game facts
- Install: `D:\SteamLibrary\steamapps\common\Bleeding Edge\Moblade` (exe `Binaries\Win64\MobladeClient-Win64-Shipping.exe`, SHA-256 `41ab697b4edd3061baff37568de6e9501427374a859b048b3595f29297bfd306`, image base `0x140000000`). UE 4.20.3, Steam build. Steam must be running. EAC is not started when launching the Shipping exe directly.
- Old research workspace (read-only archive): `..\bleeding-edge-revival`. It holds the 108 MB reflection index `local\research\reflection\reflection-full.json`, the Ghidra project `local\research\ghidra` (headless wrapper `tools\research\ghidra\Invoke-FocusedGhidra.ps1`), the pak AES key in `secrets\`, and older findings.
- Full feasibility report: `docs\p2p-feasibility.md`. Key points:
  - Gameplay runs on Ninja Theory's deterministic rollback engine (`NTRollbackEngine`) over a custom UE channel (`NTRollbackChannel`). No gameplay UE RPCs. Rules are `MBInputEvent*` events in the sim.
  - The client runs full matches standalone: `OpenLevel(world, "/Game/Levels/Map_Train/GameMode_CP/Map_Train_CP_Main")` gives `MB_RollbackGameMode`, then `PreMatchCountdown`, then `InProgress`. This works even from the title screen.
  - The rollback server role is in the client: `NTRollbackNetworkInterface::ParsePacket` `0x140409EE0` handles all 22 packet types, and every packet class (vtables `0x14341ED28`..`0x14341EFA8`, IDs 6–22) has send sites.
  - Compiled out (Client target, `WITH_SERVER_CODE=0`): `UWorld::Listen` (always false) and `UNetDriver::ServerReplicateActors` (vtable slot 85 = `xor eax,eax; ret`). Present: `UIpNetDriver::InitListen` `0x1404CBE50` (slot 75), `USteamNetDriver::InitListen` `0x140804110`, `UNetDriver` vtable `0x143FDC328`, server login handshake, `UActorChannel::ReplicateActor`.
  - `GameNetDriver` is `SteamNetDriver` with `bAllowP2PPacketRelay=true`, so Steam P2P relay is available.
  - Custom paks are rejected (signed build). v1 shouldn't need new assets.
  - The official custom-lobby service (Xbox MPSD) returns 404 and dies with the servers. Don't build on PlayFab or Xbox sessions.
- Live vtable dump of the key classes: `docs\research\vtables-live-20261124.json`. Reflected RPCs: `docs\research\reflected-rpcs.txt`. Rollback class layouts: `docs\research\rollback-classes.txt`, `docs\research\reflection-layouts.h`.
- UE4SS UFunction layout is shifted +0x20 vs stock 4.20, fixed by `tools\harness\ue4ss\MemberVariableLayout.ini`. Don't remove it.

## Test harness (`tools\harness`)
- Build: `sh host/build.sh` (DLL) and `sh launcher/build.sh` (BE1v1.exe, devlaunch.exe), winlibs MinGW g++ 14. Output in `build\`.
- `ctl.ps1 -Action boot [-Instance 2] [-NoNative] [-ExtraArgs '-be1v1host -be1v1lan']`: starts the game through `build\devlaunch.exe` with a fresh copy of be1v1.dll (log: `build\run\be1v1-<pid>.log`), injects the UE4SS probe, waits until it reports in (~15 s; intro videos are skipped). Instance 2 uses the hard link `BEInstance2-Win64-Shipping.exe` and its own probe folder `ue4ss2` (synced on each launch). Other actions: `launch|inject|shot|post|hold|key|kill|status|dismiss`.
- The BEProbe mod polls `ue4ss\cmd.txt` (or `ue4ss2\`) and runs it as Lua on the game thread; send with `lua.ps1 [-Dir ue4ss2] -Code '...'`. Helpers: `snapshot(label)`, `world()`, `live(all("Class"))`, `call(o,"Fn",...)`, `get(o,"Prop")`, `plog(...)`, `fname(o)`, `cls(o)`, `openmap(url)`, `console(cmd)` (console is disabled in this build; use `openmap`).
- v2 lobby testing (dev backend `-be1v1devlobby`: lobby data in `%TEMP%\be1v1-devlobby`, transport 127.0.0.1): `menu.ps1 [-Instance N] [-ExtraArgs ..] [-NoBoot]` boots to the main menu (instance 2 can't log in, so it stays on the title screen: use it as host or as a member without UI). `lobbytest.ps1 [-Map N] [-Start]` (inst 1 hosts, inst 2 joins), `membertest.ps1` (roles swapped), `browsetest.ps1` (browse, join, back, slot click, LEAVE). `dev.ps1 [-Instance N] -Cmd "..."` sends be1v1.dll dev commands: `lobby create|leave|join <id>|start|team <n>|tomenu|status`, `ui ask|list|msg|hooks|press <ButtonName>|slot <team> local|empty|other`, `cursor x y|cursor off`. Lua helpers (reloaded each call from `helpers.lua`): `cgscreen()`, `cgpress("start|settings|maps|invite|leave")`, `inscreen(cls)`, `fns`, `props`, `dumpstruct`. UE4SS `call()` silently fails on functions with parameters; use `dev.ps1 ui press/slot` for button events.
- `duo.ps1`: kill both, boot host, `openmap('<Train>?listen?bIsLanMatch')`, boot instance 2, join 127.0.0.1:7777. `pick.ps1 -Instance N -Hero Ninja` selects a hero and presses FIGHT (posted Space x2). Hero names: Azrael Bruiser Buttercup Cass Gizmo KeyboardGuy Kulev Makutu Ninja(Daemon) Miko Nidhoggr Prism Wrekko.
- `shot` captures the game window only. `post -Keys 20` / `hold -Keys "57,2500"` post keys without focus (gameplay input works). Posted mouse clicks don't work. Enter opens text chat.
- Every launch shows an EasyAntiCheat "IGameClient" message box; be1v1.dll auto-accepts it, and `dialogwatch.ps1` (start hidden) dismisses it for runs without the DLL.
- Tracing: `trace.ps1 -Instance N -Agent join.js` attaches Frida (agents in `tools\re\frida`, prelude gives `VA()`, `hook()`, `fstr()`, `bt()`). Decompile: `python tools/re/decomp.py <outdir> 0xADDR:label ...` (headless Ghidra from the old workspace; outdir must not contain `!`). `xref.py`, `rel32.py`, `refscan.py`, `structrefs.py` (`callers()`), `bedis.py`, `dumpcls.py <reflection-full.json> <regex>` as before.
- The game log is useless (almost all categories compiled out). One Steam account: only the first game process gets Steam sockets, so local two-instance tests use IP (`-be1v1lan`, 127.0.0.1).
- Pitfalls: malformed `UE4SS-settings.ini` silently disables mods. Bash heredocs, sed and Python string literals eat Windows backslashes, and PowerShell treats `$Map?listen` as one variable name. Don't name a Python script `dis.py`.

## Layout
`host\` native DLL (be1v1.dll) · `launcher\` BE1v1.exe (installer + Launch_Game.exe replacement) + devlaunch.exe + README.txt · `tools\` dev only · `docs\` · `dist\BE1v1\` + `dist\BE1v1.zip` package.
Releases: bump `BE1V1_VERSION` in `host\src\mod.h`, commit + push `main` (remote `vainstar1/project-BE`), then `tools\release.ps1 -Notes "..."` (builds, zips, publishes `v<version>` with `BE1v1.zip`). The installed mod checks the latest release at start-up. Updates are applied by the *old* version's code, so updater bugs only get fixed for the release after the fix.

## Status (2026-11-26, v2.3.0 released)
v2 is described in `docs\v2-implementation.md` (v2.2.0 and v2.3.0 sections at the end). v2.2.0: smooth matches, chat, fighter select, spectating, rules, rebuilt lobby UI, Official Custom Queue row, no official leave reports. v2.3.0: **3-4 teams** (up to 4v4v4v4; Objective Control capture points work for every team; teams 3/4 yellow/green; shared bases with spawn-room invisibility; N-team HUD row; lobby 2x2 columns), optional **Knockouts Only** scoring (Team Brawl, any team count) and **Steam avatars** in the lobby and on the loading screen. Power Collection is two-team only (3-4 teams play the arena's Objective Control version). Lobby protocol 4. Tested locally with two instances (one Steam account): 3-team captures and takeovers, KO scoring, per-player Victory/Defeat, spawn sharing, HUD, lobby, settings, 2-team regression.
Needs a real two-account test: Steam invites/"Join Game", friends-only visibility, host-left handling, chat over Steam, avatars of other accounts, 3-4 real players in Team Brawl. Not done: dojo settings persistence, keyboard-only team switching can't be tested with posted keys (mouse/Enter on slots and LT/RT work), Xbox build.
