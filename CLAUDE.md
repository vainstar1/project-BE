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
- `ctl.ps1 -Action launch|inject|shot|post|key|kill|status [-TargetPid N] [-Dll path] [-Keys ..] [-Out png]`
  - `inject` LoadLibrary's `tools\harness\ue4ss\UE4SS.dll`. The BEProbe mod polls `ue4ss\cmd.txt` every second, runs it as Lua on the game thread, and logs to `ue4ss\probe.log`. Lua helpers: `snapshot(label)`, `world()`, `live(all("Class"))`, `call(o,"Fn",...)`, `get(o,"Prop")`, `plog(...)`, `fname(o)`, `cls(o)`.
  - `shot` captures the game window only (PrintWindow). `post -Keys 0D` posts virtual keys without focus. Posted mouse clicks don't work.
- `vtables.ps1` reads live vtables for CDO addresses that the probe logs as `ADDR <path> 0x...`. `readconsole.ps1` dumps the UE4SS console; run it in a separate powershell process.
- Typical boot today: launch, wait ~40 s, `key {ENTER}` (or skip), inject, wait ~20 s, then send Lua. **Planned improvement:** a single `boot` command that polls for readiness instead of fixed sleeps, at low resolution, loading straight into a map.
- Second instance on one PC: the game kills itself if another process has the same exe name (check at `0x14153EE70`). Hard-link the exe under a different name in `Binaries\Win64` (e.g. `BEInstance2-Win64-Shipping.exe`), launch that, and delete the link afterwards. Give the second instance its own UE4SS staging copy so the `cmd.txt` files don't collide.
- Pitfalls: any malformed line in `UE4SS-settings.ini` makes UE4SS silently use defaults (console on, no mods, no log). Bash heredocs and sed eat Windows backslashes, so use Python with raw strings or forward slashes. Don't name a Python script `dis.py`.
- `tools\re`: Python RE helpers. `xref.py` builds a cached lea/pdata index in its own folder; `rel32.py` builds the rel32 target index needed by `refscan.py`/`structrefs.py`; `bedis.py` is a capstone disassembler; `pkttypes.py` maps packet vtables. Python 3.11 with capstone, pefile and numpy. `tools\re\frida\exittrace.js` is an example Frida spawn and hook, run with the node and frida from `..\bleeding-edge-rea-research\tools` (node v22, frida 17).

## Layout
`host\` native host DLL · `launcher\` friend-facing exe · `lua\` UE4SS glue (if any ships) · `tools\` dev only · `docs\` · `dist\` built package.

## v1 plan
1. Faster `boot` harness, plus two instances on this PC.
2. Host side (native DLL): create the `GameNetDriver` and `InitListen` (reimplement `UWorld::Listen`), then get instance 2 to complete the UE handshake to instance 1 via `open 127.0.0.1`.
3. Replace stubbed `ServerReplicateActors` with a minimal loop (GameState, PlayerControllers, PlayerStates) so the joining client gets its controller.
4. Trace and enable the host's rollback server path and `NTRollbackChannel` for the joiner. Both clients spawn and fight on Train CP, and the match ends normally.
5. Switch transport to Steam P2P (SteamNetDriver + Steam ID join) for internet play.
6. Package: one launcher exe that injects the DLL and offers Host/Join with a Steam invite or code.
