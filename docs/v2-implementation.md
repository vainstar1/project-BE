# v2 implementation notes (2026-11-25, v2.1.1)

How the custom-game mod works on top of the v1 patches (`docs/v1-implementation.md`). Exe SHA-256 `41ab697b…bfd306`.

## Modules (host/src)

| File | Role |
|---|---|
| `uobj.*` | Native reflection: GUObjectArray `0x14507ff60`, FName ctor `0x1414f3970` / ToString `0x14150ac20`, FText from FString `0x141454760`, ProcessEvent = UObject vtable slot 0x41 (`0x141686380`). Layout: UStruct is 0x20 larger than stock (Super 0x30, Children 0x38, Size 0x40; UFunction Flags 0xa8, ParmsSize 0xae, Func 0xd0; UProperty Offset 0x44, UBoolProperty ByteOffset/Mask 0x71/0x72). `FindAll` uses an incremental class index (`IndexStep`, 12k objects per frame); entries are validated through the object array only, never by dereferencing (objects can be freed). `uo::Call` runs a UFunction by name with named parameters. |
| `steam.*` | Flat Steamworks 1.39 API from the game's `steam_api64.dll` (SteamMatchMaking009, SteamFriends015, SteamUser019, SteamUtils008). Async results polled with `IsAPICallCompleted`; callbacks 333 (lobby join requested), 337 (rich presence join) through a hand-built CCallbackBase. |
| `lobby.cpp` | Lobby state + backends (Steam lobbies; `-be1v1devlobby` file backend in `%TEMP%\be1v1-devlobby` for local tests). Drives the dormant **CustomGameScreen** through **MBCustomGameManager** fields (MemberList 0x80, Teams 0xe0, Spectators 0x110, MapRoster 0x128, CurrentMap 0x138, GameName 0x160, Privacy 0x170, MaxRoster 0x174, TeamsLocked 0x178, IsLeader 0x179). Host publishes lobby data (`teams`, `maps`, `rules`, `seq`, `state`, `addr`, …); members mirror it. |
| `ui.cpp` | Blueprint event interception by swapping `UFunction::Func` for a thunk (all Invoke paths hit it). Main menu relabel (CUSTOM QUEUE → CUSTOM GAME), lobby browser and prompts on the game's system message screen (`ShowSystemMessageInfo` with `DefaultYesNoSystemMessageScreen_C`; list rows are `PromptListButtonTemplate_C` added into its `VerticalBox_2`). |
| `settings.cpp` | Adds rule rows to the Custom Game settings panel (`Widget_ShifterOption_C` / `Widget_TickBoxOption_C` created after the panel's open transition — rows added earlier never draw values). |
| `rules.cpp` | Applies rules on every machine when the match world streams in: `MBCapturePointManagerData` PointsRequiredToWin 0x4c, InfiniteCycle 0x98, CycleActiveTime 0x9c; `MBCapturePointData` CaptureTime 0x220. Map modifiers: sets the `MapMods.ActiveMapMods` CVar string (`*0x145341278`) and calls `TrySetActiveMapModsFromCVar` `0x14102c6b0` from a hook on the manager's world init `0x14101a6d0` (the game only did this offline). |
| `game.cpp` | Teams: joiners put `?BETeam=<n>` in the join URL; the host finds it in the connection's request URL and sets `PlayerState.TeamId` (0x5d4) — fixes shared fighter rosters. Spectators (team -1): no AddPlayer event (`0x1410f9640` returns null, both callers handle it), host sets `bOnlySpectator`/`bIsSpectator` (match no longer waits for them), client calls `StartSpectating` and closes `FE_HeroSelectScreen_C` → native spectator HUD. |
| `update.cpp` | GitHub `releases/latest` of `vainstar1/project-BE` (WinHTTP, anonymous). Newer tag → native Yes/No prompt on the main menu; "Later" turns the billboard's Leaderboards line into "Update". Update: download `BE1v1.zip`, unpack with `tar.exe` (PowerShell `Expand-Archive` fallback), rename the loaded DLL to `.old`, copy new files, run `BE1v1.exe --relaunch <pid>` which refreshes `Launch_Game.exe` and restarts through `steam://rungameid/1189800` (`-be1v1direct` test runs restart Launch_Game.exe directly). |

## Lobby screen hooks (game addresses)

IsInCustomGameLobby `0x1411058f0` (false while the player stepped out with BACK, so the screen closes itself and the main menu doesn't reopen it), IsLocalPlayerLobbyLeader `0x1411059d0`, StartGame `0x14110cdb0`, menu SetPlayerTeamId `0x140fcfdc0` / SetLocalTeamId `0x140fcf9e0`, CanStartGame `0x140fbd490`, TryStartGame `0x140fd8650`, InviteFriend `0x141105390`, TryGetLocalTeam `0x14110fd30`, RequestLocalTeamChange `0x141110290`, exec LeaveLobby `0x1412f6250` / LeaveGame `0x141309e10`, GetMapList `0x141010c40` (replaced by our list: 7 CP + 7 Power Collection arenas, Dojo, `MB_DefaultRollbackMap` with a synthetic row). Blueprint events: `FE_MainMenuScreen_C.OnCustomQueuePressed` (browser), `.OnLeaderboardButtonPressed` (update), `CustomGameScreen_C` invite/leave bound events, `CustomGame_PlayerSlot_Queue_C.OnPressed_Event` (mouse team switching), `PromptListButtonTemplate_C` pressed event (list rows, LEAVE = the screen's hidden debug buttons moved into HostView/ClientView).

## Known gaps

- Steam invites and friends-only visibility are untested with two real accounts.
- Dojo settings are not carried between sessions; Power Collection score rule not wired (`MBSeedManagerActorData.SeedsRequired` 0x188 is a struct).
- Spectator HUD shows replay controls (rewind/fast-forward) that do nothing in live play.
