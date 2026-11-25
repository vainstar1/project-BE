# Static UE4.20 reflection recovery

Source SHA-256: `41ab697b4edd3061baff37568de6e9501427374a859b048b3595f29297bfd306`

These are source-layout-correlated descriptors, not a live SDK. Offsets are hexadecimal.
Bool offsets require recognized setter decoding. Nested container descriptors are omitted from member rows.

## AIController

Class params `0x1443e4fd0`; resolver `0x1412c59d0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ReceiveMoveCompleted | MulticastDelegate | 0x490 | 0x14522db50 |
| DefaultNavigationFilterClass | Class | 0x488 | 0x14522db90 |
| CachedGameplayTasksComponent | Object | 0x480 | 0x14522dbe0 |
| Blackboard | Object | 0x478 | 0x14522dc20 |
| ActionsComp | Object | 0x470 | 0x14522dc60 |
| PerceptionComponent | Object | 0x468 | 0x14522dca0 |
| BrainComponent | Object | 0x460 | 0x14522dce0 |
| PathFollowingComponent | Object | 0x458 | 0x14522dd20 |
| bSetControlRotationFromPawnOrientation | Bool | unresolved | 0x14522dd60 |
| bWantsPlayerState | Bool | unresolved | 0x14522ddb0 |
| bAllowStrafe | Bool | unresolved | 0x14522de00 |
| bSkipExtraLOSChecks | Bool | unresolved | 0x14522de50 |
| bLOSflag | Bool | unresolved | 0x14522dea0 |
| bStopAILogicOnUnposses | Bool | unresolved | 0x14522def0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ClaimTaskResource | 8 | 0x14522cab0 |
| GetAIPerceptionComponent | 8 | 0x14522cb30 |
| GetFocalPoint | 12 | 0x14522cbb0 |
| GetFocalPointOnActor | 24 | 0x14522cc70 |
| GetFocusActor | 8 | 0x14522ccf0 |
| GetImmediateMoveDestination | 12 | 0x14522cd70 |
| GetMoveStatus | 1 | 0x14522cdf0 |
| GetPathFollowingComponent | 8 | 0x14522ce70 |
| HasPartialPath | 1 | 0x14522cf00 |
| K2_ClearFocus | 0 | 0x14522cf40 |
| K2_SetFocalPoint | 12 | 0x14522cfc0 |
| K2_SetFocus | 8 | 0x14522d040 |
| MoveToActor | 32 | 0x14522d2c0 |
| MoveToLocation | 40 | 0x14522d590 |
| OnGameplayTaskResourcesClaimed | 4 | 0x14522d650 |
| OnPossess | 8 | 0x14522d6d0 |
| OnUnpossess | 8 | 0x14522d750 |
| OnUsingBlackBoard | 16 | 0x14522d810 |
| RunBehaviorTree | 16 | 0x14522d8e0 |
| SetMoveBlockDetection | 1 | 0x14522d970 |
| UnclaimTaskResource | 8 | 0x14522da00 |
| UseBlackboard | 24 | 0x14522db10 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## ConsoleSettings

Class params `0x143d5f4f0`; resolver `0x141cc16a0`; size `0x70`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| AutoCompleteFadedColor | Struct | 0x68 | 0x14508dcc0 |
| AutoCompleteCVarColor | Struct | 0x64 | 0x14508dd00 |
| AutoCompleteCommandColor | Struct | 0x60 | 0x14508dd40 |
| HistoryColor | Struct | 0x5c | 0x14508dd80 |
| InputColor | Struct | 0x58 | 0x14508ddc0 |
| bOrderTopToBottom | Bool | 0x54 | 0x14508de00 |
| BackgroundOpacityPercentage | Float | 0x50 | 0x14508dc88 |
| AutoCompleteMapPaths | Array | 0x40 | 0x14508de48 |
| ManualAutoCompleteList | Array | 0x30 | 0x14508deb8 |
| MaxScrollbackSize | Int | 0x28 | 0x14508df30 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## Controller

Class params `0x1440f3ae0`; resolver `0x142675260`; size `0x418`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bIsPlayerController | Bool | unresolved | 0x145126a00 |
| bAttachToPawn | Bool | unresolved | 0x145126a50 |
| ControlRotation | Struct | 0x400 | 0x145126aa0 |
| TransformComponent | Object | 0x3e0 | 0x145126ae0 |
| Character | Object | 0x3d8 | 0x145126b20 |
| Pawn | Object | 0x3c8 | 0x145126b60 |
| StateName | Name | 0x3c0 | 0x145125fa8 |
| OnInstigatedAnyDamage | MulticastDelegate | 0x3b0 | 0x145126ba0 |
| PlayerState | Object | 0x3a0 | 0x145126be0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CastToPlayerController | 8 | 0x145125be0 |
| ClientSetLocation | 24 | 0x145125ca0 |
| ClientSetRotation | 16 | 0x145125da0 |
| GetControlRotation | 12 | 0x145125e20 |
| GetDesiredRotation | 12 | 0x145125ea0 |
| GetViewTarget | 8 | 0x145125f20 |
| IsLocalController | 1 | 0x145125fe0 |
| IsLocalPlayerController | 1 | 0x145126090 |
| IsLookInputIgnored | 1 | 0x145126120 |
| IsMoveInputIgnored | 1 | 0x1451261b0 |
| IsPlayerController | 1 | 0x145126240 |
| K2_GetPawn | 8 | 0x1451262c0 |
| LineOfSightTo | 24 | 0x145126420 |
| OnRep_Pawn | 0 | 0x145126460 |
| OnRep_PlayerState | 0 | 0x1451264a0 |
| Possess | 8 | 0x145126520 |
| ReceiveInstigatedAnyDamage | 32 | 0x145126620 |
| ResetIgnoreInputFlags | 0 | 0x145126660 |
| ResetIgnoreLookInput | 0 | 0x1451266a0 |
| ResetIgnoreMoveInput | 0 | 0x1451266e0 |
| SetControlRotation | 12 | 0x145126760 |
| SetIgnoreLookInput | 1 | 0x1451267f0 |
| SetIgnoreMoveInput | 1 | 0x145126880 |
| SetInitialLocationAndRotation | 24 | 0x145126940 |
| StopMovement | 0 | 0x145126980 |
| UnPossess | 0 | 0x1451269c0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CastToPlayerController | 0x1426770e0 | 0x1440f62a0 |
| ClientSetLocation | 0x142677110 | 0x1440f62b0 |
| ClientSetRotation | 0x1426771f0 | 0x1440f62c0 |
| GetControlRotation | 0x1426772d0 | 0x1440f62d0 |
| GetDesiredRotation | 0x142677310 | 0x1440f62e0 |
| GetViewTarget | 0x142677350 | 0x1440f62f0 |
| IsLocalController | 0x142677380 | 0x1440f6300 |
| IsLocalPlayerController | 0x1426773b0 | 0x1440f6310 |
| IsLookInputIgnored | 0x142677400 | 0x1440f6320 |
| IsMoveInputIgnored | 0x142677430 | 0x1440f6330 |
| IsPlayerController | 0x142677460 | 0x1440f6340 |
| K2_GetPawn | 0x142677490 | 0x1440f6350 |
| LineOfSightTo | 0x1426774c0 | 0x1440f6360 |
| OnRep_Pawn | 0x1426775e0 | 0x1440f6370 |
| OnRep_PlayerState | 0x142677600 | 0x1440f6380 |
| Possess | 0x142677620 | 0x1440f6390 |
| ResetIgnoreInputFlags | 0x1426776b0 | 0x1440f63a0 |
| ResetIgnoreLookInput | 0x1426776d0 | 0x1440f63b0 |
| ResetIgnoreMoveInput | 0x1426776f0 | 0x1440f63c0 |
| SetControlRotation | 0x142677790 | 0x1440f63d0 |
| SetIgnoreLookInput | 0x142677820 | 0x1440f63e0 |
| SetIgnoreMoveInput | 0x1426778b0 | 0x1440f63f0 |
| SetInitialLocationAndRotation | 0x142677940 | 0x1440f6400 |
| StopMovement | 0x142677a30 | 0x1440f6410 |
| UnPossess | 0x142677a50 | 0x1440f6420 |

## DemoNetDriver

Class params `0x1440fd7e0`; resolver `0x14267d000`; size `0xb70`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bIsLocalReplay | Bool | 0xa08 | 0x14512aac0 |
| CheckpointSaveMaxMSPerFrame | Float | 0x9d4 | 0x14512aa08 |
| RollbackNetStartupActors | Map | 0x5f0 | 0x14512aa88 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## GameEngine

Class params `0x144118870`; resolver `0x14133b360`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0xcb8 | 0x14513e5f0 |
| ServerFlushLogInterval | Float | 0xcb4 | 0x14513e630 |
| MaxDeltaTime | Float | 0xcb0 | 0x14513e668 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## GameInstance

Class params `0x144118dd0`; resolver `0x142662200`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ReferencedObjects | Array | 0x50 | 0x14513e990 |
| OnlineSession | Object | 0x48 | 0x14513ea10 |
| LocalPlayers | Array | 0x38 | 0x14513ea50 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| DebugCreatePlayer | 4 | 0x14513e700 |
| DebugRemovePlayer | 4 | 0x14513e780 |
| HandleNetworkError | 2 | 0x14513e850 |
| HandleTravelError | 1 | 0x14513e8d0 |
| ReceiveInit | 0 | 0x14513e910 |
| ReceiveShutdown | 0 | 0x14513e950 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## GameMapsSettings

Class params `0x143d5e700`; resolver `0x141cc17c0`; size `0x108`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameModeClassAliases | Array | 0xf8 | 0x14508e008 |
| GameModeMapPrefixes | Array | 0xe8 | 0x14508e088 |
| GlobalDefaultServerGameMode | Struct | 0xd0 | 0x14508e140 |
| GlobalDefaultGameMode | Struct | 0xb8 | 0x14508e180 |
| ServerDefaultMap | Struct | 0xa0 | 0x14508e1c0 |
| GameDefaultMap | Struct | 0x88 | 0x14508e200 |
| GameInstanceClass | Struct | 0x70 | 0x14508e240 |
| bOffsetPlayerGamepadIds | Bool | 0x6b | 0x14508e280 |
| ThreePlayerSplitscreenLayout | Byte | 0x6a | 0x14508e300 |
| TwoPlayerSplitscreenLayout | Byte | 0x69 | 0x14508e340 |
| bUseSplitscreen | Bool | 0x68 | 0x14508e380 |
| TransitionMap | Struct | 0x50 | 0x14508e3f0 |
| LocalMapOptions | Str | 0x40 | 0x14508e2c8 |
| EditorStartupMap | Struct | 0x28 | 0x14508e430 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## GameMode

Class params `0x144117b30`; resolver `0x14268c3c0`; size `0x480`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bHandleDedicatedServerReplays | Bool | 0x478 | 0x14513f040 |
| MaxInactivePlayers | Int | 0x474 | 0x14513f088 |
| InactivePlayerStateLifeSpan | Float | 0x470 | 0x14513f0c0 |
| InactivePlayerArray | Array | 0x460 | 0x14513f0f8 |
| EngineMessageClass | Class | 0x458 | 0x14513f170 |
| NumTravellingPlayers | Int | 0x454 | 0x14513f1b8 |
| MinRespawnDelay | Float | 0x450 | 0x14513f1f0 |
| NumBots | Int | 0x44c | 0x14513f228 |
| NumPlayers | Int | 0x448 | 0x14513f260 |
| NumSpectators | Int | 0x444 | 0x14513f298 |
| bDelayedStart | Bool | unresolved | 0x14513f2d0 |
| MatchState | Name | 0x438 | 0x14513f318 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AbortMatch | 0 | 0x14513eb00 |
| EndMatch | 0 | 0x14513eb40 |
| GetMatchState | 8 | 0x14513ebc0 |
| HasMatchEnded | 1 | 0x14513ec50 |
| IsMatchInProgress | 1 | 0x14513ece0 |
| K2_OnSetMatchState | 8 | 0x14513ed60 |
| ReadyToEndMatch | 1 | 0x14513edf0 |
| ReadyToStartMatch | 1 | 0x14513ee80 |
| RestartGame | 0 | 0x14513eec0 |
| Say | 16 | 0x14513ef40 |
| SetBandwidthLimit | 4 | 0x14513efc0 |
| StartMatch | 0 | 0x14513f000 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AbortMatch | 0x14268ebe0 | 0x14411a990 |
| EndMatch | 0x14266c910 | 0x14411a9a0 |
| GetMatchState | 0x14268f010 | 0x14411a9b0 |
| HasMatchEnded | 0x14268f030 | 0x14411a9c0 |
| IsMatchInProgress | 0x14268f060 | 0x14411a9d0 |
| ReadyToEndMatch | 0x14268f130 | 0x14411a9e0 |
| ReadyToStartMatch | 0x14268f160 | 0x14411a9f0 |
| RestartGame | 0x14266c930 | 0x14411aa00 |
| Say | 0x14268f240 | 0x14411aa10 |
| SetBandwidthLimit | 0x14268f2f0 | 0x14411aa20 |
| StartMatch | 0x14266c950 | 0x14411aa30 |

## GameModeBase

Class params `0x14411c850`; resolver `0x141341d20`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bPauseable | Bool | unresolved | 0x145140800 |
| bStartPlayersAsSpectators | Bool | unresolved | 0x145140880 |
| bUseSeamlessTravel | Bool | unresolved | 0x145140900 |
| DefaultPlayerName | Text | 0x408 | 0x14513fd58 |
| ServerStatReplicator | Object | 0x400 | 0x145140980 |
| GameState | Object | 0x3f8 | 0x1451409c0 |
| GameSession | Object | 0x3f0 | 0x145140a00 |
| ServerStatReplicatorClass | Class | 0x3e8 | 0x145140a40 |
| ReplaySpectatorPlayerControllerClass | Class | 0x3e0 | 0x145140ac0 |
| SpectatorClass | Class | 0x3d8 | 0x145140b40 |
| DefaultPawnClass | Class | 0x3d0 | 0x145140bc0 |
| HUDClass | Class | 0x3c8 | 0x145140c40 |
| PlayerStateClass | Class | 0x3c0 | 0x145140cc0 |
| PlayerControllerClass | Class | 0x3b8 | 0x145140d40 |
| GameStateClass | Class | 0x3b0 | 0x145140dc0 |
| GameSessionClass | Class | 0x3a8 | 0x145140e40 |
| OptionsString | Str | 0x398 | 0x145140098 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CanSpectate | 24 | 0x14513f520 |
| ChangeName | 32 | 0x14513f620 |
| ChoosePlayerStart | 16 | 0x14513f6e0 |
| FindPlayerStart | 32 | 0x14513f7a0 |
| GetDefaultPawnClassForController | 16 | 0x14513f8a0 |
| GetNumPlayers | 4 | 0x14513f8e0 |
| GetNumSpectators | 4 | 0x14513f990 |
| HandleStartingNewPlayer | 8 | 0x14513fa10 |
| HasMatchStarted | 1 | 0x14513fad0 |
| InitStartSpot | 16 | 0x14513fc10 |
| InitializeHUDForPlayer | 8 | 0x14513fb50 |
| K2_FindPlayerStart | 32 | 0x14513fcd0 |
| K2_OnChangeName | 32 | 0x14513fdd0 |
| K2_OnLogout | 8 | 0x14513fe50 |
| K2_OnRestartPlayer | 8 | 0x14513fed0 |
| K2_OnSwapPlayerControllers | 16 | 0x14513ff90 |
| K2_PostLogin | 8 | 0x145140010 |
| MustSpectate | 16 | 0x145140110 |
| PlayerCanRestart | 16 | 0x145140200 |
| ResetLevel | 0 | 0x145140240 |
| RestartPlayer | 8 | 0x1451402c0 |
| RestartPlayerAtPlayerStart | 16 | 0x145140380 |
| RestartPlayerAtTransform | 64 | 0x145140440 |
| ReturnToMainMenuHost | 0 | 0x145140480 |
| ShouldReset | 16 | 0x145140580 |
| SpawnDefaultPawnAtTransform | 80 | 0x145140680 |
| SpawnDefaultPawnFor | 24 | 0x145140780 |
| StartPlay | 0 | 0x1451407c0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## GameUserSettings, MBGameUserSettings

Class params `0x143a0eb00`; resolver `0x141340650`; size `0x3a8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bCloudSettingsRequestInProgress | Bool | 0x3a0 | 0x144fbf6f0 |
| BannedFXTags | Array | 0x390 | 0x144fbf1b8 |
| bAudioSettingsDirty | Bool | 0x38a | 0x144fbf770 |
| CloudBindingsDirty | Bool | 0x389 | 0x144fbf7f0 |
| CloudOptionsDirty | Bool | 0x388 | 0x144fbf870 |
| FrontendSettings | Struct | 0x370 | 0x144fbf8f0 |
| KeyBinds | Struct | 0x330 | 0x144fbf930 |
| AccessibilitySettings | Struct | 0x320 | 0x144fbf970 |
| SocialSettings | Struct | 0x310 | 0x144fbf9b0 |
| UISettings | Struct | 0x2f0 | 0x144fbf9f0 |
| MouseSettings | Struct | 0x2d8 | 0x144fbfa30 |
| ControllerSettings | Struct | 0x2ac | 0x144fbfa70 |
| Inited | Bool | 0x2a8 | 0x144fbfab0 |
| AccessibilitySettingsChangedMulticaster | MulticastDelegate | 0x298 | 0x144fbfb30 |
| ControllerIconsChangedMulticaster | MulticastDelegate | 0x288 | 0x144fbfb70 |
| MaxMatchmakingPing | Int | 0x284 | 0x144fbf738 |
| OverridingRegion | Int | 0x280 | 0x144fbf7b8 |
| ChatWheelMode | Enum | 0x279 | 0x144fbfbb0 |
| AxisMappings_Add | Array | 0x248 | 0x144fbf838 |
| AxisMappings_Remove | Array | 0x238 | 0x144fbf8b8 |
| ActionMappings_Add | Array | 0x228 | 0x144fbfaf8 |
| ActionMappings_Remove | Array | 0x218 | 0x144fbfcf0 |
| AudioMultiplier_PCNarration | Float | 0x214 | 0x144fbfd28 |
| NarrationVolume_PC | Float | 0x210 | 0x144fbfda0 |
| NarrationVolume | Float | 0x20c | 0x144fbfdd8 |
| bSpeechToText | Bool | 0x20a | 0x144fbfe10 |
| bTextToSpeech | Bool | 0x209 | 0x144fbfe90 |
| bLetGamesReadToMe | Bool | 0x208 | 0x144fbff10 |
| VoiceAudioOutputDevice | Str | 0x1f8 | 0x144fbfe58 |
| AudioOutputDevice | Str | 0x1e8 | 0x144fbfed8 |
| AudioInputDevice | Str | 0x1d8 | 0x144fbff58 |
| MicrophoneSensitivity | Float | 0x1d0 | 0x144fbff90 |
| VoiceOutVolume | Float | 0x1cc | 0x144fbffc8 |
| VoiceChatVolume | Float | 0x1c8 | 0x144fc0000 |
| VoiceChatMode | Enum | 0x1c4 | 0x144fc0070 |
| bMuteAudioWhenGameNotInFocus | Bool | 0x1c3 | 0x144fc00f0 |
| bHighContrastMenus | Bool | 0x1c2 | 0x144fc0170 |
| bLargeChatFonts | Bool | 0x1c1 | 0x144fc01f0 |
| bDynamicBackgrounds | Bool | 0x1c0 | 0x144fc0270 |
| UiVolume | Float | 0x1bc | 0x144fc0038 |
| VoVolume | Float | 0x1b8 | 0x144fc0138 |
| SfxVolume | Float | 0x1b4 | 0x144fc01b8 |
| InGameMusicVolume | Float | 0x1b0 | 0x144fc0238 |
| MusicVolume | Float | 0x1ac | 0x144fc02b8 |
| MasterVolume | Float | 0x1a8 | 0x144fc02f0 |
| bEnableScreenSpaceReflections | Bool | 0x1a5 | 0x144fc0360 |
| DisplaySyncMethod | Enum | 0x1a4 | 0x144fc03e0 |
| Gamma | Float | 0x1a0 | 0x144fc0328 |
| TextureFilterQuality | Int | 0x19c | 0x144fc03a8 |
| AAMode | Int | 0x198 | 0x144fc0460 |
| RenderScalePercentage | Int | 0x194 | 0x144fc0498 |
| ActiveMonitorIndex | Int | 0x190 | 0x144fc04d0 |
| bDisplayPlaystationButtons | Bool | 0x184 | 0x144fc0540 |
| LockOnType_Controller | Enum | 0x160 | 0x144fc05b0 |
| bForceFeedbackEnabled | Bool | 0x15c | 0x144fc0630 |
| PlaceableSensitivity_KeyboardAndMouse | Float | 0x158 | 0x144fc0508 |
| SoftLockTargetingMode_KeyboardAndMouse | Enum | 0x157 | 0x144fc0680 |
| LockOnTargetingMode_KeyboardAndMouse | Enum | 0x156 | 0x144fc0700 |
| LockOnType_KeyboardAndMouse | Enum | 0x155 | 0x144fc0780 |
| bCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | Bool | 0x154 | 0x144fc0800 |
| bCameraLockOnTargetTrackingEnabled | Bool | 0x153 | 0x144fc0850 |
| bCameraAutoRotationEnabled_KeyboardAndMouse | Bool | 0x152 | 0x144fc08a0 |
| CameraCombatZoomMode_KeyboardAndMouse | Enum | 0x151 | 0x144fc08f0 |
| CameraCombatZoomMode | Enum | 0x150 | 0x144fc0970 |
| OnBannedTagsChanged | MulticastDelegate | 0x140 | 0x144fc09f0 |
| OnSettingsChanged | MulticastDelegate | 0x130 | 0x144fc0a30 |
| OnKeybindsChanged | MulticastDelegate | 0x120 | 0x144fc0a70 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ApplyColourBlindSettings | 0 | 0x144fb6eb0 |
| ApplyGamma | 0 | 0x144fb6ef0 |
| ApplySettingsToGameActors | 8 | 0x144fb6f70 |
| GetAAMode | 4 | 0x144fb6fb0 |
| GetActiveMonitor | 4 | 0x144fb6ff0 |
| GetAllowInvitesFrom | 1 | 0x144fb70b0 |
| GetAudioDevices | 88 | 0x144fb71b0 |
| GetAudioInputDevice | 16 | 0x144fb71f0 |
| GetAudioOutputDevice | 16 | 0x144fb7230 |
| GetBloodEffects | 1 | 0x144fb72f0 |
| GetCameraAutoRotationEnabled_Controller | 1 | 0x144fb73b0 |
| GetCameraAutoRotationEnabled_KeyboardAndMouse | 1 | 0x144fb7470 |
| GetCameraCombatZoomMode_Controller | 1 | 0x144fb7530 |
| GetCameraCombatZoomMode_KeyboardAndMouse | 1 | 0x144fb75f0 |
| GetCameraLockOnTargetTrackingEnabled_Controller | 1 | 0x144fb76b0 |
| GetCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 1 | 0x144fb7770 |
| GetChatWheelMode | 1 | 0x144fb7830 |
| GetControllerAcceleration | 4 | 0x144fb7870 |
| GetControllerAcceleration_Alpha | 4 | 0x144fb78b0 |
| GetCulture | 16 | 0x144fb78f0 |
| GetDefaultAAMode | 4 | 0x144fb7930 |
| GetDefaultAAQuality | 4 | 0x144fb7970 |
| GetDefaultAllowInvitesFrom | 1 | 0x144fb7a30 |
| GetDefaultAudioQualityLevel | 4 | 0x144fb7a70 |
| GetDefaultBloodEffects | 1 | 0x144fb7b30 |
| GetDefaultCameraAutoRotationEnabled_Controller | 1 | 0x144fb7bf0 |
| GetDefaultCameraAutoRotationEnabled_KeyboardAndMouse | 1 | 0x144fb7cb0 |
| GetDefaultCameraCombatZoomMode_Controller | 1 | 0x144fb7d70 |
| GetDefaultCameraCombatZoomMode_KeyboardAndMouse | 1 | 0x144fb7e30 |
| GetDefaultCameraLockOnTargetTrackingEnabled_Controller | 1 | 0x144fb7ef0 |
| GetDefaultCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 1 | 0x144fb7fb0 |
| GetDefaultChatWheelMode | 1 | 0x144fb8070 |
| GetDefaultControllerAcceleration | 4 | 0x144fb80b0 |
| GetDefaultControllerAcceleration_Alpha | 4 | 0x144fb80f0 |
| GetDefaultCulture | 16 | 0x144fb8130 |
| GetDefaultDisplayPlaystationButtons | 1 | 0x144fb81f0 |
| GetDefaultDynamicBackgrounds | 1 | 0x144fb82b0 |
| GetDefaultEffectsQuality | 4 | 0x144fb82f0 |
| GetDefaultEnableController | 1 | 0x144fb83b0 |
| GetDefaultForceFeedbackEnabled | 1 | 0x144fb8470 |
| GetDefaultGamma | 4 | 0x144fb84b0 |
| GetDefaultGroupMembersCanInvite | 1 | 0x144fb8570 |
| GetDefaultHighContrastMenus | 1 | 0x144fb8630 |
| GetDefaultImprovedControlResponse | 1 | 0x144fb86f0 |
| GetDefaultInvertControllerX | 1 | 0x144fb87b0 |
| GetDefaultInvertControllerY | 1 | 0x144fb8870 |
| GetDefaultInvertMouseY | 1 | 0x144fb8930 |
| GetDefaultJoinability | 1 | 0x144fb89f0 |
| GetDefaultLargeChatFonts | 1 | 0x144fb8ab0 |
| GetDefaultLockOnTargetingMode_Controller | 1 | 0x144fb8b70 |
| GetDefaultLockOnTargetingMode_KeyboardAndMouse | 1 | 0x144fb8c30 |
| GetDefaultLockOnType_Controller | 1 | 0x144fb8cf0 |
| GetDefaultLockOnType_KeyboardAndMouse | 1 | 0x144fb8db0 |
| GetDefaultMatchChat | 1 | 0x144fb8e70 |
| GetDefaultMicrophoneSensitivity | 4 | 0x144fb8eb0 |
| GetDefaultModelDetailQuality | 4 | 0x144fb8ef0 |
| GetDefaultMouseSensitivity | 4 | 0x144fb8f30 |
| GetDefaultMuteAudioWhenGameNotInFocus | 1 | 0x144fb8ff0 |
| GetDefaultNarrationVolume | 4 | 0x144fb9030 |
| GetDefaultOverlayIntensity | 4 | 0x144fb9070 |
| GetDefaultPartyChat | 1 | 0x144fb9130 |
| GetDefaultPartyVoiceChatJoin | 1 | 0x144fb91f0 |
| GetDefaultPlaceableSensitivity_Controller | 4 | 0x144fb9230 |
| GetDefaultPlaceableSensitivity_KeyboardAndMouse | 4 | 0x144fb9270 |
| GetDefaultPostProcessQuality | 4 | 0x144fb92b0 |
| GetDefaultProfanityFilter | 1 | 0x144fb9370 |
| GetDefaultReceiveWhispers | 1 | 0x144fb9430 |
| GetDefaultRenderScale | 4 | 0x144fb9470 |
| GetDefaultScreenSpaceReflectionsEnabled | 1 | 0x144fb9530 |
| GetDefaultShadowQuality | 4 | 0x144fb9570 |
| GetDefaultShowHUD | 1 | 0x144fb9630 |
| GetDefaultSoftLockTargetingMode_Controller | 1 | 0x144fb96f0 |
| GetDefaultSoftLockTargetingMode_KeyboardAndMouse | 1 | 0x144fb97b0 |
| GetDefaultSpeechToText | 1 | 0x144fb9870 |
| GetDefaultSpeedControllerX | 4 | 0x144fb98b0 |
| GetDefaultSpeedControllerX_Alpha | 4 | 0x144fb98f0 |
| GetDefaultSpeedControllerY | 4 | 0x144fb9930 |
| GetDefaultSpeedControllerY_Alpha | 4 | 0x144fb9970 |
| GetDefaultStatsVisibility | 1 | 0x144fb9a30 |
| GetDefaultSwapMouseButtons | 1 | 0x144fb9af0 |
| GetDefaultSwitchSticks | 1 | 0x144fb9bb0 |
| GetDefaultSyncMethod | 1 | 0x144fb9c70 |
| GetDefaultTeamChat | 1 | 0x144fb9d30 |
| GetDefaultTeamVoiceChatJoin | 1 | 0x144fb9df0 |
| GetDefaultTextToSpeech | 1 | 0x144fb9eb0 |
| GetDefaultTextureFilterQuality | 4 | 0x144fb9ef0 |
| GetDefaultTextureQuality | 4 | 0x144fb9f30 |
| GetDefaultThrottleEngineTickRate | 1 | 0x144fb9ff0 |
| GetDefaultVoiceChatMode | 1 | 0x144fba0b0 |
| GetDisplayPlaystationButtons | 1 | 0x144fba170 |
| GetDynamicBackgrounds | 1 | 0x144fba230 |
| GetEnableController | 1 | 0x144fba2f0 |
| GetForceFeedbackEnabled | 1 | 0x144fba3b0 |
| GetGamma | 4 | 0x144fba3f0 |
| GetGroupMembersCanInvite | 1 | 0x144fba4b0 |
| GetHighContrastMenus | 1 | 0x144fba570 |
| GetImprovedControlResponse | 1 | 0x144fba630 |
| GetInGameMusicVolume | 4 | 0x144fba670 |
| GetInvertControllerX | 1 | 0x144fba730 |
| GetInvertControllerY | 1 | 0x144fba7f0 |
| GetInvertMouseY | 1 | 0x144fba8b0 |
| GetJoinability | 1 | 0x144fba970 |
| GetLargeChatFonts | 1 | 0x144fbaa30 |
| GetLetGamesReadToMe | 1 | 0x144fbaaf0 |
| GetLockOnTargetingMode_Controller | 1 | 0x144fbabb0 |
| GetLockOnTargetingMode_KeyboardAndMouse | 1 | 0x144fbac70 |
| GetLockOnType_Controller | 1 | 0x144fbad30 |
| GetLockOnType_KeyboardAndMouse | 1 | 0x144fbadf0 |
| GetMBGameUserSettings | 8 | 0x144fbafb0 |
| GetMasterVolume | 4 | 0x144fbae30 |
| GetMatchChat | 1 | 0x144fbaef0 |
| GetMaximumMatchmakingPing | 4 | 0x144fbaf30 |
| GetMicrophoneSensitivity | 4 | 0x144fbaff0 |
| GetMonitorList | 16 | 0x144fbb030 |
| GetMonitorSupportedFullscreenResolutions | 32 | 0x144fbb130 |
| GetMouseSensitivity | 4 | 0x144fbb170 |
| GetMusicVolume | 4 | 0x144fbb1b0 |
| GetMuteAudioWhenGameNotInFocus | 1 | 0x144fbb270 |
| GetNarrationVolume | 4 | 0x144fbb2b0 |
| GetNarrationVolume_Internal | 4 | 0x144fbb2f0 |
| GetNarrationVolume_PC | 4 | 0x144fbb330 |
| GetOverlayIntensity | 4 | 0x144fbb370 |
| GetOverridingRegion | 4 | 0x144fbb3b0 |
| GetPartyChat | 1 | 0x144fbb470 |
| GetPartyVoiceChatJoin | 1 | 0x144fbb530 |
| GetPlaceableSensitivity_Controller | 4 | 0x144fbb570 |
| GetPlaceableSensitivity_KeyboardAndMouse | 4 | 0x144fbb5b0 |
| GetProfanityFilter | 1 | 0x144fbb670 |
| GetReceiveWhispers | 1 | 0x144fbb730 |
| GetRenderScalePercentage | 4 | 0x144fbb770 |
| GetScreenSpaceReflectionsEnabled | 1 | 0x144fbb830 |
| GetSfxVolume | 4 | 0x144fbb870 |
| GetShowHUD | 1 | 0x144fbb930 |
| GetSoftLockTargetingMode_Controller | 1 | 0x144fbb9f0 |
| GetSoftLockTargetingMode_KeyboardAndMouse | 1 | 0x144fbbab0 |
| GetSpeechToText | 1 | 0x144fbbb70 |
| GetSpeechToText_Internal | 1 | 0x144fbbc30 |
| GetSpeedControllerX | 4 | 0x144fbbc70 |
| GetSpeedControllerX_Alpha | 4 | 0x144fbbcb0 |
| GetSpeedControllerY | 4 | 0x144fbbcf0 |
| GetSpeedControllerY_Alpha | 4 | 0x144fbbd30 |
| GetStatsScreenDisplayingMods | 1 | 0x144fbbdf0 |
| GetStatsScreenOpenTab | 4 | 0x144fbbe30 |
| GetStatsVisibility | 1 | 0x144fbbef0 |
| GetSwapMouseButtons | 1 | 0x144fbbfb0 |
| GetSwitchSticks | 1 | 0x144fbc070 |
| GetSyncMethod | 1 | 0x144fbc130 |
| GetTeamChat | 1 | 0x144fbc1f0 |
| GetTeamVoiceChatJoin | 1 | 0x144fbc2b0 |
| GetTextToSpeech | 1 | 0x144fbc370 |
| GetTextToSpeech_Internal | 1 | 0x144fbc430 |
| GetTextureFilterQuality | 4 | 0x144fbc470 |
| GetThrottleEngineTickRate | 1 | 0x144fbc530 |
| GetUiVolume | 4 | 0x144fbc570 |
| GetVoVolume | 4 | 0x144fbc730 |
| GetVoiceAudioOutputDevice | 16 | 0x144fbc5b0 |
| GetVoiceChatMode | 1 | 0x144fbc670 |
| GetVoiceChatVolume | 4 | 0x144fbc6b0 |
| GetVoiceOutVolume | 4 | 0x144fbc6f0 |
| IsAllowedThrottleEngineTickRate | 1 | 0x144fbc7f0 |
| RegisterAccessibilitySettingsChangedDelegate | 16 | 0x144fbc870 |
| RegisterControllerIconsChangedDelegate | 16 | 0x144fbc8f0 |
| SaveCloudSettings | 0 | 0x144fbc930 |
| SaveKeyBindings | 0 | 0x144fbc970 |
| SetAAMode | 4 | 0x144fbc9b0 |
| SetActiveMonitor | 4 | 0x144fbc9f0 |
| SetAllowInvitesFrom | 1 | 0x144fbcab0 |
| SetAudioInputDevice | 16 | 0x144fbcaf0 |
| SetAudioOutputDevice | 16 | 0x144fbcb30 |
| SetBloodEffects | 1 | 0x144fbcbf0 |
| SetCameraAutoRotationEnabled_Controller | 1 | 0x144fbccb0 |
| SetCameraAutoRotationEnabled_KeyboardAndMouse | 1 | 0x144fbcd70 |
| SetCameraCombatZoomMode_Controller | 1 | 0x144fbce30 |
| SetCameraCombatZoomMode_KeyboardAndMouse | 1 | 0x144fbcef0 |
| SetCameraLockOnTargetTrackingEnabled_Controller | 1 | 0x144fbcfb0 |
| SetCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 1 | 0x144fbd070 |
| SetChatWheelMode | 1 | 0x144fbd130 |
| SetControllerAcceleration | 8 | 0x144fbd170 |
| SetCulture | 16 | 0x144fbd1b0 |
| SetDisplayPlaystationButtons | 1 | 0x144fbd270 |
| SetDynamicBackgrounds | 1 | 0x144fbd330 |
| SetEnableController | 1 | 0x144fbd3f0 |
| SetForceFeedbackEnabled | 1 | 0x144fbd4b0 |
| SetGamma | 4 | 0x144fbd4f0 |
| SetGroupMembersCanInvite | 1 | 0x144fbd5b0 |
| SetHighContrastMenus | 1 | 0x144fbd670 |
| SetImprovedControlResponse | 1 | 0x144fbd730 |
| SetInGameMusicVolume | 4 | 0x144fbd770 |
| SetInvertControllerX | 1 | 0x144fbd830 |
| SetInvertControllerY | 1 | 0x144fbd8f0 |
| SetInvertMouseY | 1 | 0x144fbd9b0 |
| SetJoinability | 1 | 0x144fbda70 |
| SetLargeChatFonts | 1 | 0x144fbdb30 |
| SetLetGamesReadToMe | 1 | 0x144fbdbf0 |
| SetLockOnTargetingMode_Controller | 1 | 0x144fbdcb0 |
| SetLockOnTargetingMode_KeyboardAndMouse | 1 | 0x144fbdd70 |
| SetLockOnType_Controller | 1 | 0x144fbde30 |
| SetLockOnType_KeyboardAndMouse | 1 | 0x144fbdef0 |
| SetMasterVolume | 4 | 0x144fbdf30 |
| SetMatchChat | 1 | 0x144fbdff0 |
| SetMaximumMatchmakingPing | 4 | 0x144fbe030 |
| SetMicrophoneSensitivity | 4 | 0x144fbe070 |
| SetMouseSensitivity | 4 | 0x144fbe0b0 |
| SetMusicVolume | 4 | 0x144fbe0f0 |
| SetMuteAudioWhenGameNotInFocus | 1 | 0x144fbe1b0 |
| SetNarrationVolume | 4 | 0x144fbe1f0 |
| SetNarrationVolume_Internal | 4 | 0x144fbe230 |
| SetNarrationVolume_PC | 4 | 0x144fbe270 |
| SetOverlayIntensity | 1 | 0x144fbe330 |
| SetOverridingRegion | 4 | 0x144fbe370 |
| SetPartyChat | 1 | 0x144fbe430 |
| SetPartyVoiceChatJoin | 1 | 0x144fbe4f0 |
| SetPlaceableSensitivity_Controller | 4 | 0x144fbe530 |
| SetPlaceableSensitivity_KeyboardAndMouse | 4 | 0x144fbe570 |
| SetProfanityFilter | 1 | 0x144fbe630 |
| SetReceiveWhispers | 1 | 0x144fbe6f0 |
| SetRenderScalePercentage | 4 | 0x144fbe730 |
| SetScreenSpaceReflectionsEnabled | 1 | 0x144fbe7f0 |
| SetSfxVolume | 4 | 0x144fbe830 |
| SetShowHUD | 1 | 0x144fbe8f0 |
| SetSoftLockTargetingMode_Controller | 1 | 0x144fbe9b0 |
| SetSoftLockTargetingMode_KeyboardAndMouse | 1 | 0x144fbea70 |
| SetSpeechToText | 1 | 0x144fbeb30 |
| SetSpeedControllerX | 8 | 0x144fbeb70 |
| SetSpeedControllerY | 8 | 0x144fbebb0 |
| SetStatsScreenDisplayingMods | 1 | 0x144fbec70 |
| SetStatsScreenOpenTab | 4 | 0x144fbecb0 |
| SetStatsVisibility | 1 | 0x144fbed70 |
| SetSwapMouseButtons | 1 | 0x144fbee30 |
| SetSwitchSticks | 1 | 0x144fbeef0 |
| SetSyncMethod | 1 | 0x144fbefb0 |
| SetTeamChat | 1 | 0x144fbf070 |
| SetTeamVoiceChatJoin | 1 | 0x144fbf130 |
| SetTextToSpeech | 1 | 0x144fbf1f0 |
| SetTextureFilterQuality | 4 | 0x144fbf230 |
| SetThrottleEngineTickRate | 1 | 0x144fbf2f0 |
| SetUiVolume | 4 | 0x144fbf330 |
| SetVoVolume | 4 | 0x144fbf4f0 |
| SetVoiceAudioOutputDevice | 16 | 0x144fbf370 |
| SetVoiceChatMode | 1 | 0x144fbf430 |
| SetVoiceChatVolume | 4 | 0x144fbf470 |
| SetVoiceOutVolume | 4 | 0x144fbf4b0 |
| UnregisterAccessibilitySettingsChangedDelegate | 16 | 0x144fbf570 |
| UnregisterControllerIconsChangedDelegate | 16 | 0x144fbf5f0 |
| UpdateCloudIfDirty | 0 | 0x144fbf630 |
| UpdatePostProcessVolumes | 8 | 0x144fbf6b0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ApplyColourBlindSettings | 0x1413427e0 | 0x143a19e60 |
| ApplyGamma | 0x141342800 | 0x143a19e70 |
| ApplySettingsToGameActors | 0x141342820 | 0x143a19e80 |
| GetAAMode | 0x141342950 | 0x143a19e90 |
| GetActiveMonitor | 0x141342970 | 0x143a19ea0 |
| GetAllowInvitesFrom | 0x1413429a0 | 0x143a19eb0 |
| GetAudioDevices | 0x1413429c0 | 0x143a19ec0 |
| GetAudioInputDevice | 0x141342b40 | 0x143a19ed0 |
| GetAudioOutputDevice | 0x141342b70 | 0x143a19ee0 |
| GetBloodEffects | 0x141342ba0 | 0x143a19ef0 |
| GetCameraAutoRotationEnabled_Controller | 0x141342bc0 | 0x143a19f00 |
| GetCameraAutoRotationEnabled_KeyboardAndMouse | 0x141342be0 | 0x143a19f10 |
| GetCameraCombatZoomMode_Controller | 0x141342c00 | 0x143a19f20 |
| GetCameraCombatZoomMode_KeyboardAndMouse | 0x141342c20 | 0x143a19f30 |
| GetCameraLockOnTargetTrackingEnabled_Controller | 0x141342c40 | 0x143a19f40 |
| GetCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 0x141342c60 | 0x143a19f50 |
| GetChatWheelMode | 0x141342c80 | 0x143a19f60 |
| GetControllerAcceleration | 0x141342ca0 | 0x143a19f70 |
| GetControllerAcceleration_Alpha | 0x1403d8280 | 0x143a19f80 |
| GetCulture | 0x141342cc0 | 0x143a19f90 |
| GetDefaultAAMode | 0x141342da0 | 0x143a19fa0 |
| GetDefaultAAQuality | 0x141342dc0 | 0x143a19fb0 |
| GetDefaultAllowInvitesFrom | 0x141342de0 | 0x143a19fc0 |
| GetDefaultAudioQualityLevel | 0x141342e00 | 0x143a19fd0 |
| GetDefaultBloodEffects | 0x141342e30 | 0x143a19fe0 |
| GetDefaultCameraAutoRotationEnabled_Controller | 0x141342e30 | 0x143a19ff0 |
| GetDefaultCameraAutoRotationEnabled_KeyboardAndMouse | 0x141342e30 | 0x143a1a000 |
| GetDefaultCameraCombatZoomMode_Controller | 0x141342de0 | 0x143a1a010 |
| GetDefaultCameraCombatZoomMode_KeyboardAndMouse | 0x141342de0 | 0x143a1a020 |
| GetDefaultCameraLockOnTargetTrackingEnabled_Controller | 0x141342e30 | 0x143a1a030 |
| GetDefaultCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 0x141342de0 | 0x143a1a040 |
| GetDefaultChatWheelMode | 0x141342de0 | 0x143a1a050 |
| GetDefaultControllerAcceleration | 0x141342e50 | 0x143a1a060 |
| GetDefaultControllerAcceleration_Alpha | 0x141342e50 | 0x143a1a070 |
| GetDefaultCulture | 0x141342e70 | 0x143a1a080 |
| GetDefaultDisplayPlaystationButtons | 0x141342de0 | 0x143a1a090 |
| GetDefaultDynamicBackgrounds | 0x141342e30 | 0x143a1a0a0 |
| GetDefaultEffectsQuality | 0x141342f00 | 0x143a1a0b0 |
| GetDefaultEnableController | 0x141342e30 | 0x143a1a0c0 |
| GetDefaultForceFeedbackEnabled | 0x141342e30 | 0x143a1a0d0 |
| GetDefaultGamma | 0x141342f20 | 0x143a1a0e0 |
| GetDefaultGroupMembersCanInvite | 0x141342e30 | 0x143a1a0f0 |
| GetDefaultHighContrastMenus | 0x141342de0 | 0x143a1a100 |
| GetDefaultImprovedControlResponse | 0x141342de0 | 0x143a1a110 |
| GetDefaultInvertControllerX | 0x141342de0 | 0x143a1a120 |
| GetDefaultInvertControllerY | 0x141342de0 | 0x143a1a130 |
| GetDefaultInvertMouseY | 0x141342de0 | 0x143a1a140 |
| GetDefaultJoinability | 0x141342e30 | 0x143a1a150 |
| GetDefaultLargeChatFonts | 0x141342de0 | 0x143a1a160 |
| GetDefaultLockOnTargetingMode_Controller | 0x141342de0 | 0x143a1a170 |
| GetDefaultLockOnTargetingMode_KeyboardAndMouse | 0x141342e30 | 0x143a1a180 |
| GetDefaultLockOnType_Controller | 0x141342de0 | 0x143a1a190 |
| GetDefaultLockOnType_KeyboardAndMouse | 0x141342e30 | 0x143a1a1a0 |
| GetDefaultMatchChat | 0x141342de0 | 0x143a1a1b0 |
| GetDefaultMicrophoneSensitivity | 0x141342f40 | 0x143a1a1c0 |
| GetDefaultModelDetailQuality | 0x141342f00 | 0x143a1a1d0 |
| GetDefaultMouseSensitivity | 0x141342f60 | 0x143a1a1e0 |
| GetDefaultMuteAudioWhenGameNotInFocus | 0x141342de0 | 0x143a1a1f0 |
| GetDefaultNarrationVolume | 0x141342f90 | 0x143a1a200 |
| GetDefaultOverlayIntensity | 0x141342f40 | 0x143a1a210 |
| GetDefaultPartyChat | 0x141342de0 | 0x143a1a220 |
| GetDefaultPartyVoiceChatJoin | 0x141342de0 | 0x143a1a230 |
| GetDefaultPlaceableSensitivity_Controller | 0x141342fc0 | 0x143a1a240 |
| GetDefaultPlaceableSensitivity_KeyboardAndMouse | 0x141342fc0 | 0x143a1a250 |
| GetDefaultPostProcessQuality | 0x141342f00 | 0x143a1a260 |
| GetDefaultProfanityFilter | 0x141342e30 | 0x143a1a270 |
| GetDefaultReceiveWhispers | 0x141342e30 | 0x143a1a280 |
| GetDefaultRenderScale | 0x141342fe0 | 0x143a1a290 |
| GetDefaultScreenSpaceReflectionsEnabled | 0x141342e30 | 0x143a1a2a0 |
| GetDefaultShadowQuality | 0x141342f00 | 0x143a1a2b0 |
| GetDefaultShowHUD | 0x141342e30 | 0x143a1a2c0 |
| GetDefaultSoftLockTargetingMode_Controller | 0x141342de0 | 0x143a1a2d0 |
| GetDefaultSoftLockTargetingMode_KeyboardAndMouse | 0x141342e30 | 0x143a1a2e0 |
| GetDefaultSpeechToText | 0x141343000 | 0x143a1a2f0 |
| GetDefaultSpeedControllerX | 0x141342f40 | 0x143a1a300 |
| GetDefaultSpeedControllerX_Alpha | 0x141343030 | 0x143a1a310 |
| GetDefaultSpeedControllerY | 0x141342f40 | 0x143a1a320 |
| GetDefaultSpeedControllerY_Alpha | 0x141343030 | 0x143a1a330 |
| GetDefaultStatsVisibility | 0x141342de0 | 0x143a1a340 |
| GetDefaultSwapMouseButtons | 0x141342de0 | 0x143a1a350 |
| GetDefaultSwitchSticks | 0x141342de0 | 0x143a1a360 |
| GetDefaultSyncMethod | 0x141342de0 | 0x143a1a370 |
| GetDefaultTeamChat | 0x141342de0 | 0x143a1a380 |
| GetDefaultTeamVoiceChatJoin | 0x141342de0 | 0x143a1a390 |
| GetDefaultTextToSpeech | 0x141343050 | 0x143a1a3a0 |
| GetDefaultTextureFilterQuality | 0x141342f00 | 0x143a1a3b0 |
| GetDefaultTextureQuality | 0x141342f00 | 0x143a1a3c0 |
| GetDefaultThrottleEngineTickRate | 0x141342e30 | 0x143a1a3d0 |
| GetDefaultVoiceChatMode | 0x14133c120 | 0x143a1a3e0 |
| GetDisplayPlaystationButtons | 0x141343080 | 0x143a1a3f0 |
| GetDynamicBackgrounds | 0x1413430a0 | 0x143a1a400 |
| GetEnableController | 0x1413430c0 | 0x143a1a410 |
| GetForceFeedbackEnabled | 0x1413430e0 | 0x143a1a420 |
| GetGamma | 0x141343100 | 0x143a1a430 |
| GetGroupMembersCanInvite | 0x141343120 | 0x143a1a440 |
| GetHighContrastMenus | 0x141343140 | 0x143a1a450 |
| GetImprovedControlResponse | 0x141343160 | 0x143a1a460 |
| GetInGameMusicVolume | 0x141343180 | 0x143a1a470 |
| GetInvertControllerX | 0x1413431a0 | 0x143a1a480 |
| GetInvertControllerY | 0x1413431c0 | 0x143a1a490 |
| GetInvertMouseY | 0x1413431e0 | 0x143a1a4a0 |
| GetJoinability | 0x141343200 | 0x143a1a4b0 |
| GetLargeChatFonts | 0x141343220 | 0x143a1a4c0 |
| GetLetGamesReadToMe | 0x141343240 | 0x143a1a4d0 |
| GetLockOnTargetingMode_Controller | 0x141343270 | 0x143a1a4e0 |
| GetLockOnTargetingMode_KeyboardAndMouse | 0x141343290 | 0x143a1a4f0 |
| GetLockOnType_Controller | 0x1413432b0 | 0x143a1a500 |
| GetLockOnType_KeyboardAndMouse | 0x1413432d0 | 0x143a1a510 |
| GetMasterVolume | 0x141343320 | 0x143a1a520 |
| GetMatchChat | 0x141343340 | 0x143a1a530 |
| GetMaximumMatchmakingPing | 0x141343360 | 0x143a1a540 |
| GetMBGameUserSettings | 0x1413432f0 | 0x143a1a550 |
| GetMicrophoneSensitivity | 0x141343380 | 0x143a1a560 |
| GetMonitorList | 0x1413433a0 | 0x143a1a570 |
| GetMonitorSupportedFullscreenResolutions | 0x141343450 | 0x143a1a580 |
| GetMouseSensitivity | 0x141343550 | 0x143a1a590 |
| GetMusicVolume | 0x141343580 | 0x143a1a5a0 |
| GetMuteAudioWhenGameNotInFocus | 0x1413435a0 | 0x143a1a5b0 |
| GetNarrationVolume | 0x1413435c0 | 0x143a1a5c0 |
| GetNarrationVolume_Internal | 0x1413435f0 | 0x143a1a5d0 |
| GetNarrationVolume_PC | 0x1413435c0 | 0x143a1a5e0 |
| GetOverlayIntensity | 0x141343610 | 0x143a1a5f0 |
| GetOverridingRegion | 0x141343630 | 0x143a1a600 |
| GetPartyChat | 0x141343650 | 0x143a1a610 |
| GetPartyVoiceChatJoin | 0x141343670 | 0x143a1a620 |
| GetPlaceableSensitivity_Controller | 0x141343690 | 0x143a1a630 |
| GetPlaceableSensitivity_KeyboardAndMouse | 0x1413436b0 | 0x143a1a640 |
| GetProfanityFilter | 0x1413436d0 | 0x143a1a650 |
| GetReceiveWhispers | 0x1413436f0 | 0x143a1a660 |
| GetRenderScalePercentage | 0x141343710 | 0x143a1a670 |
| GetScreenSpaceReflectionsEnabled | 0x141343730 | 0x143a1a680 |
| GetSfxVolume | 0x1413437a0 | 0x143a1a690 |
| GetShowHUD | 0x1413437c0 | 0x143a1a6a0 |
| GetSoftLockTargetingMode_Controller | 0x1413437e0 | 0x143a1a6b0 |
| GetSoftLockTargetingMode_KeyboardAndMouse | 0x141343800 | 0x143a1a6c0 |
| GetSpeechToText | 0x141343820 | 0x143a1a6d0 |
| GetSpeechToText_Internal | 0x141343850 | 0x143a1a6e0 |
| GetSpeedControllerX | 0x1412f5b20 | 0x143a1a6f0 |
| GetSpeedControllerX_Alpha | 0x141343870 | 0x143a1a700 |
| GetSpeedControllerY | 0x141343890 | 0x143a1a710 |
| GetSpeedControllerY_Alpha | 0x1413438b0 | 0x143a1a720 |
| GetStatsScreenDisplayingMods | 0x1413438d0 | 0x143a1a730 |
| GetStatsScreenOpenTab | 0x1413438f0 | 0x143a1a740 |
| GetStatsVisibility | 0x141343910 | 0x143a1a750 |
| GetSwapMouseButtons | 0x141343930 | 0x143a1a760 |
| GetSwitchSticks | 0x141343950 | 0x143a1a770 |
| GetSyncMethod | 0x141343970 | 0x143a1a780 |
| GetTeamChat | 0x141343990 | 0x143a1a790 |
| GetTeamVoiceChatJoin | 0x1413439b0 | 0x143a1a7a0 |
| GetTextToSpeech | 0x1413439d0 | 0x143a1a7b0 |
| GetTextToSpeech_Internal | 0x141343a00 | 0x143a1a7c0 |
| GetTextureFilterQuality | 0x141343a20 | 0x143a1a7d0 |
| GetThrottleEngineTickRate | 0x141343a40 | 0x143a1a7e0 |
| GetUiVolume | 0x141343a60 | 0x143a1a7f0 |
| GetVoiceAudioOutputDevice | 0x141343aa0 | 0x143a1a800 |
| GetVoiceChatMode | 0x141343ad0 | 0x143a1a810 |
| GetVoiceChatVolume | 0x141343af0 | 0x143a1a820 |
| GetVoiceOutVolume | 0x141343b10 | 0x143a1a830 |
| GetVoVolume | 0x141343a80 | 0x143a1a840 |
| IsAllowedThrottleEngineTickRate | 0x141343b30 | 0x143a1a850 |
| RegisterAccessibilitySettingsChangedDelegate | 0x141343c80 | 0x143a1a860 |
| RegisterControllerIconsChangedDelegate | 0x141343d30 | 0x143a1a870 |
| SaveCloudSettings | 0x141343de0 | 0x143a1a880 |
| SaveKeyBindings | 0x141343e00 | 0x143a1a890 |
| SetAAMode | 0x141343e20 | 0x143a1a8a0 |
| SetActiveMonitor | 0x141343ea0 | 0x143a1a8b0 |
| SetAllowInvitesFrom | 0x141343f20 | 0x143a1a8c0 |
| SetAudioInputDevice | 0x141343fa0 | 0x143a1a8d0 |
| SetAudioOutputDevice | 0x141344040 | 0x143a1a8e0 |
| SetBloodEffects | 0x1413440e0 | 0x143a1a8f0 |
| SetCameraAutoRotationEnabled_Controller | 0x141344170 | 0x143a1a900 |
| SetCameraAutoRotationEnabled_KeyboardAndMouse | 0x141344200 | 0x143a1a910 |
| SetCameraCombatZoomMode_Controller | 0x141344290 | 0x143a1a920 |
| SetCameraCombatZoomMode_KeyboardAndMouse | 0x141344310 | 0x143a1a930 |
| SetCameraLockOnTargetTrackingEnabled_Controller | 0x141344390 | 0x143a1a940 |
| SetCameraLockOnTargetTrackingEnabled_KeyboardAndMouse | 0x141344420 | 0x143a1a950 |
| SetChatWheelMode | 0x1413444a0 | 0x143a1a960 |
| SetControllerAcceleration | 0x141344520 | 0x143a1a970 |
| SetCulture | 0x1413445e0 | 0x143a1a980 |
| SetDisplayPlaystationButtons | 0x1413446e0 | 0x143a1a990 |
| SetDynamicBackgrounds | 0x141344770 | 0x143a1a9a0 |
| SetEnableController | 0x1413447f0 | 0x143a1a9b0 |
| SetForceFeedbackEnabled | 0x141344870 | 0x143a1a9c0 |
| SetGamma | 0x1413448f0 | 0x143a1a9d0 |
| SetGroupMembersCanInvite | 0x141344970 | 0x143a1a9e0 |
| SetHighContrastMenus | 0x141344a00 | 0x143a1a9f0 |
| SetImprovedControlResponse | 0x141344a80 | 0x143a1aa00 |
| SetInGameMusicVolume | 0x141344b10 | 0x143a1aa10 |
| SetInvertControllerX | 0x141344b90 | 0x143a1aa20 |
| SetInvertControllerY | 0x141344c20 | 0x143a1aa30 |
| SetInvertMouseY | 0x141344cb0 | 0x143a1aa40 |
| SetJoinability | 0x141344d30 | 0x143a1aa50 |
| SetLargeChatFonts | 0x141344db0 | 0x143a1aa60 |
| SetLetGamesReadToMe | 0x141344e30 | 0x143a1aa70 |
| SetLockOnTargetingMode_Controller | 0x141344ec0 | 0x143a1aa80 |
| SetLockOnTargetingMode_KeyboardAndMouse | 0x141344f40 | 0x143a1aa90 |
| SetLockOnType_Controller | 0x141344fc0 | 0x143a1aaa0 |
| SetLockOnType_KeyboardAndMouse | 0x141345040 | 0x143a1aab0 |
| SetMasterVolume | 0x1413450c0 | 0x143a1aac0 |
| SetMatchChat | 0x141345140 | 0x143a1aad0 |
| SetMaximumMatchmakingPing | 0x1413451c0 | 0x143a1aae0 |
| SetMicrophoneSensitivity | 0x141345240 | 0x143a1aaf0 |
| SetMouseSensitivity | 0x1413452c0 | 0x143a1ab00 |
| SetMusicVolume | 0x141345340 | 0x143a1ab10 |
| SetMuteAudioWhenGameNotInFocus | 0x1413453c0 | 0x143a1ab20 |
| SetNarrationVolume | 0x141345440 | 0x143a1ab30 |
| SetNarrationVolume_Internal | 0x1413454c0 | 0x143a1ab40 |
| SetNarrationVolume_PC | 0x141345440 | 0x143a1ab50 |
| SetOverlayIntensity | 0x141345540 | 0x143a1ab60 |
| SetOverridingRegion | 0x1413455e0 | 0x143a1ab70 |
| SetPartyChat | 0x141345660 | 0x143a1ab80 |
| SetPartyVoiceChatJoin | 0x1413456e0 | 0x143a1ab90 |
| SetPlaceableSensitivity_Controller | 0x141345760 | 0x143a1aba0 |
| SetPlaceableSensitivity_KeyboardAndMouse | 0x1413457e0 | 0x143a1abb0 |
| SetProfanityFilter | 0x141345860 | 0x143a1abc0 |
| SetReceiveWhispers | 0x1413458f0 | 0x143a1abd0 |
| SetRenderScalePercentage | 0x141345980 | 0x143a1abe0 |
| SetScreenSpaceReflectionsEnabled | 0x141345a00 | 0x143a1abf0 |
| SetSfxVolume | 0x141345a80 | 0x143a1ac00 |
| SetShowHUD | 0x141345b00 | 0x143a1ac10 |
| SetSoftLockTargetingMode_Controller | 0x141345b90 | 0x143a1ac20 |
| SetSoftLockTargetingMode_KeyboardAndMouse | 0x141345c10 | 0x143a1ac30 |
| SetSpeechToText | 0x141345c90 | 0x143a1ac40 |
| SetSpeedControllerX | 0x141345d20 | 0x143a1ac50 |
| SetSpeedControllerY | 0x141345de0 | 0x143a1ac60 |
| SetStatsScreenDisplayingMods | 0x141345ea0 | 0x143a1ac70 |
| SetStatsScreenOpenTab | 0x141345f20 | 0x143a1ac80 |
| SetStatsVisibility | 0x141345fa0 | 0x143a1ac90 |
| SetSwapMouseButtons | 0x141346020 | 0x143a1aca0 |
| SetSwitchSticks | 0x1413460a0 | 0x143a1acb0 |
| SetSyncMethod | 0x141346120 | 0x143a1acc0 |
| SetTeamChat | 0x1413461a0 | 0x143a1acd0 |
| SetTeamVoiceChatJoin | 0x141346220 | 0x143a1ace0 |
| SetTextToSpeech | 0x1413462a0 | 0x143a1acf0 |
| SetTextureFilterQuality | 0x141346330 | 0x143a1ad00 |
| SetThrottleEngineTickRate | 0x1413463d0 | 0x143a1ad10 |
| SetUiVolume | 0x141346460 | 0x143a1ad20 |
| SetVoiceAudioOutputDevice | 0x141346560 | 0x143a1ad30 |
| SetVoiceChatMode | 0x141346600 | 0x143a1ad40 |
| SetVoiceChatVolume | 0x141346680 | 0x143a1ad50 |
| SetVoiceOutVolume | 0x141346700 | 0x143a1ad60 |
| SetVoVolume | 0x1413464e0 | 0x143a1ad70 |
| UnregisterAccessibilitySettingsChangedDelegate | 0x1413468c0 | 0x143a1ad80 |
| UnregisterControllerIconsChangedDelegate | 0x141346970 | 0x143a1ad90 |
| UpdateCloudIfDirty | 0x141346a20 | 0x143a1ada0 |
| UpdatePostProcessVolumes | 0x141346a40 | 0x143a1adb0 |

## GameViewportClient

Class params `0x144123b10`; resolver `0x1413496e0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0x80 | 0x14514f3c0 |
| World | Object | 0x78 | 0x14514f400 |
| DebugProperties | Array | 0x48 | 0x14514f2c8 |
| ViewportConsole | Object | 0x40 | 0x14514f480 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| SSSwapControllers | 0 | 0x14514f380 |
| SetConsoleTarget | 4 | 0x14514f300 |
| ShowTitleSafeArea | 0 | 0x14514f340 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## LocalPlayer

Class params `0x144167240`; resolver `0x1426fadf0`; size `0x1c8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ControllerId | Int | 0x108 | 0x14519a570 |
| bSentSplitJoin | Bool | unresolved | 0x14519a5d0 |
| PendingLevelPlayerControllerClass | Class | 0x98 | 0x14519a650 |
| AspectRatioAxisConstraint | Byte | 0x94 | 0x14519a6d0 |
| ViewportClient | Object | 0x70 | 0x14519a710 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBAFKManager

Class params `0x14396cfe0`; resolver `0x1412c4200`; size `0x1f0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bWasMatchInProgress | Bool | 0x1e8 | 0x144f39ff0 |
| LocalPlayerInfo | Struct | 0x48 | 0x144f3a070 |
| GameInstance | Object | 0x40 | 0x144f3a0b0 |
| WorldSingleton | Object | 0x38 | 0x144f3a0f0 |
| ActivationTimeOnJoin | Float | 0x34 | 0x144f39f38 |
| LastChanceCountdown | Float | 0x30 | 0x144f39fb8 |
| MenuKickTime | Float | 0x2c | 0x144f3a038 |
| KickTime | Float | 0x28 | 0x144f3a130 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBAFKWarningOverlay

Class params `0x14396d230`; resolver `0x1412c3f00`; size `0x2f8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LastChanceCountdown | Int | 0x2f0 | 0x144f3a1c8 |
| LastChanceCountdownTimerHandle | Struct | 0x2e8 | 0x144f3a280 |
| GameInstance | Object | 0x2e0 | 0x144f3a2c0 |
| AFKManager | Object | 0x2d8 | 0x144f3a300 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetLastChanceCountdown | 4 | 0x144f3a200 |
| OnLastChanceCountdownUpdated | 0 | 0x144f3a240 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetLastChanceCountdown | 0x1412c66c0 | 0x1439726d8 |

## MBAchievementsManager

Class params `0x14396a110`; resolver `0x1412bed70`; size `0xb8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0x58 | 0x144f38690 |
| LocalPlayerId | Struct | 0x30 | 0x144f386d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnPlayerQuestsInitComplete | 40 | 0x144f38650 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnPlayerQuestsInitComplete | 0x1412c2e50 | 0x14396ca08 |

## MBBaseReticleActor

Class params `0x143981db0`; resolver `0x1412d20f0`; size `0x3a8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PlayerController | Object | 0x3a0 | 0x144f46be0 |
| ReticleWidget | Object | 0x398 | 0x144f46c20 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBBaseWidget

Class params `0x1439849f0`; resolver `0x1412c59e0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CachedSpectatorCameraMode | Enum | 0x36a | 0x144f48390 |
| CachedSpectatorType | Enum | 0x369 | 0x144f48410 |
| bIsTickEnabled | Bool | 0x368 | 0x144f48490 |
| OwnerProxyLastFrame | Object | 0x360 | 0x144f48510 |
| ControllingPlayerProxyLastFrame | Object | 0x358 | 0x144f48550 |
| WidgetOwnerProxy | Object | 0x350 | 0x144f48590 |
| CachedWidgetManager | Object | 0x348 | 0x144f485d0 |
| CachedOwningPlayerController | Object | 0x340 | 0x144f48610 |
| CachedHUDContainerWidget | Object | 0x338 | 0x144f48650 |
| CachedHudComponent | Object | 0x330 | 0x144f48690 |
| bRegisterSpectatorDelegates | Bool | 0x32b | 0x144f486d0 |
| bNeedsOnControllingPlayerProxyChanged | Bool | 0x32a | 0x144f48750 |
| bNeedsGameOvertimeEvent | Bool | 0x329 | 0x144f487d0 |
| bNeedsReceiveOutputEvent | Bool | 0x328 | 0x144f48850 |
| WidgetOwnerComponent | Object | 0x320 | 0x144f488d0 |
| bConvertedGraffitiWidgetAvailable | Bool | 0x319 | 0x144f48910 |
| WidgetAdvanceRate | Enum | 0x318 | 0x144f48990 |
| CommonLevelObjectProxy | Object | 0x310 | 0x144f48a10 |
| WidgetOwnerActor | Object | 0x308 | 0x144f48a50 |
| bDoZeroTickWhenContainerBecomesVisible | Bool | 0x300 | 0x144f48a90 |
| WatchOwnerProxyAttributes | Array | 0x2f0 | 0x144f48298 |
| WatchOwnerProxyTokens | Array | 0x2e0 | 0x144f48718 |
| WatchControllingPlayerAttributes | Array | 0x2d0 | 0x144f48818 |
| WatchControllingPlayerTokens | Array | 0x2c0 | 0x144f48958 |
| bIgnoreTimeDilation | Bool | 0x2bc | 0x144f48b10 |
| bTickValidControllerRequiresPlayerState | Bool | 0x2bb | 0x144f48b80 |
| bCanTickWhilstOwnerHidden | Bool | 0x2ba | 0x144f48bf0 |
| bCanTickWhilstHidden | Bool | 0x2b9 | 0x144f48c70 |
| bCanEverBeTicked | Bool | 0x2b8 | 0x144f48ce0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetControllerPlayerState | 8 | 0x144f474e0 |
| GetControllingPlayerProxy | 8 | 0x144f47560 |
| GetOwnerActor | 8 | 0x144f475e0 |
| GetOwnerActorState | 8 | 0x144f47660 |
| GetOwningPlayerController | 8 | 0x144f476e0 |
| InitialiseToOwner | 8 | 0x144f47760 |
| IsTickEnabled | 1 | 0x144f47820 |
| NativeOnControllingPlayerAttributeChanged | 16 | 0x144f47860 |
| NativeOnControllingPlayerTokenChanged | 16 | 0x144f47920 |
| NativeOnOwnerProxyAttributeChanged | 16 | 0x144f47a40 |
| NativeOnOwnerProxyTokenChanged | 16 | 0x144f47b00 |
| OnControllingPlayerAttributeChanged | 16 | 0x144f47bb0 |
| OnControllingPlayerProxyChanged | 0 | 0x144f47bf0 |
| OnControllingPlayerTokenChanged | 16 | 0x144f47cb0 |
| OnGameOvertime | 0 | 0x144f47cf0 |
| OnHUDContainerVisibilityChanged | 1 | 0x144f47db0 |
| OnOwnerProxyAttributeChanged | 16 | 0x144f47e60 |
| OnOwnerProxyChanged | 0 | 0x144f47ea0 |
| OnOwnerProxyTokenChanged | 16 | 0x144f47f60 |
| OnPlayerControllerPossessProxy | 16 | 0x144f48020 |
| OnPlayerControllerUnpossessProxy | 16 | 0x144f480e0 |
| OnWidgetInitialised | 0 | 0x144f48120 |
| ReceiveOutputEvent | 16 | 0x144f48210 |
| SetTickEnabled | 1 | 0x144f482d0 |
| TickValidController | 60 | 0x144f48350 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBCaptureFlagManagerData

Class params `0x14448ab40`; resolver `0x142ad8650`; size `0x40`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CapsGapWhenMatchmakingClosed | Int | 0x38 | 0x145266b58 |
| NumRemainingCapsWhenMatchmakingClosed | Int | 0x34 | 0x145266b90 |
| NumCapsRequiredToWin | Int | 0x30 | 0x145266bc8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBCapturePointManagerData

Class params `0x14448c690`; resolver `0x142ad9560`; size `0xad8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| AllyFinishCaptureVO | Array | 0xac8 | 0x145268238 |
| EnemyFinishCaptureVO | Array | 0xab8 | 0x1452682b0 |
| EnemyStartCaptureVO | Array | 0xaa8 | 0x145268330 |
| CloseScoreVO | Struct | 0x758 | 0x1452683b0 |
| NearlyLostVO | Struct | 0x408 | 0x1452683f0 |
| NearlyWonVO | Struct | 0xb8 | 0x145268430 |
| PointsGapForCloseGame | Int | 0xb4 | 0x145268470 |
| NumRemainingPointsNearlyEndedVO | Int | 0xb0 | 0x1452684a8 |
| MaxAcheivablePoints | Int | 0xac | 0x1452684e0 |
| bUseMaxAcheivablePoints | Bool | 0xa8 | 0x145268520 |
| SelectNextCapturePointsTimeThreshold | Float | 0xa4 | 0x145268568 |
| CycleInactiveTime | Float | 0xa0 | 0x1452685a0 |
| CycleActiveTime | Float | 0x9c | 0x1452685d8 |
| bInfiniteCycleActiveTime | Bool | 0x98 | 0x145268610 |
| CycleWaitInitial | Float | 0x94 | 0x145268658 |
| CycleCapturePoints | Bool | 0x91 | 0x145268690 |
| KingOfTheHill | Bool | 0x90 | 0x1452686e0 |
| CustomObjectiveActivationList | Struct | 0x80 | 0x145268730 |
| NumPointsRemainingWaves | Array | 0x70 | 0x145268770 |
| NumPointsToActivateEachRound | Array | 0x60 | 0x1452687f0 |
| NumCapturePoints | Int | 0x5c | 0x145268860 |
| PointsGapWhenMatchmakingClosed | Int | 0x58 | 0x145268898 |
| NumRemainingPointsWhenMatchmakingClosed | Int | 0x54 | 0x1452688d0 |
| PointsRequiredToWinOnOvertime | Int | 0x50 | 0x145268908 |
| PointsRequiredToWin | Int | 0x4c | 0x145268940 |
| GivePlayersCurrencyAmount | Int | 0x48 | 0x145268978 |
| GivePlayersCurrencyCooldown | Float | 0x44 | 0x1452689b0 |
| GivePlayersCurrencyOverTime | Bool | 0x40 | 0x1452689f0 |
| PointsOnCapturePointCaptured | Int | 0x3c | 0x145268a38 |
| PointsOnCapturePointTick | Int | 0x38 | 0x145268a70 |
| PointsOnMinionEnemyPortal | Int | 0x34 | 0x145268aa8 |
| PointsOnPlayerDeath | Int | 0x30 | 0x145268ae0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBCapturePointManagerState

Class params `0x144488290`; resolver `0x142ad7ef0`; size `0x1b8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PointsOnPlayerDeathConditions | Array | 0x1a8 | 0x14526c3d0 |
| bInfiniteCycleActiveTime | Bool | 0x1a1 | 0x14526c450 |
| bSelectNextCapturePointsPending | Bool | 0x1a0 | 0x14526c4a0 |
| CurrentWaveIndex | Int | 0x19c | 0x14526c4e8 |
| bKioskModeEndGame | Bool | 0x199 | 0x14526c520 |
| bIsOvertime | Bool | 0x198 | 0x14526c570 |
| PointsActivated | MulticastDelegate | 0x188 | 0x14526c5c0 |
| PointsReachedDelegates | Array | 0x178 | 0x14526c600 |
| PhaseEndDelegates | Array | 0x168 | 0x14526c680 |
| TimerDelegates | Array | 0x158 | 0x14526c700 |
| bPauseTimer | Bool | 0x154 | 0x14526c780 |
| bPlayedNearlyEndedVO | Bool | 0x153 | 0x14526c7d0 |
| bAllowPlayerSlotRefilling | Bool | 0x152 | 0x14526c820 |
| bSetInitialCycle | Bool | 0x151 | 0x14526c870 |
| bIsActive | Bool | 0x150 | 0x14526c8c0 |
| OnExitedMulticasters | Array | 0x140 | 0x14526c908 |
| OnEnteredMulticasters | Array | 0x130 | 0x14526c980 |
| OnLostMulticasters | Array | 0x120 | 0x14526ca00 |
| OnCapturedMulticasters | Array | 0x110 | 0x14526ca80 |
| CapturePoints | Array | 0x100 | 0x14526cb00 |
| CapturePointTeamIds | Array | 0xf0 | 0x14526cb80 |
| NumPointsToActivateEachRoundOverride | Array | 0xe0 | 0x14526cbf0 |
| PreviousSingleActiveControlPointIndex | Int | 0xd8 | 0x14526cc60 |
| NextControlPointsIndices | Array | 0xc8 | 0x14526cc98 |
| CurrentControlPointsIndices | Array | 0xb8 | 0x14526cd08 |
| PointsRequiredToWinOverride | Int | 0xb4 | 0x14526cd78 |
| CurrentRound | Int | 0xb0 | 0x14526cdb0 |
| GiveCurrencyTimer | Float | 0xac | 0x14526cde8 |
| NumTimesCyclicCapturePointsActive | Int | 0xa8 | 0x14526ce20 |
| CapturePointsActive | Bool | 0xa4 | 0x14526ce60 |
| CapturePointTimer | Float | 0xa0 | 0x14526cea8 |
| Points | Array | 0x90 | 0x14526cee0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddPoints | 112 | 0x145268fb0 |
| AddPointsOnCapturePointCaptured | 112 | 0x145269070 |
| AddPointsOnCapturePointTick | 112 | 0x145269130 |
| AddPointsOnMinionEnemyPortal | 112 | 0x1452691f0 |
| AddPointsOnPlayerDeath | 272 | 0x145269330 |
| AddPointsReachedEvent | 128 | 0x145269460 |
| AddTimerEvent | 128 | 0x1452695a0 |
| FilterFunction_CapturePointIndex | 24 | 0x1452696b0 |
| FilterFunction_GiveCurrency | 24 | 0x1452697c0 |
| GMC_ActivateCapturePoint | 120 | 0x145269bb0 |
| GMC_AddPointCapturedEvent | 120 | 0x145269cb0 |
| GMC_AddPointEnteredEvent | 120 | 0x145269db0 |
| GMC_AddPointExitedEvent | 120 | 0x145269eb0 |
| GMC_AddPointLostEvent | 120 | 0x145269fb0 |
| GMC_AddPointsActivatedEvent | 120 | 0x14526a0b0 |
| GMC_AddPointsOnCapturePointCaptured | 120 | 0x14526a1b0 |
| GMC_AddPointsOnCapturePointTick | 120 | 0x14526a2b0 |
| GMC_AddPointsOnMinionEnemyPortal | 120 | 0x14526a3b0 |
| GMC_AddPointsReachedEvent | 120 | 0x14526a4b0 |
| GMC_AddTimerEvent | 120 | 0x14526a5b0 |
| GMC_DeactivateCapturePoint | 120 | 0x14526a6b0 |
| GMC_OnCapturePointChangedTeam | 120 | 0x14526a7b0 |
| GMC_PauseCapturePoints | 120 | 0x14526a8b0 |
| GMC_PlayCapturePointVOOnNearestPlayer | 120 | 0x14526a9b0 |
| GMC_RegisterCapturePoint | 120 | 0x14526aab0 |
| GMC_RemovePointCapturedEvent | 120 | 0x14526abb0 |
| GMC_RemovePointEnteredEvent | 120 | 0x14526acb0 |
| GMC_RemovePointExitedEvent | 120 | 0x14526adb0 |
| GMC_RemovePointLostEvent | 120 | 0x14526aeb0 |
| GMC_RemovePointsActivatedEvent | 120 | 0x14526afb0 |
| GMC_RequestTimeRemaining | 120 | 0x14526b0b0 |
| GMC_SetActive | 120 | 0x14526b1b0 |
| GetFilterFunction_CapturePointIndex | 136 | 0x1452698c0 |
| GetFilterFunction_GiveCurrency | 128 | 0x145269980 |
| GetPoints | 8 | 0x145269a30 |
| GetPointsRequiredToWin | 4 | 0x145269ab0 |
| OnActorDiedFromContact | 272 | 0x14526b270 |
| OnCapturePointChangedTeam | 112 | 0x14526b330 |
| OnGameEnded | 120 | 0x14526b3f0 |
| OnGameStarted | 104 | 0x14526b470 |
| RegisterOnPointCapturedCallback | 128 | 0x14526b570 |
| RegisterOnPointEnteredCallback | 128 | 0x14526b670 |
| RegisterOnPointExitedCallback | 128 | 0x14526b770 |
| RegisterOnPointLostCallback | 128 | 0x14526b870 |
| RegisterOnPointsActivatedCallback | 120 | 0x14526b930 |
| SetCapturePointActive | 112 | 0x14526b9f0 |
| SetCapturePointInactive | 112 | 0x14526bab0 |
| SetCapturePointNextActive | 112 | 0x14526bbb0 |
| SetCapturePointPause | 112 | 0x14526bc70 |
| SetCapturePointUnpause | 112 | 0x14526bd30 |
| SetTimerPaused | 112 | 0x14526be00 |
| TurnOffActiveCapturePoints | 112 | 0x14526bed0 |
| UnregisterOnPointCapturedCallback | 128 | 0x14526bfd0 |
| UnregisterOnPointEnteredCallback | 128 | 0x14526c0d0 |
| UnregisterOnPointExitedCallback | 128 | 0x14526c1d0 |
| UnregisterOnPointLostCallback | 128 | 0x14526c2d0 |
| UnregisterOnPointsActivatedCallback | 120 | 0x14526c390 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddPoints | 0x142add820 | 0x14448e380 |
| AddPointsOnCapturePointCaptured | 0x142add950 | 0x14448e390 |
| AddPointsOnCapturePointTick | 0x142adda50 | 0x14448e3a0 |
| AddPointsOnMinionEnemyPortal | 0x142addb50 | 0x14448e3b0 |
| AddPointsOnPlayerDeath | 0x142addc50 | 0x14448e3c0 |
| AddPointsReachedEvent | 0x142addea0 | 0x14448e3d0 |
| AddTimerEvent | 0x142ade060 | 0x14448e3e0 |
| FilterFunction_CapturePointIndex | 0x142ade4d0 | 0x14448e3f0 |
| FilterFunction_GiveCurrency | 0x142ade590 | 0x14448e400 |
| GetFilterFunction_CapturePointIndex | 0x142ae01a0 | 0x14448e410 |
| GetFilterFunction_GiveCurrency | 0x142ae02c0 | 0x14448e420 |
| GetPoints | 0x142ae0410 | 0x14448e430 |
| GetPointsRequiredToWin | 0x142ae04a0 | 0x14448e440 |
| GMC_ActivateCapturePoint | 0x142ade650 | 0x14448e450 |
| GMC_AddPointCapturedEvent | 0x142ade780 | 0x14448e460 |
| GMC_AddPointEnteredEvent | 0x142ade8b0 | 0x14448e470 |
| GMC_AddPointExitedEvent | 0x142ade9e0 | 0x14448e480 |
| GMC_AddPointLostEvent | 0x142adeb10 | 0x14448e490 |
| GMC_AddPointsActivatedEvent | 0x142adec40 | 0x14448e4a0 |
| GMC_AddPointsOnCapturePointCaptured | 0x142aded70 | 0x14448e4b0 |
| GMC_AddPointsOnCapturePointTick | 0x142adeea0 | 0x14448e4c0 |
| GMC_AddPointsOnMinionEnemyPortal | 0x142adefd0 | 0x14448e4d0 |
| GMC_AddPointsReachedEvent | 0x142adf100 | 0x14448e4e0 |
| GMC_AddTimerEvent | 0x142adf230 | 0x14448e4f0 |
| GMC_DeactivateCapturePoint | 0x142adf360 | 0x14448e500 |
| GMC_OnCapturePointChangedTeam | 0x142adf490 | 0x14448e510 |
| GMC_PauseCapturePoints | 0x142adf5c0 | 0x14448e520 |
| GMC_PlayCapturePointVOOnNearestPlayer | 0x142adf6f0 | 0x14448e530 |
| GMC_RegisterCapturePoint | 0x142adf820 | 0x14448e540 |
| GMC_RemovePointCapturedEvent | 0x142adf950 | 0x14448e550 |
| GMC_RemovePointEnteredEvent | 0x142adfa80 | 0x14448e560 |
| GMC_RemovePointExitedEvent | 0x142adfbb0 | 0x14448e570 |
| GMC_RemovePointLostEvent | 0x142adfce0 | 0x14448e580 |
| GMC_RemovePointsActivatedEvent | 0x142adfe10 | 0x14448e590 |
| GMC_RequestTimeRemaining | 0x142adff40 | 0x14448e5a0 |
| GMC_SetActive | 0x142ae0070 | 0x14448e5b0 |
| OnActorDiedFromContact | 0x142ae0600 | 0x14448e5c0 |
| OnCapturePointChangedTeam | 0x142ae07b0 | 0x14448e5d0 |
| OnGameEnded | 0x142ae08b0 | 0x14448e5e0 |
| OnGameStarted | 0x142ae09b0 | 0x14448e5f0 |
| RegisterOnPointCapturedCallback | 0x142ae0a50 | 0x14448e600 |
| RegisterOnPointEnteredCallback | 0x142ae0bc0 | 0x14448e610 |
| RegisterOnPointExitedCallback | 0x142ae0d30 | 0x14448e620 |
| RegisterOnPointLostCallback | 0x142ae0ea0 | 0x14448e630 |
| RegisterOnPointsActivatedCallback | 0x142ae1010 | 0x14448e640 |
| SetCapturePointActive | 0x142ae1270 | 0x14448e650 |
| SetCapturePointInactive | 0x142ae1370 | 0x14448e660 |
| SetCapturePointNextActive | 0x142ae1470 | 0x14448e670 |
| SetCapturePointPause | 0x142ae15b0 | 0x14448e680 |
| SetCapturePointUnpause | 0x142ae16b0 | 0x14448e690 |
| SetTimerPaused | 0x142ae17b0 | 0x14448e6a0 |
| TurnOffActiveCapturePoints | 0x142ae18b0 | 0x14448e6b0 |
| UnregisterOnPointCapturedCallback | 0x142ae19b0 | 0x14448e6c0 |
| UnregisterOnPointEnteredCallback | 0x142ae1b20 | 0x14448e6d0 |
| UnregisterOnPointExitedCallback | 0x142ae1c90 | 0x14448e6e0 |
| UnregisterOnPointLostCallback | 0x142ae1e00 | 0x14448e6f0 |
| UnregisterOnPointsActivatedCallback | 0x142ae1f70 | 0x14448e700 |

## MBCapturePointManagerWidget

Class params `0x143997eb0`; resolver `0x1412e1e10`; size `0x400`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bInfiniteCycleActiveTimeLastFrame | Bool | 0x3f9 | 0x144f59000 |
| bIsWaitingForPlayersLastFrame | Bool | 0x3f8 | 0x144f59080 |
| bInitialised | Bool | 0x3f7 | 0x144f59100 |
| bGameStartedLastFrame | Bool | 0x3f6 | 0x144f59180 |
| CapturePointTimerIntLastFrame | Int | 0x3f0 | 0x144f59048 |
| PreMatchCountdownTimerIntLastFrame | Int | 0x3ec | 0x144f590c8 |
| AllyTeamIdLastFrame | Int | 0x3e8 | 0x144f59148 |
| PointsRequiredToWinLastFrame | Int | 0x3e4 | 0x144f591c8 |
| EnemyTeamPointsLastFrame | Int | 0x3e0 | 0x144f59200 |
| AllyTeamPointsLastFrame | Int | 0x3dc | 0x144f59238 |
| bGameStarted | Bool | 0x3d9 | 0x144f59270 |
| bCapturePointsActive | Bool | 0x3d8 | 0x144f592f0 |
| CapturePointTimerInt | Int | 0x3d4 | 0x144f592b8 |
| PreMatchCountdownTimerInt | Int | 0x3d0 | 0x144f59338 |
| CapturePointWidgetData | Array | 0x3c0 | 0x144f59370 |
| NumCapturePointsOwnedByEnemies | Int | 0x3b8 | 0x144f593a8 |
| NumCapturePointsOwnedByAllies | Int | 0x3b4 | 0x144f59420 |
| PointsRequiredToWin | Int | 0x3b0 | 0x144f59458 |
| EnemyTeamPoints | Int | 0x3ac | 0x144f59490 |
| AllyTeamPoints | Int | 0x3a8 | 0x144f594c8 |
| CapturePointManagerProxy | Object | 0x3a0 | 0x144f59500 |
| CapturePointIconWidgets | Array | 0x390 | 0x144f59540 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| IsInfiniteCycleActiveTime | 1 | 0x144f58960 |
| OnAllyTeamAwardedKillPoints | 12 | 0x144f589a0 |
| OnAllyTeamPointsChanged | 0 | 0x144f589e0 |
| OnCapturePointActiveChanged | 4 | 0x144f58a20 |
| OnCapturePointCaptureValueChanged | 4 | 0x144f58a60 |
| OnCapturePointTeamChanged | 4 | 0x144f58b90 |
| OnCapturePointTelegraphActiveChanged | 4 | 0x144f58bd0 |
| OnCapturePointTelegraphTimeChanged | 4 | 0x144f58c80 |
| OnCapturePointTimerChanged | 0 | 0x144f58cc0 |
| OnCapturePointUnderAttackChanged | 4 | 0x144f58d00 |
| OnCapturePointsActivated | 0 | 0x144f58aa0 |
| OnCapturePointsDeactivated | 0 | 0x144f58ae0 |
| OnEnemyTeamPointsChanged | 0 | 0x144f58d40 |
| OnGameStarted | 0 | 0x144f58d80 |
| OnGameUnstarted | 0 | 0x144f58dc0 |
| OnGlobalManagerMessageCreated | 16 | 0x144f58e80 |
| OnInitialised | 0 | 0x144f58ec0 |
| OnIsWaitingForPlayersEnded | 0 | 0x144f58f00 |
| OnIsWaitingForPlayersStarted | 0 | 0x144f58f40 |
| OnPointsRequiredToWinChanged | 0 | 0x144f58f80 |
| OnPreMatchCountdownTimerChanged | 0 | 0x144f58fc0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| IsInfiniteCycleActiveTime | 0x1412e3b70 | 0x14399b780 |
| OnGlobalManagerMessageCreated | 0x1412e3d30 | 0x14399b790 |

## MBCommonLevelObjectActorState

Class params `0x1444b0bf0`; resolver `0x142b05b80`; size `0xe0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bAllowPlayerSlotRefilling | Bool | 0xda | 0x145283e10 |
| bGameEnded | Bool | 0xd9 | 0x145283e60 |
| bGameStarted | Bool | 0xd8 | 0x145283eb0 |
| EndGameTimeDilationTimer | Float | 0xd4 | 0x145283ef8 |
| GlobalTimeDilation | Float | 0xd0 | 0x145283f30 |
| GameTimer | Float | 0xcc | 0x145283f68 |
| GameStartFrameNumber | Int | 0xc8 | 0x145283fa0 |
| AssignedSpawnPoints | Array | 0xb8 | 0x145283fd8 |
| WinningTeam | Int | 0xb4 | 0x145284050 |
| NextSpawnPointIndex | Int | 0xb0 | 0x145284088 |
| TeamStatsArray | Array | 0xa0 | 0x1452840c0 |
| TeamInfoArray | Array | 0x90 | 0x145284140 |
| GameModeManagerObj | Object | 0x88 | 0x1452841c0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GMC_RequestGlobalTimeDilation | 120 | 0x145283050 |
| GetActorFromIdViaCallback | 136 | 0x145282720 |
| GetActorsViaCallback | 136 | 0x145282870 |
| GetGameTime | 4 | 0x1452828f0 |
| GetHasGameStartedViaCallback | 128 | 0x1452829f0 |
| GetRespawnDataViaCallback | 136 | 0x145282b30 |
| GetRespawnTime | 16 | 0x145282bf0 |
| GetScoreRequiredToWin | 16 | 0x145282cb0 |
| GetTeamScore | 8 | 0x145282d60 |
| GetTeamStats | 24 | 0x145282e20 |
| GetTeamVictoryCount | 8 | 0x145282ed0 |
| GetWinningTeam | 4 | 0x145282f50 |
| HasGameEnded | 1 | 0x1452830e0 |
| HasGameStarted | 1 | 0x145283170 |
| IsValidTeamID | 8 | 0x145283230 |
| NativeOnActorDied | 264 | 0x1452832f0 |
| NativeOnFlagCaptured | 112 | 0x1452833b0 |
| NativeOnGameEnded | 120 | 0x145283470 |
| NativeOnGameOvertime | 104 | 0x1452834f0 |
| NativeOnGameStarted | 104 | 0x145283570 |
| NativeOnPlayerRespawned | 184 | 0x145283630 |
| NativeOnTeamCapturePointScoreChanged | 112 | 0x1452836f0 |
| NativeOnTeamSeedCountChanged | 112 | 0x1452837b0 |
| OnGameEnded | 112 | 0x145283870 |
| OnGameStarted | 104 | 0x1452838f0 |
| PUC_PostTeleportToSpawnPoint | 120 | 0x1452839f0 |
| SetTeamSpawnGroup | 8 | 0x145283b20 |
| SetTeamVictoryCounts | 16 | 0x145283bd0 |
| SetTeams | 104 | 0x145283a70 |
| TryTeleportToSpawnPoint | 112 | 0x145283c90 |
| TryTeleportToSpawnPointWithCallback | 136 | 0x145283dd0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetActorFromIdViaCallback | 0x142b08b10 | 0x1444b3b90 |
| GetActorsViaCallback | 0x142b08cc0 | 0x1444b3ba0 |
| GetGameTime | 0x142b08ed0 | 0x1444b3bb0 |
| GetHasGameStartedViaCallback | 0x142b08ef0 | 0x1444b3bc0 |
| GetRespawnDataViaCallback | 0x142b09050 | 0x1444b3bd0 |
| GetRespawnTime | 0x142b09200 | 0x1444b3be0 |
| GetScoreRequiredToWin | 0x142b092a0 | 0x1444b3bf0 |
| GetTeamScore | 0x142b09330 | 0x1444b3c00 |
| GetTeamStats | 0x142b093c0 | 0x1444b3c10 |
| GetTeamVictoryCount | 0x142b094a0 | 0x1444b3c20 |
| GetWinningTeam | 0x142b09530 | 0x1444b3c30 |
| GMC_RequestGlobalTimeDilation | 0x142b089e0 | 0x1444b3c40 |
| HasGameEnded | 0x142b09550 | 0x1444b3c50 |
| HasGameStarted | 0x142b09570 | 0x1444b3c60 |
| IsValidTeamID | 0x142b097d0 | 0x1444b3c70 |
| NativeOnActorDied | 0x142b09860 | 0x1444b3c80 |
| NativeOnFlagCaptured | 0x142b09a00 | 0x1444b3c90 |
| NativeOnGameEnded | 0x142b09b10 | 0x1444b3ca0 |
| NativeOnGameOvertime | 0x142b09c10 | 0x1444b3cb0 |
| NativeOnGameStarted | 0x142b09cb0 | 0x1444b3cc0 |
| NativeOnPlayerRespawned | 0x142b09d50 | 0x1444b3cd0 |
| NativeOnTeamCapturePointScoreChanged | 0x142b09ec0 | 0x1444b3ce0 |
| NativeOnTeamSeedCountChanged | 0x142b09fd0 | 0x1444b3cf0 |
| PUC_PostTeleportToSpawnPoint | 0x142b0a0e0 | 0x1444b3d00 |
| SetTeams | 0x142b0a480 | 0x1444b3d10 |
| SetTeamSpawnGroup | 0x142b0a310 | 0x1444b3d20 |
| SetTeamVictoryCounts | 0x142b0a3d0 | 0x1444b3d30 |
| TryTeleportToSpawnPoint | 0x142b0a510 | 0x1444b3d40 |
| TryTeleportToSpawnPointWithCallback | 0x142b0a600 | 0x1444b3d50 |

## MBConnectionManager

Class params `0x1439a83e0`; resolver `0x1412ece10`; size `0x50`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bDisconnectWarningShown | Bool | 0x48 | 0x144f66bf0 |
| PlayerInfos | Array | 0x38 | 0x144f66bb8 |
| GameInstance | Object | 0x30 | 0x144f66ca0 |
| WorldSingleton | Object | 0x28 | 0x144f66ce0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBCrowdManager

Class params `0x1439aae40`; resolver `0x1412ed440`; size `0x1c8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ActorMessageHandlers | Array | 0x108 | 0x144f68cd8 |
| GameInstance | Object | 0x100 | 0x144f68e90 |
| WorldSingleton | Object | 0xf8 | 0x144f68ed0 |
| VisualEventList | Map | 0xa8 | 0x144f68f10 |
| CrowdList | Array | 0x98 | 0x144f68f48 |
| LocalPlayerKillstreakEvent | Struct | 0x90 | 0x144f69040 |
| LocalPlayerNearbyEvent | Struct | 0x80 | 0x144f69080 |
| CrowdEventData | Map | 0x30 | 0x144f690c0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| Debug_TriggerCrowdEvent | 16 | 0x144f68360 |
| HandleActorGameMessage | 40 | 0x144f68420 |
| HandleCapturePointActiveMessage | 40 | 0x144f684e0 |
| HandleCapturePointInactiveMessage | 40 | 0x144f685a0 |
| HandleMatchNearingEndMessage | 40 | 0x144f68660 |
| HandlePlayerCastSuperMessage | 40 | 0x144f68720 |
| HandlePlayerDeathMessage | 40 | 0x144f687e0 |
| HandlePlayerEndRespawnMessage | 40 | 0x144f688a0 |
| HandlePlayerSuperReadyMessage | 40 | 0x144f68960 |
| HandleTeamLostCapturePointMessage | 40 | 0x144f68a20 |
| HandleTeamWonCapturePointMessage | 40 | 0x144f68ae0 |
| OnActorMessageCreated | 16 | 0x144f68ba0 |
| OnGlobalManagerMessageCreated | 16 | 0x144f68c60 |
| OnLocalPlayerTeamChanged | 8 | 0x144f68d10 |
| OnMessageRetired | 4 | 0x144f68d90 |
| OnMessageReverted | 4 | 0x144f68e10 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| Debug_TriggerCrowdEvent | 0x1412efe30 | 0x1439ad8e0 |
| HandleActorGameMessage | 0x1412f0ae0 | 0x1439ad8f0 |
| HandleCapturePointActiveMessage | 0x1412f0be0 | 0x1439ad900 |
| HandleCapturePointInactiveMessage | 0x1412f0ce0 | 0x1439ad910 |
| HandleMatchNearingEndMessage | 0x1412f0de0 | 0x1439ad920 |
| HandlePlayerCastSuperMessage | 0x1412f0ee0 | 0x1439ad930 |
| HandlePlayerDeathMessage | 0x1412f0fe0 | 0x1439ad940 |
| HandlePlayerEndRespawnMessage | 0x1412f10e0 | 0x1439ad950 |
| HandlePlayerSuperReadyMessage | 0x1412f11e0 | 0x1439ad960 |
| HandleTeamLostCapturePointMessage | 0x1412f12e0 | 0x1439ad970 |
| HandleTeamWonCapturePointMessage | 0x1412f13e0 | 0x1439ad980 |
| OnActorMessageCreated | 0x1412f14e0 | 0x1439ad990 |
| OnGlobalManagerMessageCreated | 0x1412f15b0 | 0x1439ad9a0 |
| OnLocalPlayerTeamChanged | 0x1412f1940 | 0x1439ad9b0 |
| OnMessageRetired | 0x1412f1a00 | 0x1439ad9c0 |
| OnMessageReverted | 0x1412f1a80 | 0x1439ad9d0 |

## MBCustomGameManager

Class params `0x1439aea40`; resolver `0x1412f2000`; size `0x288`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| Participants | Array | 0x190 | 0x144f6aa58 |
| PendingPlayerIdRequests | Array | 0x180 | 0x144f6ab10 |
| bAcceptInvitePending | Bool | 0x17c | 0x144f6abc0 |
| bShowCustomGameDebug | Bool | 0x17b | 0x144f6ac40 |
| bCreateSessionPending | Bool | 0x17a | 0x144f6acc0 |
| bIsLobbyLeader | Bool | 0x179 | 0x144f6ad40 |
| bTeamsLocked | Bool | 0x178 | 0x144f6adc0 |
| MaxMapRosterSize | Int | 0x174 | 0x144f6ab48 |
| Privacy | Enum | 0x170 | 0x144f6ae40 |
| GameName | Str | 0x160 | 0x144f6ac08 |
| LastServerAddress | Str | 0x150 | 0x144f6ac88 |
| CachedMapRosterString | Str | 0x140 | 0x144f6ad08 |
| CurrentMapIndex | Int | 0x138 | 0x144f6ad88 |
| MapRoster | Array | 0x128 | 0x144f6ae08 |
| SpectatorTeam | Struct | 0x110 | 0x144f6af30 |
| Teams | Struct | 0xe0 | 0x144f6af70 |
| MemberList | Array | 0x80 | 0x144f6aef8 |
| OnlineSessionManager | Object | 0x78 | 0x144f6aff0 |
| OnMemberSetTeamRequestFailed | MulticastDelegate | 0x68 | 0x144f6b030 |
| OnMemberTeamChanged | MulticastDelegate | 0x58 | 0x144f6b070 |
| OnCustomGameTeamNameChanged | MulticastDelegate | 0x48 | 0x144f6b0b0 |
| OnCustomGameNameChanged | MulticastDelegate | 0x38 | 0x144f6b0f0 |
| OnSessionUpdated | MulticastDelegate | 0x28 | 0x144f6b130 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddMapToRoster | 4 | 0x144f69c10 |
| CreateCustomGameSession | 0 | 0x144f69c50 |
| DebugClientFetchSessionData | 0 | 0x144f69c90 |
| DebugHostUpdateSessionData | 0 | 0x144f69cd0 |
| EndGame | 0 | 0x144f69d10 |
| GetCurrentMapIndex | 4 | 0x144f69d50 |
| GetMapRoster | 16 | 0x144f69dd0 |
| GetMapRosterSize | 4 | 0x144f69e80 |
| GetMaxMapRosterSize | 4 | 0x144f69ec0 |
| GetPrivacy | 1 | 0x144f69f80 |
| GetTeamMaxPlayers | 8 | 0x144f6a030 |
| GetTeamsLocked | 1 | 0x144f6a0f0 |
| InviteFriend | 16 | 0x144f6a130 |
| IsInCustomGameLobby | 1 | 0x144f6a1f0 |
| IsLocalPlayerLobbyLeader | 1 | 0x144f6a2b0 |
| IsMapInRoster | 8 | 0x144f6a370 |
| IsMember | 24 | 0x144f6a430 |
| LeaveLobby | 0 | 0x144f6a470 |
| OnPlayFabIdCached | 80 | 0x144f6a530 |
| RemoveMapFromRoster | 4 | 0x144f6a570 |
| RemoveMember | 16 | 0x144f6a5b0 |
| SetMaxMapRosterSize | 4 | 0x144f6a660 |
| SetPrivacy | 1 | 0x144f6a720 |
| SetTeamMaxPlayers | 8 | 0x144f6a7d0 |
| SetTeamsLocked | 1 | 0x144f6a890 |
| StartGame | 0 | 0x144f6a8d0 |
| TryGetMemberFromNetId | 80 | 0x144f6a9d0 |
| TryGetTimeSinceLastInvite | 24 | 0x144f6aa90 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddMapToRoster | 0x1412f57a0 | 0x1439b30a0 |
| CreateCustomGameSession | 0x1412f5850 | 0x1439b30b0 |
| DebugClientFetchSessionData | 0x1412f5870 | 0x1439b30c0 |
| DebugHostUpdateSessionData | 0x1412f5890 | 0x1439b30d0 |
| EndGame | 0x1412f58b0 | 0x1439b30e0 |
| GetCurrentMapIndex | 0x1412f58d0 | 0x1439b30f0 |
| GetMapRoster | 0x1412f58f0 | 0x1439b3100 |
| GetMapRosterSize | 0x1412f5b00 | 0x1439b3110 |
| GetMaxMapRosterSize | 0x1412f5b20 | 0x1439b3120 |
| GetPrivacy | 0x1412f5b40 | 0x1439b3130 |
| GetTeamMaxPlayers | 0x1412f5b60 | 0x1439b3140 |
| GetTeamsLocked | 0x1412f5bf0 | 0x1439b3150 |
| InviteFriend | 0x1412f5f90 | 0x1439b3160 |
| IsInCustomGameLobby | 0x1412f6030 | 0x1439b3170 |
| IsLocalPlayerLobbyLeader | 0x1412f6060 | 0x1439b3180 |
| IsMapInRoster | 0x1412f60c0 | 0x1439b3190 |
| IsMember | 0x1412f6150 | 0x1439b31a0 |
| LeaveLobby | 0x1412f6250 | 0x1439b31b0 |
| OnPlayFabIdCached | 0x1412f6790 | 0x1439b31c0 |
| RemoveMapFromRoster | 0x1412f6930 | 0x1439b31d0 |
| RemoveMember | 0x1412f69b0 | 0x1439b31e0 |
| SetMaxMapRosterSize | 0x1412f6ce0 | 0x1439b31f0 |
| SetPrivacy | 0x1412f6d60 | 0x1439b3200 |
| SetTeamMaxPlayers | 0x1412f6de0 | 0x1439b3210 |
| SetTeamsLocked | 0x1412f6ea0 | 0x1439b3220 |
| StartGame | 0x1412f6f30 | 0x1439b3230 |
| TryGetMemberFromNetId | 0x1412f6f50 | 0x1439b3240 |
| TryGetTimeSinceLastInvite | 0x1412f70c0 | 0x1439b3250 |

## MBCustomQueueMenu

Class params `0x1439bc120`; resolver `0x1412fa6f0`; size `0x488`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| SavedCustomQueue | Str | 0x448 | 0x144f744f0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnCheckCanPlayFinished | 32 | 0x144f74270 |
| OnMatchmakingStatusChanged | 1 | 0x144f74330 |
| SaveCustomQueue | 16 | 0x144f74370 |
| StartMatchmaking | 40 | 0x144f74470 |
| StrToAlnumStr | 32 | 0x144f744b0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnCheckCanPlayFinished | 0x1412fdfc0 | 0x1439bd550 |
| OnMatchmakingStatusChanged | 0x1412fe290 | 0x1439bd560 |
| SaveCustomQueue | 0x1412fe3d0 | 0x1439bd570 |
| StartMatchmaking | 0x1412fe470 | 0x1439bd580 |
| StrToAlnumStr | 0x1412fe590 | 0x1439bd590 |

## MBDeathReplayManager

Class params `0x1439ba260`; resolver `0x1412fb310`; size `0x800`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| DelayedStateChangeTimerHandle | Struct | 0x7f8 | 0x144f75dd0 |
| bReplayBufferDisabled | Bool | 0x7f2 | 0x144f75e10 |
| bIsChangingState | Bool | 0x7f1 | 0x144f75e90 |
| bDelayedStateChangePending | Bool | 0x7f0 | 0x144f75f10 |
| bSupportsPlayback | Bool | 0x7ef | 0x144f75f90 |
| bValidDeathReplayInfo | Bool | 0x7ee | 0x144f76010 |
| bDeathReplayCameraSetupPending | Bool | 0x7ed | 0x144f76090 |
| bDeathReplayPending | Bool | 0x7ec | 0x144f76110 |
| LatestRollbackEngine | Object | 0x7e0 | 0x144f76190 |
| ActiveTimeDilationHandles | Map | 0x790 | 0x144f75d98 |
| NextTimeDilationKey | Int | 0x788 | 0x144f75ed8 |
| PlayerIds | Array | 0x778 | 0x144f75f58 |
| DeathReplayInfo | Struct | 0x560 | 0x144f76210 |
| DeathReplayState | Enum | 0x558 | 0x144f76250 |
| DeathReplayDuration | Float | 0x554 | 0x144f76058 |
| DeathReplayTimer | Float | 0x550 | 0x144f760d8 |
| ProcessedLoadFrames | Set | 0x500 | 0x144f76158 |
| PendingDeathReplayLoadFrame | Int | 0x4f8 | 0x144f76308 |
| LastDeathReplayFrameNumber | Int | 0x4f4 | 0x144f76340 |
| DeathReplayStartFrame | Int | 0x4f0 | 0x144f76378 |
| DeathReplayLoadingSchedule | Struct | 0x448 | 0x144f763b0 |
| DeathReplayEventTimeline | Struct | 0x430 | 0x144f763f0 |
| LastLocalPlayerDeath | Struct | 0x3e0 | 0x144f76430 |
| DeathReplayBufferPlayback | Struct | 0x2f8 | 0x144f76470 |
| DeathReplayBufferStream | Struct | 0x2b0 | 0x144f764b0 |
| ReplayCameraManager | Object | 0x2a8 | 0x144f764f0 |
| BackgroundEngineInterface | Object | 0x2a0 | 0x144f76530 |
| ReplayInputPredictor | Object | 0x298 | 0x144f76570 |
| PlayerAssetHandler | Object | 0x290 | 0x144f765b0 |
| WorldSingleton | Object | 0x288 | 0x144f765f0 |
| World | Object | 0x280 | 0x144f76630 |
| DefaultKillFrameSloMo | Struct | 0x210 | 0x144f76670 |
| LongRangeKillFrameSloMo | Struct | 0x1e8 | 0x144f766b0 |
| LongRangeCastFrameSloMo | Struct | 0x1c0 | 0x144f766f0 |
| MinTelegraphTimeForLongRangeCast | Float | 0x1b8 | 0x144f76730 |
| LongRangeKillNoCastContactTagCheck | Struct | 0x178 | 0x144f767a0 |
| LongRangeKillContactTagCheck | Struct | 0x138 | 0x144f767e0 |
| LongRangeKillMinDistance | Float | 0x130 | 0x144f76768 |
| CloseRangeKillFrameSloMo | Struct | 0x108 | 0x144f76820 |
| CloseRangeKillContactTagCheck | Struct | 0xc8 | 0x144f76860 |
| CloseRangeKillMaxDistance | Float | 0xc0 | 0x144f768a0 |
| ContactTagCheckForVictimPOVTrackingMinion | Struct | 0x80 | 0x144f76910 |
| ContactTagCheckForVictimPOVTrackingAttacker | Struct | 0x40 | 0x144f76950 |
| DeathReplayDurationAfterEndOfDeathSloMo | Float | 0x3c | 0x144f768d8 |
| DeathReplayDurationBeforeEndOfDeathSloMo | Float | 0x38 | 0x144f76990 |
| PlayerClassAssetType | Name | 0x30 | 0x144f769c8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBEventsManager

Class params `0x1439c96c0`; resolver `0x141306bf0`; size `0x70`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PopupScreen | Object | 0x50 | 0x144f811d0 |
| PopupScreenClass | Class | 0x48 | 0x144f81210 |
| PopupScreenClassName | Struct | 0x30 | 0x144f81290 |
| GameInstance | Object | 0x28 | 0x144f812d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnAzureTextureCached | 8 | 0x144f810d0 |
| OnEnterFrontendMap | 0 | 0x144f81110 |
| OnPopupDismissed | 8 | 0x144f81190 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnAzureTextureCached | 0x14130a2e0 | 0x1439cf3a0 |
| OnEnterFrontendMap | 0x14130a380 | 0x1439cf3b0 |
| OnPopupDismissed | 0x14130a440 | 0x1439cf3c0 |

## MBFECustomGameMapSlotButton

Class params `0x1439cab20`; resolver `0x141306ee0`; size `0x548`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| OnlineSessionManager | Object | 0x540 | 0x144f82a20 |
| MapIndex | Int | 0x538 | 0x144f82928 |
| Keyboard_Previous | Struct | 0x520 | 0x144f82a60 |
| Controller_Previous | Struct | 0x508 | 0x144f82aa0 |
| Keyboard_Next | Struct | 0x4f0 | 0x144f82ae0 |
| Controller_Next | Struct | 0x4d8 | 0x144f82b20 |
| Keyboard_AddMap | Struct | 0x4c0 | 0x144f82b60 |
| Controller_AddMap | Struct | 0x4a8 | 0x144f82ba0 |
| Keyboard_ClearMap | Struct | 0x490 | 0x144f82be0 |
| Controller_ClearMap | Struct | 0x478 | 0x144f82c20 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CycleToNextMap | 0 | 0x144f827a0 |
| CycleToPrevMap | 0 | 0x144f827e0 |
| GetActiveSwitcherWidgetIndex | 4 | 0x144f82820 |
| GetMapIndex | 4 | 0x144f82860 |
| GetMapInfo | 152 | 0x144f82960 |
| OnMapIndexChanged | 0 | 0x144f829a0 |
| SetMapIndex | 4 | 0x144f829e0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CycleToNextMap | 0x141308e00 | 0x1439cf4a0 |
| CycleToPrevMap | 0x141308e20 | 0x1439cf4b0 |
| GetMapIndex | 0x1413093e0 | 0x1439cf4c0 |
| GetMapInfo | 0x141309400 | 0x1439cf4d0 |
| SetMapIndex | 0x14130ab20 | 0x1439cf4e0 |

## MBFECustomGameMapsMenu

Class params `0x1439caf00`; resolver `0x141305670`; size `0x480`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| MapSlotButtons | Array | 0x470 | 0x144f82dc0 |
| CustomGameManager | Object | 0x468 | 0x144f82e70 |
| OnlineSessionManager | Object | 0x460 | 0x144f82eb0 |
| DefaultMapName | Name | 0x458 | 0x144f82df8 |
| MapSlotContainer | Object | 0x450 | 0x144f82ef0 |
| MapSlotButtonWidgetClass | Class | 0x448 | 0x144f82f30 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetMapRosterSize | 4 | 0x144f82cc0 |
| InitialiseMapSlotButton | 8 | 0x144f82d40 |
| RefreshMapSlotButtons | 0 | 0x144f82d80 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetMapRosterSize | 0x141309600 | 0x1439cf4f0 |
| RefreshMapSlotButtons | 0x14130a8c0 | 0x1439cf500 |

## MBFECustomGameMenu

Class params `0x1439cc480`; resolver `0x1413057d0`; size `0x4c8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| TeamSlotButtonLists | Array | 0x4b0 | 0x144f840a8 |
| CustomGameManager | Object | 0x4a8 | 0x144f842e0 |
| OnlineSessionManager | Object | 0x4a0 | 0x144f84320 |
| QueuedTeamSlotButtonContainers | Array | 0x490 | 0x144f84168 |
| TeamSlotButtonContainers | Array | 0x480 | 0x144f84228 |
| QueuedSpectatorSlotButtonWidgetClass | Class | 0x478 | 0x144f843e0 |
| QueuedTeamSlotButtonWidgetClass | Class | 0x470 | 0x144f84460 |
| SpectatorSlotButtonWidgetClass | Class | 0x468 | 0x144f844e0 |
| TeamSlotButtonWidgetClass | Class | 0x460 | 0x144f84560 |
| NumQueueSlots | Int | 0x458 | 0x144f84428 |
| TeamOrder | Array | 0x448 | 0x144f844a8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CanStartGame | 1 | 0x144f83190 |
| GetGameName | 16 | 0x144f831d0 |
| GetTeamName | 24 | 0x144f83280 |
| GetTeamSlotButtonWithPlayerNetId | 24 | 0x144f83300 |
| InitialiseTeamSlotButton | 16 | 0x144f833f0 |
| IsHost | 1 | 0x144f834b0 |
| LeaveGame | 0 | 0x144f834f0 |
| NativeOnGameNameChanged | 16 | 0x144f83530 |
| NativeOnPlayerSetTeamFailed | 24 | 0x144f835e0 |
| NativeOnPlayerTeamChanged | 24 | 0x144f83690 |
| NativeOnSessionUpdated | 0 | 0x144f836d0 |
| NativeOnTeamNameChanged | 24 | 0x144f83780 |
| OnGameNameChanged | 16 | 0x144f837c0 |
| OnPlayerSetTeamFailed | 24 | 0x144f83870 |
| OnPlayerTeamChanged | 24 | 0x144f83920 |
| OnSessionUpdated | 0 | 0x144f83960 |
| OnTeamNameChanged | 24 | 0x144f83a10 |
| RefreshTeamSlotButtons | 0 | 0x144f83a50 |
| SetGameName | 16 | 0x144f83b00 |
| SetLocalTeamId | 4 | 0x144f83b40 |
| SetPlayerTeamId | 24 | 0x144f83bf0 |
| SetTeamName | 24 | 0x144f83ca0 |
| TryAssignLocalPlayerToNextTeam | 1 | 0x144f83d60 |
| TryAssignLocalPlayerToPrevTeam | 1 | 0x144f83e20 |
| TryAssignPlayerInSlotToNextTeam | 16 | 0x144f83f20 |
| TryAssignPlayerInSlotToPrevTeam | 16 | 0x144f84020 |
| TryGetNextAvailableTeam | 12 | 0x144f840e0 |
| TryGetPrevAvailableTeam | 12 | 0x144f841a0 |
| TryStartGame | 1 | 0x144f84260 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CanStartGame | 0x141308db0 | 0x1439cf630 |
| GetGameName | 0x1413092a0 | 0x1439cf640 |
| GetTeamName | 0x141309b20 | 0x1439cf650 |
| GetTeamSlotButtonWithPlayerNetId | 0x141309c00 | 0x1439cf660 |
| IsHost | 0x141309de0 | 0x1439cf670 |
| LeaveGame | 0x141309e10 | 0x1439cf680 |
| NativeOnGameNameChanged | 0x141309e30 | 0x1439cf690 |
| NativeOnPlayerSetTeamFailed | 0x141309f30 | 0x1439cf6a0 |
| NativeOnPlayerTeamChanged | 0x14130a060 | 0x1439cf6b0 |
| NativeOnSessionUpdated | 0x14130a190 | 0x1439cf6c0 |
| NativeOnTeamNameChanged | 0x14130a1b0 | 0x1439cf6d0 |
| RefreshTeamSlotButtons | 0x14130a8e0 | 0x1439cf6e0 |
| SetGameName | 0x14130a900 | 0x1439cf6f0 |
| SetLocalTeamId | 0x14130aaa0 | 0x1439cf700 |
| SetPlayerTeamId | 0x14130aba0 | 0x1439cf710 |
| SetTeamName | 0x14130ac80 | 0x1439cf720 |
| TryAssignLocalPlayerToNextTeam | 0x14130ad60 | 0x1439cf730 |
| TryAssignLocalPlayerToPrevTeam | 0x14130ad90 | 0x1439cf740 |
| TryAssignPlayerInSlotToNextTeam | 0x14130adc0 | 0x1439cf750 |
| TryAssignPlayerInSlotToPrevTeam | 0x14130ae50 | 0x1439cf760 |
| TryGetNextAvailableTeam | 0x14130aee0 | 0x1439cf770 |
| TryGetPrevAvailableTeam | 0x14130afb0 | 0x1439cf780 |
| TryStartGame | 0x14130b080 | 0x1439cf790 |

## MBFECustomGameTeamSlotButton

Class params `0x1439d2870`; resolver `0x14130b550`; size `0x4c8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ViewMode | Enum | 0x4c0 | 0x144f848d0 |
| NetId | Str | 0x4b0 | 0x144f84758 |
| bCanSwitchPrevTeam | Bool | 0x4ac | 0x144f84950 |
| bCanSwitchNextTeam | Bool | 0x4ab | 0x144f849d0 |
| bIsLocal | Bool | 0x4aa | 0x144f84a50 |
| bIsHost | Bool | 0x4a9 | 0x144f84ad0 |
| bIsOccupied | Bool | 0x4a8 | 0x144f84b40 |
| PlayerPresence | Str | 0x498 | 0x144f84998 |
| PlayerName | Str | 0x488 | 0x144f84a18 |
| TeamId | Int | 0x480 | 0x144f84a98 |
| AvatarTexture | Object | 0x478 | 0x144f84bb0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnAvatarLoaded | 56 | 0x144f84810 |
| OnPlayerChanged | 0 | 0x144f84850 |
| OnViewModeChanged | 0 | 0x144f84890 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnAvatarLoaded | 0x14130ec40 | 0x1439d38a8 |

## MBFECustomQueueScreen

Class params `0x1439d2ac0`; resolver `0x14130b3e0`; size `0x440`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBFEKioskPlayerReadyScreen

Class params `0x1439dfc30`; resolver `0x141316a60`; size `0x470`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| BackgroundWidget | Object | 0x468 | 0x144f8f0f0 |
| StartMatchCountdownRemainingLastFrame | Int | 0x464 | 0x144f8e9c8 |
| bStartMatchCountdownActiveLastFrame | Bool | 0x461 | 0x144f8f130 |
| bIsPlayerReadyLastFrame | Bool | 0x460 | 0x144f8f1b0 |
| PlayerName | Str | 0x450 | 0x144f8eac8 |
| StartMatchCountdownRemaining | Int | 0x44c | 0x144f8ecc8 |
| bStartMatchCountdownActive | Bool | 0x449 | 0x144f8f230 |
| bIsPlayerReady | Bool | 0x448 | 0x144f8f2b0 |
| BackgroundWidgetClass | Class | 0x440 | 0x144f8f330 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetKioskPlayerReadyStatus | 1 | 0x144f8eef0 |
| OnPlayerNameChanged | 0 | 0x144f8ef30 |
| OnPlayerReadyChanged | 0 | 0x144f8ef70 |
| OnStartMatchCountdownActiveChanged | 0 | 0x144f8efb0 |
| OnStartMatchCountdownRemainingChanged | 0 | 0x144f8eff0 |
| SetKioskPlayerReadyStatus | 1 | 0x144f8f0b0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetKioskPlayerReadyStatus | 0x1413184c0 | 0x1439e0c18 |
| SetKioskPlayerReadyStatus | 0x14131a380 | 0x1439e0c28 |

## MBFriendsListWidget

Class params `0x1439f5190`; resolver `0x1413295d0`; size `0x408`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bForceBatchedAvatarRequests | Bool | 0x3f7 | 0x144fa2600 |
| bFirstReadFriends | Bool | 0x3f6 | 0x144fa2680 |
| bReadFriendsPending | Bool | 0x3f5 | 0x144fa2700 |
| bReadFriendsEnabled | Bool | 0x3f4 | 0x144fa2780 |
| FriendListUpdateCounter | Int | 0x3f0 | 0x144fa2288 |
| FriendWidgetsInView | Array | 0x3e0 | 0x144fa2388 |
| FriendWidgets | Array | 0x3d0 | 0x144fa2648 |
| FriendWidgetData | Array | 0x3c0 | 0x144fa26c8 |
| SizeBox | Object | 0x3b8 | 0x144fa2880 |
| PartyManager | Object | 0x3b0 | 0x144fa28c0 |
| OnlineSessionManager | Object | 0x3a8 | 0x144fa2900 |
| FriendWidgetContainer | Object | 0x3a0 | 0x144fa2940 |
| ReadFriendsRetryFrequency | Float | 0x39c | 0x144fa2748 |
| ReadFriendsFrequency | Float | 0x398 | 0x144fa27c8 |
| FriendWidgetClass | Class | 0x390 | 0x144fa2980 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| Initialise | 16 | 0x144fa1d00 |
| InitialiseFriendWidget | 8 | 0x144fa1d80 |
| IsReadFriendsEnabled | 1 | 0x144fa1e40 |
| OnAvatarLoaded | 56 | 0x144fa1f80 |
| OnInviteReceived | 80 | 0x144fa2000 |
| OnInviteRemoved | 80 | 0x144fa2080 |
| OnPartyUpdated | 1 | 0x144fa2140 |
| OnPlayFabIdCached | 80 | 0x144fa2200 |
| OnReadFriendsComplete | 24 | 0x144fa2300 |
| OnUserInfoCached | 88 | 0x144fa2440 |
| OnUserScrolledEvent | 4 | 0x144fa2480 |
| OnUserStoppedScrolling | 0 | 0x144fa24c0 |
| RefreshFriendWidgets | 16 | 0x144fa2500 |
| SetReadFriendsEnabled | 1 | 0x144fa25c0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| Initialise | 0x14132c310 | 0x1439f99b0 |
| IsReadFriendsEnabled | 0x14132c420 | 0x1439f99c0 |
| OnAvatarLoaded | 0x14132c580 | 0x1439f99d0 |
| OnInviteReceived | 0x14132c780 | 0x1439f99e0 |
| OnInviteRemoved | 0x14132c780 | 0x1439f99f0 |
| OnPartyUpdated | 0x14132c8b0 | 0x1439f9a00 |
| OnPlayFabIdCached | 0x14132c940 | 0x1439f9a10 |
| OnReadFriendsComplete | 0x14132cb60 | 0x1439f9a20 |
| OnUserInfoCached | 0x14132cd10 | 0x1439f9a30 |
| OnUserScrolledEvent | 0x14132ced0 | 0x1439f9a40 |
| OnUserStoppedScrolling | 0x14132cf50 | 0x1439f9a50 |
| SetReadFriendsEnabled | 0x14132db80 | 0x1439f9a60 |

## MBFrontEnd

Class params `0x1439f7980`; resolver `0x1413294b0`; size `0x318`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PendingScreenPopWidgets | Array | 0x300 | 0x144fa51a8 |
| bIsInStartScreen | Bool | 0x2f8 | 0x144fa5c60 |
| CustomQueueScreenClass | Struct | 0x2e0 | 0x144fa5ce0 |
| WatchZoneScreenClass | Struct | 0x2c8 | 0x144fa5d20 |
| CurrentExitMenuTokens | Array | 0x2b8 | 0x144fa5328 |
| CurrentCameraTag | Name | 0x2b0 | 0x144fa56e8 |
| OnFinalSplashScreenComplete | MulticastDelegate | 0x2a0 | 0x144fa5d60 |
| bCanCloseFinalSplashScreen | Bool | 0x298 | 0x144fa5da0 |
| SplashPlayerController | Object | 0x290 | 0x144fa5e20 |
| PendingSplashScreen | Struct | 0x278 | 0x144fa5e60 |
| RemainingSplashScreens | Array | 0x268 | 0x144fa5828 |
| SetUserFocusRefCount | Int | 0x260 | 0x144fa5aa8 |
| bIsInitialisedToPlayerController | Bool | 0x25d | 0x144fa5ee0 |
| bRestoringScreenStack | Bool | 0x25c | 0x144fa5f60 |
| bIsKeyCapturing | Bool | 0x25b | 0x144fa5fe0 |
| bIsCameraTransitioning | Bool | 0x25a | 0x144fa6060 |
| bInPopTransition | Bool | 0x259 | 0x144fa60e0 |
| bInPushTransition | Bool | 0x258 | 0x144fa6160 |
| PendingPopMenuCompleteCallback | Delegate | 0x248 | 0x144fa61d0 |
| PendingPushMenuWidgets | Array | 0x238 | 0x144fa5ca8 |
| PendingScreenPushWidgets | Array | 0x228 | 0x144fa5de8 |
| WorldSingleton | Object | 0x220 | 0x144fa6290 |
| ScreenStack | Array | 0x210 | 0x144fa5f28 |
| WidgetContainer | Object | 0x208 | 0x144fa6310 |
| LatentActionManager | Struct | 0x118 | 0x144fa6350 |
| TokenManager | Struct | 0x90 | 0x144fa6390 |
| CachedScreens | Array | 0x80 | 0x144fa5fa8 |
| LoadedObjects | Array | 0x70 | 0x144fa6028 |
| FrontendObjectsToLoadAsync | Array | 0x60 | 0x144fa60a8 |
| CachedFrontendScreenClasses | Array | 0x50 | 0x144fa6128 |
| DefaultFrontendWidgetContainer | Struct | 0x38 | 0x144fa64d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddOverlay | 24 | 0x144fa3660 |
| AddOverlayWidget | 16 | 0x144fa3720 |
| CanSkipStartScreen | 1 | 0x144fa37e0 |
| ClearUserFocus | 16 | 0x144fa38e0 |
| CreateToken | 16 | 0x144fa3920 |
| CreateTokens | 24 | 0x144fa3960 |
| DeleteToken | 16 | 0x144fa3a10 |
| DeleteTokens | 24 | 0x144fa3b30 |
| DestroyAllScreenStackRestorePoints | 0 | 0x144fa3b70 |
| DestroyScreenStackRestorePoint | 0 | 0x144fa3bb0 |
| DoesScreenStackRestorePointExist | 1 | 0x144fa3c70 |
| FinalizePopScreenTransition | 8 | 0x144fa3cf0 |
| FinalizePushScreenTransition | 8 | 0x144fa3d70 |
| FinishedTransition | 16 | 0x144fa3df0 |
| GetFrontend | 16 | 0x144fa3eb0 |
| GetLevelScriptActor | 16 | 0x144fa3f70 |
| GetNameForTokenOwner | 16 | 0x144fa3ff0 |
| GetNumTokens | 16 | 0x144fa40a0 |
| GetScreenByClass | 16 | 0x144fa41a0 |
| GetUserFocus | 24 | 0x144fa4260 |
| HasAnyToken | 24 | 0x144fa4320 |
| HasToken | 16 | 0x144fa43e0 |
| HasTokenOwnedBy | 24 | 0x144fa44a0 |
| IsInStartScreen | 1 | 0x144fa4560 |
| IsProcessingInput | 1 | 0x144fa4620 |
| IsRestoringScreenStack | 1 | 0x144fa46e0 |
| IsTopScreen | 16 | 0x144fa4820 |
| IsTopScreenWidget | 16 | 0x144fa4920 |
| OnClosePoppedMenuComplete | 8 | 0x144fa49a0 |
| OnPushedPendingSplashScreen | 8 | 0x144fa4a20 |
| PlayFocusSoundIfAppropriate | 48 | 0x144fa4b60 |
| PopMenu | 8 | 0x144fa4be0 |
| PopMenu_Immediate | 8 | 0x144fa4c60 |
| PopScreen | 0 | 0x144fa4ca0 |
| PopScreenWhenTop | 24 | 0x144fa4da0 |
| PopScreen_Immediate | 0 | 0x144fa4ce0 |
| PopSystemMessageScreen | 0 | 0x144fa4de0 |
| PopSystemMessageScreen_Immediate | 0 | 0x144fa4e20 |
| PushMenu | 24 | 0x144fa4f60 |
| PushMenuWidget | 16 | 0x144fa5020 |
| PushPendingMenuWidgetsAfterMenuTransitionComplete | 8 | 0x144fa50a0 |
| PushScreen | 24 | 0x144fa51e0 |
| PushScreenWidget | 16 | 0x144fa52a0 |
| RefocusOnViewport | 16 | 0x144fa53a0 |
| RegisterTokenAddedDelegate | 24 | 0x144fa5420 |
| RegisterTokenRemovedDelegate | 24 | 0x144fa54a0 |
| RemoveOverlayWidget | 8 | 0x144fa5520 |
| SetCanCloseFinalSplashScreen | 16 | 0x144fa55a0 |
| SetIsKeycapture | 1 | 0x144fa5660 |
| SetUserFocus | 32 | 0x144fa57a0 |
| SetUserFocusToWidget | 24 | 0x144fa58e0 |
| ShowNextSplashScreen | 0 | 0x144fa5920 |
| TransitionCameraCut | 16 | 0x144fa59a0 |
| TransitionToScreenStackRestorePoint | 16 | 0x144fa5a20 |
| TryCreateScreenStackRestorePoint | 1 | 0x144fa5ae0 |
| UnregisterTokenAddedDelegate | 24 | 0x144fa5b60 |
| UnregisterTokenRemovedDelegate | 24 | 0x144fa5be0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddOverlay | 0x14132b450 | 0x1439fa030 |
| AddOverlayWidget | 0x14132b510 | 0x1439fa040 |
| CanSkipStartScreen | 0x14132b5d0 | 0x1439fa050 |
| ClearUserFocus | 0x14132b600 | 0x1439fa060 |
| CreateToken | 0x14132b680 | 0x1439fa070 |
| CreateTokens | 0x14132b740 | 0x1439fa080 |
| DeleteToken | 0x14132b840 | 0x1439fa090 |
| DeleteTokens | 0x14132b900 | 0x1439fa0a0 |
| DestroyAllScreenStackRestorePoints | 0x14132ba00 | 0x1439fa0b0 |
| DestroyScreenStackRestorePoint | 0x14132ba20 | 0x1439fa0c0 |
| DoesScreenStackRestorePointExist | 0x14132ba60 | 0x1439fa0d0 |
| FinalizePopScreenTransition | 0x14132bb70 | 0x1439fa0e0 |
| FinalizePushScreenTransition | 0x14132bbf0 | 0x1439fa0f0 |
| FinishedTransition | 0x14132bc70 | 0x1439fa100 |
| GetFrontend | 0x14132bd30 | 0x1439fa110 |
| GetLevelScriptActor | 0x14132bdb0 | 0x1439fa120 |
| GetNameForTokenOwner | 0x14132be30 | 0x1439fa130 |
| GetNumTokens | 0x14132bec0 | 0x1439fa140 |
| GetScreenByClass | 0x14132bf50 | 0x1439fa150 |
| GetUserFocus | 0x14132bfe0 | 0x1439fa160 |
| HasAnyToken | 0x14132c0c0 | 0x1439fa170 |
| HasToken | 0x14132c1c0 | 0x1439fa180 |
| HasTokenOwnedBy | 0x14132c250 | 0x1439fa190 |
| IsInStartScreen | 0x14132c3d0 | 0x1439fa1a0 |
| IsProcessingInput | 0x14132c3f0 | 0x1439fa1b0 |
| IsRestoringScreenStack | 0x14132c440 | 0x1439fa1c0 |
| IsTopScreen | 0x14132c460 | 0x1439fa1d0 |
| IsTopScreenWidget | 0x14132c4f0 | 0x1439fa1e0 |
| OnClosePoppedMenuComplete | 0x14132c700 | 0x1439fa1f0 |
| OnPushedPendingSplashScreen | 0x14132cae0 | 0x1439fa200 |
| PlayFocusSoundIfAppropriate | 0x14132cf70 | 0x1439fa210 |
| PopMenu | 0x14132d160 | 0x1439fa220 |
| PopMenu_Immediate | 0x14132d1e0 | 0x1439fa230 |
| PopScreen | 0x14132d260 | 0x1439fa240 |
| PopScreen_Immediate | 0x14132d370 | 0x1439fa250 |
| PopScreenWhenTop | 0x14132d280 | 0x1439fa260 |
| PopSystemMessageScreen | 0x14132d390 | 0x1439fa270 |
| PopSystemMessageScreen_Immediate | 0x14132d3b0 | 0x1439fa280 |
| PushMenu | 0x14132d3d0 | 0x1439fa290 |
| PushMenuWidget | 0x14132d490 | 0x1439fa2a0 |
| PushPendingMenuWidgetsAfterMenuTransitionComplete | 0x14132d550 | 0x1439fa2b0 |
| PushScreen | 0x14132d5d0 | 0x1439fa2c0 |
| PushScreenWidget | 0x14132d690 | 0x1439fa2d0 |
| RefocusOnViewport | 0x14132d750 | 0x1439fa2e0 |
| RegisterTokenAddedDelegate | 0x14132d7d0 | 0x1439fa2f0 |
| RegisterTokenRemovedDelegate | 0x14132d8c0 | 0x1439fa300 |
| RemoveOverlayWidget | 0x14132d9b0 | 0x1439fa310 |
| SetCanCloseFinalSplashScreen | 0x14132da30 | 0x1439fa320 |
| SetIsKeycapture | 0x14132daf0 | 0x1439fa330 |
| SetUserFocus | 0x14132dc10 | 0x1439fa340 |
| SetUserFocusToWidget | 0x14132dd10 | 0x1439fa350 |
| ShowNextSplashScreen | 0x14132ddd0 | 0x1439fa360 |
| TransitionCameraCut | 0x14132ddf0 | 0x1439fa370 |
| TransitionToScreenStackRestorePoint | 0x14132dff0 | 0x1439fa380 |
| TryCreateScreenStackRestorePoint | 0x14132e0b0 | 0x1439fa390 |
| UnregisterTokenAddedDelegate | 0x14132e0e0 | 0x1439fa3a0 |
| UnregisterTokenRemovedDelegate | 0x14132e1d0 | 0x1439fa3b0 |

## MBGameInstance

Class params `0x143a09070`; resolver `0x141339ce0`; size `0xa68`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| DataTableManager | Object | 0xa60 | 0x144fb26a0 |
| ServerWorkInProgressObjectsList | Array | 0xa50 | 0x144fb09b8 |
| ServerConnectionChangedMulticast | MulticastDelegate | 0x9b8 | 0x144fb2720 |
| TimeToNextServerOpen | Float | 0x9b4 | 0x144fb0a38 |
| ServerConnectionType | Enum | 0x9b0 | 0x144fb2760 |
| MapStatusList | Array | 0x980 | 0x144fb0af8 |
| KioskPlayerName | Str | 0x960 | 0x144fb0b78 |
| KioskType | Enum | 0x958 | 0x144fb2820 |
| bHasLoadedFirstMap | Bool | 0x39c | 0x144fb28a0 |
| SeparateTranslucencyEnabledOnStartup | Int | 0x398 | 0x144fb0bf8 |
| DynamicResolutionModeOnStartup | Int | 0x394 | 0x144fb0c78 |
| PlayerClassLoadStatus | Struct | 0x390 | 0x144fb2920 |
| PlayerClassLookupTable | Object | 0x388 | 0x144fb2960 |
| DefaultOnlineStatusMessagesPath | Struct | 0x370 | 0x144fb29a0 |
| DefaultSystemMessageManagerClassName | Struct | 0x358 | 0x144fb29e0 |
| DefaultLoadingScreenManagerClassName | Struct | 0x340 | 0x144fb2a20 |
| bIsLocalPlayerAFK | Bool | 0x338 | 0x144fb2a60 |
| AsyncLoadedWorlds | Array | 0x328 | 0x144fb16f8 |
| AsyncLoadedPackages | Array | 0x318 | 0x144fb17b8 |
| NumAsyncPackages | Int | 0x310 | 0x144fb1878 |
| PlayerAssetManager | Object | 0x308 | 0x144fb2b60 |
| OnlineStatusMessages | Object | 0x300 | 0x144fb2ba0 |
| PlayFabReporter | Object | 0x2f8 | 0x144fb2be0 |
| LeaverStatusManager | Object | 0x2f0 | 0x144fb2c20 |
| AchievementsManager | Object | 0x2e8 | 0x144fb2c60 |
| MapModsManager | Object | 0x2e0 | 0x144fb2ca0 |
| QuestsManager | Object | 0x2d8 | 0x144fb2ce0 |
| KioskModeManager | Object | 0x2d0 | 0x144fb2d20 |
| EventsManager | Object | 0x2c8 | 0x144fb2d60 |
| SystemMessageManager | Object | 0x2c0 | 0x144fb2da0 |
| WatchZoneManager | Object | 0x2b8 | 0x144fb2de0 |
| MapLoadingManager | Object | 0x2b0 | 0x144fb2e20 |
| LoadingScreenManager | Object | 0x2a8 | 0x144fb2e60 |
| MusicManager | Object | 0x2a0 | 0x144fb2ea0 |
| GameServerManager | Object | 0x298 | 0x144fb2ee0 |
| AzureFileCache | Object | 0x290 | 0x144fb2f20 |
| ReplayStreamingManager | Object | 0x288 | 0x144fb2f60 |
| QuestionManager | Object | 0x280 | 0x144fb2fa0 |
| LeaderboardManager | Object | 0x278 | 0x144fb2fe0 |
| PlayerAvatarManager | Object | 0x270 | 0x144fb3020 |
| OnlinePlayerIdManager | Object | 0x268 | 0x144fb3060 |
| UpdateManager | Object | 0x260 | 0x144fb30a0 |
| PlayerAccountManager | Object | 0x258 | 0x144fb30e0 |
| bGettingMultiplayerBuildId | Bool | 0x250 | 0x144fb3120 |
| BuildJsonString | Str | 0x240 | 0x144fb1938 |
| MultiplayerBuildId | Str | 0x230 | 0x144fb19f8 |
| PlayFabRegionManager | Object | 0x228 | 0x144fb31a0 |
| PlayFabServerMigrationManager | Object | 0x220 | 0x144fb31e0 |
| PlayFabBackfillingManager | Object | 0x218 | 0x144fb3220 |
| PlayFabMatchmakingManager | Object | 0x210 | 0x144fb3260 |
| bApplicationActivated | Bool | 0x1dc | 0x144fb32a0 |
| TickMontagesDistance | Float | 0x1d8 | 0x144fb1ab8 |
| ApplicationDeactivatedSoundMix | Object | 0x1d0 | 0x144fb3320 |
| HeroStatusList | Object | 0x1c8 | 0x144fb3360 |
| bPendingCheckCanPlay | Bool | 0x1c1 | 0x144fb33a0 |
| bAnalyticsEnabled | Bool | 0x1c0 | 0x144fb3410 |
| OnlineSessionManager | Object | 0x1b8 | 0x144fb3460 |
| LoadTime | Float | 0x198 | 0x144fb1b78 |
| OnCheckCanPlayResponseDelegate | MulticastDelegate | 0x188 | 0x144fb34a0 |
| AIPlayers | Array | 0x178 | 0x144fb1c38 |
| MapIndex | Int | 0x174 | 0x144fb1cf8 |
| NetworkConnectionLostReason | Enum | 0x170 | 0x144fb3520 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AsyncLoadPackages | 32 | 0x144fb0d30 |
| BlueprintCheckCanPlay | 0 | 0x144fb0d70 |
| CheckCanPlayFromRegion | 0 | 0x144fb0db0 |
| ConnectToOnlineService | 0 | 0x144fb0df0 |
| Debug_ToggleConsoleMenus | 0 | 0x144fb0e30 |
| Debug_TogglePlayfabMapList | 0 | 0x144fb0e70 |
| Debug_TutorialSkipToCombat | 0 | 0x144fb0eb0 |
| GetChangelist | 4 | 0x144fb0ef0 |
| GetCustomQueueName | 16 | 0x144fb0f30 |
| GetHeroStatusList | 8 | 0x144fb0fb0 |
| GetKioskPlayerName | 24 | 0x144fb1030 |
| GetKioskType | 16 | 0x144fb1130 |
| GetMultiplayerBuildId | 16 | 0x144fb1170 |
| GetMusicManager | 8 | 0x144fb11f0 |
| GetOnlineSessionManager | 8 | 0x144fb1270 |
| GetPlayFabBackfillingManager | 8 | 0x144fb13f0 |
| GetPlayFabMatchmakingManager | 8 | 0x144fb1470 |
| GetPlayFabRegionManager | 8 | 0x144fb14f0 |
| GetPlayFabReporter | 8 | 0x144fb1570 |
| GetPlayFabServerMigrationManager | 8 | 0x144fb15f0 |
| GetPlayerAccountManager | 8 | 0x144fb12f0 |
| GetPlayerAssetManager | 8 | 0x144fb1370 |
| GetUpdateManager | 8 | 0x144fb1670 |
| IsAnalyticsEnabled | 1 | 0x144fb1730 |
| IsConnectedToOnlineService | 1 | 0x144fb17f0 |
| IsConnectingToOnlineService | 1 | 0x144fb18b0 |
| IsConnectionToOnlineServiceRequired | 1 | 0x144fb1970 |
| IsConsoleMenus | 1 | 0x144fb1a30 |
| IsCustomQueue | 1 | 0x144fb1af0 |
| IsGameAuthorised | 1 | 0x144fb1bb0 |
| IsKioskMode | 1 | 0x144fb1c70 |
| IsLocalPlayerAFK | 1 | 0x144fb1d30 |
| MoveToNewMap | 24 | 0x144fb1db0 |
| ReRequestEncryptionKey | 16 | 0x144fb1eb0 |
| RegisterServerConnectionDelegate | 16 | 0x144fb1e30 |
| SetIsLocalPlayerAFK | 1 | 0x144fb1f60 |
| SetKioskPlayerName | 24 | 0x144fb1fe0 |
| SetKioskType | 16 | 0x144fb20e0 |
| ShouldSkipSplashScreens | 16 | 0x144fb21e0 |
| SkipTutorial | 1 | 0x144fb22a0 |
| TryGetMapStatusFromLevelName | 48 | 0x144fb23a0 |
| TryGetOnlineServiceUserID | 24 | 0x144fb2460 |
| UnregisterServerConnectionDelegate | 16 | 0x144fb24e0 |
| UpdateHeroList | 1 | 0x144fb25a0 |
| UsePlayfabMapList | 1 | 0x144fb2660 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AsyncLoadPackages | 0x14133bab0 | 0x143a0c3a0 |
| BlueprintCheckCanPlay | 0x14133bc00 | 0x143a0c3b0 |
| CheckCanPlayFromRegion | 0x14133bc20 | 0x143a0c3c0 |
| ConnectToOnlineService | 0x14133bc40 | 0x143a0c3d0 |
| Debug_ToggleConsoleMenus | 0x14133bc80 | 0x143a0c3e0 |
| Debug_TogglePlayfabMapList | 0x14133bca0 | 0x143a0c3f0 |
| Debug_TutorialSkipToCombat | 0x14133bcc0 | 0x143a0c400 |
| GetChangelist | 0x14133bce0 | 0x143a0c410 |
| GetCustomQueueName | 0x14133bd00 | 0x143a0c420 |
| GetHeroStatusList | 0x14133bd90 | 0x143a0c430 |
| GetKioskPlayerName | 0x14133bdb0 | 0x143a0c440 |
| GetKioskType | 0x14133be80 | 0x143a0c450 |
| GetMultiplayerBuildId | 0x14133bf00 | 0x143a0c460 |
| GetMusicManager | 0x14133bf30 | 0x143a0c470 |
| GetOnlineSessionManager | 0x14133bf50 | 0x143a0c480 |
| GetPlayerAccountManager | 0x14133c010 | 0x143a0c490 |
| GetPlayerAssetManager | 0x14133c030 | 0x143a0c4a0 |
| GetPlayFabBackfillingManager | 0x14133bf70 | 0x143a0c4b0 |
| GetPlayFabMatchmakingManager | 0x14133bf90 | 0x143a0c4c0 |
| GetPlayFabRegionManager | 0x14133bfb0 | 0x143a0c4d0 |
| GetPlayFabReporter | 0x14133bfd0 | 0x143a0c4e0 |
| GetPlayFabServerMigrationManager | 0x14133bff0 | 0x143a0c4f0 |
| GetUpdateManager | 0x14133c050 | 0x143a0c500 |
| IsAnalyticsEnabled | 0x14133c090 | 0x143a0c510 |
| IsConnectedToOnlineService | 0x14133c0c0 | 0x143a0c520 |
| IsConnectingToOnlineService | 0x14133c0f0 | 0x143a0c530 |
| IsConnectionToOnlineServiceRequired | 0x14133c120 | 0x143a0c540 |
| IsConsoleMenus | 0x14133c150 | 0x143a0c550 |
| IsCustomQueue | 0x14133c180 | 0x143a0c560 |
| IsGameAuthorised | 0x14133c120 | 0x143a0c570 |
| IsKioskMode | 0x1412d7e80 | 0x143a0c580 |
| IsLocalPlayerAFK | 0x14133c1b0 | 0x143a0c590 |
| MoveToNewMap | 0x14133c1d0 | 0x143a0c5a0 |
| RegisterServerConnectionDelegate | 0x14133c9a0 | 0x143a0c5b0 |
| ReRequestEncryptionKey | 0x14133c830 | 0x143a0c5c0 |
| SetIsLocalPlayerAFK | 0x14133ca60 | 0x143a0c5d0 |
| SetKioskPlayerName | 0x14133caf0 | 0x143a0c5e0 |
| SetKioskType | 0x14133cbc0 | 0x143a0c5f0 |
| ShouldSkipSplashScreens | 0x14133cc70 | 0x143a0c600 |
| SkipTutorial | 0x14133ccf0 | 0x143a0c610 |
| TryGetMapStatusFromLevelName | 0x14133cd10 | 0x143a0c620 |
| TryGetOnlineServiceUserID | 0x14133ce30 | 0x143a0c630 |
| UnregisterServerConnectionDelegate | 0x14133cef0 | 0x143a0c640 |
| UpdateHeroList | 0x14133cfb0 | 0x143a0c650 |
| UsePlayfabMapList | 0x14133d040 | 0x143a0c660 |

## MBGameModeManagerState

Class params `0x14445ca50`; resolver `0x142aa9ce0`; size `0x28`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBGameServerManager

Class params `0x143a178b0`; resolver `0x14133d210`; size `0xc8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bServerAllocated | Bool | 0x70 | 0x144fb48c0 |
| SourceMatchId | Str | 0x60 | 0x144fb4888 |
| bEnableAnalytics | Bool | 0x5a | 0x144fb4940 |
| bEnableSlotRefilling | Bool | 0x59 | 0x144fb49c0 |
| bAllowSlotRefilling | Bool | 0x58 | 0x144fb4a40 |
| ActiveMatchmakingRequestIds | Array | 0x48 | 0x144fb4908 |
| TeamSlotManagers | Array | 0x38 | 0x144fb4a08 |
| GameInstance | Object | 0x30 | 0x144fb4af0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBGlobalManagerObjectState

Class params `0x1444efdd0`; resolver `0x142ab9830`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| MessageCountIndex | UInt32 | 0x80 | 0x1452a5830 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBGraffitiBaseWidget

Class params `0x143a1c410`; resolver `0x141347de0`; size `0x240`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CachedSpectatorCameraMode | Enum | 0x211 | 0x144fc28d0 |
| CachedSpectatorType | Enum | 0x210 | 0x144fc2950 |
| OwnerProxyLastFrame | Object | 0x208 | 0x144fc29d0 |
| ControllingPlayerProxyLastFrame | Object | 0x200 | 0x144fc2a10 |
| WidgetOwnerProxy | Object | 0x1f8 | 0x144fc2a50 |
| CachedOwningPlayerController | Object | 0x1f0 | 0x144fc2a90 |
| bRegisterSpectatorDelegates | Bool | 0x1eb | 0x144fc2ad0 |
| bNeedsGameOvertimeEvent | Bool | 0x1ea | 0x144fc2b50 |
| bNeedsReceiveOutputEvent | Bool | 0x1e9 | 0x144fc2bd0 |
| bCanTickWhilstOwnerHidden | Bool | 0x1e8 | 0x144fc2c50 |
| CommonLevelObjectProxy | Object | 0x1e0 | 0x144fc2cd0 |
| WatchOwnerProxyAttributes | Array | 0x1d0 | 0x144fc2b18 |
| WatchOwnerProxyTokens | Array | 0x1c0 | 0x144fc2c18 |
| WatchControllingPlayerAttributes | Array | 0x1b0 | 0x144fc2d10 |
| WatchControllingPlayerTokens | Array | 0x1a0 | 0x144fc2d80 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetControllerPlayerState | 8 | 0x144fc1cf0 |
| GetControllingPlayerProxy | 8 | 0x144fc1d70 |
| GetOwnerActor | 8 | 0x144fc1df0 |
| GetOwnerActorState | 8 | 0x144fc1e70 |
| GetOwningPlayerController | 8 | 0x144fc1ef0 |
| NativeOnControllingPlayerAttributeChanged | 16 | 0x144fc1fa0 |
| NativeOnControllingPlayerTokenChanged | 16 | 0x144fc2060 |
| NativeOnOwnerProxyAttributeChanged | 16 | 0x144fc2180 |
| NativeOnOwnerProxyTokenChanged | 16 | 0x144fc2240 |
| OnControllingPlayerAttributeChanged | 16 | 0x144fc22f0 |
| OnControllingPlayerProxyChanged | 0 | 0x144fc2330 |
| OnControllingPlayerTokenChanged | 16 | 0x144fc23f0 |
| OnGameOvertime | 0 | 0x144fc2430 |
| OnOwnerProxyAttributeChanged | 16 | 0x144fc2550 |
| OnOwnerProxyChanged | 0 | 0x144fc2590 |
| OnOwnerProxyTokenChanged | 16 | 0x144fc2650 |
| OnPlayerControllerPossessProxy | 16 | 0x144fc2710 |
| OnPlayerControllerUnpossessProxy | 16 | 0x144fc27d0 |
| OnWidgetInitialised | 0 | 0x144fc2810 |
| ReceiveOutputEvent | 16 | 0x144fc2890 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetControllerPlayerState | 0x141349f00 | 0x143a22170 |
| GetControllingPlayerProxy | 0x141349f90 | 0x143a22180 |
| GetOwnerActor | 0x141349fc0 | 0x143a22190 |
| GetOwnerActorState | 0x14134a050 | 0x143a221a0 |
| GetOwningPlayerController | 0x14134a0e0 | 0x143a221b0 |
| NativeOnControllingPlayerAttributeChanged | 0x14134a130 | 0x143a221c0 |
| NativeOnControllingPlayerTokenChanged | 0x14134a230 | 0x143a221d0 |
| NativeOnOwnerProxyAttributeChanged | 0x14134a300 | 0x143a221e0 |
| NativeOnOwnerProxyTokenChanged | 0x14134a400 | 0x143a221f0 |
| OnPlayerControllerPossessProxy | 0x14134a850 | 0x143a22200 |
| OnPlayerControllerUnpossessProxy | 0x14134a850 | 0x143a22210 |
| ReceiveOutputEvent | 0x14134a910 | 0x143a22220 |

## MBHeroesBanterSystem

Class params `0x143a24e40`; resolver `0x14134b9a0`; size `0xa8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bMatchStarted | Bool | 0xa0 | 0x144fc8d10 |
| RemainingTimeBetweenBanters | Float | 0x9c | 0x144fc8c58 |
| TimeToTryPlayBanter | Float | 0x98 | 0x144fc8d58 |
| ActivePlayers | Array | 0x88 | 0x144fc8d90 |
| ActiveBanters | Array | 0x78 | 0x144fc8dc8 |
| EffectsPluginVO | Object | 0x70 | 0x144fc8e80 |
| WorldSingleton | Object | 0x68 | 0x144fc8ec0 |
| GameInstance | Object | 0x60 | 0x144fc8f00 |
| ActiveBanterIds | Array | 0x50 | 0x144fc8f40 |
| Banters | Array | 0x40 | 0x144fc8fb0 |
| TimeBetweenBanters | Struct | 0x38 | 0x144fc9050 |
| DelayFromCharacterSelection | Struct | 0x30 | 0x144fc9090 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ReceiveGameplayEvent | 16 | 0x144fc8cd0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ReceiveGameplayEvent | 0x14134e6e0 | 0x143a27ec0 |

## MBInputEventApplyKioskModeHandicap

Class params `0x1444f8570`; resolver `0x142b4aac0`; size `0x40`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| HandicapType | Enum | 0x3c | 0x1452b09c0 |
| Multiplier | Float | 0x38 | 0x1452b0a40 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| PUC_SetHandicap | 120 | 0x1452b0980 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| PUC_SetHandicap | 0x142b4d6e0 | 0x1444fbff8 |

## MBInputEventKioskModeEndGame

Class params `0x1444f5670`; resolver `0x142b49460`; size `0x38`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBKioskModeEndGameWidget

Class params `0x143a3ca10`; resolver `0x14135cd30`; size `0x398`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| KioskModeManager | Object | 0x390 | 0x144fd9980 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnBeginDeathReplay | 0 | 0x144fd9800 |
| OnEndDeathReplay | 0 | 0x144fd9840 |
| OnEndGameCountdownChanged | 4 | 0x144fd9880 |
| OnEndGameCountdownStarted | 0 | 0x144fd98c0 |
| OnMatchEndedDefeat | 0 | 0x144fd9900 |
| OnMatchEndedVictory | 0 | 0x144fd9940 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBKioskModeHandicapsData

Class params `0x1445010f0`; resolver `0x142b4eb40`; size `0x40`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBKioskModeHandicapsStateWrapper

Class params `0x144501800`; resolver `0x142b4ecb0`; size `0x68`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| StateStruct | Struct | 0x40 | 0x1452b4030 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnApplyDamageMultipliers | 8 | 0x1452b3ff0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnApplyDamageMultipliers | 0x142b55280 | 0x1445080e0 |

## MBKioskModeHandicapsWidget

Class params `0x143a43060`; resolver `0x141360a80`; size `0x398`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| KioskModeManager | Object | 0x390 | 0x144fd9cd0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnCanActivateHandicapsChanged | 1 | 0x144fd9bd0 |
| OnHandicapMultiplierChanged | 8 | 0x144fd9c90 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBKioskModeManager

Class params `0x143a43560`; resolver `0x141360590`; size `0x110`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0x108 | 0x144fda0b0 |
| ResetToDefaultSettingsMaps | Array | 0xf8 | 0x144fda0f0 |
| EndGameWidgetClass | Class | 0xf0 | 0x144fda1a0 |
| EndGameCountdown | Int | 0xe8 | 0x144fda128 |
| HandicapsWidgetClass | Class | 0xe0 | 0x144fda220 |
| DefenceMultiplierData | Struct | 0xd4 | 0x144fda2a0 |
| DamageMultiplierData | Struct | 0xc8 | 0x144fda2e0 |
| KioskModeDecDefenceAction | Name | 0xc0 | 0x144fda1e8 |
| KioskModeIncDefenceAction | Name | 0xb8 | 0x144fda268 |
| KioskModeDecDamageAction | Name | 0xb0 | 0x144fda320 |
| KioskModeIncDamageAction | Name | 0xa8 | 0x144fda358 |
| KioskModeHandicapBAction | Name | 0xa0 | 0x144fda390 |
| KioskModeHandicapAAction | Name | 0x98 | 0x144fda3c8 |
| HeroCustomisations | Array | 0x88 | 0x144fda400 |
| AdditionalCustomisations | Array | 0x78 | 0x144fda438 |
| CPPointsRequiredToWin | Int | 0x70 | 0x144fda4f0 |
| SeedsRequiredToWin | Struct | 0x40 | 0x144fda550 |
| TypesBlueprintObjectRef | Struct | 0x28 | 0x144fda590 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetHandicapMultiplier | 8 | 0x144fd9ff0 |
| StartEndGame | 8 | 0x144fda070 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetHandicapMultiplier | 0x141364320 | 0x143a452b8 |
| StartEndGame | 0x1413648e0 | 0x143a452c8 |

## MBKioskRollbackGameMode

Class params `0x143a439e0`; resolver `0x14135fba0`; size `0x528`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| NumPlayersRequiredOverride | Int | 0x524 | 0x144fda5d0 |
| bUseKioskPlayerName | Bool | 0x520 | 0x144fda640 |
| StartMatchCountdownDuration | Int | 0x51c | 0x144fda608 |
| NumPlayersRequired | Int | 0x518 | 0x144fda688 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBKioskRollbackGameState

Class params `0x143a40020`; resolver `0x141360010`; size `0x4f0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CurrentPlayerReadyScreenClass | Class | 0x4e8 | 0x144fda820 |
| bKioskStartMatchCountdownActive | Bool | 0x4e4 | 0x144fda8a0 |
| KioskStartMatchCountdownEndTimeSeconds | Float | 0x4e0 | 0x144fda768 |
| DefaultPlayerReadyScreenClass | Class | 0x4d8 | 0x144fda910 |
| PlayerReadyScreenClasses | Map | 0x488 | 0x144fda868 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetKioskStartMatchCountdownActive | 1 | 0x144fda7a0 |
| GetKioskStartMatchCountdownTimeRemaining | 4 | 0x144fda7e0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetKioskStartMatchCountdownActive | 0x1413643b0 | 0x143a452d8 |
| GetKioskStartMatchCountdownTimeRemaining | 0x1413643e0 | 0x143a452e8 |

## MBLeaderboardManager

Class params `0x143a41b70`; resolver `0x1413606b0`; size `0x120`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| NumPostMatchStatsBatchesRemaining | Int | 0x11c | 0x144fdc308 |
| NumPostMatchSkillBatchesRemaining | Int | 0x118 | 0x144fdc3c0 |
| PendingLocalPlayerHeroLeaderboardRequests | Array | 0xc8 | 0x144fdc3f8 |
| PendingHeroLeaderboardRequests | Array | 0xb8 | 0x144fdc470 |
| PendingFriendLeaderboardRequests | Array | 0xa8 | 0x144fdc4a8 |
| PendingLeaderboardAroundPlayerRequests | Array | 0x98 | 0x144fdc560 |
| PendingLeaderboardRequests | Array | 0x88 | 0x144fdc598 |
| CachedLocalPlayerHeroLeaderboards | Array | 0x78 | 0x144fdc650 |
| CachedHeroLeaderboards | Array | 0x68 | 0x144fdc688 |
| CachedLocalPlayerLeaderboardEntries | Array | 0x58 | 0x144fdc740 |
| CachedFriendLeaderboards | Array | 0x48 | 0x144fdc778 |
| CachedLeaderboards | Array | 0x38 | 0x144fdc830 |
| GameInstance | Object | 0x30 | 0x144fdc8d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| DebugClearLeaderboardCache | 0 | 0x144fdbf30 |
| DebugPrintFriendLeaderboard | 24 | 0x144fdbf70 |
| DebugPrintLeaderboard | 24 | 0x144fdc020 |
| DebugPrintLocalPlayerRank | 16 | 0x144fdc0d0 |
| DebugPrintLocalPlayerSkillRank | 0 | 0x144fdc110 |
| DebugUpdateLocalPlayerSkill_Decayed | 4 | 0x144fdc150 |
| DebugUpdateLocalPlayerSkill_OnLogin | 0 | 0x144fdc190 |
| DebugUpdateLocalPlayerSkill_PostMatch | 0 | 0x144fdc1d0 |
| DebugWriteToLeaderboard | 24 | 0x144fdc280 |
| OnLocalPlayerLoginComplete | 1 | 0x144fdc340 |
| OnPostMatchCountdown | 0 | 0x144fdc380 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| DebugClearLeaderboardCache | 0x141363ee0 | 0x143a46360 |
| DebugPrintFriendLeaderboard | 0x141363f00 | 0x143a46370 |
| DebugPrintLeaderboard | 0x141363fe0 | 0x143a46380 |
| DebugPrintLocalPlayerRank | 0x1413640c0 | 0x143a46390 |
| DebugPrintLocalPlayerSkillRank | 0x141364160 | 0x143a463a0 |
| DebugUpdateLocalPlayerSkill_Decayed | 0x141364180 | 0x143a463b0 |
| DebugUpdateLocalPlayerSkill_OnLogin | 0x141364200 | 0x143a463c0 |
| DebugUpdateLocalPlayerSkill_PostMatch | 0x141364220 | 0x143a463d0 |
| DebugWriteToLeaderboard | 0x141364240 | 0x143a463e0 |
| OnLocalPlayerLoginComplete | 0x141364690 | 0x143a463f0 |
| OnPostMatchCountdown | 0x141364720 | 0x143a46400 |

## MBLeaverStatusManager

Class params `0x143a42560`; resolver `0x141360760`; size `0xb0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LeaverStatusConfig | Struct | 0x78 | 0x144fdceb0 |
| bIsEnabled | Bool | 0x71 | 0x144fdcef0 |
| bHadLocalPlayerLeaverStatusWhenLoadedLevel | Bool | 0x70 | 0x144fdcf60 |
| LocalPlayerLeaverStatus | Struct | 0x50 | 0x144fdcfe0 |
| WorldSingleton | Object | 0x48 | 0x144fdd020 |
| GameInstance | Object | 0x40 | 0x144fdd060 |
| GainedLeaverStatusMessageId | Name | 0x38 | 0x144fdcd38 |
| OnLeaverStatusChangedMulticaster | MulticastDelegate | 0x28 | 0x144fdd0a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnGainedLeaverStatusMessageComplete | 1 | 0x144fdcdf0 |
| ReceiveOutputEvent | 16 | 0x144fdce70 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnGainedLeaverStatusMessageComplete | 0x141364610 | 0x143a46640 |
| ReceiveOutputEvent | 0x141364740 | 0x143a46650 |

## MBLoadingScreenBaseWidget

Class params `0x143a4a580`; resolver `0x141365150`; size `0x2d0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ObjectReferences | Array | 0x2c0 | 0x144fddce8 |
| CachedGameInstance | Object | 0x2b8 | 0x144fddf10 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBLoadingScreenManager

Class params `0x143a47080`; resolver `0x141365330`; size `0x1d0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bHasFrontEndEverBeenLoaded | Bool | 0x1c8 | 0x144fdea60 |
| StartedLoading | Struct | 0x1c0 | 0x144fdead0 |
| State | Enum | 0x1b8 | 0x144fdeb10 |
| LoadingScreenRuntimeData | Struct | 0x180 | 0x144fdeb90 |
| LoadingScreenData | Struct | 0x150 | 0x144fdebd0 |
| PendingTravelURL | Struct | 0xe0 | 0x144fdec10 |
| LoadingMapName | Name | 0xd8 | 0x144fde678 |
| LoadingLevelName | Str | 0xc8 | 0x144fde6f8 |
| LoadingScreenWidget | Object | 0x90 | 0x144fdec50 |
| GameInstance | Object | 0x88 | 0x144fdec90 |
| SoundMixModifier | Object | 0x60 | 0x144fdecd0 |
| DefaultLoadingScreenData | Struct | 0x30 | 0x144fded10 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnAvatarLoaded | 56 | 0x144fde7b0 |
| OnFakeAvatarLoaded | 56 | 0x144fde8e0 |
| OnPlayerInfoCached | 88 | 0x144fdea20 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnAvatarLoaded | 0x141368b10 | 0x143a4c2b0 |
| OnFakeAvatarLoaded | 0x141368c90 | 0x143a4c2c0 |
| OnPlayerInfoCached | 0x141368e10 | 0x143a4c2d0 |

## MBMatchmakingConfigProvider

Class params `0x143a4e5d0`; resolver `0x14136a4d0`; size `0x98`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bPopulated | Bool | 0x88 | 0x144fe4490 |
| Rules | Array | 0x78 | 0x144fe4398 |
| Profiles | Map | 0x28 | 0x144fe4418 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnTitleDataCached | 1 | 0x144fe4450 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnTitleDataCached | 0x14136d430 | 0x143a51550 |

## MBMatchmakingPanelWidget

Class params `0x143a4ef30`; resolver `0x141369ea0`; size `0x2f8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bCanShowInCurrentMap | Bool | 0x2f1 | 0x144fe4d60 |
| State | Enum | 0x2f0 | 0x144fe4de0 |
| PartyManager | Object | 0x2e8 | 0x144fe4e60 |
| OnlineSessionManager | Object | 0x2e0 | 0x144fe4ea0 |
| MatchmakingManager | Object | 0x2d8 | 0x144fe4ee0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| BlueprintOnMatchmakingCancelled | 0 | 0x144fe45f0 |
| BlueprintOnMatchmakingEstimateUpdated | 4 | 0x144fe4630 |
| BlueprintOnMatchmakingPendingCancel | 0 | 0x144fe4670 |
| BlueprintOnMatchmakingStarted | 0 | 0x144fe46b0 |
| BlueprintOnPartyUpdated | 0 | 0x144fe46f0 |
| CanShowInCurrentMap | 1 | 0x144fe47b0 |
| GetState | 1 | 0x144fe4870 |
| IsMatchmaking | 1 | 0x144fe4930 |
| IsWaitingToStopMatchmaking | 1 | 0x144fe49f0 |
| OnMatchmakingCancelled | 24 | 0x144fe4a30 |
| OnMatchmakingEstimateUpdated | 4 | 0x144fe4a70 |
| OnMatchmakingPendingCancel | 0 | 0x144fe4ab0 |
| OnMatchmakingStarted | 0 | 0x144fe4af0 |
| OnPartyUpdated | 1 | 0x144fe4bb0 |
| TryGetMatchmakingEstimate | 8 | 0x144fe4c60 |
| TryGetMatchmakingTime | 8 | 0x144fe4d20 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CanShowInCurrentMap | 0x14136c530 | 0x143a51590 |
| GetState | 0x14136c730 | 0x143a515a0 |
| IsMatchmaking | 0x14136cd40 | 0x143a515b0 |
| IsWaitingToStopMatchmaking | 0x14136cd70 | 0x143a515c0 |
| OnMatchmakingCancelled | 0x14136d0e0 | 0x143a515d0 |
| OnMatchmakingEstimateUpdated | 0x14136d1c0 | 0x143a515e0 |
| OnMatchmakingPendingCancel | 0x14136d240 | 0x143a515f0 |
| OnMatchmakingStarted | 0x14136d260 | 0x143a51600 |
| OnPartyUpdated | 0x14136d380 | 0x143a51610 |
| TryGetMatchmakingEstimate | 0x14136d980 | 0x143a51620 |
| TryGetMatchmakingTime | 0x14136da30 | 0x143a51630 |

## MBMusicManager

Class params `0x143a5e1f0`; resolver `0x141378100`; size `0x148`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LevelLoadingMusicState | Enum | 0xa0 | 0x144ff3bc0 |
| ActiveMusic | Object | 0x98 | 0x144ff3c70 |
| GameInstance | Object | 0x90 | 0x144ff3cb0 |
| CapturePointScoreRemainingThresholdIndex | Int | 0x88 | 0x144ff3c38 |
| CapturePointScoreRemainingThresholdLookup | Array | 0x78 | 0x144ff3cf0 |
| CapturePointScoreRemainingThreshold | Array | 0x68 | 0x144ff3d60 |
| MusicFadeOutTime | Float | 0x64 | 0x144ff3dd0 |
| MusicFadeInTime | Float | 0x60 | 0x144ff3e08 |
| DontPlayDefaultLoadingMusicGameModes | Array | 0x50 | 0x144ff3e40 |
| DefaultLevelLoadingMusic | Object | 0x48 | 0x144ff3f20 |
| bDisabledInPIE | Bool | 0x40 | 0x144ff3f60 |
| TypesBlueprintObjectRef | Struct | 0x28 | 0x144ff3fd0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AudioFinished | 8 | 0x144ff3100 |
| GetActiveMusicComponent | 8 | 0x144ff3180 |
| IsEnabled | 1 | 0x144ff3240 |
| OnActorMessageCreated | 16 | 0x144ff3300 |
| OnBeginDeathReplay | 0 | 0x144ff3340 |
| OnBeginMatchWarmUp | 0 | 0x144ff3380 |
| OnBeginRespawnSpectatorMode | 0 | 0x144ff33c0 |
| OnBeginSeedsNearEndState | 0 | 0x144ff3400 |
| OnEndDeathReplay | 0 | 0x144ff3440 |
| OnEndRespawnSpectatorMode | 0 | 0x144ff3480 |
| OnEndSeedsNearEndState | 0 | 0x144ff34c0 |
| OnEnterEndGameScreen | 0 | 0x144ff3500 |
| OnEnterFrontendMap | 0 | 0x144ff3540 |
| OnEnterMainMenu | 0 | 0x144ff3580 |
| OnExitFrontendMap | 0 | 0x144ff35c0 |
| OnLoadingScreenStateChanged | 24 | 0x144ff3680 |
| OnLocalPlayerBeginRespawn | 0 | 0x144ff36c0 |
| OnLocalPlayerDied | 0 | 0x144ff3700 |
| OnLocalPlayerEndRespawn | 0 | 0x144ff3740 |
| OnMatchEndedDefeat | 0 | 0x144ff3780 |
| OnMatchEndedVictory | 0 | 0x144ff37c0 |
| OnMatchStarted | 0 | 0x144ff38c0 |
| OnMatchmakingCancelled | 0 | 0x144ff3800 |
| OnMatchmakingLoadMap | 0 | 0x144ff3840 |
| OnMatchmakingStarted | 0 | 0x144ff3880 |
| OnPostMatchCountdown | 0 | 0x144ff3900 |
| OnPreMatchCountdown | 0 | 0x144ff3940 |
| OnReachedCapturePointScoreRemainingThreshold | 4 | 0x144ff3980 |
| PlayMusic | 24 | 0x144ff3ac0 |
| ReceiveOutputEvent | 16 | 0x144ff3b40 |
| StopMusic | 0 | 0x144ff3b80 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AudioFinished | 0x14137aa40 | 0x143a63780 |
| GetActiveMusicComponent | 0x14137aac0 | 0x143a63790 |
| IsEnabled | 0x14133c120 | 0x143a637a0 |
| OnActorMessageCreated | 0x14137b010 | 0x143a637b0 |
| PlayMusic | 0x14137b4d0 | 0x143a637c0 |
| ReceiveOutputEvent | 0x14137b620 | 0x143a637d0 |
| StopMusic | 0x14137bc20 | 0x143a637e0 |

## MBNotificationManagerWidget

Class params `0x143a5f2b0`; resolver `0x1413779f0`; size `0x3b8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| QueuedInviteIds | Array | 0x3a8 | 0x144ff4570 |
| OnlineSessionManager | Object | 0x3a0 | 0x144ff45e0 |
| NotificationContainer | Object | 0x398 | 0x144ff4620 |
| InviteNotificationWidgetClass | Class | 0x390 | 0x144ff4660 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnInviteReceived | 80 | 0x144ff44b0 |
| OnInviteRemoved | 80 | 0x144ff4530 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnInviteReceived | 0x14137b160 | 0x143a63800 |
| OnInviteRemoved | 0x14137b290 | 0x143a63810 |

## MBOnlinePlayerIdManager

Class params `0x143a5fad0`; resolver `0x141378300`; size `0x128`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PlayFabIdToNativeId | Map | 0xd0 | 0x144ff4c78 |
| NativeIdToPlayFabId | Map | 0x80 | 0x144ff4f70 |
| PendingPlayFabIdRequests | Map | 0x30 | 0x144ff5020 |
| GameInstance | Object | 0x28 | 0x144ff50d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetOnlinePlayerIdManager | 16 | 0x144ff4d30 |
| RequestPlayFabId | 56 | 0x144ff4df0 |
| RequestPlayFabIds | 32 | 0x144ff4eb0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetOnlinePlayerIdManager | 0x14137ac10 | 0x143a63938 |
| RequestPlayFabId | 0x14137b8a0 | 0x143a63948 |
| RequestPlayFabIds | 0x14137ba10 | 0x143a63958 |

## MBOnlineSessionManager

Class params `0x143a60bd0`; resolver `0x141378c60`; size `0x208`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LastSeenInviteNotificationId | Int | 0x158 | 0x144ff66e8 |
| LastReadFriendsTime | Float | 0x154 | 0x144ff67a0 |
| LastInviteId | Int | 0x150 | 0x144ff67d8 |
| PendingInvites | Map | 0x100 | 0x144ff6810 |
| ActiveNativeId | Struct | 0xe0 | 0x144ff68c0 |
| GameInstance | Object | 0xd8 | 0x144ff6900 |
| DirectPartyVoiceChatManager | Object | 0xd0 | 0x144ff6940 |
| VoiceChatManager | Object | 0xc8 | 0x144ff6980 |
| PartyManager | Object | 0xc0 | 0x144ff69c0 |
| CustomGameManager | Object | 0xb8 | 0x144ff6a00 |
| bIsDebugLobby | Bool | 0x98 | 0x144ff6a40 |
| OnInviteRemoved | MulticastDelegate | 0x88 | 0x144ff6ab0 |
| OnInviteReceived | MulticastDelegate | 0x78 | 0x144ff6af0 |
| OnControllerConnect | MulticastDelegate | 0x68 | 0x144ff6b30 |
| OnControllerDisconnect | MulticastDelegate | 0x58 | 0x144ff6b70 |
| OnOnlineLogin | MulticastDelegate | 0x48 | 0x144ff6bb0 |
| OnOnlineLogout | MulticastDelegate | 0x38 | 0x144ff6bf0 |
| OnReadFriendsCompleted | MulticastDelegate | 0x28 | 0x144ff6c30 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AcceptInviteByHandle | 24 | 0x144ff5d00 |
| AcceptInviteById | 8 | 0x144ff5dc0 |
| AcceptInviteFromUser | 24 | 0x144ff5e80 |
| AddFriend | 40 | 0x144ff5f00 |
| GetCustomGameManager | 8 | 0x144ff5f80 |
| GetLocalPlayerNetId | 16 | 0x144ff5fc0 |
| GetPartyManager | 8 | 0x144ff6040 |
| GetPendingInvites | 16 | 0x144ff6130 |
| GetVoiceChatManager | 8 | 0x144ff61b0 |
| IsFriend | 48 | 0x144ff62b0 |
| OnDisconnectMessageComplete | 1 | 0x144ff6370 |
| OnPartyUpdated | 1 | 0x144ff6430 |
| OnProfileSwitchedMessageComplete | 1 | 0x144ff64f0 |
| ReadFriends | 4 | 0x144ff6530 |
| RemoveInviteByHandle | 16 | 0x144ff6570 |
| RemoveInviteById | 4 | 0x144ff65b0 |
| RemoveInviteFromUser | 16 | 0x144ff6660 |
| TryGetPendingInvite | 96 | 0x144ff6760 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AcceptInviteByHandle | 0x14137a760 | 0x143a63bb0 |
| AcceptInviteById | 0x14137a810 | 0x143a63bc0 |
| AcceptInviteFromUser | 0x14137a8a0 | 0x143a63bd0 |
| AddFriend | 0x14137a950 | 0x143a63be0 |
| GetCustomGameManager | 0x14137ab60 | 0x143a63bf0 |
| GetLocalPlayerNetId | 0x14137ab80 | 0x143a63c00 |
| GetPartyManager | 0x14137ac90 | 0x143a63c10 |
| GetPendingInvites | 0x14137acb0 | 0x143a63c20 |
| GetVoiceChatManager | 0x14137aef0 | 0x143a63c30 |
| IsFriend | 0x14137af10 | 0x143a63c40 |
| OnDisconnectMessageComplete | 0x14137b0e0 | 0x143a63c50 |
| OnPartyUpdated | 0x14137b3c0 | 0x143a63c60 |
| OnProfileSwitchedMessageComplete | 0x14137b450 | 0x143a63c70 |
| ReadFriends | 0x14137b5a0 | 0x143a63c80 |
| RemoveInviteByHandle | 0x14137b6e0 | 0x143a63c90 |
| RemoveInviteById | 0x14137b780 | 0x143a63ca0 |
| RemoveInviteFromUser | 0x14137b800 | 0x143a63cb0 |
| TryGetPendingInvite | 0x14137bc40 | 0x143a63cc0 |

## MBPFBackfillingManager

Class params `0x143a6b830`; resolver `0x141380aa0`; size `0x1a8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| MatchmakingConfigProvider | Object | 0x50 | 0x144fff470 |
| GameInstance | Object | 0x48 | 0x144fff4b0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBPFMatchmakingManager

Class params `0x143a720d0`; resolver `0x141389270`; size `0x458`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| OnMatchmakingEstimateUpdated | MulticastDelegate | 0x3a8 | 0x1450010b0 |
| OnMatchmakingCancelComplete | MulticastDelegate | 0x398 | 0x1450010f0 |
| OnMatchmakingStatusChanged | MulticastDelegate | 0x388 | 0x145001130 |
| OnMatchmakingCancelled | MulticastDelegate | 0x378 | 0x145001170 |
| OnMatchmakingStarted | MulticastDelegate | 0x368 | 0x1450011b0 |
| MatchmakingConfigProvider | Object | 0x48 | 0x1450011f0 |
| OnlineStatusMessages | Object | 0x40 | 0x145001230 |
| PartyManager | Object | 0x38 | 0x145001270 |
| GameInstance | Object | 0x30 | 0x1450012b0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CancelMatchmaking | 0 | 0x145000080 |
| CheckActiveCustomAttributeValue | 40 | 0x145000140 |
| ClearAutoStartMatchmaking | 0 | 0x145000180 |
| GetActiveCustomAttributeValue | 40 | 0x145000240 |
| GetCheckingCanPlay | 1 | 0x145000300 |
| GetMatchmakingManager | 16 | 0x1450003c0 |
| IsMatchmaking | 1 | 0x145000480 |
| IsWaitingToStopMatchmaking | 1 | 0x145000540 |
| OnControllerDisconnect | 0 | 0x145000580 |
| OnOnlineLogout | 24 | 0x145000640 |
| OnPostLoadMap | 8 | 0x1450006c0 |
| OnRegionsPingsUpdated | 0 | 0x145000700 |
| OnUpdateAvailable | 1 | 0x1450007b0 |
| RegisterMatchmakingCancelledDelegate | 16 | 0x145000830 |
| RegisterMatchmakingEstimateUpdatedDelegate | 16 | 0x1450008b0 |
| RegisterMatchmakingStartedDelegate | 16 | 0x145000930 |
| RegisterMatchmakingStatusChangedDelegate | 16 | 0x1450009b0 |
| SetAutoStartMatchmaking | 0 | 0x1450009f0 |
| SetCheckingCanPlay | 1 | 0x145000ab0 |
| ShouldAutoStartMatchmaking | 1 | 0x145000b70 |
| StartMatchmaking | 1 | 0x145000c30 |
| StartMatchmakingWithSecret | 24 | 0x145000cf0 |
| TryGetMatchmakingEstimate | 8 | 0x145000db0 |
| TryGetMatchmakingTime | 8 | 0x145000e70 |
| UnregisterMatchmakingCancelledDelegate | 16 | 0x145000ef0 |
| UnregisterMatchmakingEstimateUpdatedDelegate | 16 | 0x145000f70 |
| UnregisterMatchmakingStartedDelegate | 16 | 0x145000ff0 |
| UnregisterMatchmakingStatusChangedDelegate | 16 | 0x145001070 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CancelMatchmaking | 0x141394ab0 | 0x143a82ca0 |
| CheckActiveCustomAttributeValue | 0x141394af0 | 0x143a82cb0 |
| ClearAutoStartMatchmaking | 0x141394d90 | 0x143a82cc0 |
| GetActiveCustomAttributeValue | 0x141395380 | 0x143a82cd0 |
| GetCheckingCanPlay | 0x141396f10 | 0x143a82ce0 |
| GetMatchmakingManager | 0x141397a10 | 0x143a82cf0 |
| IsMatchmaking | 0x141399560 | 0x143a82d00 |
| IsWaitingToStopMatchmaking | 0x1413995c0 | 0x143a82d10 |
| OnControllerDisconnect | 0x141394ab0 | 0x143a82d20 |
| OnOnlineLogout | 0x141399d50 | 0x143a82d30 |
| OnPostLoadMap | 0x14139a000 | 0x143a82d40 |
| OnRegionsPingsUpdated | 0x14139a080 | 0x143a82d50 |
| OnUpdateAvailable | 0x14139a0a0 | 0x143a82d60 |
| RegisterMatchmakingCancelledDelegate | 0x14139a890 | 0x143a82d70 |
| RegisterMatchmakingEstimateUpdatedDelegate | 0x14139a950 | 0x143a82d80 |
| RegisterMatchmakingStartedDelegate | 0x14139aa10 | 0x143a82d90 |
| RegisterMatchmakingStatusChangedDelegate | 0x14139aad0 | 0x143a82da0 |
| SetAutoStartMatchmaking | 0x14139ae20 | 0x143a82db0 |
| SetCheckingCanPlay | 0x14139ae40 | 0x143a82dc0 |
| ShouldAutoStartMatchmaking | 0x14139b810 | 0x143a82dd0 |
| StartMatchmaking | 0x14139b830 | 0x143a82de0 |
| StartMatchmakingWithSecret | 0x14139b8c0 | 0x143a82df0 |
| TryGetMatchmakingEstimate | 0x14139bab0 | 0x143a82e00 |
| TryGetMatchmakingTime | 0x14139bb60 | 0x143a82e10 |
| UnregisterMatchmakingCancelledDelegate | 0x14139bd90 | 0x143a82e20 |
| UnregisterMatchmakingEstimateUpdatedDelegate | 0x14139be50 | 0x143a82e30 |
| UnregisterMatchmakingStartedDelegate | 0x14139bf10 | 0x143a82e40 |
| UnregisterMatchmakingStatusChangedDelegate | 0x14139bfd0 | 0x143a82e50 |

## MBPFRegionManager

Class params `0x143a74b80`; resolver `0x141386310`; size `0x140`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0xc8 | 0x145001a40 |
| OnRegionsPingedDelegate | MulticastDelegate | 0x30 | 0x145001a80 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CanChangeSettings | 1 | 0x145001630 |
| CancelPingingRegions | 0 | 0x145001570 |
| DisableOverrideRegion | 0 | 0x145001670 |
| GetMaxPingToMatchmake | 4 | 0x1450016b0 |
| GetOverrideRegion | 4 | 0x1450016f0 |
| GetRegionNameDropdown | 40 | 0x145001770 |
| GetUserMaxPingToMatchmake | 4 | 0x145001820 |
| IsPingingRegions | 1 | 0x1450018e0 |
| SetOverrideRegion | 4 | 0x145001920 |
| SetUserMaxPingToMatchmake | 4 | 0x145001960 |
| StartPingingRegions | 4 | 0x145001a00 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CancelPingingRegions | 0x141394ad0 | 0x143a831b0 |
| CanChangeSettings | 0x141394710 | 0x143a831c0 |
| DisableOverrideRegion | 0x141395360 | 0x143a831d0 |
| GetMaxPingToMatchmake | 0x141397a90 | 0x143a831e0 |
| GetOverrideRegion | 0x141397d20 | 0x143a831f0 |
| GetRegionNameDropdown | 0x1413988f0 | 0x143a83200 |
| GetUserMaxPingToMatchmake | 0x141398f50 | 0x143a83210 |
| IsPingingRegions | 0x141399590 | 0x143a83220 |
| SetOverrideRegion | 0x14139b690 | 0x143a83230 |
| SetUserMaxPingToMatchmake | 0x14139b790 | 0x143a83240 |
| StartPingingRegions | 0x14139b9b0 | 0x143a83250 |

## MBPFServerMigrationManager

Class params `0x143a75330`; resolver `0x1413889b0`; size `0x188`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| MatchmakingConfigProvider | Object | 0x78 | 0x145001ac0 |
| ConnectedPlayersCount | Int | 0x70 | 0x145001b00 |
| GameInstance | Object | 0x68 | 0x145001b70 |
| State | Enum | 0x60 | 0x145001bb0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBPartyManager

Class params `0x143a69140`; resolver `0x141380a00`; size `0x630`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| OnlineStatusMessages | Object | 0x48 | 0x144ffce80 |
| OnlineSessionManager | Object | 0x40 | 0x144ffcec0 |
| OnPartyUpdated | MulticastDelegate | 0x30 | 0x144ffcf00 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AllPlayersCanStart | 1 | 0x144ffbf90 |
| CreatePartySession | 1 | 0x144ffc050 |
| GetPartyMembersNames | 16 | 0x144ffc090 |
| InviteFriend | 24 | 0x144ffc150 |
| IsInParty | 1 | 0x144ffc210 |
| IsInSession | 1 | 0x144ffc2d0 |
| IsInviteAllowed | 24 | 0x144ffc390 |
| IsLocalPlayerPartyLeader | 2 | 0x144ffc4c0 |
| IsLocalPlayerSinglePlayer | 1 | 0x144ffc580 |
| IsPartyFullTeam | 1 | 0x144ffc640 |
| IsPartySystemEnabled | 1 | 0x144ffc700 |
| IsPlayerInMatch | 24 | 0x144ffc7c0 |
| IsPlayerInParty | 24 | 0x144ffc880 |
| IsPlayerInvited | 24 | 0x144ffc940 |
| KickPlayerFromParty | 40 | 0x144ffc9c0 |
| LeaveParty | 1 | 0x144ffca80 |
| OnLeavePartyMessageComplete | 1 | 0x144ffcb40 |
| OnPlayerUserInfoCached | 88 | 0x144ffcc80 |
| OnSettingsUpdated | 0 | 0x144ffccc0 |
| OnUpdateAvailable | 1 | 0x144ffcd80 |
| PromoteToPartyLeader | 40 | 0x144ffce00 |
| UpdateGroupCanInvite | 0 | 0x144ffce40 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AllPlayersCanStart | 0x141383a70 | 0x143a6e0b0 |
| CreatePartySession | 0x141383c40 | 0x143a6e0c0 |
| GetPartyMembersNames | 0x141383ec0 | 0x143a6e0d0 |
| InviteFriend | 0x1413842b0 | 0x143a6e0e0 |
| IsInParty | 0x141384360 | 0x143a6e0f0 |
| IsInSession | 0x141384390 | 0x143a6e100 |
| IsInviteAllowed | 0x1413843c0 | 0x143a6e110 |
| IsLocalPlayerPartyLeader | 0x141384470 | 0x143a6e120 |
| IsLocalPlayerSinglePlayer | 0x141384500 | 0x143a6e130 |
| IsPartyFullTeam | 0x141384560 | 0x143a6e140 |
| IsPartySystemEnabled | 0x141384590 | 0x143a6e150 |
| IsPlayerInMatch | 0x1413845c0 | 0x143a6e160 |
| IsPlayerInParty | 0x141384670 | 0x143a6e170 |
| IsPlayerInvited | 0x141384720 | 0x143a6e180 |
| KickPlayerFromParty | 0x141384850 | 0x143a6e190 |
| LeaveParty | 0x141384940 | 0x143a6e1a0 |
| OnLeavePartyMessageComplete | 0x141384a10 | 0x143a6e1b0 |
| OnPlayerUserInfoCached | 0x141385220 | 0x143a6e1c0 |
| OnSettingsUpdated | 0x1413853e0 | 0x143a6e1d0 |
| OnUpdateAvailable | 0x141385400 | 0x143a6e1e0 |
| PromoteToPartyLeader | 0x141385690 | 0x143a6e1f0 |
| UpdateGroupCanInvite | 0x141385cd0 | 0x143a6e200 |

## MBPartyPanelWidget

Class params `0x143a69f20`; resolver `0x141380410`; size `0x3d0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bLoginPending | Bool | 0x3a0 | 0x144ffe110 |
| PartyUpdateCounter | Int | 0x380 | 0x144ffd1c8 |
| LocalMemberData | Struct | 0x300 | 0x144ffe180 |
| MemberData | Array | 0x2f0 | 0x144ffd248 |
| VoiceChatManager | Object | 0x2e8 | 0x144ffe200 |
| PartyManager | Object | 0x2e0 | 0x144ffe240 |
| OnlineSessionManager | Object | 0x2d8 | 0x144ffe280 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddFriend | 4 | 0x144ffd3b0 |
| Debug_SetNumPartyMembers | 4 | 0x144ffd3f0 |
| GetPlayerIdForFriend | 48 | 0x144ffd470 |
| GetPlayerIdForSelf | 40 | 0x144ffd4f0 |
| GetPlayfabPlayerIdForFriend | 48 | 0x144ffd570 |
| GetPlayfabPlayerIdForSelf | 40 | 0x144ffd5f0 |
| IsPartyFull | 1 | 0x144ffd6a0 |
| KickFromParty | 4 | 0x144ffd6e0 |
| LeaveParty | 0 | 0x144ffd720 |
| MutePartyMember | 4 | 0x144ffd760 |
| OnLocalAvatarLoaded | 56 | 0x144ffd8a0 |
| OnLogoutConfirmed | 1 | 0x144ffd960 |
| OnMemberAvatarLoaded | 56 | 0x144ffdaa0 |
| OnOnlineLogin | 24 | 0x144ffdb60 |
| OnOnlineLogout | 24 | 0x144ffdc20 |
| OnOnlineStatusChanged | 1 | 0x144ffdcd0 |
| OnPartyMemberDataUpdated | 0 | 0x144ffdd10 |
| OnPartyUpdated | 1 | 0x144ffddd0 |
| OnPlayFabIdCached | 80 | 0x144ffde90 |
| OnUserInfoCached | 88 | 0x144ffdfd0 |
| OnVoiceChatTalkerDataUpdated | 0 | 0x144ffe010 |
| PromoteToPartyLeader | 4 | 0x144ffe050 |
| SwitchPlayerAccount | 0 | 0x144ffe090 |
| UnmutePartyMember | 4 | 0x144ffe0d0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddFriend | 0x141383800 | 0x143a6e330 |
| Debug_SetNumPartyMembers | 0x141357320 | 0x143a6e340 |
| GetPlayerIdForFriend | 0x141383fb0 | 0x143a6e350 |
| GetPlayerIdForSelf | 0x1413840a0 | 0x143a6e360 |
| GetPlayfabPlayerIdForFriend | 0x141384130 | 0x143a6e370 |
| GetPlayfabPlayerIdForSelf | 0x141384220 | 0x143a6e380 |
| IsPartyFull | 0x141384530 | 0x143a6e390 |
| KickFromParty | 0x1413847d0 | 0x143a6e3a0 |
| LeaveParty | 0x141384970 | 0x143a6e3b0 |
| MutePartyMember | 0x141384990 | 0x143a6e3c0 |
| OnLocalAvatarLoaded | 0x141384a90 | 0x143a6e3d0 |
| OnLogoutConfirmed | 0x141384c10 | 0x143a6e3e0 |
| OnMemberAvatarLoaded | 0x141384c90 | 0x143a6e3f0 |
| OnOnlineLogin | 0x141384e10 | 0x143a6e400 |
| OnOnlineLogout | 0x141384f00 | 0x143a6e410 |
| OnPartyUpdated | 0x141384ff0 | 0x143a6e420 |
| OnPlayFabIdCached | 0x141385080 | 0x143a6e430 |
| OnUserInfoCached | 0x141385490 | 0x143a6e440 |
| OnVoiceChatTalkerDataUpdated | 0x141385650 | 0x143a6e450 |
| PromoteToPartyLeader | 0x141385780 | 0x143a6e460 |
| SwitchPlayerAccount | 0x141385b90 | 0x143a6e470 |
| UnmutePartyMember | 0x141385bd0 | 0x143a6e480 |

## MBPlayerAccountManager

Class params `0x143a70950`; resolver `0x141386b80`; size `0xa38`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| Server_PendingEndGameUpdate | Struct | 0x9e0 | 0x145011840 |
| PendingMatchTeamMemberCount | Int | 0x9d8 | 0x145011548 |
| PendingMatchHistoryTeamMemberRefs | Map | 0x988 | 0x145011608 |
| LastDirtyCharacterCustomisations | Array | 0x978 | 0x1450118b8 |
| DirtyCharacterCustomisations | Array | 0x968 | 0x145011968 |
| PushingDirtyCharacterCustomisation | Bool | 0x960 | 0x145011a10 |
| DirtyCharacterTimerHandle | Struct | 0x958 | 0x145011a90 |
| SendPIEOnlineRequestTimer | Struct | 0x940 | 0x145011ad0 |
| DelayedPIEOnlineRequests | Array | 0x930 | 0x1450119d8 |
| PIERequestFailureRate | Float | 0x92c | 0x145011a58 |
| CurrentOnlineStatus | Enum | 0x928 | 0x145011b50 |
| PendingRequests | Array | 0x918 | 0x145011bd0 |
| AccountInformationStrings | Array | 0x908 | 0x145011c08 |
| StatsManager | Object | 0x900 | 0x145011cf0 |
| PlayerClassTable | Object | 0x8f8 | 0x145011d30 |
| AchievementAssetList | Object | 0x8f0 | 0x145011d70 |
| StoreAssetList | Object | 0x8e8 | 0x145011db0 |
| MaxStatsCacheMinutes | Float | 0x8e0 | 0x145011cb8 |
| CachedPartsData | Struct | 0x8c8 | 0x145011df0 |
| CachedCreditsData | Struct | 0x8b0 | 0x145011e30 |
| CachedHeroXPData | Struct | 0x880 | 0x145011e70 |
| CachedAccountXPData | Struct | 0x850 | 0x145011eb0 |
| CachedTrashModPartsCost | Int | 0x848 | 0x145011ef0 |
| CachedBuildModPartsCost | Int | 0x844 | 0x145011f28 |
| EulaStatus | Enum | 0x840 | 0x145011f60 |
| CompletedTutorials | Array | 0x830 | 0x145011fe0 |
| TutorialStatus | Enum | 0x828 | 0x145012050 |
| ViewedTaunts | Array | 0x818 | 0x1450120d0 |
| ViewedCustomisations | Array | 0x808 | 0x145012140 |
| ViewedMods | Array | 0x7f8 | 0x1450121b0 |
| bHasPendingDirtyUpdate | Bool | 0x7f0 | 0x145012220 |
| PlayerIdToDisplayName | Map | 0x7a0 | 0x145012268 |
| AchievementAssetMap | Map | 0x750 | 0x145012310 |
| SkinAssetMap | Map | 0x700 | 0x1450123c0 |
| TauntAssetMap | Map | 0x6b0 | 0x145012470 |
| CustomisationAssetMap | Map | 0x660 | 0x145012520 |
| ModAssetMap | Map | 0x610 | 0x1450125d0 |
| LocalPlayerLoggedOutMulticaster | MulticastDelegate | 0x600 | 0x145012680 |
| LocalPlayerLoggedInMulticaster | MulticastDelegate | 0x5f0 | 0x1450126c0 |
| LocalPlayerLoginStatus | Enum | 0x5e8 | 0x145012700 |
| LocalPlayerId | Struct | 0x5c0 | 0x145012780 |
| PlayerIdMap | Map | 0x570 | 0x1450127c0 |
| AccountData | Map | 0x510 | 0x145012870 |
| bIsFreeBuildActive | Bool | 0x50a | 0x145012960 |
| bIsFreeBuildAvailable | Bool | 0x509 | 0x1450129e0 |
| bFakeOnlineResponses | Bool | 0x508 | 0x145012a60 |
| OnlineSessionManager | Object | 0x4f8 | 0x145012ae0 |
| GameInstance | Object | 0x4f0 | 0x145012b20 |
| MostRecentXPUpdate | Struct | 0x380 | 0x145012b60 |
| XPUpdateMulticasters | Map | 0x330 | 0x1450128a8 |
| OnMatchDetailsUpdated | MulticastDelegate | 0x2c0 | 0x145012be0 |
| OnMatchPagesUpdated | MulticastDelegate | 0x2b0 | 0x145012c20 |
| OnEulaStatusCached | MulticastDelegate | 0x2a0 | 0x145012c60 |
| OnTutorialStatusCached | MulticastDelegate | 0x290 | 0x145012ca0 |
| OnOnlineStatusChanged | MulticastDelegate | 0x280 | 0x145012ce0 |
| OnPendingRequestsChanged | MulticastDelegate | 0x270 | 0x145012d20 |
| OnCustomisationPurchaseFailure | MulticastDelegate | 0x260 | 0x145012d60 |
| OnNewModBuildMade | MulticastDelegate | 0x250 | 0x145012da0 |
| OnModTrashFailure | MulticastDelegate | 0x240 | 0x145012de0 |
| OnModBuildFailure | MulticastDelegate | 0x230 | 0x145012e20 |
| OnEntitlementItemsChanged | MulticastDelegate | 0x220 | 0x145012e60 |
| OnAchievementChanged | MulticastDelegate | 0x210 | 0x145012ea0 |
| OnSkinPurchaseFailure | MulticastDelegate | 0x200 | 0x145012ee0 |
| OnSkinEquipped | MulticastDelegate | 0x1f0 | 0x145012f20 |
| OnSkinPurchased | MulticastDelegate | 0x1e0 | 0x145012f60 |
| OnSkinChanged | MulticastDelegate | 0x1d0 | 0x145012fa0 |
| OnTauntPurchaseFailure | MulticastDelegate | 0x1c0 | 0x145012fe0 |
| OnTauntEquipped | MulticastDelegate | 0x1b0 | 0x145013020 |
| OnTauntPurchased | MulticastDelegate | 0x1a0 | 0x145013060 |
| OnTauntChanged | MulticastDelegate | 0x190 | 0x1450130a0 |
| OnAwardsGiven | MulticastDelegate | 0x180 | 0x1450130e0 |
| OnPurchaseResult | MulticastDelegate | 0x170 | 0x145013120 |
| OnCustomisationEquipped | MulticastDelegate | 0x160 | 0x145013160 |
| OnCustomisationPurchased | MulticastDelegate | 0x150 | 0x1450131a0 |
| OnCustomisationChanged | MulticastDelegate | 0x140 | 0x1450131e0 |
| OnCreditsChanged | MulticastDelegate | 0x130 | 0x145013220 |
| OnHeroBuildsChanged | MulticastDelegate | 0x120 | 0x145013260 |
| OnModsChanged | MulticastDelegate | 0x110 | 0x1450132a0 |
| OnPartsChanged | MulticastDelegate | 0x100 | 0x1450132e0 |
| StatManagerClass | Struct | 0x88 | 0x145013320 |
| PartsTableCsv | Str | 0x78 | 0x145012a28 |
| CreditsTableCsv | Str | 0x68 | 0x145012aa8 |
| CommonLevellingCsv | Str | 0x58 | 0x145013360 |
| HeroLevellingCsv | Str | 0x48 | 0x145013398 |
| AccountLevellingCsv | Str | 0x38 | 0x1450133d0 |
| HeroFreeBuildCount | Int | 0x30 | 0x145013408 |
| HeroBuildCount | Int | 0x2c | 0x145013440 |
| HeroBuildModCount | Int | 0x28 | 0x145013478 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AcceptedEula | 0 | 0x14500a090 |
| AreCreditsCached | 1 | 0x14500a150 |
| AreHeroBuildsCached | 1 | 0x14500a210 |
| AreHeroCustomisationsCached | 1 | 0x14500a2d0 |
| AreLevelsCached | 1 | 0x14500a390 |
| AreModsCached | 1 | 0x14500a450 |
| ArePartsCached | 1 | 0x14500a510 |
| ArePlayerHeroCustomisationsCached | 48 | 0x14500a610 |
| ArePlayerModsCached | 48 | 0x14500a710 |
| ArePlayerSkinsCached | 48 | 0x14500a810 |
| ArePlayerTauntsCached | 48 | 0x14500a910 |
| AreSkinsCached | 1 | 0x14500a9d0 |
| AreTauntsCached | 1 | 0x14500aa90 |
| BuildMod | 8 | 0x14500ab10 |
| BuyCustomisation | 24 | 0x14500abd0 |
| BuySkin | 24 | 0x14500ac90 |
| BuyTaunt | 24 | 0x14500ad50 |
| CacheEulaStatus | 16 | 0x14500add0 |
| CachePlayerAccountInformation | 16 | 0x14500ae90 |
| CachePlayerAccountInformationWithCallback | 32 | 0x14500af90 |
| CacheTutorialStatus | 16 | 0x14500b010 |
| CallbackWhenAccountInfoCached | 24 | 0x14500b110 |
| CallbackWhenCustomisationsCached | 16 | 0x14500b190 |
| CallbackWhenHeroBuildsCached | 16 | 0x14500b210 |
| CallbackWhenLevelsCached | 16 | 0x14500b290 |
| CallbackWhenModsCached | 16 | 0x14500b310 |
| CallbackWhenPartsCached | 16 | 0x14500b390 |
| CallbackWhenSkinCached | 16 | 0x14500b410 |
| CallbackWhenTauntCached | 16 | 0x14500b490 |
| CanCustomise | 24 | 0x14500b590 |
| CanEquipSkin | 24 | 0x14500b690 |
| CanEquipTaunt | 24 | 0x14500b790 |
| CanPutModOnHeroBuildSlot | 32 | 0x14500b890 |
| CheckCustomisationNameIsValid | 24 | 0x14500b910 |
| CheckCustomisationType | 24 | 0x14500ba50 |
| ClearAllCachedPlayerAccountInformation | 0 | 0x14500ba90 |
| ClearCachedPlayerAccountInformation | 40 | 0x14500bb10 |
| ClearSpecifiedCachedPlayerAccountInformation | 16 | 0x14500bbd0 |
| ClearSpecifiedCachedPlayerAccountInformationForPlayer | 56 | 0x14500bcd0 |
| CompletedTutorial | 16 | 0x14500bd90 |
| Debug_BuyTaunt | 16 | 0x14500bdd0 |
| Debug_EquipTaunt | 16 | 0x14500be80 |
| Debug_TryGetRandomModName | 16 | 0x14500bf40 |
| GetCachedAccountLevel | 4 | 0x14500bf80 |
| GetCachedAccountXP | 4 | 0x14500c030 |
| GetCachedAccountXPValues | 20 | 0x14500c150 |
| GetCachedBuildModCost | 4 | 0x14500c200 |
| GetCachedCompletedAchievements | 32 | 0x14500c300 |
| GetCachedCustomisationByHero | 120 | 0x14500c3f0 |
| GetCachedDailyAchievements | 32 | 0x14500c4f0 |
| GetCachedHeroBuild | 64 | 0x14500c5e0 |
| GetCachedHeroLevel | 16 | 0x14500c690 |
| GetCachedHeroXP | 16 | 0x14500c740 |
| GetCachedHeroXPValues | 32 | 0x14500c8d0 |
| GetCachedPlayerAccountXPValues | 64 | 0x14500caa0 |
| GetCachedPlayerAchievements | 24 | 0x14500cb90 |
| GetCachedPlayerAvailableSkin | 24 | 0x14500cc80 |
| GetCachedPlayerAvailableTaunt | 24 | 0x14500cd70 |
| GetCachedPlayerCredits | 4 | 0x14500cdb0 |
| GetCachedPlayerCustomisation | 24 | 0x14500cea0 |
| GetCachedPlayerEquippedCustomisation | 40 | 0x14500cfd0 |
| GetCachedPlayerHeroXPValues | 72 | 0x14500d1a0 |
| GetCachedPlayerMods | 32 | 0x14500d310 |
| GetCachedPlayerParts | 4 | 0x14500d3c0 |
| GetCachedRegularHeroBuildCount | 16 | 0x14500d470 |
| GetCachedTauntsByHero | 24 | 0x14500d4f0 |
| GetCachedTotalHeroBuildCount | 16 | 0x14500d5a0 |
| GetCachedTrashModCost | 4 | 0x14500d650 |
| GetCharacterStatOwnerList | 16 | 0x14500d700 |
| GetCompletedTutorialList | 16 | 0x14500d7b0 |
| GetCustomisationForHero | 48 | 0x14500d8f0 |
| GetEquippedSkinForHero | 32 | 0x14500d9f0 |
| GetEquippedTauntForHero | 32 | 0x14500daf0 |
| GetFreeBuildActive | 1 | 0x14500dbb0 |
| GetFreeBuildAvailable | 1 | 0x14500dc70 |
| GetHeroBuildCharacters | 16 | 0x14500dcb0 |
| GetIntroCinematicWatched | 16 | 0x14500dd30 |
| GetKillDeathRatio | 16 | 0x14500dde0 |
| GetLocalPlayerId | 40 | 0x14500de60 |
| GetMatchHistoryCount | 48 | 0x14500df90 |
| GetMatchHistoryEntry | 200 | 0x14500e0c0 |
| GetMatchesPerPage | 4 | 0x14500df10 |
| GetModDefinition | 16 | 0x14500e140 |
| GetMountInfoByHero | 104 | 0x14500e240 |
| GetNumNewMods | 16 | 0x14500e2f0 |
| GetNumPendingOnlineRequests | 4 | 0x14500e3a0 |
| GetOnlineStatus | 1 | 0x14500e460 |
| GetPlayTimeHours | 16 | 0x14500ed40 |
| GetPlayerAccountManager | 16 | 0x14500e520 |
| GetPlayerCachedPlayerAvailableSkin | 64 | 0x14500e650 |
| GetPlayerCachedPlayerAvailableTaunt | 64 | 0x14500e780 |
| GetPlayerCachedPlayerCustomisation | 64 | 0x14500e8b0 |
| GetPlayerCachedPlayerEquippedCustomisation | 80 | 0x14500ea20 |
| GetPlayerCachedPlayerMods | 72 | 0x14500ebd0 |
| GetPlayerId | 48 | 0x14500ec90 |
| GetProfileStatsManager | 16 | 0x14500ee00 |
| GetStatAsFloat | 24 | 0x14500eeb0 |
| GetStatAsInt | 24 | 0x14500efd0 |
| GetStatAsTime | 32 | 0x14500f0f0 |
| GetStatsVisible | 48 | 0x14500f1f0 |
| GetTotalKills | 16 | 0x14500f2a0 |
| GetTotalNumNewMods | 4 | 0x14500f2e0 |
| GetWinRatio | 16 | 0x14500f390 |
| GetXPForAccountLevel | 8 | 0x14500f440 |
| GetXPForHeroLevel | 8 | 0x14500f4f0 |
| HasAnyInvalidBuilds | 1 | 0x14500f5b0 |
| HasAnyModsForType | 16 | 0x14500f6f0 |
| HasAnyPatchedBuilds | 1 | 0x14500f7b0 |
| HasCompletedTutorial | 16 | 0x14500f870 |
| HasInvalidBuilds | 16 | 0x14500f930 |
| HasNewMods | 16 | 0x14500f9f0 |
| HasPatchedBuilds | 16 | 0x14500fab0 |
| HasShownPatchedBuildWarning | 1 | 0x14500fb70 |
| IsAccountInformationCached | 48 | 0x14500fcf0 |
| MarkCustomisationAsEquipped | 16 | 0x14500fdf0 |
| MarkCustomisationAsViewed | 8 | 0x14500fe30 |
| MarkModAsViewed | 8 | 0x14500fe70 |
| MarkSkinAsEquipped | 16 | 0x14500ff70 |
| MarkTauntAsEquipped | 16 | 0x145010070 |
| MarkTauntnAsViewed | 8 | 0x1450100b0 |
| OnCachePlayerAccountInformation | 40 | 0x145010130 |
| OnEnterWorkshop | 0 | 0x145010170 |
| OnExitWorkshop | 0 | 0x1450101b0 |
| OnFinishedCachingStats | 48 | 0x1450102b0 |
| OnPlayerUserInfoCached | 88 | 0x1450103f0 |
| PushDirtyUpdates | 0 | 0x145010430 |
| PutCustomisationOnAllHeroes | 16 | 0x1450104f0 |
| PutCustomisationOnHero | 56 | 0x145010670 |
| PutModOnHeroBuildSlot | 32 | 0x145010770 |
| PutSkinOnHero | 24 | 0x1450108e0 |
| PutTauntOnHero | 24 | 0x1450109e0 |
| ReceiveOutputEvent | 16 | 0x145010ad0 |
| RegisterLoggedInCallback | 16 | 0x145010b50 |
| RegisterLoggedOutCallback | 16 | 0x145010bd0 |
| RenameHeroBuild | 40 | 0x145010c80 |
| RequiresEulaPrompt | 2 | 0x145010dc0 |
| RequiresTutorialPrompt | 1 | 0x145010e80 |
| SendNextOnlineRequest | 0 | 0x145010ec0 |
| SetDesiredMatchPages | 56 | 0x145010f40 |
| SetFreeBuildActive | 1 | 0x145011000 |
| SetFreeBuildAvailable | 1 | 0x1450110c0 |
| SetHeroBuild | 56 | 0x1450111c0 |
| SetHeroCustomisation | 104 | 0x1450112c0 |
| SetHeroSkin | 32 | 0x1450113c0 |
| SetHeroTaunt | 32 | 0x1450114c0 |
| SetIntroCinematicWatched | 1 | 0x145011580 |
| SetShownPatchedBuildWarning | 1 | 0x145011640 |
| TrashMod | 8 | 0x1450116c0 |
| UnregisterLoggedInCallback | 16 | 0x145011740 |
| UnregisterLoggedOutCallback | 16 | 0x1450117c0 |
| UpdateFreeBuildAvailable | 0 | 0x145011800 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AcceptedEula | 0x141393450 | 0x143a86c50 |
| AreCreditsCached | 0x141393470 | 0x143a86c60 |
| AreHeroBuildsCached | 0x1413934a0 | 0x143a86c70 |
| AreHeroCustomisationsCached | 0x1413934d0 | 0x143a86c80 |
| AreLevelsCached | 0x141393500 | 0x143a86c90 |
| AreModsCached | 0x141393530 | 0x143a86ca0 |
| ArePartsCached | 0x141393560 | 0x143a86cb0 |
| ArePlayerHeroCustomisationsCached | 0x141393590 | 0x143a86cc0 |
| ArePlayerModsCached | 0x141393690 | 0x143a86cd0 |
| ArePlayerSkinsCached | 0x141393790 | 0x143a86ce0 |
| ArePlayerTauntsCached | 0x141393890 | 0x143a86cf0 |
| AreSkinsCached | 0x141393990 | 0x143a86d00 |
| AreTauntsCached | 0x1413939c0 | 0x143a86d10 |
| BuildMod | 0x1413939f0 | 0x143a86d20 |
| BuyCustomisation | 0x141393a70 | 0x143a86d30 |
| BuySkin | 0x141393b70 | 0x143a86d40 |
| BuyTaunt | 0x141393c70 | 0x143a86d50 |
| CacheEulaStatus | 0x141393d70 | 0x143a86d60 |
| CachePlayerAccountInformation | 0x141393e30 | 0x143a86d70 |
| CachePlayerAccountInformationWithCallback | 0x141393ee0 | 0x143a86d80 |
| CacheTutorialStatus | 0x141394010 | 0x143a86d90 |
| CallbackWhenAccountInfoCached | 0x1413940d0 | 0x143a86da0 |
| CallbackWhenCustomisationsCached | 0x1413941d0 | 0x143a86db0 |
| CallbackWhenHeroBuildsCached | 0x141394290 | 0x143a86dc0 |
| CallbackWhenLevelsCached | 0x141394350 | 0x143a86dd0 |
| CallbackWhenModsCached | 0x141394410 | 0x143a86de0 |
| CallbackWhenPartsCached | 0x1413944d0 | 0x143a86df0 |
| CallbackWhenSkinCached | 0x141394590 | 0x143a86e00 |
| CallbackWhenTauntCached | 0x141394650 | 0x143a86e10 |
| CanCustomise | 0x141394730 | 0x143a86e20 |
| CanEquipSkin | 0x1413947f0 | 0x143a86e30 |
| CanEquipTaunt | 0x1413948b0 | 0x143a86e40 |
| CanPutModOnHeroBuildSlot | 0x141394970 | 0x143a86e50 |
| CheckCustomisationNameIsValid | 0x141394bf0 | 0x143a86e60 |
| CheckCustomisationType | 0x141394cb0 | 0x143a86e70 |
| ClearAllCachedPlayerAccountInformation | 0x141394d70 | 0x143a86e80 |
| ClearCachedPlayerAccountInformation | 0x141394db0 | 0x143a86e90 |
| ClearSpecifiedCachedPlayerAccountInformation | 0x141394ea0 | 0x143a86ea0 |
| ClearSpecifiedCachedPlayerAccountInformationForPlayer | 0x141394f50 | 0x143a86eb0 |
| CompletedTutorial | 0x1413950b0 | 0x143a86ec0 |
| Debug_BuyTaunt | 0x141395140 | 0x143a86ed0 |
| Debug_EquipTaunt | 0x141395200 | 0x143a86ee0 |
| Debug_TryGetRandomModName | 0x1413952c0 | 0x143a86ef0 |
| GetCachedAccountLevel | 0x141395490 | 0x143a86f00 |
| GetCachedAccountXP | 0x1413954c0 | 0x143a86f10 |
| GetCachedAccountXPValues | 0x1413954f0 | 0x143a86f20 |
| GetCachedBuildModCost | 0x1413956f0 | 0x143a86f30 |
| GetCachedCompletedAchievements | 0x141395720 | 0x143a86f40 |
| GetCachedCustomisationByHero | 0x141395820 | 0x143a86f50 |
| GetCachedDailyAchievements | 0x1413959a0 | 0x143a86f60 |
| GetCachedHeroBuild | 0x141395aa0 | 0x143a86f70 |
| GetCachedHeroLevel | 0x141395c20 | 0x143a86f80 |
| GetCachedHeroXP | 0x141395cb0 | 0x143a86f90 |
| GetCachedHeroXPValues | 0x141395d40 | 0x143a86fa0 |
| GetCachedPlayerAccountXPValues | 0x141395f60 | 0x143a86fb0 |
| GetCachedPlayerAchievements | 0x1413961f0 | 0x143a86fc0 |
| GetCachedPlayerAvailableSkin | 0x1413962e0 | 0x143a86fd0 |
| GetCachedPlayerAvailableTaunt | 0x141396400 | 0x143a86fe0 |
| GetCachedPlayerCredits | 0x141396520 | 0x143a86ff0 |
| GetCachedPlayerCustomisation | 0x141396550 | 0x143a87000 |
| GetCachedPlayerEquippedCustomisation | 0x141396670 | 0x143a87010 |
| GetCachedPlayerHeroXPValues | 0x1413967d0 | 0x143a87020 |
| GetCachedPlayerMods | 0x141396aa0 | 0x143a87030 |
| GetCachedPlayerParts | 0x141396c00 | 0x143a87040 |
| GetCachedRegularHeroBuildCount | 0x141396c30 | 0x143a87050 |
| GetCachedTauntsByHero | 0x141396cc0 | 0x143a87060 |
| GetCachedTotalHeroBuildCount | 0x141396da0 | 0x143a87070 |
| GetCachedTrashModCost | 0x141396e30 | 0x143a87080 |
| GetCharacterStatOwnerList | 0x141396e60 | 0x143a87090 |
| GetCompletedTutorialList | 0x141396f30 | 0x143a870a0 |
| GetCustomisationForHero | 0x141396fe0 | 0x143a870b0 |
| GetEquippedSkinForHero | 0x141397140 | 0x143a870c0 |
| GetEquippedTauntForHero | 0x141397230 | 0x143a870d0 |
| GetFreeBuildActive | 0x141397320 | 0x143a870e0 |
| GetFreeBuildAvailable | 0x141397350 | 0x143a870f0 |
| GetHeroBuildCharacters | 0x141397380 | 0x143a87100 |
| GetIntroCinematicWatched | 0x141397430 | 0x143a87110 |
| GetKillDeathRatio | 0x1413974f0 | 0x143a87120 |
| GetLocalPlayerId | 0x141397590 | 0x143a87130 |
| GetMatchesPerPage | 0x1413979f0 | 0x143a87140 |
| GetMatchHistoryCount | 0x141397620 | 0x143a87150 |
| GetMatchHistoryEntry | 0x141397720 | 0x143a87160 |
| GetModDefinition | 0x141397ab0 | 0x143a87170 |
| GetMountInfoByHero | 0x141397b40 | 0x143a87180 |
| GetNumNewMods | 0x141397c50 | 0x143a87190 |
| GetNumPendingOnlineRequests | 0x141397ce0 | 0x143a871a0 |
| GetOnlineStatus | 0x141397d00 | 0x143a871b0 |
| GetPlayerAccountManager | 0x141397df0 | 0x143a871c0 |
| GetPlayerCachedPlayerAvailableSkin | 0x141397e70 | 0x143a871d0 |
| GetPlayerCachedPlayerAvailableTaunt | 0x141398020 | 0x143a871e0 |
| GetPlayerCachedPlayerCustomisation | 0x1413981d0 | 0x143a871f0 |
| GetPlayerCachedPlayerEquippedCustomisation | 0x141398380 | 0x143a87200 |
| GetPlayerCachedPlayerMods | 0x141398580 | 0x143a87210 |
| GetPlayerId | 0x141398780 | 0x143a87220 |
| GetPlayTimeHours | 0x141397d50 | 0x143a87230 |
| GetProfileStatsManager | 0x141398870 | 0x143a87240 |
| GetStatAsFloat | 0x141398a40 | 0x143a87250 |
| GetStatAsInt | 0x141398b00 | 0x143a87260 |
| GetStatAsTime | 0x141398bc0 | 0x143a87270 |
| GetStatsVisible | 0x141398d90 | 0x143a87280 |
| GetTotalKills | 0x141398e90 | 0x143a87290 |
| GetTotalNumNewMods | 0x141398f20 | 0x143a872a0 |
| GetWinRatio | 0x1413974f0 | 0x143a872b0 |
| GetXPForAccountLevel | 0x141398f80 | 0x143a872c0 |
| GetXPForHeroLevel | 0x141399010 | 0x143a872d0 |
| HasAnyInvalidBuilds | 0x1413990a0 | 0x143a872e0 |
| HasAnyModsForType | 0x1413990d0 | 0x143a872f0 |
| HasAnyPatchedBuilds | 0x141399190 | 0x143a87300 |
| HasCompletedTutorial | 0x1413991c0 | 0x143a87310 |
| HasInvalidBuilds | 0x141399250 | 0x143a87320 |
| HasNewMods | 0x1413992e0 | 0x143a87330 |
| HasPatchedBuilds | 0x141399370 | 0x143a87340 |
| HasShownPatchedBuildWarning | 0x141399400 | 0x143a87350 |
| IsAccountInformationCached | 0x141399420 | 0x143a87360 |
| MarkCustomisationAsEquipped | 0x1413995e0 | 0x143a87370 |
| MarkCustomisationAsViewed | 0x1413996b0 | 0x143a87380 |
| MarkModAsViewed | 0x141399730 | 0x143a87390 |
| MarkSkinAsEquipped | 0x1413997b0 | 0x143a873a0 |
| MarkTauntAsEquipped | 0x141399880 | 0x143a873b0 |
| MarkTauntnAsViewed | 0x141399950 | 0x143a873c0 |
| OnCachePlayerAccountInformation | 0x1413999d0 | 0x143a873d0 |
| OnEnterWorkshop | 0x141399bd0 | 0x143a873e0 |
| OnExitWorkshop | 0x141399bf0 | 0x143a873f0 |
| OnFinishedCachingStats | 0x141399c10 | 0x143a87400 |
| OnPlayerUserInfoCached | 0x141399e40 | 0x143a87410 |
| PushDirtyUpdates | 0x14139a130 | 0x143a87420 |
| PutCustomisationOnAllHeroes | 0x14139a150 | 0x143a87430 |
| PutCustomisationOnHero | 0x14139a1e0 | 0x143a87440 |
| PutModOnHeroBuildSlot | 0x14139a390 | 0x143a87450 |
| PutSkinOnHero | 0x14139a4d0 | 0x143a87460 |
| PutTauntOnHero | 0x14139a590 | 0x143a87470 |
| ReceiveOutputEvent | 0x14139a650 | 0x143a87480 |
| RegisterLoggedInCallback | 0x14139a710 | 0x143a87490 |
| RegisterLoggedOutCallback | 0x14139a7d0 | 0x143a874a0 |
| RenameHeroBuild | 0x14139ab90 | 0x143a874b0 |
| RequiresEulaPrompt | 0x14139acf0 | 0x143a874c0 |
| RequiresTutorialPrompt | 0x14139add0 | 0x143a874d0 |
| SendNextOnlineRequest | 0x14139ae00 | 0x143a874e0 |
| SetDesiredMatchPages | 0x14139aed0 | 0x143a874f0 |
| SetFreeBuildActive | 0x14139b060 | 0x143a87500 |
| SetFreeBuildAvailable | 0x14139b0f0 | 0x143a87510 |
| SetHeroBuild | 0x14139b180 | 0x143a87520 |
| SetHeroCustomisation | 0x14139b310 | 0x143a87530 |
| SetHeroSkin | 0x14139b420 | 0x143a87540 |
| SetHeroTaunt | 0x14139b510 | 0x143a87550 |
| SetIntroCinematicWatched | 0x14139b600 | 0x143a87560 |
| SetShownPatchedBuildWarning | 0x14139b710 | 0x143a87570 |
| TrashMod | 0x14139ba30 | 0x143a87580 |
| UnregisterLoggedInCallback | 0x14139bc10 | 0x143a87590 |
| UnregisterLoggedOutCallback | 0x14139bcd0 | 0x143a875a0 |
| UpdateFreeBuildAvailable | 0x14139c090 | 0x143a875b0 |

## MBPlayerAssetHandler

Class params `0x143a87990`; resolver `0x14139cbf0`; size `0x68`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| OverrideRequestLevel | Enum | 0x60 | 0x145014ac0 |
| PlayerRecords | Array | 0x50 | 0x145014b40 |
| GameInstance | Object | 0x48 | 0x145014be0 |
| PlayerAssetManager | Object | 0x40 | 0x145014c20 |
| PlayerClassTable | Object | 0x38 | 0x145014c60 |
| PlayerLoadStatusDelegate | MulticastDelegate | 0x28 | 0x145014ca0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AreGKAssetsLoaded | 8 | 0x145013f90 |
| ArePreviewAssetsLoaded | 8 | 0x145014050 |
| AreVisualAssetsLoaded | 8 | 0x145014110 |
| CleanupAssetHandler | 0 | 0x145014150 |
| ClearAllPlayers | 0 | 0x145014190 |
| ClearPlayerAssets | 4 | 0x1450141d0 |
| CreateAssetHandler | 16 | 0x145014290 |
| GetPlayerAssetsLoadStatus | 8 | 0x1450143c0 |
| OnAssetLoadStatusChange | 40 | 0x1450144c0 |
| SetOverrideRequestLevel | 1 | 0x145014580 |
| SetPlayerAssets | 96 | 0x1450148c0 |
| SetPlayerRequestLevel | 8 | 0x145014a80 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AreGKAssetsLoaded | 0x14139f700 | 0x143a8be70 |
| ArePreviewAssetsLoaded | 0x14139f790 | 0x143a8be80 |
| AreVisualAssetsLoaded | 0x14139f820 | 0x143a8be90 |
| CleanupAssetHandler | 0x14139f8b0 | 0x143a8bea0 |
| ClearAllPlayers | 0x14139f8b0 | 0x143a8beb0 |
| ClearPlayerAssets | 0x14139f8d0 | 0x143a8bec0 |
| CreateAssetHandler | 0x14139f950 | 0x143a8bed0 |
| GetPlayerAssetsLoadStatus | 0x14139fa10 | 0x143a8bee0 |
| OnAssetLoadStatusChange | 0x14139fcc0 | 0x143a8bef0 |
| SetOverrideRequestLevel | 0x1413a0180 | 0x143a8bf00 |
| SetPlayerAssets | 0x1413a0200 | 0x143a8bf10 |
| SetPlayerRequestLevel | 0x1413a05a0 | 0x143a8bf20 |

## MBPlayerAvatarManager

Class params `0x143a88450`; resolver `0x14139c6e0`; size `0x158`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CachedPlayerUserInfo | Map | 0xf8 | 0x1450154e8 |
| PendingPlayerUserInfoRequests | Map | 0xa8 | 0x145015568 |
| AvatarTextureSetMap | Map | 0x58 | 0x1450156e8 |
| NextRequestId | Int | 0x50 | 0x145015768 |
| AvatarTextureBatchRequestQueue | Array | 0x40 | 0x1450158a8 |
| AvatarTextureRequests | Array | 0x30 | 0x145015aa0 |
| GameInstance | Object | 0x28 | 0x145015b40 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBPlayerController

Class params `0x143a920c0`; resolver `0x1413a2d10`; size `0x1098`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PendingChangeClassTimeRemaining | Float | 0x1088 | 0x145020ec8 |
| PendingChangeClassParams | Struct | 0x1020 | 0x145020f40 |
| JoinTime | Float | 0x1018 | 0x145020f80 |
| bDebugLookControls | Bool | 0x1014 | 0x145020ff0 |
| AccelerationTimer_Y | Float | 0x1010 | 0x145020fb8 |
| AccelerationTimer_X | Float | 0x100c | 0x145021038 |
| AcceleratingLook_Y | Bool | 0x100a | 0x145021070 |
| AcceleratingLook_X | Bool | 0x1009 | 0x1450210f0 |
| bCanUseDebugCam | Bool | 0x1008 | 0x145021170 |
| FrontendInputChangedMulticaster | MulticastDelegate | 0xf78 | 0x1450211f0 |
| bResetCameraOnPosses | Bool | 0xf72 | 0x145021230 |
| bForceShowMouseCursor | Bool | 0xf71 | 0x1450212b0 |
| SpectatorManager | Object | 0xf68 | 0x145021330 |
| CharacterLockInMulticaster | MulticastDelegate | 0xf58 | 0x145021370 |
| CharacterSelectMulticaster | MulticastDelegate | 0xf48 | 0x1450213b0 |
| LastSelectedModBuildIndices | Map | 0xef8 | 0x1450210b8 |
| CosmeticTauntAssets | Array | 0xee8 | 0x145021278 |
| CosmeticAssetSession | Object | 0xee0 | 0x145021430 |
| CosmeticSkins | Array | 0xed0 | 0x1450212f8 |
| CosmeticTaunts | Array | 0xec0 | 0x1450214b0 |
| CosmeticUserData | Struct | 0xeb0 | 0x145021560 |
| CosmeticCustomisations | Array | 0xea0 | 0x1450214e8 |
| CosmeticMods | Array | 0xe90 | 0x1450215e0 |
| CosmeticSuperAbilityIndex | Int | 0xe88 | 0x145021618 |
| CosmeticCharacterClass | Name | 0xe80 | 0x145021690 |
| CosmeticCharacterLockInState | Enum | 0xe78 | 0x145021700 |
| EnabledCheats | Array | 0xe60 | 0x1450216c8 |
| MuteAudioTokens | Array | 0xe50 | 0x1450217b8 |
| ChatWheelWidgets | Array | 0xe40 | 0x145021828 |
| ChatWidgets | Array | 0xe30 | 0x1450218a0 |
| MutedPlayers | Array | 0xe20 | 0x1450218d8 |
| MutedChannels | Int | 0xe1c | 0x145021988 |
| ChatIdGenerator | Struct | 0xe18 | 0x1450219c0 |
| TimerHandle_HideOldChat | Struct | 0xe10 | 0x145021a00 |
| ChatHistory | Array | 0xe00 | 0x145021a40 |
| PreviousChannel | Enum | 0xdf8 | 0x145021af0 |
| CurrentMessage | Str | 0xde8 | 0x145021a78 |
| CurrentTarget | Str | 0xdd8 | 0x145021b70 |
| CurrentChannel | Enum | 0xdd1 | 0x145021be0 |
| ChatActive | Bool | 0xdd0 | 0x145021c60 |
| ChatWheelSpamFilter | Struct | 0xdb0 | 0x145021ce0 |
| MostRecentAcknowledgeableChatTimeStamp | Float | 0xdac | 0x145021ba8 |
| MostRecentAcknowledgeableChatType | Enum | 0xda8 | 0x145021d20 |
| ChatWheelHistory | Map | 0xd58 | 0x145021ca8 |
| bIsProvidingAnyFrontEndInput | Bool | 0xd54 | 0x145021e50 |
| MostRecentInputTimeStamp | Float | 0xd50 | 0x145021dd8 |
| LastStickInput | Struct | 0xd48 | 0x145021ed0 |
| ComboRecords | Array | 0xd38 | 0x145021e98 |
| TargetableProxies | Array | 0xd10 | 0x145021f50 |
| LeaveReason | Str | 0xcf0 | 0x145021f88 |
| TargetingSettings_Controller | Struct | 0xcd8 | 0x145022000 |
| TargetingSettings_KeyboardAndMouse | Struct | 0xcd0 | 0x145022040 |
| OnChatWheelSelectionReceived | MulticastDelegate | 0xcc0 | 0x145022080 |
| OnChatUpdated | MulticastDelegate | 0xcb0 | 0x1450220c0 |
| bCosmeticKioskPlayerReadyStatus | Bool | 0xcac | 0x145022100 |
| ProfileLoadTest_CharIndex | Int | 0xca8 | 0x145022148 |
| DebugContacts | Map | 0xc58 | 0x145022180 |
| OnMikoHairTestUpdate | MulticastDelegate | 0xc48 | 0x145022270 |
| MasterSoundClassMap | Map | 0xbf8 | 0x145022238 |
| ChangeCharacterAnywhere | Bool | 0xbf0 | 0x145022370 |
| PartyPanelDisabledToken | Name | 0xbe8 | 0x1450223b8 |
| bPartyPanelDisabled | Bool | 0xbe0 | 0x1450223f0 |
| PartyPanelHiddenToken | Name | 0xbd8 | 0x145022438 |
| bPartyPanelHidden | Bool | 0xbd0 | 0x145022470 |
| MatchmakingPanelHiddenToken | Name | 0xbc8 | 0x1450224b8 |
| bMatchmakingPanelHidden | Bool | 0xbc0 | 0x1450224f0 |
| ModScreenClass | Class | 0xbb8 | 0x145022570 |
| InGameMenuScreenClass | Class | 0xbb0 | 0x1450225f0 |
| StatsScreenClass | Class | 0xba8 | 0x145022670 |
| CharacterSelectScreenClass | Class | 0xba0 | 0x1450226f0 |
| SpectatorManagerClass | Class | 0xb98 | 0x145022770 |
| ActionTargetReticleActor | Object | 0xb90 | 0x1450227f0 |
| ActionTargetReticleActorClass | Class | 0xb88 | 0x145022830 |
| LockOnReticleActor | Object | 0xb80 | 0x1450228b0 |
| LockOnReticleActorClass | Class | 0xb78 | 0x1450228f0 |
| CameraFastTiltBlendAlpha | Float | 0xb70 | 0x145022538 |
| CameraFastTiltBlendOutTime | Float | 0xb6c | 0x1450225b8 |
| CameraFastTiltBlendInTime | Float | 0xb68 | 0x145022638 |
| CameraFastTiltSpeed | Float | 0xb64 | 0x1450226b8 |
| CameraFastTiltInputThreshold | Float | 0xb60 | 0x145022738 |
| CameraTiltSpeed | Float | 0xb5c | 0x1450227b8 |
| CameraDeltaCap | Float | 0xb58 | 0x145022878 |
| CameraFastTurnBlendAlpha | Float | 0xb54 | 0x145022938 |
| CameraFastTurnBlendOutTime | Float | 0xb50 | 0x145022970 |
| CameraFastTurnBlendInTime | Float | 0xb4c | 0x1450229a8 |
| CameraFastTurnSpeed | Float | 0xb48 | 0x1450229e0 |
| CameraFastTurnInputThreshold | Float | 0xb44 | 0x145022a18 |
| CameraTurnSpeed | Float | 0xb40 | 0x145022a50 |
| ProfanityFilterComponent | Object | 0xb38 | 0x145022ac0 |
| FrontEndInputComponent | Object | 0xb30 | 0x145022b00 |
| FrontEndInputPriority | Int | 0xb28 | 0x145022a88 |
| DebugInputComponent | Object | 0xb20 | 0x145022b40 |
| DebugInputPriority | Int | 0xb18 | 0x145022b80 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ApplyContact | 8 | 0x145019f90 |
| CallCloseInGameMenuScreen | 1 | 0x14501a050 |
| CallOpenInGameMenuScreen | 0 | 0x14501a090 |
| CentreCamera | 1 | 0x14501a150 |
| ChangePlayerAttribute | 16 | 0x14501a210 |
| ChangePlayerClass | 112 | 0x14501a310 |
| ChangePlayerTeam | 4 | 0x14501a350 |
| CheckPhysScenes | 8 | 0x14501a390 |
| ClientMessageIsMuted | 4 | 0x14501aaa0 |
| ClientReceiveChat | 32 | 0x14501abd0 |
| ClientReceiveChatWheelSelection | 40 | 0x14501ad80 |
| ClientReceiveLikeForHighlight | 8 | 0x14501ae70 |
| Client_CreateVoiceChatNetwork | 16 | 0x14501a3d0 |
| Client_Debug_AFKEnable | 1 | 0x14501a490 |
| Client_Debug_ConnectionEnable | 1 | 0x14501a550 |
| Client_ExecuteMultipleHeroExploit | 4 | 0x14501a590 |
| Client_KioskMode_StartEndGame | 0 | 0x14501a5d0 |
| Client_LeaveConfirmed | 0 | 0x14501a610 |
| Client_ReceiveXPUpdate | 128 | 0x14501a690 |
| Client_ReportCheckPhysScenes | 16 | 0x14501a6d0 |
| Client_ReportPhysXTestSweepResults | 16 | 0x14501a780 |
| Client_ReportSent | 1 | 0x14501a840 |
| Client_SetNetworkSimulationSettings | 44 | 0x14501a9b0 |
| Client_UpdateAchievement | 24 | 0x14501aa60 |
| ContactWith | 8 | 0x14501aeb0 |
| ContinueProfileLoadTest | 0 | 0x14501aef0 |
| DebugDraw_MBPersistent | 0 | 0x14501bc40 |
| DebugFlag | 8 | 0x14501bc80 |
| DebugMessage | 16 | 0x14501bd30 |
| DebugOpenModScreen | 0 | 0x14501bd70 |
| Debug_AddCustomisation | 8 | 0x14501afa0 |
| Debug_AddSkin | 8 | 0x14501afe0 |
| Debug_AddTaunt | 8 | 0x14501b090 |
| Debug_Ban_ApplyPermanentBanOutright | 0 | 0x14501b0d0 |
| Debug_Ban_ApplyPermanentBanRepeat | 0 | 0x14501b110 |
| Debug_Ban_ApplyTemporaryBan | 16 | 0x14501b150 |
| Debug_Ban_ApplyWarning | 0 | 0x14501b190 |
| Debug_Ban_ClearBanStatus | 0 | 0x14501b1d0 |
| Debug_ChangePlayerClassFromName | 16 | 0x14501b2f0 |
| Debug_EndGame | 0 | 0x14501b330 |
| Debug_GiveCredits | 4 | 0x14501b370 |
| Debug_GiveModParts | 4 | 0x14501b420 |
| Debug_MarkCustomisationGiftsAsOwned | 0 | 0x14501b460 |
| Debug_MarkCustomisationGiftsAsUnowned | 0 | 0x14501b4a0 |
| Debug_MarkTutorialIncomplete | 0 | 0x14501b4e0 |
| Debug_MoveForward | 4 | 0x14501b520 |
| Debug_MoveRight | 4 | 0x14501b5d0 |
| Debug_PIEOnlineRequestsFailureRate | 4 | 0x14501b610 |
| Debug_ResetAchievements | 0 | 0x14501b650 |
| Debug_ResetToDefaultMods | 8 | 0x14501b700 |
| Debug_SendInputEvent | 16 | 0x14501b7c0 |
| Debug_Server_StartOvertime | 0 | 0x14501b800 |
| Debug_SetCustomisation | 16 | 0x14501b8b0 |
| Debug_SetSkin | 8 | 0x14501b8f0 |
| Debug_SetTaunt | 8 | 0x14501b9a0 |
| Debug_SetTeams | 0 | 0x14501b9e0 |
| Debug_StartGame | 0 | 0x14501ba20 |
| Debug_StartOvertime | 0 | 0x14501ba60 |
| Debug_TestProfanityFilter | 16 | 0x14501baa0 |
| Debug_UnlockAchievement | 16 | 0x14501bb50 |
| Debug_UpdateAchievement | 24 | 0x14501bc00 |
| DisableCameraAutoReset | 0 | 0x14501bdb0 |
| DisableFrontEndInput | 0 | 0x14501bdf0 |
| DisablePassives | 0 | 0x14501be30 |
| DisableStatsSnapshot | 0 | 0x14501be70 |
| DoPhysXTestSweep | 0 | 0x14501beb0 |
| DownloadAnalyticsForMatch | 32 | 0x14501bf60 |
| EnableFrontEndInput | 0 | 0x14501bfa0 |
| EnableStatsSnapshot | 0 | 0x14501bfe0 |
| ExitToFrontend | 16 | 0x14501c020 |
| GetChatHistory | 16 | 0x14501c110 |
| GetEnabledCheats | 16 | 0x14501c1c0 |
| GetFirstActionMapping | 64 | 0x14501c340 |
| GetFirstAxisMapping | 64 | 0x14501c4c0 |
| GetKioskPlayerReadyStatus | 1 | 0x14501c580 |
| GetLastSelectedModBuildIndex | 16 | 0x14501c5c0 |
| GetPlayerClass | 40 | 0x14501c740 |
| GetSpectatorManager | 8 | 0x14501c7c0 |
| GodMode | 0 | 0x14501c800 |
| HideOldChatMessages | 0 | 0x14501c840 |
| IgnoreCooldowns | 0 | 0x14501c880 |
| IgnoreMana | 0 | 0x14501c8c0 |
| InputEventNotify | 8 | 0x14501c900 |
| IsChannelMuted | 2 | 0x14501ca40 |
| IsDebugCamActive | 1 | 0x14501cb00 |
| IsDev | 1 | 0x14501cbc0 |
| IsFrontEndInputActive | 1 | 0x14501cc80 |
| IsFrontendInputEnabled | 1 | 0x14501cd40 |
| IsInParty | 1 | 0x14501ce00 |
| IsPlayerChatMuted | 24 | 0x14501cec0 |
| LeaveToSplash | 16 | 0x14501cf00 |
| LockInCharacter | 104 | 0x14501cf80 |
| LockInCharacterOnServer | 104 | 0x14501d000 |
| MBCrashGame | 0 | 0x14501d040 |
| MBDebugDraw | 8 | 0x14501d080 |
| MBDebugDraw_Clear | 0 | 0x14501d0c0 |
| MBDebugDraw_Persistent | 0 | 0x14501d100 |
| MBDebugDraw_Target | 8 | 0x14501d140 |
| MBFailAssert | 0 | 0x14501d180 |
| MBFailEnsure | 0 | 0x14501d1c0 |
| MBToggleDbgRollback | 0 | 0x14501d200 |
| MuteGlobalAudio | 8 | 0x14501d240 |
| NoCameraResetOnNextPosses | 0 | 0x14501d280 |
| NotifyCharacterLockInReceived | 112 | 0x14501d380 |
| NotifyCharacterSelectReceived | 16 | 0x14501d440 |
| NotifyKioskPlayerReadyStatusReceived | 1 | 0x14501d500 |
| NotifyViewingCharacterReceived | 8 | 0x14501d540 |
| OnControllerDisconnected | 0 | 0x14501d580 |
| OnGameEnded | 0 | 0x14501d600 |
| OnGameResumed | 0 | 0x14501d640 |
| OnOnlineLogout | 24 | 0x14501d700 |
| OnOnlineSubsystemLogoutMessageComplete | 1 | 0x14501d7c0 |
| OnProxyActorAdded | 16 | 0x14501d880 |
| OnProxyActorDestroyedUnexpectedly | 8 | 0x14501d900 |
| OnProxyActorRemoved | 16 | 0x14501d9c0 |
| OnViewportReceivedFocus | 0 | 0x14501da00 |
| OneHitKill | 0 | 0x14501d5c0 |
| PlayerHasMicrophone | 24 | 0x14501dac0 |
| PlayerHasSpeakers | 24 | 0x14501db80 |
| PrintPowercellDebug | 0 | 0x14501dbc0 |
| ProfileLoadNextCharacter | 0 | 0x14501dc00 |
| ProfileLoadPlayerClass | 8 | 0x14501dc40 |
| ProfileUnloadPlayerClasses | 0 | 0x14501dc80 |
| RegisterFrontendInputChangedDelegate | 16 | 0x14501dd00 |
| ReleaseAllButtons | 0 | 0x14501dd40 |
| RequestAssetLoadOnClient | 104 | 0x14501ddc0 |
| RequestGameState | 0 | 0x14501de00 |
| RequestKioskRestart | 0 | 0x14501de40 |
| ResetCameraStackOnPosses | 1 | 0x14501df00 |
| SelectCharacter | 24 | 0x14501df80 |
| SelectCharacterOnServer | 8 | 0x14501dfc0 |
| SendChat | 48 | 0x14501e0f0 |
| ServerBroadcastChat | 32 | 0x14501eb90 |
| ServerBroadcastChatWheelSelection | 32 | 0x14501ed40 |
| ServerRequestKioskRestart | 0 | 0x14501ed80 |
| ServerSetKioskPlayerReadyStatus | 1 | 0x14501ee40 |
| ServerSetPlayerMuted | 8 | 0x14501ef00 |
| ServerSubmitLikeForHighlight | 8 | 0x14501ef80 |
| ServerUpdateTargetingSettings | 20 | 0x14501f0c0 |
| Server_CheckPhysScenes | 8 | 0x14501e1a0 |
| Server_Debug_AFKEnable | 1 | 0x14501e260 |
| Server_Debug_ConnectionEnable | 1 | 0x14501e320 |
| Server_Debug_SkipPreMatchCountdown | 0 | 0x14501e360 |
| Server_DoPhysXTestSweep | 0 | 0x14501e3a0 |
| Server_ExecuteMultipleHeroExploit | 0 | 0x14501e3e0 |
| Server_KioskMode_StartEndGame | 0 | 0x14501e420 |
| Server_LeaveWithReason | 16 | 0x14501e460 |
| Server_ReportLoadingTime | 40 | 0x14501e510 |
| Server_ReportPlayer | 104 | 0x14501e6f0 |
| Server_SeekInServerSideReplay | 4 | 0x14501e730 |
| Server_SetHasMicrophone | 1 | 0x14501e7f0 |
| Server_SetHasSpeakers | 1 | 0x14501e8b0 |
| Server_SetNetworkPreset | 8 | 0x14501e8f0 |
| Server_VoiceChatNetworkCreated | 40 | 0x14501ea20 |
| Server_VoiceChatNetworkInfoChanged | 32 | 0x14501ea60 |
| SetCanDebugCamTeleport | 1 | 0x14501f180 |
| SetCanUseDebugCam | 1 | 0x14501f240 |
| SetChannelMuted | 2 | 0x14501f380 |
| SetEnabledCheats | 16 | 0x14501f3c0 |
| SetFocusToViewport | 0 | 0x14501f400 |
| SetHashCheckingEnabled | 1 | 0x14501f4c0 |
| SetHeroBuild | 4 | 0x14501f500 |
| SetIsFrontEndInputActiveOnServer | 1 | 0x14501f5c0 |
| SetIsProvidingAnyFrontEndInputOnServer | 1 | 0x14501f680 |
| SetKioskPlayerReadyStatus | 1 | 0x14501f740 |
| SetLastSelectedModBuildIndex | 16 | 0x14501f780 |
| SetNetSimulationPreset | 8 | 0x14501f7c0 |
| SetPlayerMuted | 24 | 0x14501f880 |
| SetPlayerName | 16 | 0x14501f8c0 |
| SetSelectingCharacter | 1 | 0x14501f980 |
| SetSelectingCharacterOnServer | 1 | 0x14501fa40 |
| SetUIInputEnabled | 1 | 0x14501fb00 |
| SetUseSweepCaching | 1 | 0x14501fbc0 |
| SkipPreMatchCountdown | 0 | 0x14501fc00 |
| StartProfileLoadTest | 0 | 0x14501fc40 |
| SubmitChangePlayerClassInputEvent | 104 | 0x14501fcc0 |
| SubmitChangePlayerClassInputEventOnServer | 104 | 0x14501fd40 |
| SubmitLikeForHighlight | 8 | 0x14501fdc0 |
| TestDynamicDebug | 36 | 0x14501fee0 |
| TestNavMeshDebug | 44 | 0x1450201d0 |
| ToggleDebugCam | 0 | 0x145020210 |
| ToggleDebugInputDisplay | 0 | 0x145020250 |
| ToggleDebugLookControls | 0 | 0x145020290 |
| ToggleTraceTickedWidgetCount | 0 | 0x1450202d0 |
| TraceTickedWidgetsThisFrame | 0 | 0x145020310 |
| UI_GetCharacterClass | 24 | 0x1450203d0 |
| UI_GetCharacterLockInState | 24 | 0x145020510 |
| UI_GetCharacterSelectionClass | 24 | 0x145020640 |
| UI_GetCustomUserData | 32 | 0x145020840 |
| UI_GetCustomisation | 32 | 0x145020740 |
| UI_GetMods | 32 | 0x1450209b0 |
| UI_GetSkins | 32 | 0x145020ab0 |
| UI_GetSuperAbilityIndex | 24 | 0x145020be0 |
| UI_GetTaunts | 32 | 0x145020ce0 |
| UnmuteGlobalAudio | 8 | 0x145020d90 |
| UnregisterFrontendInputChangedDelegate | 16 | 0x145020e10 |
| ViewingCharacter | 8 | 0x145020e50 |
| ViewingCharacterOnServer | 8 | 0x145020f00 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ApplyContact | 0x1413a5770 | 0x143a97fb0 |
| CallCloseInGameMenuScreen | 0x1413a57f0 | 0x143a97fc0 |
| CallOpenInGameMenuScreen | 0x1413a5880 | 0x143a97fd0 |
| CentreCamera | 0x1413a58a0 | 0x143a97fe0 |
| ChangePlayerAttribute | 0x1413a5930 | 0x143a97ff0 |
| ChangePlayerClass | 0x1413a5a40 | 0x143a98000 |
| ChangePlayerTeam | 0x1413a5b90 | 0x143a98010 |
| CheckPhysScenes | 0x1413a5c10 | 0x143a98020 |
| Client_CreateVoiceChatNetwork | 0x1413a6130 | 0x143a98030 |
| Client_Debug_AFKEnable | 0x1413a61e0 | 0x143a98040 |
| Client_Debug_ConnectionEnable | 0x1413a6270 | 0x143a98050 |
| Client_ExecuteMultipleHeroExploit | 0x1413a6300 | 0x143a98060 |
| Client_KioskMode_StartEndGame | 0x1413a6390 | 0x143a98070 |
| Client_LeaveConfirmed | 0x1413a63b0 | 0x143a98080 |
| Client_ReceiveXPUpdate | 0x1413a6400 | 0x143a98090 |
| Client_ReportCheckPhysScenes | 0x1413a6510 | 0x143a980a0 |
| Client_ReportPhysXTestSweepResults | 0x1413a65e0 | 0x143a980b0 |
| Client_ReportSent | 0x1413a66b0 | 0x143a980c0 |
| Client_SetNetworkSimulationSettings | 0x1413a6740 | 0x143a980d0 |
| Client_UpdateAchievement | 0x1413a6920 | 0x143a980e0 |
| ClientMessageIsMuted | 0x1413a5cd0 | 0x143a980f0 |
| ClientReceiveChat | 0x1413a5d60 | 0x143a98100 |
| ClientReceiveChatWheelSelection | 0x1413a5eb0 | 0x143a98110 |
| ClientReceiveLikeForHighlight | 0x1413a6060 | 0x143a98120 |
| ContactWith | 0x1413a6a10 | 0x143a98130 |
| ContinueProfileLoadTest | 0x14036dae0 | 0x143a98140 |
| Debug_AddCustomisation | 0x1413a6c50 | 0x143a98150 |
| Debug_AddSkin | 0x1413a6cd0 | 0x143a98160 |
| Debug_AddTaunt | 0x1413a6d50 | 0x143a98170 |
| Debug_Ban_ApplyPermanentBanOutright | 0x14036dae0 | 0x143a98180 |
| Debug_Ban_ApplyPermanentBanRepeat | 0x14036dae0 | 0x143a98190 |
| Debug_Ban_ApplyTemporaryBan | 0x1413a6dd0 | 0x143a981a0 |
| Debug_Ban_ApplyWarning | 0x14036dae0 | 0x143a981b0 |
| Debug_Ban_ClearBanStatus | 0x14036dae0 | 0x143a981c0 |
| Debug_ChangePlayerClassFromName | 0x1413a6ed0 | 0x143a981d0 |
| Debug_EndGame | 0x1413a6fd0 | 0x143a981e0 |
| Debug_GiveCredits | 0x1413a7020 | 0x143a981f0 |
| Debug_GiveModParts | 0x1413a70a0 | 0x143a98200 |
| Debug_MarkCustomisationGiftsAsOwned | 0x1413a7120 | 0x143a98210 |
| Debug_MarkCustomisationGiftsAsUnowned | 0x1413a7120 | 0x143a98220 |
| Debug_MarkTutorialIncomplete | 0x1413a7140 | 0x143a98230 |
| Debug_MoveForward | 0x1413a7160 | 0x143a98240 |
| Debug_MoveRight | 0x1413a71e0 | 0x143a98250 |
| Debug_PIEOnlineRequestsFailureRate | 0x1413a7260 | 0x143a98260 |
| Debug_ResetAchievements | 0x14036dae0 | 0x143a98270 |
| Debug_ResetToDefaultMods | 0x1413a72e0 | 0x143a98280 |
| Debug_SendInputEvent | 0x1413a7360 | 0x143a98290 |
| Debug_Server_StartOvertime | 0x1413a7430 | 0x143a982a0 |
| Debug_SetCustomisation | 0x1413a7480 | 0x143a982b0 |
| Debug_SetSkin | 0x1413a7540 | 0x143a982c0 |
| Debug_SetTaunt | 0x1413a75c0 | 0x143a982d0 |
| Debug_SetTeams | 0x1413a7640 | 0x143a982e0 |
| Debug_StartGame | 0x1413a7690 | 0x143a982f0 |
| Debug_StartOvertime | 0x1413a76e0 | 0x143a98300 |
| Debug_TestProfanityFilter | 0x1413a7730 | 0x143a98310 |
| Debug_UnlockAchievement | 0x1413a77d0 | 0x143a98320 |
| Debug_UpdateAchievement | 0x1413a78d0 | 0x143a98330 |
| DebugDraw_MBPersistent | 0x1413a6a90 | 0x143a98340 |
| DebugFlag | 0x1413a6ab0 | 0x143a98350 |
| DebugMessage | 0x1413a6b30 | 0x143a98360 |
| DebugOpenModScreen | 0x1413a6c30 | 0x143a98370 |
| DisableCameraAutoReset | 0x1413a7a00 | 0x143a98380 |
| DisableFrontEndInput | 0x1413a7a20 | 0x143a98390 |
| DisablePassives | 0x1413a7a40 | 0x143a983a0 |
| DisableStatsSnapshot | 0x1413a7a60 | 0x143a983b0 |
| DoPhysXTestSweep | 0x1413a7a80 | 0x143a983c0 |
| DownloadAnalyticsForMatch | 0x1413a7aa0 | 0x143a983d0 |
| EnableFrontEndInput | 0x1413a7ba0 | 0x143a983e0 |
| EnableStatsSnapshot | 0x1413a7bc0 | 0x143a983f0 |
| ExitToFrontend | 0x1413a7be0 | 0x143a98400 |
| GetChatHistory | 0x1413a7dc0 | 0x143a98410 |
| GetEnabledCheats | 0x1413a81e0 | 0x143a98420 |
| GetFirstActionMapping | 0x1413a8290 | 0x143a98430 |
| GetFirstAxisMapping | 0x1413a8470 | 0x143a98440 |
| GetKioskPlayerReadyStatus | 0x1413a8800 | 0x143a98450 |
| GetLastSelectedModBuildIndex | 0x1413a8830 | 0x143a98460 |
| GetPlayerClass | 0x1413a8a10 | 0x143a98470 |
| GetSpectatorManager | 0x1413a8cb0 | 0x143a98480 |
| GodMode | 0x1413a8e50 | 0x143a98490 |
| HideOldChatMessages | 0x1413a8e70 | 0x143a984a0 |
| IgnoreCooldowns | 0x1413a8e90 | 0x143a984b0 |
| IgnoreMana | 0x1413a8eb0 | 0x143a984c0 |
| IsChannelMuted | 0x1413a8ed0 | 0x143a984d0 |
| IsDebugCamActive | 0x1413a8f60 | 0x143a984e0 |
| IsDev | 0x1413a8f90 | 0x143a984f0 |
| IsFrontEndInputActive | 0x1413a8fc0 | 0x143a98500 |
| IsFrontendInputEnabled | 0x1413a8fc0 | 0x143a98510 |
| IsInParty | 0x1413a8fe0 | 0x143a98520 |
| IsPlayerChatMuted | 0x1413a9010 | 0x143a98530 |
| LeaveToSplash | 0x1413a90c0 | 0x143a98540 |
| LockInCharacter | 0x1413a91e0 | 0x143a98550 |
| LockInCharacterOnServer | 0x1413a92f0 | 0x143a98560 |
| MBCrashGame | 0x14036dae0 | 0x143a98570 |
| MBDebugDraw | 0x1413a9410 | 0x143a98580 |
| MBDebugDraw_Clear | 0x1413a9490 | 0x143a98590 |
| MBDebugDraw_Persistent | 0x1413a6a90 | 0x143a985a0 |
| MBDebugDraw_Target | 0x1413a94b0 | 0x143a985b0 |
| MBFailAssert | 0x14036dae0 | 0x143a985c0 |
| MBFailEnsure | 0x14036dae0 | 0x143a985d0 |
| MBToggleDbgRollback | 0x14036dae0 | 0x143a985e0 |
| MuteGlobalAudio | 0x1413a9530 | 0x143a985f0 |
| NoCameraResetOnNextPosses | 0x1413a95b0 | 0x143a98600 |
| NotifyCharacterLockInReceived | 0x1413a95d0 | 0x143a98610 |
| NotifyCharacterSelectReceived | 0x1413a9710 | 0x143a98620 |
| NotifyKioskPlayerReadyStatusReceived | 0x1413a97e0 | 0x143a98630 |
| NotifyViewingCharacterReceived | 0x1413a9870 | 0x143a98640 |
| OnControllerDisconnected | 0x1413a9900 | 0x143a98650 |
| OneHitKill | 0x1413a9cf0 | 0x143a98660 |
| OnGameResumed | 0x1413a9920 | 0x143a98670 |
| OnOnlineLogout | 0x1413a9940 | 0x143a98680 |
| OnOnlineSubsystemLogoutMessageComplete | 0x1413a9a30 | 0x143a98690 |
| OnProxyActorAdded | 0x1413a9ab0 | 0x143a986a0 |
| OnProxyActorDestroyedUnexpectedly | 0x1413a9b80 | 0x143a986b0 |
| OnProxyActorRemoved | 0x1413a9c00 | 0x143a986c0 |
| OnViewportReceivedFocus | 0x1413a9cd0 | 0x143a986d0 |
| PlayerHasMicrophone | 0x1413a9d10 | 0x143a986e0 |
| PlayerHasSpeakers | 0x1413a9dc0 | 0x143a986f0 |
| PrintPowercellDebug | 0x14036dae0 | 0x143a98700 |
| ProfileLoadNextCharacter | 0x14036dae0 | 0x143a98710 |
| ProfileLoadPlayerClass | 0x141318cc0 | 0x143a98720 |
| ProfileUnloadPlayerClasses | 0x14036dae0 | 0x143a98730 |
| RegisterFrontendInputChangedDelegate | 0x1413a9e70 | 0x143a98740 |
| ReleaseAllButtons | 0x1413a9f20 | 0x143a98750 |
| RequestAssetLoadOnClient | 0x1413a9f40 | 0x143a98760 |
| RequestGameState | 0x1413aa060 | 0x143a98770 |
| RequestKioskRestart | 0x1413aa080 | 0x143a98780 |
| ResetCameraStackOnPosses | 0x1413aa0a0 | 0x143a98790 |
| SelectCharacter | 0x1413aa130 | 0x143a987a0 |
| SelectCharacterOnServer | 0x1413aa250 | 0x143a987b0 |
| SendChat | 0x1413aa310 | 0x143a987c0 |
| Server_CheckPhysScenes | 0x1413aac10 | 0x143a987d0 |
| Server_Debug_AFKEnable | 0x1413aad10 | 0x143a987e0 |
| Server_Debug_ConnectionEnable | 0x1413aadd0 | 0x143a987f0 |
| Server_Debug_SkipPreMatchCountdown | 0x1413aae90 | 0x143a98800 |
| Server_DoPhysXTestSweep | 0x1413aaee0 | 0x143a98810 |
| Server_ExecuteMultipleHeroExploit | 0x1413aaf30 | 0x143a98820 |
| Server_KioskMode_StartEndGame | 0x1413aaf80 | 0x143a98830 |
| Server_LeaveWithReason | 0x1413aafd0 | 0x143a98840 |
| Server_ReportLoadingTime | 0x1413ab0a0 | 0x143a98850 |
| Server_ReportPlayer | 0x1413ab210 | 0x143a98860 |
| Server_SeekInServerSideReplay | 0x1413ab4f0 | 0x143a98870 |
| Server_SetHasMicrophone | 0x1413ab5a0 | 0x143a98880 |
| Server_SetHasSpeakers | 0x1413ab660 | 0x143a98890 |
| Server_SetNetworkPreset | 0x1413ab720 | 0x143a988a0 |
| Server_VoiceChatNetworkCreated | 0x1413ab7e0 | 0x143a988b0 |
| Server_VoiceChatNetworkInfoChanged | 0x1413ab950 | 0x143a988c0 |
| ServerBroadcastChat | 0x1413aa490 | 0x143a988d0 |
| ServerBroadcastChatWheelSelection | 0x1413aa610 | 0x143a988e0 |
| ServerRequestKioskRestart | 0x1413aa7a0 | 0x143a988f0 |
| ServerSetKioskPlayerReadyStatus | 0x1413aa7f0 | 0x143a98900 |
| ServerSetPlayerMuted | 0x1413aa8b0 | 0x143a98910 |
| ServerSubmitLikeForHighlight | 0x1413aa9b0 | 0x143a98920 |
| ServerUpdateTargetingSettings | 0x1413aaab0 | 0x143a98930 |
| SetCanDebugCamTeleport | 0x1413aba80 | 0x143a98940 |
| SetCanUseDebugCam | 0x1413abb10 | 0x143a98950 |
| SetChannelMuted | 0x1413abba0 | 0x143a98960 |
| SetEnabledCheats | 0x1413abc70 | 0x143a98970 |
| SetFocusToViewport | 0x1413abd20 | 0x143a98980 |
| SetHashCheckingEnabled | 0x1413abd40 | 0x143a98990 |
| SetHeroBuild | 0x1413abdd0 | 0x143a989a0 |
| SetIsFrontEndInputActiveOnServer | 0x1413abe50 | 0x143a989b0 |
| SetIsProvidingAnyFrontEndInputOnServer | 0x1413abf10 | 0x143a989c0 |
| SetKioskPlayerReadyStatus | 0x1413abfd0 | 0x143a989d0 |
| SetLastSelectedModBuildIndex | 0x1413ac060 | 0x143a989e0 |
| SetNetSimulationPreset | 0x1413ac120 | 0x143a989f0 |
| SetPlayerMuted | 0x1413ac1a0 | 0x143a98a00 |
| SetPlayerName | 0x1413ac290 | 0x143a98a10 |
| SetSelectingCharacter | 0x1413ac330 | 0x143a98a20 |
| SetSelectingCharacterOnServer | 0x1413ac3c0 | 0x143a98a30 |
| SetUIInputEnabled | 0x1413ac480 | 0x143a98a40 |
| SetUseSweepCaching | 0x1413ac510 | 0x143a98a50 |
| SkipPreMatchCountdown | 0x1413ac5a0 | 0x143a98a60 |
| StartProfileLoadTest | 0x14036dae0 | 0x143a98a70 |
| SubmitChangePlayerClassInputEvent | 0x1413ac5c0 | 0x143a98a80 |
| SubmitChangePlayerClassInputEventOnServer | 0x1413ac6d0 | 0x143a98a90 |
| SubmitLikeForHighlight | 0x1413ac7f0 | 0x143a98aa0 |
| TestDynamicDebug | 0x1413ac8c0 | 0x143a98ab0 |
| TestNavMeshDebug | 0x1413acb70 | 0x143a98ac0 |
| ToggleDebugCam | 0x1413ace90 | 0x143a98ad0 |
| ToggleDebugInputDisplay | 0x1413aceb0 | 0x143a98ae0 |
| ToggleDebugLookControls | 0x1413aced0 | 0x143a98af0 |
| ToggleTraceTickedWidgetCount | 0x1413acef0 | 0x143a98b00 |
| TraceTickedWidgetsThisFrame | 0x1413acef0 | 0x143a98b10 |
| UI_GetCharacterClass | 0x1413acf10 | 0x143a98b20 |
| UI_GetCharacterLockInState | 0x1413acfd0 | 0x143a98b30 |
| UI_GetCharacterSelectionClass | 0x1413ad090 | 0x143a98b40 |
| UI_GetCustomisation | 0x1413ad220 | 0x143a98b50 |
| UI_GetCustomUserData | 0x1413ad150 | 0x143a98b60 |
| UI_GetMods | 0x1413ad340 | 0x143a98b70 |
| UI_GetSkins | 0x1413ad460 | 0x143a98b80 |
| UI_GetSuperAbilityIndex | 0x1413ad580 | 0x143a98b90 |
| UI_GetTaunts | 0x1413ad640 | 0x143a98ba0 |
| UnmuteGlobalAudio | 0x1413ad760 | 0x143a98bb0 |
| UnregisterFrontendInputChangedDelegate | 0x1413ad7e0 | 0x143a98bc0 |
| ViewingCharacter | 0x1413ad890 | 0x143a98bd0 |
| ViewingCharacterOnServer | 0x1413ad910 | 0x143a98be0 |

## MBPlayerControllerBase

Class params `0x143a98e90`; resolver `0x1413a5130`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| InputMethodChangedMulticaster | MulticastDelegate | 0xaf8 | 0x145023bb0 |
| LastFrameInputMethod | Enum | 0xae9 | 0x145023bf0 |
| MostRecentInputMethod | Enum | 0xae8 | 0x145023c70 |
| MinStickInputForControllerChange | Float | 0xae4 | 0x1450234f8 |
| SpectatorStateInputComponent | Object | 0xac8 | 0x145023cf0 |
| ControlledPawn | Object | 0x790 | 0x145023d30 |
| MinPressInputSize | Float | 0x76c | 0x145023778 |
| MaxReleaseInputSize | Float | 0x768 | 0x145023838 |
| CameraDeadZone | Float | 0x764 | 0x145023978 |
| MovementDeadZone | Float | 0x760 | 0x145023a38 |
| OverrideActorDepthStencils | Map | 0x710 | 0x145023d70 |
| HiddenDecals | Array | 0x700 | 0x145023da8 |
| StartingClass | Class | 0x6f8 | 0x145023ea0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddSplitscreen | 0 | 0x145022ef0 |
| GetInputMethod | 1 | 0x145022fb0 |
| GetProxyPawn | 8 | 0x145023030 |
| IsDebugFlagActive | 16 | 0x1450230f0 |
| IsSpectator | 1 | 0x1450231b0 |
| IsUsingGamepad | 1 | 0x145023270 |
| K2_ClientReturnToMainMenu | 24 | 0x1450232b0 |
| K2_PreClientTravel | 0 | 0x1450232f0 |
| OnPartyUpdated | 1 | 0x1450233b0 |
| OnPartyVoiceChatEnabledChanged | 1 | 0x145023470 |
| OnTeamVoiceChatEnabledChanged | 1 | 0x145023530 |
| PostLoadedWorld | 0 | 0x145023570 |
| RegisterInputMethodChangedDelegate | 16 | 0x1450235f0 |
| RemoveSplitscreen | 0 | 0x145023630 |
| ServerCreateCommsEventlet | 16 | 0x145023670 |
| ServerSetPartyMembers | 16 | 0x1450236f0 |
| ServerSetPartyVoiceChatEnabled | 1 | 0x1450237b0 |
| ServerSetTeamVoiceChatEnabled | 1 | 0x145023870 |
| ServerStartSpectating | 0 | 0x1450238b0 |
| ServerStopSpectating | 0 | 0x1450238f0 |
| ServerTravelToNewMap | 24 | 0x1450239b0 |
| SetFrameInputDisabled | 1 | 0x145023a70 |
| StartSpectating | 0 | 0x145023ab0 |
| StopSpectating | 0 | 0x145023af0 |
| UnregisterInputMethodChangedDelegate | 16 | 0x145023b70 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBPlayerState

Class params `0x144517ec0`; resolver `0x142b63de0`; size `0x15e0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bHasGameStarted | Bool | 0x15d0 | 0x1452c6590 |
| GrindRailBoundsHandle | Struct | 0x15b8 | 0x1452c65e0 |
| bSpawnRespawnFX | Bool | 0x15b5 | 0x1452c6620 |
| bInputEnabled | Bool | 0x15b4 | 0x1452c6670 |
| FastHealthChangeProccerId | Struct | 0x15b0 | 0x1452c66c0 |
| EnabledCheats | Array | 0x15a0 | 0x1452c6700 |
| bTeleportedThisFrame | Bool | 0x159e | 0x1452c6770 |
| bIsLivePlayer | Bool | 0x159d | 0x1452c67c0 |
| DeathState | Enum | 0x159c | 0x1452c6810 |
| SpawnFrameNumber | Int | 0x1598 | 0x1452c6890 |
| SourceRecordingActor | Object | 0x1590 | 0x1452c68d0 |
| SourceRecordingStream | Object | 0x1588 | 0x1452c6910 |
| OnDeathMulticaster | MulticastDelegate | 0x1578 | 0x1452c6950 |
| LastCameraChangeFrame | Int | 0x1574 | 0x1452c6990 |
| SmoothCameraYawLastFrame | Float | 0x1570 | 0x1452c69c8 |
| SmoothCameraYaw | Float | 0x156c | 0x1452c6a00 |
| CurrentCameraYawBlendSpeed | Float | 0x1568 | 0x1452c6a38 |
| ActorVisiblityList | Array | 0x1558 | 0x1452c6a70 |
| ClaimedSpawnPoint | Struct | 0x1550 | 0x1452c6af0 |
| CurrentSpawnPoint | Object | 0x1548 | 0x1452c6b30 |
| NextFrameControllingPlayerID | Int | 0x1540 | 0x1452c6b70 |
| ControllingPlayerID | Int | 0x153c | 0x1452c6ba8 |
| LastFrameControllingPlayerID | Int | 0x1538 | 0x1452c6be0 |
| ActiveCastBars | Array | 0x1528 | 0x1452c6c18 |
| Effects_CurrentTurnIndex | Int | 0x1524 | 0x1452c6c90 |
| Effects_SumTurnValues | Float | 0x1520 | 0x1452c6cc8 |
| Effects_PreviousTurnValues | Array | 0x1510 | 0x1452c6d00 |
| Effects_TurnValue | Float | 0x150c | 0x1452c6d70 |
| Effects_MovementSpeed | Float | 0x1508 | 0x1452c6da8 |
| GrindingSFXId | Struct | 0x1500 | 0x1452c6de0 |
| GrindingPFXId | Struct | 0x14f8 | 0x1452c6e20 |
| MovementStateSFXId | Struct | 0x14f0 | 0x1452c6e60 |
| MovementStatePFXId | Struct | 0x14e8 | 0x1452c6ea0 |
| MovementSFXId | Struct | 0x14e0 | 0x1452c6ee0 |
| MovementPFXId | Struct | 0x14d8 | 0x1452c6f20 |
| MovementIsTransitioning | Bool | 0x14d0 | 0x1452c6f60 |
| MovementStateChangeTime | Float | 0x14cc | 0x1452c6fa8 |
| MovementIsMounted | Bool | 0x14c9 | 0x1452c6fe0 |
| MovementCurrentState | Enum | 0x14c8 | 0x1452c7030 |
| PassiveProccerIds | Array | 0x14b8 | 0x1452c70b0 |
| CurrentPassivesIndex | Int | 0x14b0 | 0x1452c7130 |
| CurrentSuperIndex | Int | 0x14ac | 0x1452c7168 |
| CurrentAbilityIndex | Int | 0x14a8 | 0x1452c71a0 |
| CurrentRangeIndex | Int | 0x14a4 | 0x1452c71d8 |
| CurrentStaminaIndex | Int | 0x14a0 | 0x1452c7210 |
| CurrentHealthIndex | Int | 0x149c | 0x1452c7248 |
| StaminaRegenTimer | Struct | 0x1498 | 0x1452c7280 |
| HealthRegenTimer | Struct | 0x1494 | 0x1452c72c0 |
| TargetingSettings_Controller | Struct | 0x148c | 0x1452c7300 |
| TargetingSettings_KeyboardAndMouse | Struct | 0x1484 | 0x1452c7340 |
| LastUpdateFrame | Int | 0x1480 | 0x1452c7380 |
| TotalMoveDelta | Struct | 0x1450 | 0x1452c73c0 |
| OwnMoveDelta | Struct | 0x1420 | 0x1452c7400 |
| NextPlayerClassName | Name | 0x1410 | 0x1452c7440 |
| SkinDefAssetPath | Struct | 0x13f8 | 0x1452c7480 |
| CustomisationUserData | Struct | 0x13e8 | 0x1452c74c0 |
| CustomisationDefs | Array | 0x13d8 | 0x1452c7500 |
| TauntDefs | Array | 0x13c8 | 0x1452c7580 |
| CameraManagerState | Struct | 0x1330 | 0x1452c7600 |
| ModManagerState | Struct | 0x1300 | 0x1452c7640 |
| StatisticsState | Struct | 0x1250 | 0x1452c7680 |
| PlayerInputState | Struct | 0x11d8 | 0x1452c76c0 |
| DeathTimer | Float | 0x11d0 | 0x1452c7700 |
| RespawnEventName | Name | 0x11c8 | 0x1452c7738 |
| RespawnTimer | Float | 0x11c0 | 0x1452c7770 |
| NativePlayerId | Struct | 0x11a8 | 0x1452c77b0 |
| PlayerName | Str | 0x1198 | 0x1452c77f0 |
| UnrealPlayerID | Int | 0x1190 | 0x1452c7828 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddCastBar | 120 | 0x1452c21b0 |
| BindGamepadInputCallbacks | 112 | 0x1452c2280 |
| BindInputEvent | 24 | 0x1452c2340 |
| BindInputEventPress | 24 | 0x1452c2400 |
| BindInputEventRelease | 24 | 0x1452c24c0 |
| BindKeyboardInputCallbacks | 112 | 0x1452c2590 |
| CanChangeClass | 1 | 0x1452c2620 |
| CooldownTicks | 104 | 0x1452c26a0 |
| Dismount | 104 | 0x1452c2720 |
| DismountOnContacted | 200 | 0x1452c2860 |
| GetBasicAttackRange | 56 | 0x1452c2930 |
| GetCastBarFraction | 120 | 0x1452c2a20 |
| GetCurrentAbilityData | 1040 | 0x1452c2b30 |
| GetCurrentPassiveData | 152 | 0x1452c2c40 |
| GetCurrentSuperData | 1864 | 0x1452c2d10 |
| GetCurrentSuperIndex | 4 | 0x1452c2d90 |
| GetDyingTimeRemaining | 4 | 0x1452c2e10 |
| GetEffectsSpeedValue | 4 | 0x1452c2e90 |
| GetEffectsTurnValue | 4 | 0x1452c2f10 |
| GetPlaceableSensitivity | 112 | 0x1452c2fd0 |
| GetPlayerAttribute | 256 | 0x1452c30d0 |
| GetPlayerData | 8 | 0x1452c3150 |
| GetRespawnTimeRemaining | 4 | 0x1452c31d0 |
| GetSelectedBuildMods_ForBlueprint | 16 | 0x1452c3290 |
| GetSelectedSuperAbilityIndex | 4 | 0x1452c3310 |
| GetTargetingMode | 112 | 0x1452c3490 |
| GetUnrealPlayerID | 4 | 0x1452c3510 |
| IsAnyCastBarActive | 1 | 0x1452c35a0 |
| IsCastBarActive | 16 | 0x1452c3660 |
| IsDying | 1 | 0x1452c36f0 |
| IsInfiniteStaminaActive | 112 | 0x1452c37c0 |
| IsInfiniteSuperActive | 112 | 0x1452c3890 |
| IsMounted | 1 | 0x1452c3920 |
| IsNoCooldownsActive | 112 | 0x1452c39f0 |
| IsRespawning | 1 | 0x1452c3a80 |
| LockOnToTarget | 104 | 0x1452c3b00 |
| MountDisabled | 128 | 0x1452c3bc0 |
| OnAbilityCooldownChanged | 208 | 0x1452c3c80 |
| OnAmmoCountChanged | 208 | 0x1452c3d40 |
| OnGameEnded | 120 | 0x1452c3e00 |
| OnGameStarted | 104 | 0x1452c3e80 |
| OnHealthChanged_Native | 208 | 0x1452c3f40 |
| OnHealthRegenChanged_Native | 208 | 0x1452c4000 |
| OnPostContacted | 200 | 0x1452c4140 |
| OnRangedCooldownChanged | 208 | 0x1452c4200 |
| OnStaminaChanged_Native | 208 | 0x1452c42c0 |
| OnStaminaRegenChanged_Native | 208 | 0x1452c4380 |
| OnSuperBarChanged_Native | 208 | 0x1452c4440 |
| PUC_CommonPostSpawnInit | 120 | 0x1452c4540 |
| PUC_PlayUntargetedVOLine | 120 | 0x1452c4640 |
| PUC_PostRecallToBase | 120 | 0x1452c4740 |
| PUC_PostTeleportToSpawnPoint | 120 | 0x1452c4840 |
| PUC_ReceiveHasGameStarted | 120 | 0x1452c4940 |
| PUC_RespawnWithFadeOut | 120 | 0x1452c4a40 |
| PUC_SetPassiveAbilities | 120 | 0x1452c4b40 |
| PUC_StartRespawn | 120 | 0x1452c4c40 |
| RecallToBase | 104 | 0x1452c4cc0 |
| RecordHeroEventlet | 24 | 0x1452c4dc0 |
| RecordInteractionEvent | 32 | 0x1452c4f10 |
| RegenHealthTick | 104 | 0x1452c4f90 |
| RegenStaminaTick | 104 | 0x1452c5010 |
| RegisterOnDeathCallback | 120 | 0x1452c50d0 |
| ReleaseLockOn | 104 | 0x1452c5150 |
| RemoveCastBar | 112 | 0x1452c5210 |
| ResetCastBars | 8 | 0x1452c5290 |
| SendVisualLayerMessage | 112 | 0x1452c5350 |
| SetCastBarFraction | 120 | 0x1452c5440 |
| SetInputEnabled | 120 | 0x1452c5550 |
| SetLockOnTargetingMode | 112 | 0x1452c5720 |
| SetLockOnType | 112 | 0x1452c5870 |
| SetMounted | 104 | 0x1452c58f0 |
| SetPlaceableSensitivity | 112 | 0x1452c59f0 |
| SetPlayerAttribute | 272 | 0x1452c5b60 |
| SetPlayerMounted | 112 | 0x1452c5c80 |
| SetTargetingSettings | 120 | 0x1452c5d90 |
| StartCastBar | 1000 | 0x1452c5e90 |
| StartControlByPlayer | 8 | 0x1452c5f10 |
| StartRecall | 104 | 0x1452c5f90 |
| StopControlByPlayer | 0 | 0x1452c5fd0 |
| SuperBarIncrease_DealDamage | 128 | 0x1452c6110 |
| SuperBarIncrease_ReceiveDamage | 200 | 0x1452c6250 |
| SuperBarTick | 104 | 0x1452c62d0 |
| SwitchLockOnTarget | 104 | 0x1452c6350 |
| ToggleLockOn | 104 | 0x1452c63d0 |
| UnRegisterOnDeathCallback | 120 | 0x1452c6490 |
| UpdateReplacementAbilities | 128 | 0x1452c6550 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddCastBar | 0x142b68740 | 0x14451cca0 |
| BindGamepadInputCallbacks | 0x142b68880 | 0x14451ccb0 |
| BindInputEvent | 0x142b68980 | 0x14451ccc0 |
| BindInputEventPress | 0x142b68a70 | 0x14451ccd0 |
| BindInputEventRelease | 0x142b68b60 | 0x14451cce0 |
| BindKeyboardInputCallbacks | 0x142b68c50 | 0x14451ccf0 |
| CanChangeClass | 0x142b68d50 | 0x14451cd00 |
| CooldownTicks | 0x142b68d80 | 0x14451cd10 |
| Dismount | 0x142b68e20 | 0x14451cd20 |
| DismountOnContacted | 0x142b68ec0 | 0x14451cd30 |
| GetBasicAttackRange | 0x142b690a0 | 0x14451cd40 |
| GetCastBarFraction | 0x142b69160 | 0x14451cd50 |
| GetCurrentAbilityData | 0x142b69260 | 0x14451cd60 |
| GetCurrentPassiveData | 0x142b69360 | 0x14451cd70 |
| GetCurrentSuperData | 0x142b69490 | 0x14451cd80 |
| GetCurrentSuperIndex | 0x142b69550 | 0x14451cd90 |
| GetDyingTimeRemaining | 0x142b69580 | 0x14451cda0 |
| GetEffectsSpeedValue | 0x142b695b0 | 0x14451cdb0 |
| GetEffectsTurnValue | 0x142b695e0 | 0x14451cdc0 |
| GetPlaceableSensitivity | 0x142b69610 | 0x14451cdd0 |
| GetPlayerAttribute | 0x142b696c0 | 0x14451cde0 |
| GetPlayerData | 0x1403e1e60 | 0x14451cdf0 |
| GetRespawnTimeRemaining | 0x142b69830 | 0x14451ce00 |
| GetSelectedBuildMods_ForBlueprint | 0x142b69860 | 0x14451ce10 |
| GetSelectedSuperAbilityIndex | 0x142b69910 | 0x14451ce20 |
| GetTargetingMode | 0x142b69a40 | 0x14451ce30 |
| GetUnrealPlayerID | 0x142b69b40 | 0x14451ce40 |
| IsAnyCastBarActive | 0x142b69b60 | 0x14451ce50 |
| IsCastBarActive | 0x142b69b90 | 0x14451ce60 |
| IsDying | 0x142b69c20 | 0x14451ce70 |
| IsInfiniteStaminaActive | 0x142b69c50 | 0x14451ce80 |
| IsInfiniteSuperActive | 0x142b69d00 | 0x14451ce90 |
| IsMounted | 0x142b69db0 | 0x14451cea0 |
| IsNoCooldownsActive | 0x142b69de0 | 0x14451ceb0 |
| IsRespawning | 0x142b69e90 | 0x14451cec0 |
| LockOnToTarget | 0x142b69ec0 | 0x14451ced0 |
| MountDisabled | 0x142b69f60 | 0x14451cee0 |
| OnAbilityCooldownChanged | 0x142b6a070 | 0x14451cef0 |
| OnAmmoCountChanged | 0x142b6a1f0 | 0x14451cf00 |
| OnGameEnded | 0x142b6a370 | 0x14451cf10 |
| OnGameStarted | 0x142b6a470 | 0x14451cf20 |
| OnHealthChanged_Native | 0x142b6a510 | 0x14451cf30 |
| OnHealthRegenChanged_Native | 0x142b6a690 | 0x14451cf40 |
| OnPostContacted | 0x142b6a810 | 0x14451cf50 |
| OnRangedCooldownChanged | 0x142b6a9f0 | 0x14451cf60 |
| OnStaminaChanged_Native | 0x142b6ab70 | 0x14451cf70 |
| OnStaminaRegenChanged_Native | 0x142b6acf0 | 0x14451cf80 |
| OnSuperBarChanged_Native | 0x142b6ae70 | 0x14451cf90 |
| PUC_CommonPostSpawnInit | 0x142b6aff0 | 0x14451cfa0 |
| PUC_PlayUntargetedVOLine | 0x142b6b120 | 0x14451cfb0 |
| PUC_PostRecallToBase | 0x142b6b250 | 0x14451cfc0 |
| PUC_PostTeleportToSpawnPoint | 0x142b6b380 | 0x14451cfd0 |
| PUC_ReceiveHasGameStarted | 0x142b6b4b0 | 0x14451cfe0 |
| PUC_RespawnWithFadeOut | 0x142b6b5e0 | 0x14451cff0 |
| PUC_SetPassiveAbilities | 0x142b6b710 | 0x14451d000 |
| PUC_StartRespawn | 0x142b6b840 | 0x14451d010 |
| RecallToBase | 0x142b6b970 | 0x14451d020 |
| RecordHeroEventlet | 0x142b6ba10 | 0x14451d030 |
| RecordInteractionEvent | 0x142b6bb40 | 0x14451d040 |
| RegenHealthTick | 0x142b6bcc0 | 0x14451d050 |
| RegenStaminaTick | 0x142b6bd60 | 0x14451d060 |
| RegisterOnDeathCallback | 0x142b6be00 | 0x14451d070 |
| ReleaseLockOn | 0x142b6bf20 | 0x14451d080 |
| RemoveCastBar | 0x142b6bfc0 | 0x14451d090 |
| ResetCastBars | 0x142b6c0c0 | 0x14451d0a0 |
| SendVisualLayerMessage | 0x142b6c140 | 0x14451d0b0 |
| SetCastBarFraction | 0x142b6c240 | 0x14451d0c0 |
| SetInputEnabled | 0x142b6c380 | 0x14451d0d0 |
| SetLockOnTargetingMode | 0x142b6c4d0 | 0x14451d0e0 |
| SetLockOnType | 0x142b6c650 | 0x14451d0f0 |
| SetMounted | 0x142b6c790 | 0x14451d100 |
| SetPlaceableSensitivity | 0x142b6c830 | 0x14451d110 |
| SetPlayerAttribute | 0x142b6c970 | 0x14451d120 |
| SetPlayerMounted | 0x142b6cbc0 | 0x14451d130 |
| SetTargetingSettings | 0x142b6cd10 | 0x14451d140 |
| StartCastBar | 0x142b6ce80 | 0x14451d150 |
| StartControlByPlayer | 0x142b6d050 | 0x14451d160 |
| StartRecall | 0x142b6d0d0 | 0x14451d170 |
| StopControlByPlayer | 0x142b6d170 | 0x14451d180 |
| SuperBarIncrease_DealDamage | 0x142b6d190 | 0x14451d190 |
| SuperBarIncrease_ReceiveDamage | 0x142b6d320 | 0x14451d1a0 |
| SuperBarTick | 0x142b6d500 | 0x14451d1b0 |
| SwitchLockOnTarget | 0x142b6d5a0 | 0x14451d1c0 |
| ToggleLockOn | 0x142b6d640 | 0x14451d1d0 |
| UnRegisterOnDeathCallback | 0x142b6d6e0 | 0x14451d1e0 |
| UpdateReplacementAbilities | 0x142b6d800 | 0x14451d1f0 |

## MBPlayerStateBase

Class params `0x143a9c1c0`; resolver `0x1413adeb0`; size `0x5e0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bPartyVoiceChatEnabled | Bool | 0x5da | 0x145026cd0 |
| bTeamVoiceChatEnabled | Bool | 0x5d9 | 0x145026d50 |
| CharacterLockInState | Enum | 0x5d8 | 0x145026dd0 |
| TeamId | Int | 0x5d4 | 0x145026d18 |
| bHasSpeakers | Bool | 0x5d1 | 0x145026e50 |
| bHasMicrophone | Bool | 0x5d0 | 0x145026ed0 |
| bHasBeenAskedToCreateVoiceChatNetwork | Bool | 0x5a9 | 0x145026f50 |
| bHasUnreportedLoadingTime | Bool | 0x5a8 | 0x145026fd0 |
| LoadingData | Struct | 0x580 | 0x145027050 |
| bHasUnreportedData | Bool | 0x57c | 0x145027090 |
| Modifier | Float | 0x578 | 0x145026d98 |
| Volatility | Float | 0x574 | 0x145026e98 |
| Deviation | Float | 0x570 | 0x145026f18 |
| Rating | Float | 0x56c | 0x145026f98 |
| PreferredTeamId | Int | 0x568 | 0x145027018 |
| PartyMembers | Array | 0x558 | 0x1450270d8 |
| bGloballyMuted | Bool | 0x550 | 0x145027150 |
| MuteList | Array | 0x540 | 0x145027198 |
| PlatformId | Struct | 0x518 | 0x145027240 |
| PlatformIdString | Str | 0x508 | 0x145027208 |
| bKioskPlayerReadyStatus | Bool | 0x501 | 0x145027280 |
| bIsWatchingServerSideReplay | Bool | 0x500 | 0x145027300 |
| bIsRollbackEngineReady | Bool | 0x4ff | 0x145027380 |
| bIsServerNow | Bool | 0x4fe | 0x145027400 |
| bHasEverBeenServer | Bool | 0x4fd | 0x145027480 |
| bIsHost | Bool | 0x4fc | 0x145027500 |
| ServerSelectionPriority | Int | 0x4f8 | 0x1450272c8 |
| bHasBackfilled | Bool | 0x4f6 | 0x145027580 |
| IsDev | Bool | 0x4f5 | 0x145027600 |
| bServerSetInitialViewingCharacter | Bool | 0x4f4 | 0x145027680 |
| bIsProvidingAnyFrontEndInput | Bool | 0x4f3 | 0x1450276f0 |
| bIsFrontEndInputActive | Bool | 0x4f2 | 0x145027740 |
| bIsSelectingCharacter | Bool | 0x4f1 | 0x145027790 |
| bHasSelectedCharacter | Bool | 0x4f0 | 0x1450277e0 |
| CustomUserData | Struct | 0x4e0 | 0x145027830 |
| SelectedCustomisations | Array | 0x4d0 | 0x145027348 |
| SelectedSkins | Array | 0x4c0 | 0x1450273c8 |
| SelectedTaunts | Array | 0x4b0 | 0x145027448 |
| SelectedMods | Array | 0x4a0 | 0x1450274c8 |
| SuperAbilityIndex | Int | 0x498 | 0x145027548 |
| PendingPlayerClassName | Name | 0x490 | 0x1450275c8 |
| PlayerClassName | Name | 0x488 | 0x145027648 |
| TitleAccountId | Struct | 0x478 | 0x145027970 |
| MasterAccountId | Struct | 0x468 | 0x1450279b0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetCharacterLockInState | 1 | 0x145026150 |
| GetPlatformId | 16 | 0x145026190 |
| GetPlayerClassName | 8 | 0x1450261d0 |
| GetTeamId | 4 | 0x145026280 |
| GetUniqueIdString | 16 | 0x1450262c0 |
| IsFromPreviousLevel | 1 | 0x145026380 |
| IsInactive | 1 | 0x145026440 |
| OnRep_CharacterLockInState | 0 | 0x145026480 |
| OnRep_GloballyMuted | 0 | 0x1450264c0 |
| OnRep_MicOrSpeakersChanged | 0 | 0x145026500 |
| OnRep_PartyVoiceChatEnabled | 0 | 0x145026540 |
| OnRep_PlatformId | 0 | 0x145026580 |
| OnRep_TeamId | 0 | 0x1450265c0 |
| OnRep_TeamVoiceChatEnabled | 0 | 0x145026600 |
| SetCharacterLockInState | 1 | 0x1450266c0 |
| SetCustomUserData | 16 | 0x1450267c0 |
| SetCustomisations | 16 | 0x145026740 |
| SetIsHost | 1 | 0x145026880 |
| SetMods | 16 | 0x145026900 |
| SetPendingPlayerClassName | 8 | 0x145026940 |
| SetPlayerClassName | 8 | 0x1450269f0 |
| SetPlayerName | 16 | 0x145026a30 |
| SetSkin | 16 | 0x145026b20 |
| SetSuperAbilityIndex | 4 | 0x145026b60 |
| SetTaunts | 16 | 0x145026c50 |
| SetTeamId | 4 | 0x145026c90 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetCharacterLockInState | 0x1413b0dc0 | 0x143a9f570 |
| GetPlatformId | 0x1413b0f20 | 0x143a9f580 |
| GetPlayerClassName | 0x1413b0fb0 | 0x143a9f590 |
| GetTeamId | 0x1413b11b0 | 0x143a9f5a0 |
| GetUniqueIdString | 0x1413b11d0 | 0x143a9f5b0 |
| IsFromPreviousLevel | 0x1413b12f0 | 0x143a9f5c0 |
| IsInactive | 0x1413b1320 | 0x143a9f5d0 |
| OnRep_CharacterLockInState | 0x1413b1f10 | 0x143a9f5e0 |
| OnRep_GloballyMuted | 0x1413b1f30 | 0x143a9f5f0 |
| OnRep_MicOrSpeakersChanged | 0x1413b1f50 | 0x143a9f600 |
| OnRep_PartyVoiceChatEnabled | 0x1413b1f70 | 0x143a9f610 |
| OnRep_PlatformId | 0x1413b1f90 | 0x143a9f620 |
| OnRep_TeamId | 0x1413b1fb0 | 0x143a9f630 |
| OnRep_TeamVoiceChatEnabled | 0x1413b1fd0 | 0x143a9f640 |
| SetCharacterLockInState | 0x1413b28a0 | 0x143a9f650 |
| SetCustomisations | 0x1413b29c0 | 0x143a9f660 |
| SetCustomUserData | 0x1413b2920 | 0x143a9f670 |
| SetIsHost | 0x1413b2d00 | 0x143a9f680 |
| SetMods | 0x1413b2d90 | 0x143a9f690 |
| SetPendingPlayerClassName | 0x1413b2ec0 | 0x143a9f6a0 |
| SetPlayerClassName | 0x1413b2f50 | 0x143a9f6b0 |
| SetPlayerName | 0x1413b2fe0 | 0x143a9f6c0 |
| SetSkin | 0x1413b3090 | 0x143a9f6d0 |
| SetSuperAbilityIndex | 0x1413b3170 | 0x143a9f6e0 |
| SetTaunts | 0x1413b31f0 | 0x143a9f6f0 |
| SetTeamId | 0x1413b3320 | 0x143a9f700 |

## MBQuestTask

Class params `0x143aba910`; resolver `0x1412eed60`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bIsTracking | Bool | 0xc8 | 0x14503a280 |
| PlayerStateBase | Object | 0xc0 | 0x14503a300 |
| PlayerId | Struct | 0x98 | 0x14503a340 |
| GameInstance | Object | 0x90 | 0x14503a380 |
| CurrentData | Struct | 0x8c | 0x14503a3c0 |
| bCompleteShown | Bool | 0x89 | 0x14503a400 |
| bIsCompleted | Bool | 0x88 | 0x14503a480 |
| ObserverId | Name | 0x80 | 0x14503a1c8 |
| TargetData | Struct | 0x78 | 0x14503a500 |
| Tags | Array | 0x68 | 0x14503a248 |
| Hint | Text | 0x50 | 0x14503a448 |
| Name | Text | 0x38 | 0x14503a4c8 |
| TaskId | Name | 0x30 | 0x14503a540 |
| UpdateMethod | Enum | 0x28 | 0x14503a5a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBQuestionManager

Class params `0x143ab1f60`; resolver `0x1413c1150`; size `0x88`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ResponseDelegate | MulticastDelegate | 0x70 | 0x145037670 |
| QuestionBuckets | Array | 0x60 | 0x145037538 |
| GameInstance | Object | 0x58 | 0x1450376f0 |
| DebugQuestionListJson | Text | 0x40 | 0x1450375b8 |
| TypesBlueprintObjectRef | Struct | 0x28 | 0x145037730 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AreSurveyQuestionsEnabled | 16 | 0x145037630 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AreSurveyQuestionsEnabled | 0x1413c4e70 | 0x143ab5a78 |

## MBQuestsManager

Class params `0x143ab3110`; resolver `0x1413c0be0`; size `0x100`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bLocalPlayerLoginRegistered | Bool | 0xfe | 0x145038f70 |
| bIsDedicatedServer | Bool | 0xfd | 0x145038ff0 |
| bMatchCompleted | Bool | 0xfc | 0x145039070 |
| PendingServerQuestTaskUpdateRequests | Int | 0xf8 | 0x145038bb8 |
| CachedQuestsPlayerIds | Array | 0xe8 | 0x145038c38 |
| bHasRequestedLocalPlayerInitialQuests | Bool | 0xe0 | 0x145039120 |
| QuestTaskUpdateTimerHandle | Struct | 0xd8 | 0x145039190 |
| PendingQuestTaskUpdates | Array | 0xc8 | 0x145038cb8 |
| LocalPlayerId | Struct | 0xa0 | 0x145039210 |
| GameInstance | Object | 0x98 | 0x145039250 |
| CurrencyRewardsData | Array | 0x88 | 0x145038d38 |
| TaskTags | Array | 0x78 | 0x145038db8 |
| QuestList | Array | 0x68 | 0x145039038 |
| OnQuestsUpdatedMulticaster | MulticastDelegate | 0x48 | 0x145039310 |
| TypesBlueprintObjectRef | Struct | 0x30 | 0x145039350 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnLocalPlayerLogin | 1 | 0x145038df0 |
| OnLocalPlayerLogout | 0 | 0x145038e30 |
| OnPlayerQuestsCached | 40 | 0x145038eb0 |
| ReceiveOutputEvent | 16 | 0x145038f30 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnLocalPlayerLogin | 0x1413c51e0 | 0x143ab65a0 |
| OnLocalPlayerLogout | 0x1413c5270 | 0x143ab65b0 |
| OnPlayerQuestsCached | 0x1413c53b0 | 0x143ab65c0 |
| ReceiveOutputEvent | 0x1413c55d0 | 0x143ab65d0 |

## MBReplayStreamingManager

Class params `0x143abc020`; resolver `0x1413c95d0`; size `0x1d0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PendingDownloads | Array | 0x1c0 | 0x14503e6c8 |
| TimerHandle_ContinueReplayStreamUpdate | Struct | 0x1b8 | 0x14503ebc0 |
| LastDownloadRequestTime | Float | 0x1b0 | 0x14503e748 |
| NumRequestsFailed | Int | 0x1ac | 0x14503ea88 |
| PendingReplayStreamId | Struct | 0x1a8 | 0x14503ec00 |
| ReplayDownloadRetryDelay | Array | 0x198 | 0x14503ec40 |
| TimerHandle_PrepareMatchTimeout | Struct | 0x190 | 0x14503ecb0 |
| NumPendingPlayerNames | Int | 0x188 | 0x14503ecf0 |
| NumPendingAvatarTextures | Int | 0x184 | 0x14503ed28 |
| bIsCloudMatchPending | Bool | 0x180 | 0x14503ed60 |
| CloudReplayFileInfo | Struct | 0xd8 | 0x14503ede0 |
| CloudReplayMatchData | Struct | 0xa0 | 0x14503ee20 |
| PrepareMatchTimeout | Float | 0x98 | 0x14503eda8 |
| DefaultLiveStreamPlaybackDelay | Float | 0x94 | 0x14503ee60 |
| CloudReplayFileTimeout | Float | 0x90 | 0x14503ee98 |
| ActiveReplayStreams | Array | 0x80 | 0x14503eed0 |
| bReplaysRequireAuthorisation | Bool | 0x78 | 0x14503ef80 |
| ReplayUploaderAccountKey | Str | 0x68 | 0x14503ef08 |
| ReplayUploaderAccountName | Str | 0x58 | 0x14503efc8 |
| bReplayUploaderAccountCached | Bool | 0x51 | 0x14503f000 |
| bReplayUploaderRequestPending | Bool | 0x50 | 0x14503f080 |
| ReplayAccountTag | Name | 0x48 | 0x14503f048 |
| ReplayStreamIdGenerator | Struct | 0x40 | 0x14503f0f0 |
| AzureFileCache | Object | 0x38 | 0x14503f130 |
| GameInstance | Object | 0x30 | 0x14503f170 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| OnAvatarLoaded | 56 | 0x14503e800 |
| OnAzureStorageDataCached_DownloadContainer | 40 | 0x14503e880 |
| OnAzureStorageDataCached_DownloadFile | 40 | 0x14503e900 |
| OnAzureStorageDataCached_DumpCloudFileInfo | 40 | 0x14503e980 |
| OnAzureStorageDataCached_WatchMatch | 40 | 0x14503ea00 |
| OnPlayerUserInfoCached | 88 | 0x14503eb40 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| OnAvatarLoaded | 0x1413ccb50 | 0x143ac06b0 |
| OnAzureStorageDataCached_DownloadContainer | 0x1413cccd0 | 0x143ac06c0 |
| OnAzureStorageDataCached_DownloadFile | 0x1413cccd0 | 0x143ac06d0 |
| OnAzureStorageDataCached_DumpCloudFileInfo | 0x1413cccd0 | 0x143ac06e0 |
| OnAzureStorageDataCached_WatchMatch | 0x1413cccd0 | 0x143ac06f0 |
| OnPlayerUserInfoCached | 0x1413cce40 | 0x143ac0700 |

## MBRollbackGameMode

Class params `0x143abd600`; resolver `0x141362f90`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| MatchStartTimeStamp | Struct | 0x510 | 0x14503ff20 |
| ReplayStreamMatchStartFrameNumber | Int | 0x508 | 0x14503fce8 |
| MatchEndReason | Str | 0x4f8 | 0x14503ff60 |
| NextMapURL | Str | 0x4e8 | 0x14503ff98 |
| PendingRespawnPlayerIds | Array | 0x4d8 | 0x14503ffd0 |
| NextPlayerNameChangeRequestID | Int | 0x4d4 | 0x145040040 |
| MatchEndedTimeStamp | Float | 0x4d0 | 0x145040078 |
| WaitingForServerWorkInProgress | Float | 0x4cc | 0x1450400b0 |
| WaitingForPlayersRemainingTime | Float | 0x4c8 | 0x1450400e8 |
| WaitingToStartTime | Float | 0x4c4 | 0x145040120 |
| ReturnToMenuTime | Float | 0x4c0 | 0x145040158 |
| bWaitingForServerUploads | Bool | 0x4be | 0x145040190 |
| bSentServerMatchEndedEvent | Bool | 0x4bd | 0x145040210 |
| bSentServerMatchStartedEvent | Bool | 0x4bc | 0x145040290 |
| bRequestedNextServer | Bool | 0x4bb | 0x145040310 |
| bCalledPostMatchCountdownComplete | Bool | 0x4ba | 0x145040390 |
| bAllowAbandonedGameToEnd | Bool | 0x4b9 | 0x145040410 |
| bSkipPreMatchCountdownRequested | Bool | 0x4b8 | 0x145040490 |
| SkillManager | Object | 0x4b0 | 0x145040510 |
| SendMatchEndedEventDelay | Int | 0x4ac | 0x1450401d8 |
| RetryRequestNextServerTimeout | Int | 0x4a8 | 0x145040258 |
| RequestNextServerTimeout | Int | 0x4a4 | 0x1450402d8 |
| WaitForServerUploadsTimeout | Int | 0x4a0 | 0x145040358 |
| WaitingToStartTimeOut | Int | 0x49c | 0x1450403d8 |
| PostMatchCountdownDuration | Int | 0x498 | 0x145040458 |
| WarmUpPhaseDuration | Int | 0x494 | 0x1450404d8 |
| PreMatchCountdownDuration | Int | 0x490 | 0x145040550 |
| WaitingForPlayersTimeout | Int | 0x48c | 0x145040588 |
| bManualMatchStart | Bool | 0x488 | 0x1450405c0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| Debug_EndGame | 0 | 0x14503fd20 |
| Debug_SetTeams | 0 | 0x14503fd60 |
| Debug_StartOvertime | 0 | 0x14503fda0 |
| Debug_ToggleForceWaitingForPlayers | 0 | 0x14503fde0 |
| GKStartGame | 0 | 0x14503fe60 |
| GetRollbackMatchState | 8 | 0x14503fe20 |
| RequestSkipPreMatchCountdown | 0 | 0x14503fea0 |
| StartGame | 0 | 0x14503fee0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| Debug_EndGame | 0x1413cc360 | 0x143ac0d00 |
| Debug_SetTeams | 0x1413cc380 | 0x143ac0d10 |
| Debug_StartOvertime | 0x14036dae0 | 0x143ac0d20 |
| Debug_ToggleForceWaitingForPlayers | 0x14036dae0 | 0x143ac0d30 |
| GetRollbackMatchState | 0x1413cc450 | 0x143ac0d40 |
| GKStartGame | 0x1413cc3a0 | 0x143ac0d50 |
| RequestSkipPreMatchCountdown | 0x1413cd0c0 | 0x143ac0d60 |
| StartGame | 0x1413cd110 | 0x143ac0d70 |

## MBRollbackGameState

Class params `0x143abeae0`; resolver `0x141362fa0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| NotEnoughPlayersMessageId | Name | 0x478 | 0x145041448 |
| TicksBetweenFragments | Int | 0x474 | 0x145041588 |
| FragmentsPerSend | Int | 0x470 | 0x145041688 |
| NetworkedReplays | Array | 0x450 | 0x145041888 |
| bForceSystemMessagesQueuingEnabled | Bool | 0x44b | 0x145041940 |
| bHiddenLoadingScreen | Bool | 0x44a | 0x1450419c0 |
| bCalledBeginMatchWarmUp | Bool | 0x449 | 0x145041a40 |
| bPreMatchInitCalled | Bool | 0x448 | 0x145041ac0 |
| PlayerCreatingVoiceChatNetwork | Object | 0x440 | 0x145041b40 |
| VoiceChatNetworkInfo | Struct | 0x420 | 0x145041b80 |
| bCanDoServerMigration | Bool | 0x418 | 0x145041bc0 |
| PostMatchCountdownEndTimeSeconds | Float | 0x414 | 0x145041988 |
| WarmUpStartTimeSeconds | Float | 0x410 | 0x145041a08 |
| PostMatchReplaySyncTimeSeconds | Float | 0x40c | 0x145041a88 |
| RollbackMatchStartTimeSeconds | Float | 0x408 | 0x145041b08 |
| PreviousRollbackMatchState | Name | 0x400 | 0x145041c08 |
| RollbackMatchState | Name | 0x3f8 | 0x145041c40 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetPostMatchCountdownTimeRemaining | 4 | 0x145040cc0 |
| GetPostMatchReplaySyncTime | 4 | 0x145040d00 |
| GetPreMatchCountdownTimeRemaining | 4 | 0x145040db0 |
| GetTimeUntilWarmUp | 4 | 0x145040df0 |
| HasRollbackMatchStarted | 1 | 0x145040eb0 |
| Internal_SendNextServerTravelURL | 32 | 0x145040f60 |
| Internal_SendReplayMetadata | 32 | 0x1450413c0 |
| Internal_SendReplay_Begin | 12 | 0x145041090 |
| Internal_SendReplay_End | 1 | 0x145041150 |
| Internal_SendReplay_Fragment | 24 | 0x145041250 |
| IsCharacterFreeToSelect | 24 | 0x145041500 |
| IsCharacterNameFreeToSelect | 24 | 0x145041600 |
| IsWaitingForPlayers | 1 | 0x1450416c0 |
| OnNotEnoughPlayersMessageComplete | 1 | 0x145041780 |
| OnRep_RollbackMatchState | 0 | 0x1450417c0 |
| OnRep_VoiceChatNetworkInfo | 0 | 0x145041800 |
| SendReplayFragment | 1 | 0x1450418c0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetPostMatchCountdownTimeRemaining | 0x1413cc3c0 | 0x143ac1100 |
| GetPostMatchReplaySyncTime | 0x1413cc3f0 | 0x143ac1110 |
| GetPreMatchCountdownTimeRemaining | 0x1413cc420 | 0x143ac1120 |
| GetTimeUntilWarmUp | 0x1413cc490 | 0x143ac1130 |
| HasRollbackMatchStarted | 0x1413cc4c0 | 0x143ac1140 |
| Internal_SendNextServerTravelURL | 0x1413cc4f0 | 0x143ac1150 |
| Internal_SendReplay_Begin | 0x1413cc720 | 0x143ac1160 |
| Internal_SendReplay_End | 0x1413cc820 | 0x143ac1170 |
| Internal_SendReplay_Fragment | 0x1413cc8a0 | 0x143ac1180 |
| Internal_SendReplayMetadata | 0x1413cc5f0 | 0x143ac1190 |
| IsCharacterFreeToSelect | 0x1413cc990 | 0x143ac11a0 |
| IsCharacterNameFreeToSelect | 0x1413cca50 | 0x143ac11b0 |
| IsWaitingForPlayers | 0x1413ccb20 | 0x143ac11c0 |
| OnNotEnoughPlayersMessageComplete | 0x1413ccdc0 | 0x143ac11d0 |
| OnRep_RollbackMatchState | 0x1413cd000 | 0x143ac11e0 |
| OnRep_VoiceChatNetworkInfo | 0x1413cd020 | 0x143ac11f0 |
| SendReplayFragment | 0x1413cd0e0 | 0x143ac1200 |

## MBRollbackObjectFactory

Class params `0x143ac5100`; resolver `0x1413ce4d0`; size `0x50`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBScriptManagerProxy

Class params `0x143ac1550`; resolver `0x1413ce230`; size `0x7e0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ScriptedPlayerTokens | Array | 0x7d0 | 0x145047378 |
| StickInput | Struct | 0x7c4 | 0x145048170 |
| StickInputThisFrame | Struct | 0x7b8 | 0x1450481b0 |
| InputsThisFrame | Array | 0x7a8 | 0x145047478 |
| PendingLatentInputList | Array | 0x798 | 0x145047638 |
| PendingLatentInput | Struct | 0x778 | 0x145048270 |
| CameraIdMap | Map | 0x728 | 0x145047738 |
| NumCameras | Int | 0x720 | 0x145047a78 |
| FadeCameraData | Struct | 0x708 | 0x1450482f0 |
| CameraBlendTime | Float | 0x700 | 0x145047af8 |
| CameraBlendTimer | Float | 0x6fc | 0x145047c38 |
| CameraTransitioned | Bool | 0x6fb | 0x145048330 |
| CameraTransitioning | Bool | 0x6fa | 0x1450483b0 |
| DialogConfirmed | Bool | 0x6f9 | 0x145048430 |
| InCinematicMode | Bool | 0x6f8 | 0x1450484b0 |
| AIInputsToRelease | Array | 0x6e8 | 0x145047cb8 |
| AIInputsToPress | Array | 0x6d8 | 0x145047db8 |
| CameraResetTimerFrames | Int | 0x6d4 | 0x145047e38 |
| bCameraReseting | Bool | 0x6d0 | 0x1450485b0 |
| AIPlayerProxy | Object | 0x6c8 | 0x145048630 |
| PlayerController | Object | 0x6c0 | 0x145048670 |
| PendingControllersToDestroy | Array | 0x6b0 | 0x145047ff8 |
| SpawnedControllers | Array | 0x6a0 | 0x145048078 |
| ScriptCharacters | Array | 0x690 | 0x145048378 |
| bMatchStarted | Bool | 0x689 | 0x145048770 |
| bDoneInit | Bool | 0x688 | 0x1450487f0 |
| CurrentPreparedPlayerProxy | Object | 0x680 | 0x145048870 |
| CutsceneController | Object | 0x678 | 0x1450488b0 |
| bHideStatusText | Bool | 0x671 | 0x1450488f0 |
| bNonScriptedCombatStart | Bool | 0x670 | 0x145048970 |
| RetreatPoints | Object | 0x668 | 0x1450489f0 |
| PatrolPath | Object | 0x660 | 0x145048a30 |
| BBVar_PatrolPath | Name | 0x658 | 0x1450483f8 |
| BBVar_ChanceToEvade | Name | 0x650 | 0x145048478 |
| BBVar_Special3 | Name | 0x648 | 0x1450484f8 |
| BBVar_Special2 | Name | 0x640 | 0x1450485f8 |
| BBVar_Special1 | Name | 0x638 | 0x1450487b8 |
| BBVar_EnemyTarget | Name | 0x630 | 0x145048838 |
| BBVar_HomeLocation | Name | 0x628 | 0x145048938 |
| BBVar_ReturnHome | Name | 0x620 | 0x1450489b8 |
| BBVar_ConbatRange | Name | 0x618 | 0x145048a70 |
| BBVar_CombatMode | Name | 0x610 | 0x145048aa8 |
| BehaviorToSkillLevel | Map | 0x5c0 | 0x145048ae0 |
| CharacterToBehavior | Map | 0x570 | 0x145048b18 |
| CharacterToAIVariables | Map | 0x520 | 0x145048c88 |
| ScriptPlayerClassLookupTable | Map | 0x4d0 | 0x145048d38 |
| TokenLists | Map | 0x480 | 0x145048de8 |
| ActiveTokens | Array | 0x470 | 0x145048e98 |
| PauseTokens | Array | 0x460 | 0x145048f48 |
| LatentMovementAxisY | Name | 0x458 | 0x145048fb8 |
| LatentMovementAxisX | Name | 0x450 | 0x145048ff0 |
| LastCameraID | Int | 0x448 | 0x145049028 |
| DefaultPromptWidget | Class | 0x440 | 0x145049060 |
| bEnableCutsceneController | Bool | 0x438 | 0x1450490e0 |
| CameraTransitionWaitFrames | Int | 0x434 | 0x1450490a8 |
| CameraResetWaitFrames | Int | 0x430 | 0x145049128 |
| EnemyClassOverrides | Map | 0x3e0 | 0x145049160 |
| DefaultControllerClass | Class | 0x3d8 | 0x145049250 |
| ScriptActorList | Array | 0x3c8 | 0x145049218 |
| CurrentScriptState | Enum | 0x3c0 | 0x145049300 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AIStartCombat | 64 | 0x145043f50 |
| AIStopCombat | 8 | 0x145043fd0 |
| ApplyContactToActor | 24 | 0x1450440d0 |
| ApplyContactToEnemy | 16 | 0x1450441d0 |
| ApplyContactToPlayer | 16 | 0x1450442d0 |
| BlueprintBeginState | 1 | 0x145044390 |
| BlueprintCleanupPlayerForState | 1 | 0x145044450 |
| BlueprintEndState | 1 | 0x145044510 |
| BlueprintInitialise | 0 | 0x145044550 |
| BlueprintPreparePlayerForState | 1 | 0x145044610 |
| BroadcastGlobalEventByTag | 8 | 0x145044650 |
| CallScriptManagerStateEvent | 8 | 0x145044690 |
| ChangeAIHero | 24 | 0x145044790 |
| ChangeHealth | 16 | 0x145044810 |
| ChangePlayerHero | 24 | 0x145044910 |
| ChangePlayerSpawnMode | 1 | 0x1450449d0 |
| ChangePlayerTeam | 4 | 0x145044a10 |
| ChangeSpawnMode | 16 | 0x145044b10 |
| ChangeTeam | 16 | 0x145044c10 |
| CheckAllyHealth | 16 | 0x145044c90 |
| CreatePlayerToken | 16 | 0x145044d40 |
| CreatePlayerTokens | 24 | 0x145044e60 |
| DeletePlayerToken | 24 | 0x145044f20 |
| DeletePlayerTokens | 32 | 0x145045050 |
| DespawnScriptCharacter | 8 | 0x1450450d0 |
| Disable | 0 | 0x145045110 |
| Enable | 0 | 0x145045150 |
| EnterCinematicMode | 1 | 0x145045210 |
| ExitCinematicMode | 0 | 0x145045250 |
| GetAIAttribute | 24 | 0x145045340 |
| GetCheatTagsForMode | 24 | 0x145045470 |
| GetCurrentPlayerProxy | 8 | 0x1450454f0 |
| GetPlayerAttribute | 16 | 0x1450455a0 |
| GetScriptManagerProxy | 16 | 0x145045660 |
| GetStateName | 16 | 0x145045720 |
| HandlePlayerInput | 400 | 0x145045810 |
| OnAwardsUpdate | 24 | 0x145045890 |
| OnFrontendInputChanged | 1 | 0x145045950 |
| OnGlobalManagerMessageCreated | 16 | 0x145045a10 |
| OnOptionsOpenedInPrompt | 0 | 0x145045a50 |
| OnSuppressMessages | 0 | 0x145045a90 |
| OnTutorialAwards | 12 | 0x145045b50 |
| OnUnsuppressMessages | 0 | 0x145045b90 |
| PlayRespawnFX | 16 | 0x145045c10 |
| PopCamera_Default | 56 | 0x145045e00 |
| PopCamera_Latent | 56 | 0x145045ff0 |
| PopFadeInCallback | 1 | 0x1450460b0 |
| PressAIButton | 24 | 0x1450461a0 |
| PushCamera_Latent | 56 | 0x145046350 |
| PushFadeInCallback | 1 | 0x145046410 |
| RegisterDeathEvent | 16 | 0x145046490 |
| RegisterPlayerID | 4 | 0x145046540 |
| ReleaseAIButton | 16 | 0x1450465c0 |
| RemoveAllContactFXFromPlayer | 4 | 0x145046670 |
| ResetPlayer | 28 | 0x145046930 |
| RespawnScriptCharacter | 40 | 0x145046a30 |
| ScriptPromptConfirmed | 0 | 0x145046a70 |
| SetAIAttribute | 24 | 0x145046b70 |
| SetAIBehaviour | 16 | 0x145046c70 |
| SetAITarget | 32 | 0x145046e30 |
| SetInputEnabled | 1 | 0x145046ef0 |
| SetPlayerAttribute | 16 | 0x145046fb0 |
| SetState | 1 | 0x145047070 |
| SetSubtitle | 32 | 0x145047130 |
| ShowScriptPrompt_Latent | 96 | 0x1450474f0 |
| SpawnScriptCharacter | 56 | 0x145047770 |
| SwapPlayerControllerWithAI | 16 | 0x145047870 |
| SwitchLockOnType | 1 | 0x145047930 |
| SwitchPlayerController | 1 | 0x1450479f0 |
| TeleportEnemy | 80 | 0x145047bb0 |
| TeleportPlayer | 64 | 0x145047d30 |
| TeleportProxy | 80 | 0x145047ef0 |
| TurnOnJumpPad | 8 | 0x145047f70 |
| WaitForInput_Latent | 64 | 0x145048130 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AIStartCombat | 0x1413cfd50 | 0x143ac78a0 |
| AIStopCombat | 0x1413cffd0 | 0x143ac78b0 |
| ApplyContactToActor | 0x1413d0050 | 0x143ac78c0 |
| ApplyContactToEnemy | 0x1413d0150 | 0x143ac78d0 |
| ApplyContactToPlayer | 0x1413d0210 | 0x143ac78e0 |
| BroadcastGlobalEventByTag | 0x1413d0530 | 0x143ac78f0 |
| CallScriptManagerStateEvent | 0x1413d05b0 | 0x143ac7900 |
| ChangeAIHero | 0x1413d0630 | 0x143ac7910 |
| ChangeHealth | 0x1413d06f0 | 0x143ac7920 |
| ChangePlayerHero | 0x1413d07c0 | 0x143ac7930 |
| ChangePlayerSpawnMode | 0x1413d0880 | 0x143ac7940 |
| ChangePlayerTeam | 0x1413d0900 | 0x143ac7950 |
| ChangeSpawnMode | 0x1413d0980 | 0x143ac7960 |
| ChangeTeam | 0x1413d0a40 | 0x143ac7970 |
| CheckAllyHealth | 0x1413d0b40 | 0x143ac7980 |
| CreatePlayerToken | 0x1413d0be0 | 0x143ac7990 |
| CreatePlayerTokens | 0x1413d0ca0 | 0x143ac79a0 |
| DeletePlayerToken | 0x1413d0d90 | 0x143ac79b0 |
| DeletePlayerTokens | 0x1413d0ea0 | 0x143ac79c0 |
| DespawnScriptCharacter | 0x1413d0fd0 | 0x143ac79d0 |
| Disable | 0x1413d1050 | 0x143ac79e0 |
| Enable | 0x1413d1070 | 0x143ac79f0 |
| EnterCinematicMode | 0x1413d1090 | 0x143ac7a00 |
| ExitCinematicMode | 0x1413d1120 | 0x143ac7a10 |
| GetAIAttribute | 0x1413d1170 | 0x143ac7a20 |
| GetCheatTagsForMode | 0x1413d1230 | 0x143ac7a30 |
| GetCurrentPlayerProxy | 0x141303a20 | 0x143ac7a40 |
| GetPlayerAttribute | 0x1413d1320 | 0x143ac7a50 |
| GetScriptManagerProxy | 0x1413d13c0 | 0x143ac7a60 |
| GetStateName | 0x1413d1440 | 0x143ac7a70 |
| HandlePlayerInput | 0x1413d14d0 | 0x143ac7a80 |
| OnAwardsUpdate | 0x1413d16e0 | 0x143ac7a90 |
| OnFrontendInputChanged | 0x1413d1790 | 0x143ac7aa0 |
| OnGlobalManagerMessageCreated | 0x1413d1820 | 0x143ac7ab0 |
| PlayRespawnFX | 0x1413d18f0 | 0x143ac7ac0 |
| PopCamera_Default | 0x1413d19b0 | 0x143ac7ad0 |
| PopCamera_Latent | 0x1413d1b90 | 0x143ac7ae0 |
| PopFadeInCallback | 0x1413d1db0 | 0x143ac7af0 |
| PressAIButton | 0x1413d1e40 | 0x143ac7b00 |
| PushCamera_Latent | 0x1413d1f80 | 0x143ac7b10 |
| PushFadeInCallback | 0x1413d21c0 | 0x143ac7b20 |
| RegisterDeathEvent | 0x1413d2250 | 0x143ac7b30 |
| RegisterPlayerID | 0x1413d2310 | 0x143ac7b40 |
| ReleaseAIButton | 0x1413d2390 | 0x143ac7b50 |
| RemoveAllContactFXFromPlayer | 0x1413d2450 | 0x143ac7b60 |
| ResetPlayer | 0x1413d24d0 | 0x143ac7b70 |
| RespawnScriptCharacter | 0x1413d26d0 | 0x143ac7b80 |
| ScriptPromptConfirmed | 0x1413d2800 | 0x143ac7b90 |
| SetAIAttribute | 0x1413d28a0 | 0x143ac7ba0 |
| SetAIBehaviour | 0x1413d29f0 | 0x143ac7bb0 |
| SetAITarget | 0x1413d2ab0 | 0x143ac7bc0 |
| SetInputEnabled | 0x1413d2c00 | 0x143ac7bd0 |
| SetPlayerAttribute | 0x1413d2c90 | 0x143ac7be0 |
| SetState | 0x1413d2da0 | 0x143ac7bf0 |
| SetSubtitle | 0x1413d2e20 | 0x143ac7c00 |
| ShowScriptPrompt_Latent | 0x1413d2f30 | 0x143ac7c10 |
| SpawnScriptCharacter | 0x1413d3300 | 0x143ac7c20 |
| SwapPlayerControllerWithAI | 0x1413d34b0 | 0x143ac7c30 |
| SwitchLockOnType | 0x1413d3580 | 0x143ac7c40 |
| SwitchPlayerController | 0x1413d3600 | 0x143ac7c50 |
| TeleportEnemy | 0x1413d3680 | 0x143ac7c60 |
| TeleportPlayer | 0x1413d3830 | 0x143ac7c70 |
| TeleportProxy | 0x1413d39a0 | 0x143ac7c80 |
| TurnOnJumpPad | 0x1413d3bd0 | 0x143ac7c90 |
| WaitForInput_Latent | 0x1413d3c50 | 0x143ac7ca0 |

## MBSeedManagerActorState

Class params `0x14453c0a0`; resolver `0x142b87770`; size `0x1b8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PointsOnPlayerDeathConditions | Array | 0x1a8 | 0x1452dca50 |
| PowerCellDestroyed | MulticastDelegate | 0x198 | 0x1452dcad0 |
| PowerCellGameplayEvents | Array | 0x188 | 0x1452dcb10 |
| PointsReachedDelegates | Array | 0x178 | 0x1452dcb90 |
| TimerDelegates | Array | 0x168 | 0x1452dcc10 |
| bPauseTimer | Bool | 0x164 | 0x1452dcc90 |
| bForceCentralHandInPointNextTime | Bool | 0x163 | 0x1452dcce0 |
| bKioskModeEndGame | Bool | 0x162 | 0x1452dcd30 |
| bIsOvertime | Bool | 0x161 | 0x1452dcd80 |
| bBackfillingEnabled | Bool | 0x160 | 0x1452dcdd0 |
| PlayerInfos | Map | 0x110 | 0x1452dce18 |
| SeedHandIns | Array | 0x100 | 0x1452dced0 |
| ActiveSeedPlants | Array | 0xf0 | 0x1452dcf50 |
| MapIconsSpawned | Bool | 0xec | 0x1452dcfd0 |
| NumSeedsInPickups | Int | 0xe8 | 0x1452dd018 |
| NumSeedsInGame | Int | 0xe4 | 0x1452dd050 |
| CurrentHandInWaveIndex | Int | 0xe0 | 0x1452dd088 |
| SeedHandInSpawnsPerWaveOverride | Array | 0xd0 | 0x1452dd0c0 |
| PreviousSingleActiveSeedHandInIndex | Int | 0xc8 | 0x1452dd130 |
| ActiveSeedHandInIndices | Array | 0xb8 | 0x1452dd168 |
| ShowMinimapIconsTimer | Float | 0xb0 | 0x1452dd1d8 |
| HeldSeedsCounterTeam1 | Int | 0xac | 0x1452dd210 |
| HeldSeedsCounterTeam0 | Int | 0xa8 | 0x1452dd248 |
| SeedCountTeam1 | Int | 0xa4 | 0x1452dd280 |
| SeedCountTeam0 | Int | 0xa0 | 0x1452dd2b8 |
| StateTimer | Float | 0x9c | 0x1452dd2f0 |
| LastChangeStateReason | Enum | 0x99 | 0x1452dd330 |
| State | Enum | 0x98 | 0x1452dd3b0 |
| SeedsRequiredToWinOverride | Int | 0x94 | 0x1452dd430 |
| LastNearEndState | Enum | 0x90 | 0x1452dd470 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ForceDropSeeds | 232 | 0x1452dc1f0 |
| GetHeldSeedCount | 8 | 0x1452dc2a0 |
| GetLastChangeStateReason | 1 | 0x1452dc360 |
| GetNumSeedsInGame | 4 | 0x1452dc3e0 |
| GetSeedCount | 8 | 0x1452dc490 |
| GetSeedHandIns | 16 | 0x1452dc550 |
| GetSeedsRequiredToWinBP | 16 | 0x1452dc610 |
| GetState | 1 | 0x1452dc6d0 |
| GetStateTimer | 4 | 0x1452dc750 |
| OnActorDiedFromContact | 272 | 0x1452dc810 |
| OnGameEnded | 120 | 0x1452dc8d0 |
| OnGameStarted | 104 | 0x1452dc950 |
| OnPlayerRemoved | 184 | 0x1452dca10 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ForceDropSeeds | 0x142b8c310 | 0x14453fac0 |
| GetHeldSeedCount | 0x142b8c550 | 0x14453fad0 |
| GetLastChangeStateReason | 0x142b8c5e0 | 0x14453fae0 |
| GetNumSeedsInGame | 0x142b8c600 | 0x14453faf0 |
| GetSeedCount | 0x142b8c620 | 0x14453fb00 |
| GetSeedHandIns | 0x142b8c6b0 | 0x14453fb10 |
| GetSeedsRequiredToWinBP | 0x142b8c790 | 0x14453fb20 |
| GetState | 0x142b8c850 | 0x14453fb30 |
| GetStateTimer | 0x142b8c870 | 0x14453fb40 |
| OnActorDiedFromContact | 0x142b8ca70 | 0x14453fb50 |
| OnGameEnded | 0x142b8cc20 | 0x14453fb60 |
| OnGameStarted | 0x142b8cd20 | 0x14453fb70 |
| OnPlayerRemoved | 0x142b8cdc0 | 0x14453fb80 |

## MBSessionOptions

Class params `0x1444c5580`; resolver `0x142b1d020`; size `0x70`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ActiveMapModIds | Array | 0x50 | 0x1452960c8 |
| PlayerMods | Array | 0x40 | 0x145296138 |
| AllowCheats | Bool | 0x3b | 0x1452961b0 |
| InfiniteStamina | Bool | 0x3a | 0x145296200 |
| InfiniteSuper | Bool | 0x39 | 0x145296250 |
| IgnoreCooldowns | Bool | 0x38 | 0x1452962a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBSpawnAreaGateProxy

Class params `0x143ad0680`; resolver `0x1413d8b30`; size `0x4f8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LastRollbackMatchState | Name | 0x4f0 | 0x145050a30 |
| CountdownTexts | Array | 0x4e0 | 0x145050a68 |
| LastTimeSetOnTextComponent | Int | 0x4d8 | 0x145050ae0 |
| RollbackGameState | Object | 0x4d0 | 0x145050b50 |
| CountdownVOStages | Array | 0x4c0 | 0x145050b18 |
| CurrentCountdownStage | Int | 0x4bc | 0x145050bd0 |
| bIsOpen | Bool | 0x4b8 | 0x145050c40 |
| MaxTimeDeltaForJustPassedDelegate | Float | 0x4b4 | 0x145050c08 |
| bFadeStarted | Bool | 0x4b0 | 0x145050cb0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddCountdownStage | 24 | 0x145050870 |
| AddCountdownText | 8 | 0x1450508f0 |
| FadeInForceField | 0 | 0x145050930 |
| OnCountdownChanged | 4 | 0x145050970 |
| OnCountdownReverted | 0 | 0x1450509b0 |
| OnGateStateChanged | 0 | 0x1450509f0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddCountdownStage | 0x1413daec0 | 0x143ad3a18 |
| AddCountdownText | 0x1413dafc0 | 0x143ad3a28 |

## MBSpawnPointState

Class params `0x144549fd0`; resolver `0x142b92e60`; size `0x7c0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| SpawningPlayerStateId | Struct | 0x7b8 | 0x1452e2ac0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## MBSystemMessageManager

Class params `0x143addbf0`; resolver `0x1413e3f40`; size `0x208`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bInRemoveAndQueueCurrentSystemMessage | Bool | 0x1f1 | 0x14505c450 |
| bForceMessageQueueing | Bool | 0x1f0 | 0x14505c4d0 |
| MessageQueueTimerHandle | Struct | 0x1e8 | 0x14505c550 |
| MessageTimeoutHandle | Struct | 0x1e0 | 0x14505c590 |
| MessageQueue | Array | 0x1d0 | 0x14505bed8 |
| CurrentMessageQueueData | Struct | 0x138 | 0x14505c610 |
| CurrentMessageId | Name | 0x130 | 0x14505c498 |
| GameInstance | Object | 0x120 | 0x14505c650 |
| DefaultMessageScreenClass | Class | 0x118 | 0x14505c690 |
| PCMessageInfo | Map | 0xc8 | 0x14505c518 |
| XboxMessageInfo | Map | 0x78 | 0x14505c750 |
| MessageInfo | Map | 0x28 | 0x14505c800 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetSystemMessageManager | 16 | 0x14505c050 |
| HideSystemMessage | 16 | 0x14505c0d0 |
| OnSystemMessageDismissed | 8 | 0x14505c150 |
| OnSystemMessageTimeout | 0 | 0x14505c190 |
| ShowSystemMessage | 32 | 0x14505c250 |
| ShowSystemMessageInfo | 136 | 0x14505c350 |
| ShowSystemMessageText | 56 | 0x14505c410 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetSystemMessageManager | 0x1413e5fa0 | 0x143ae1d70 |
| HideSystemMessage | 0x1413e6060 | 0x143ae1d80 |
| OnSystemMessageDismissed | 0x1413e65c0 | 0x143ae1d90 |
| OnSystemMessageTimeout | 0x1413e6640 | 0x143ae1da0 |
| ShowSystemMessage | 0x1413e6700 | 0x143ae1db0 |
| ShowSystemMessageInfo | 0x1413e6830 | 0x143ae1dc0 |
| ShowSystemMessageText | 0x1413e6a00 | 0x143ae1dd0 |

## MBUpdateManager

Class params `0x143ae9390`; resolver `0x1413ec880`; size `0xd8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| Text_PartiesKey | Str | 0xa8 | 0x145066d88 |
| Text_MatchmakingCancelledKey | Str | 0x98 | 0x145066f08 |
| Text_MatchmakingKey | Str | 0x88 | 0x145066fc8 |
| Text_QuitKey | Str | 0x78 | 0x145067040 |
| Text_NewUpdateAvailableKey | Str | 0x68 | 0x145067078 |
| UpdateMessagesTable | Name | 0x60 | 0x1450670b0 |
| bPlatform_IsUpdateAvailable | Bool | 0x59 | 0x145067110 |
| bTitleDataCache_IsUpdateAvailable | Bool | 0x58 | 0x145067180 |
| GameInstance | Object | 0x50 | 0x145067200 |
| BlueprintOnUpdateAvailable | MulticastDelegate | 0x40 | 0x145067240 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetMessageText_Matchmaking | 24 | 0x145066e00 |
| GetMessageText_MatchmakingCancelled | 24 | 0x145066e40 |
| GetMessageText_Parties | 24 | 0x145066e80 |
| IsUpdateAvailable | 1 | 0x145066f40 |
| OnTitleDataCached | 1 | 0x145067000 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetMessageText_Matchmaking | 0x1413ee640 | 0x143aebe90 |
| GetMessageText_MatchmakingCancelled | 0x1413ee6d0 | 0x143aebea0 |
| GetMessageText_Parties | 0x1413ee760 | 0x143aebeb0 |
| IsUpdateAvailable | 0x1413ee900 | 0x143aebec0 |
| OnTitleDataCached | 0x1413ee9e0 | 0x143aebed0 |

## MBVoiceChatManager

Class params `0x143aec3b0`; resolver `0x1413efca0`; size `0x178`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| TalkerData | Array | 0xf8 | 0x145068e18 |
| bConnectedToPartyNetwork | Bool | 0xf1 | 0x1450694a0 |
| bConnectedToMatchNetwork | Bool | 0xf0 | 0x145069520 |
| bTalkerDataNeedsRefresh | Bool | 0xef | 0x1450695a0 |
| bRefreshHeadsetStatus | Bool | 0xee | 0x145069620 |
| bLocalHasMicrophone | Bool | 0xed | 0x1450696a0 |
| bLocalHasSpeakers | Bool | 0xec | 0x145069720 |
| bInMatch | Bool | 0xeb | 0x1450697a0 |
| bLocalPlayersMuted | Bool | 0xea | 0x145069820 |
| bTeamVoiceChatEnabled | Bool | 0xe9 | 0x1450698a0 |
| bPartyVoiceChatEnabled | Bool | 0xe8 | 0x145069920 |
| PartyManager | Object | 0xe0 | 0x1450699a0 |
| OnlineSessionManager | Object | 0xd8 | 0x1450699e0 |
| OnPartyVoiceChatEnabledChanged | MulticastDelegate | 0x50 | 0x145069a20 |
| OnTeamVoiceChatEnabledChanged | MulticastDelegate | 0x40 | 0x145069a60 |
| OnVoiceChatTalkerDataUpdated | MulticastDelegate | 0x30 | 0x145069aa0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetMicrophoneStatus | 16 | 0x145069120 |
| GetURLOptions | 16 | 0x145069160 |
| OnOnlineLogin | 24 | 0x145069220 |
| OnOnlineLogout | 24 | 0x1450692e0 |
| OnPlayerUserInfoCached | 88 | 0x145069420 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetMicrophoneStatus | 0x1413f4120 | 0x143af1a00 |
| GetURLOptions | 0x1413f41b0 | 0x143af1a10 |
| OnOnlineLogin | 0x1413f4430 | 0x143af1a20 |
| OnOnlineLogout | 0x1413f4520 | 0x143af1a30 |
| OnPlayerUserInfoCached | 0x1413f4610 | 0x143af1a40 |

## MBWatchZoneManager

Class params `0x143aede50`; resolver `0x1413f0490`; size `0x270`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| PlayerInfoToRequestAtOnce | Int | 0x268 | 0x14506ae28 |
| ReplayBlobs | Map | 0x168 | 0x14506b028 |
| MatchRequests | Array | 0x118 | 0x14506b2a0 |
| MatchRequestGenerator | Struct | 0x110 | 0x14506b350 |
| FeaturedOnlineResponses | Array | 0x100 | 0x14506b2d8 |
| PlayerAvatarManager | Object | 0x58 | 0x14506b3d0 |
| GameInstance | Object | 0x50 | 0x14506b410 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AutoRefresh | 0 | 0x14506ae60 |
| AzureDownloadSizeReceived | 4 | 0x14506aea0 |
| AzureTextureCached | 8 | 0x14506af20 |
| OnAzureStorageDataCached | 40 | 0x14506afa0 |
| OnPlayerUserInfoCached | 88 | 0x14506b0e0 |
| SpectateMatch | 80 | 0x14506b1e0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AutoRefresh | 0x1413f4000 | 0x143af20e0 |
| AzureDownloadSizeReceived | 0x1413f4020 | 0x143af20f0 |
| AzureTextureCached | 0x1413f40a0 | 0x143af2100 |
| OnAzureStorageDataCached | 0x1413f4340 | 0x143af2110 |
| OnPlayerUserInfoCached | 0x1413f47d0 | 0x143af2120 |
| SpectateMatch | 0x1413f4d00 | 0x143af2130 |

## MBWorldSingleton

Class params `0x143af5ee0`; resolver `0x1413f5870`; size `0xc98`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bGameEndFrameRetired | Bool | 0xc79 | 0x145071310 |
| bAreProxyActorStatesStale | Bool | 0xc78 | 0x145071390 |
| ChatLog | Array | 0xc58 | 0x145071198 |
| ChatIdGenerator | Struct | 0xc50 | 0x145071450 |
| bIsCharacterSelectScreenOpen | Bool | 0xb90 | 0x145071490 |
| GameStateInterpolationAlpha | Float | 0xb78 | 0x145071358 |
| ProxyActorFactory | Struct | 0xb20 | 0x145071510 |
| GlobalManagerObjectProxies | Array | 0xb10 | 0x1450713d8 |
| PlayerClassRecords | Array | 0xb00 | 0x1450714d8 |
| GameStatus | Enum | 0xaf8 | 0x1450715d0 |
| OnReplayStatusChanged | MulticastDelegate | 0xae8 | 0x145071650 |
| OnLocalPlayerTeamChanged | MulticastDelegate | 0xad8 | 0x145071690 |
| LocalPlayerTeam | Int | 0xad0 | 0x1450716d0 |
| PlayerClassLoadStartTime | Float | 0xa08 | 0x145071708 |
| RequestedClasses | Int | 0xa04 | 0x145071740 |
| PlayerClassesLoaded | Int | 0xa00 | 0x145071778 |
| PreLoadPlayerAssetHandler | Object | 0x9f8 | 0x1450717b0 |
| bWaitForPlayerClassesToLoad | Bool | 0x9f1 | 0x1450717f0 |
| bUpdateGlobalManager | Bool | 0x9f0 | 0x145071870 |
| PublicFrameHistoryMultiplexer | Struct | 0x9b0 | 0x1450718f0 |
| Machines | Array | 0x9a0 | 0x145071838 |
| EventletCompiler | Object | 0x998 | 0x145071970 |
| MachineGroup | Object | 0x990 | 0x1450719b0 |
| bIsInSpectatorMode | Bool | 0x98d | 0x1450719f0 |
| RollbackEnginePublicFrameHistoryExtension | Struct | 0x8e8 | 0x145071a70 |
| PredictedNextFrameState | Object | 0x8e0 | 0x145071ab0 |
| MinimalTickProxies | Array | 0x8d0 | 0x1450718b8 |
| PendingDestroyProxies | Array | 0x8c0 | 0x145071a38 |
| LocalPlayerStates | Array | 0x8b0 | 0x145071b70 |
| LocalPlayerActorIds | Array | 0x8a0 | 0x145071ba8 |
| ActorInitialisers | Array | 0x890 | 0x145071c60 |
| RecordingWriter | Object | 0x888 | 0x145071d10 |
| RecordingReader | Object | 0x880 | 0x145071d50 |
| CachedMiniMapWorldObject | Object | 0x878 | 0x145071d90 |
| CommonLevelObjectProxy | Object | 0x870 | 0x145071dd0 |
| ActiveActorsMap | Map | 0x820 | 0x145071c98 |
| GameplayManager | Object | 0x818 | 0x145071ec0 |
| ConnectionManager | Object | 0x810 | 0x145071f00 |
| HostMigrationManager | Struct | 0x7b8 | 0x145071f40 |
| ServerPlaybackManager | Object | 0x7b0 | 0x145071f80 |
| CrowdManager | Object | 0x7a8 | 0x145071fc0 |
| AudioSpeakerSystem | Object | 0x7a0 | 0x145072000 |
| LocalPlayerProximityVO | Object | 0x798 | 0x145072040 |
| HeroesBanterSystem | Object | 0x790 | 0x145072080 |
| AudioImportanceSystem | Object | 0x788 | 0x1450720c0 |
| EffectsManager | Object | 0x780 | 0x145072100 |
| EffectsProxyActor | Object | 0x778 | 0x145072140 |
| EffectsPlugin_VO | Object | 0x770 | 0x145072180 |
| IncomingContactsPlugin | Object | 0x768 | 0x1450721c0 |
| GlobalManagerMessagePlugin | Object | 0x760 | 0x145072200 |
| ActorMessagePlugin | Object | 0x758 | 0x145072240 |
| ServerProfiler | Object | 0x750 | 0x145072280 |
| VisualEventManager | Object | 0x748 | 0x1450722c0 |
| AIManager | Object | 0x740 | 0x145072300 |
| PlayerInfoTracker | Object | 0x738 | 0x145072340 |
| GlobalTimeDilationManager | Object | 0x730 | 0x145072380 |
| AudioGameFlowManager | Object | 0x728 | 0x1450723c0 |
| GameFlowManager | Object | 0x720 | 0x145072400 |
| HighlightLikingManager | Object | 0x718 | 0x145072440 |
| AFKManager | Object | 0x710 | 0x145072480 |
| StatsManager | Object | 0x708 | 0x1450724c0 |
| DeathTipsManager | Object | 0x700 | 0x145072500 |
| ReplayManager | Object | 0x6f8 | 0x145072540 |
| EngineInterface | Object | 0x6f0 | 0x145072580 |
| RollbackObjectFactory | Object | 0x6e8 | 0x1450725c0 |
| AsyncLoadsRemaining | Int | 0x6e0 | 0x145071e48 |
| PerformanceManager | Object | 0x6d8 | 0x145072600 |
| FrontEnd | Object | 0x6d0 | 0x145072640 |
| GraffitiManager | Object | 0x6c8 | 0x145072680 |
| WidgetManager | Object | 0x6c0 | 0x1450726c0 |
| bCommonInitialised | Bool | 0x6b8 | 0x145072700 |
| LoadedConnectionManagerClass | Class | 0x678 | 0x145072770 |
| DefaultConnectionManagerClassName | Struct | 0x660 | 0x1450727c0 |
| LoadedCrowdManagerClass | Class | 0x658 | 0x145072800 |
| DefaultCrowdManagerClassName | Struct | 0x640 | 0x145072850 |
| LoadedAudioGameFlowManagerClass | Class | 0x638 | 0x145072890 |
| DefaultAudioGameFlowManagerClassName | Struct | 0x620 | 0x1450728e0 |
| LoadedGameFlowManagerClass | Class | 0x618 | 0x145072920 |
| DefaultGameFlowManagerClassName | Struct | 0x600 | 0x145072970 |
| LoadedAFKManagerClass | Class | 0x5f8 | 0x1450729b0 |
| DefaultAFKManagerClassName | Struct | 0x5e0 | 0x145072a00 |
| LoadedDeathTipsManagerClass | Class | 0x5d8 | 0x145072a40 |
| DefaultDeathTipsManagerClassName | Struct | 0x5c0 | 0x145072a90 |
| LoadedReplayManagerClass | Class | 0x5b8 | 0x145072ad0 |
| DefaultReplayManagerClassName | Struct | 0x5a0 | 0x145072b20 |
| LoadedLocalPlayerProximityVOClass | Class | 0x598 | 0x145072b60 |
| DefaultLocalPlayerProximityVOClassName | Struct | 0x580 | 0x145072bb0 |
| LoadedHeroesBanterSystemClass | Class | 0x578 | 0x145072bf0 |
| DefaultHeroesBanterSystemClassName | Struct | 0x560 | 0x145072c40 |
| LoadedAudioImportanceSystemClass | Class | 0x558 | 0x145072c80 |
| DefaultAudioImportanceSystemClassName | Struct | 0x540 | 0x145072cd0 |
| LoadedEffectsManagerClass | Class | 0x538 | 0x145072d10 |
| DefaultEffectsManagerClassName | Struct | 0x520 | 0x145072d60 |
| DebugPlayerControllerClassName | Struct | 0x508 | 0x145072da0 |
| DefaultPIEPlayerDataClassName | Struct | 0x4f0 | 0x145072de0 |
| LoadedEmptyPlayerDataClass | Class | 0x4e8 | 0x145072e20 |
| EmptyPlayerDataClassName | Struct | 0x4d0 | 0x145072e70 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AreAllClientsReadyToUnpause | 1 | 0x145070950 |
| GetCommonLevelObjectProxy | 16 | 0x145070a10 |
| GetCurrentLocalPlayerState | 8 | 0x145070a90 |
| GetDeathTipsManager | 8 | 0x145070b10 |
| GetFrontEnd | 8 | 0x145070b90 |
| GetGameFlowManager | 8 | 0x145070c10 |
| GetMBWorldSingleton | 16 | 0x145070cd0 |
| GetPerformanceManager | 8 | 0x145070d50 |
| GetReplayManager | 8 | 0x145070dd0 |
| GetStatsManager | 8 | 0x145070e50 |
| OnPlayerClassLoadStatusChanged | 8 | 0x145070f10 |
| RegisterOnLocalPlayerChangedTeam | 16 | 0x145070f90 |
| ReplayAddBookmark | 0 | 0x145070fd0 |
| RollbackEngineWillBeInitialisedInThisMap | 1 | 0x145071090 |
| ServerPauseGame | 0 | 0x1450710d0 |
| ServerUnpauseGame | 0 | 0x145071110 |
| SetUseHashChecking | 1 | 0x1450711d0 |
| TogglePersistentDebugDraw | 0 | 0x145071210 |
| UnRegisterOnLocalPlayerChangedTeam | 16 | 0x145071290 |
| UpdateBannedFXTags | 16 | 0x1450712d0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AreAllClientsReadyToUnpause | 0x1413f7a00 | 0x143af93c0 |
| GetCommonLevelObjectProxy | 0x1413f7d40 | 0x143af93d0 |
| GetCurrentLocalPlayerState | 0x1413f7dc0 | 0x143af93e0 |
| GetDeathTipsManager | 0x1413f7df0 | 0x143af93f0 |
| GetFrontEnd | 0x1413f7eb0 | 0x143af9400 |
| GetGameFlowManager | 0x1413f7ee0 | 0x143af9410 |
| GetMBWorldSingleton | 0x1413f7f00 | 0x143af9420 |
| GetPerformanceManager | 0x1413f7f80 | 0x143af9430 |
| GetReplayManager | 0x1413f7fa0 | 0x143af9440 |
| GetStatsManager | 0x1413f80e0 | 0x143af9450 |
| OnPlayerClassLoadStatusChanged | 0x1413f84f0 | 0x143af9460 |
| RegisterOnLocalPlayerChangedTeam | 0x1413f85b0 | 0x143af9470 |
| ReplayAddBookmark | 0x1413f8760 | 0x143af9480 |
| RollbackEngineWillBeInitialisedInThisMap | 0x1413f87f0 | 0x143af9490 |
| ServerPauseGame | 0x1413f8820 | 0x143af94a0 |
| ServerUnpauseGame | 0x1413f8840 | 0x143af94b0 |
| SetUseHashChecking | 0x1413f9690 | 0x143af94c0 |
| TogglePersistentDebugDraw | 0x1413f9720 | 0x143af94d0 |
| UnRegisterOnLocalPlayerChangedTeam | 0x1413f9740 | 0x143af94e0 |
| UpdateBannedFXTags | 0x1413f9800 | 0x143af94f0 |

## NTEngineInterface

Class params `0x1433f63a0`; resolver `0x1403d2600`; size `0x50`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| SessionRandomGeneratorSeed | Int | 0x48 | 0x144e0b040 |
| DefaultSessionOptionsClassName | Struct | 0x30 | 0x144e0b080 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ActorLOSCheck | 176 | 0x144e07d20 |
| CameraShakeDuration | 16 | 0x144e07de0 |
| CreateArc | 72 | 0x144e07f40 |
| CreateBox | 72 | 0x144e08000 |
| CreateCapsule | 64 | 0x144e080f0 |
| CreateCone | 72 | 0x144e08220 |
| CreateCylinder | 64 | 0x144e08310 |
| CreateLine | 56 | 0x144e08390 |
| CreateSphere | 64 | 0x144e08450 |
| DrawDebugAxisAlignedBox | 40 | 0x144e08620 |
| DrawDebugBox | 64 | 0x144e08830 |
| DrawDebugCapsule | 80 | 0x144e08ab0 |
| DrawDebugCollisionShape | 112 | 0x144e08cc0 |
| DrawDebugCylinder | 80 | 0x144e08f40 |
| DrawDebugLine | 44 | 0x144e09150 |
| DrawDebugPoint | 32 | 0x144e09320 |
| DrawDebugSphere | 36 | 0x144e09520 |
| DrawDebugStaticMesh | 80 | 0x144e097f0 |
| DrawDebugString | 40 | 0x144e09930 |
| EvaluateCurve | 16 | 0x144e09a20 |
| FlushDebugStrings | 0 | 0x144e09a60 |
| FlushPersistentDebugLines | 0 | 0x144e09aa0 |
| GetCurrentGameStateContext | 120 | 0x144e09b60 |
| GetCurveTimeRange | 16 | 0x144e09c50 |
| GetLastGameStateContext | 120 | 0x144e09d10 |
| LOSCheck | 176 | 0x144e09f10 |
| OverlapCollision | 280 | 0x144e0a3e0 |
| PrintStringFromGK | 40 | 0x144e0a570 |
| StartCameraShake | 32 | 0x144e0a6b0 |
| StartRangedCameraShake | 160 | 0x144e0a830 |
| StartRangedPadRumble | 168 | 0x144e0a9b0 |
| StopCameraShake | 16 | 0x144e0aa70 |
| SweepCollision | 296 | 0x144e0b000 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ActorLOSCheck | 0x1403d55a0 | 0x1433f9880 |
| CameraShakeDuration | 0x1403d5f70 | 0x1433f9890 |
| CreateArc | 0x1403d6100 | 0x1433f98a0 |
| CreateBox | 0x1403d62b0 | 0x1433f98b0 |
| CreateCapsule | 0x1403d63b0 | 0x1433f98c0 |
| CreateCone | 0x1403d6500 | 0x1433f98d0 |
| CreateCylinder | 0x1403d6670 | 0x1433f98e0 |
| CreateLine | 0x1403d67c0 | 0x1433f98f0 |
| CreateSphere | 0x1403d6850 | 0x1433f9900 |
| DrawDebugAxisAlignedBox | 0x1403d6950 | 0x1433f9910 |
| DrawDebugBox | 0x1403d6b30 | 0x1433f9920 |
| DrawDebugCapsule | 0x1403d6d50 | 0x1433f9930 |
| DrawDebugCollisionShape | 0x1403d6ff0 | 0x1433f9940 |
| DrawDebugCylinder | 0x1403d7250 | 0x1433f9950 |
| DrawDebugLine | 0x1403d74f0 | 0x1433f9960 |
| DrawDebugPoint | 0x1403d7710 | 0x1433f9970 |
| DrawDebugSphere | 0x1403d78e0 | 0x1433f9980 |
| DrawDebugStaticMesh | 0x1403d7ae0 | 0x1433f9990 |
| DrawDebugString | 0x1403d7de0 | 0x1433f99a0 |
| EvaluateCurve | 0x1403d7f90 | 0x1433f99b0 |
| FlushDebugStrings | 0x1403d8060 | 0x1433f99c0 |
| FlushPersistentDebugLines | 0x1403d8080 | 0x1433f99d0 |
| GetCurrentGameStateContext | 0x1403d80a0 | 0x1433f99e0 |
| GetCurveTimeRange | 0x1403d8150 | 0x1433f99f0 |
| GetLastGameStateContext | 0x1403d82a0 | 0x1433f9a00 |
| LOSCheck | 0x1403d8450 | 0x1433f9a10 |
| OverlapCollision | 0x1403d8670 | 0x1433f9a20 |
| PrintStringFromGK | 0x1403d8ac0 | 0x1433f9a30 |
| StartCameraShake | 0x1403d9930 | 0x1433f9a40 |
| StartRangedCameraShake | 0x1403d9a40 | 0x1433f9a50 |
| StartRangedPadRumble | 0x1403d9c20 | 0x1433f9a60 |
| StopCameraShake | 0x1403d9e00 | 0x1433f9a70 |
| SweepCollision | 0x1403d9ed0 | 0x1433f9a80 |

## NTGameState

Class params `0x1433f7db0`; resolver `0x1403d2740`; size `0x138`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ActorsToSpawn | Array | 0x128 | 0x144e0cd20 |
| GameplayEvents | Array | 0x118 | 0x144e0cda0 |
| OutputEvents | Array | 0x108 | 0x144e0ce20 |
| PreUpdateCallbacks | Array | 0xf8 | 0x144e0cea0 |
| ActorsRemovedThisFrame | Array | 0xe8 | 0x144e0cf20 |
| ActorsPendingRemoval | Array | 0xd8 | 0x144e0cfa0 |
| NextSpawnIndexForActorId | Int16 | 0xd0 | 0x144e0d020 |
| GlobalManagerObjects | Array | 0xc0 | 0x144e0d058 |
| EventManager | Object | 0xb8 | 0x144e0d0d0 |
| ActorMap | Map | 0x68 | 0x144e0d110 |
| AssetLoadRequestManager | Struct | 0x38 | 0x144e0d1c0 |
| TargetRequestManager | Struct | 0x28 | 0x144e0d200 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddGlobalManagerCallback | 136 | 0x144e0b8f0 |
| AddPreUpdateCallback | 152 | 0x144e0ba40 |
| AddPreUpdateCallbackForSpecificActor | 128 | 0x144e0bb40 |
| AddPreUpdateCallbackWithArguments | 160 | 0x144e0bc90 |
| AddPreUpdateCallbackWithArgumentsForSpecificActor | 136 | 0x144e0bd90 |
| CancelActorSpawn | 112 | 0x144e0be50 |
| InvalidateSpawnHandle | 8 | 0x144e0bed0 |
| IsActorSpawnHandleValid | 16 | 0x144e0bfa0 |
| RecordGameplayEvent | 112 | 0x144e0c060 |
| RecordOutputEvent | 112 | 0x144e0c120 |
| SpawnActor | 152 | 0x144e0c2f0 |
| SpawnActorFromActorData | 176 | 0x144e0c470 |
| SpawnActorFromActorDataWithCallback | 208 | 0x144e0c630 |
| SpawnActorFromInitialiser | 240 | 0x144e0c730 |
| SpawnActorFromInitialiserWithCallback | 256 | 0x144e0c870 |
| SpawnActorWithCallback | 176 | 0x144e0ca80 |
| TryGetGlobalManagerData | 128 | 0x144e0cbe0 |
| TrySpawnActorImmediately | 240 | 0x144e0cce0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| AddGlobalManagerCallback | 0x1403d57d0 | 0x1433fa080 |
| AddPreUpdateCallback | 0x1403d5970 | 0x1433fa090 |
| AddPreUpdateCallbackForSpecificActor | 0x1403d5b20 | 0x1433fa0a0 |
| AddPreUpdateCallbackWithArguments | 0x1403d5c80 | 0x1433fa0b0 |
| AddPreUpdateCallbackWithArgumentsForSpecificActor | 0x1403d5e20 | 0x1433fa0c0 |
| CancelActorSpawn | 0x1403d6010 | 0x1433fa0d0 |
| InvalidateSpawnHandle | 0x1403d8350 | 0x1433fa0e0 |
| IsActorSpawnHandleValid | 0x1403d83d0 | 0x1433fa0f0 |
| RecordGameplayEvent | 0x1403d8c80 | 0x1433fa100 |
| RecordOutputEvent | 0x1403d8d70 | 0x1433fa110 |
| SpawnActor | 0x1403d8e60 | 0x1433fa120 |
| SpawnActorFromActorData | 0x1403d9010 | 0x1433fa130 |
| SpawnActorFromActorDataWithCallback | 0x1403d9200 | 0x1433fa140 |
| SpawnActorFromInitialiser | 0x1403d9440 | 0x1433fa150 |
| SpawnActorFromInitialiserWithCallback | 0x1403d9570 | 0x1433fa160 |
| SpawnActorWithCallback | 0x1403d9700 | 0x1433fa170 |
| TryGetGlobalManagerData | 0x1403da3e0 | 0x1433fa180 |
| TrySpawnActorImmediately | 0x1403da530 | 0x1433fa190 |

## NTGlobalManagerObjectData

Class params `0x1433fdca0`; resolver `0x1403dbb00`; size `0x30`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| StateClass | Class | 0x28 | 0x144e0f8f0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTGlobalManagerObjectProxy

Class params `0x1434390d0`; resolver `0x140457620`; size `0x3b8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| CurrentState | Object | 0x3b0 | 0x144e1c5d0 |
| ActorData | Object | 0x3a8 | 0x144e1c610 |
| DefaultManagerDataClass | Class | 0x3a0 | 0x144e1c650 |
| GlobalManagerData | Object | 0x398 | 0x144e1c6a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetGlobalManagerDataOfClass | 24 | 0x144e1c550 |
| OnReceivedFirstState | 0 | 0x144e1c590 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetGlobalManagerDataOfClass | 0x14045c040 | 0x14343d780 |

## NTGlobalManagerObjectState

Class params `0x1433fad50`; resolver `0x1403db0f0`; size `0x80`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bManagerCallbacksHaveBeenExecutedThisFrame | Bool | 0x68 | 0x144e103a0 |
| RandomGenerator | Struct | 0x60 | 0x144e103f0 |
| TimerManager | Struct | 0x48 | 0x144e10430 |
| ManagerId | Int | 0x40 | 0x144e10470 |
| AnalyticsEventlets | Array | 0x30 | 0x144e104a8 |
| ManagerData | Object | 0x28 | 0x144e10520 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| BlueprintInitialise | 104 | 0x144e0fbb0 |
| BlueprintPostActorUpdate | 104 | 0x144e0fc30 |
| ChangeTimerDuration | 12 | 0x144e0fd30 |
| CreateTimer | 32 | 0x144e0fe70 |
| DeleteTimer | 4 | 0x144e0fef0 |
| GenerateRandomFloat | 12 | 0x144e0ffe0 |
| GenerateRandomInt | 12 | 0x144e100d0 |
| GetManagerData | 8 | 0x144e10150 |
| GetTimerRemainingTime | 8 | 0x144e10210 |
| IsTimerActive | 8 | 0x144e102e0 |
| ResetTimer | 4 | 0x144e10360 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ChangeTimerDuration | 0x1403e07e0 | 0x1434014a0 |
| CreateTimer | 0x1403e1830 | 0x1434014b0 |
| DeleteTimer | 0x1403e1c30 | 0x1434014c0 |
| GenerateRandomFloat | 0x1403e1cd0 | 0x1434014d0 |
| GenerateRandomInt | 0x1403e1da0 | 0x1434014e0 |
| GetManagerData | 0x1403e1e60 | 0x1434014f0 |
| GetTimerRemainingTime | 0x1403e1e80 | 0x143401500 |
| IsTimerActive | 0x1403e2010 | 0x143401510 |
| ResetTimer | 0x1403e20a0 | 0x143401520 |

## NTKioskModeConfig

Class params `0x1433a93f0`; resolver `0x1403202b0`; size `0x98`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| DojoMapOptions | Str | 0x88 | 0x144de6820 |
| DojoMap | Str | 0x78 | 0x144de6858 |
| TutorialMapOptions | Str | 0x68 | 0x144de6890 |
| TutorialMap | Str | 0x58 | 0x144de68c8 |
| ClientIsDev | Int | 0x50 | 0x144de6900 |
| ClientPlayerName | Str | 0x40 | 0x144de6938 |
| ClientTeamId | Int | 0x38 | 0x144de6970 |
| ServerIP | Str | 0x28 | 0x144de69a8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetClientIsDev | 4 | 0x144de64d0 |
| GetClientPlayerName | 16 | 0x144de6510 |
| GetClientTeamId | 4 | 0x144de65c0 |
| GetDojoMap | 16 | 0x144de6600 |
| GetDojoMapOptions | 16 | 0x144de66b0 |
| GetServerIP | 16 | 0x144de66f0 |
| GetTutorialMap | 16 | 0x144de67a0 |
| GetTutorialMapOptions | 16 | 0x144de67e0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetClientIsDev | 0x140326c20 | 0x1433ac4c0 |
| GetClientPlayerName | 0x140326c80 | 0x1433ac4d0 |
| GetClientTeamId | 0x140326d80 | 0x1433ac4e0 |
| GetDojoMap | 0x140326de0 | 0x1433ac4f0 |
| GetDojoMapOptions | 0x140326ee0 | 0x1433ac500 |
| GetServerIP | 0x1403275d0 | 0x1433ac510 |
| GetTutorialMap | 0x1403276d0 | 0x1433ac520 |
| GetTutorialMapOptions | 0x1403277d0 | 0x1433ac530 |

## NTPlayerAssetManager

Class params `0x1433c9ab0`; resolver `0x140369c50`; size `0x160`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| GameInstance | Object | 0x120 | 0x144df7cf0 |
| AssetTypes | Array | 0x30 | 0x144df7bc8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| CreateSession | 8 | 0x144df7cb0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| CreateSession | 0x14036bd50 | 0x1433cebc8 |

## NTPlayerController

Class params `0x1433ca3b0`; resolver `0x140368e00`; size `0x6e8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRecordPlayer

Class params `0x14343b870`; resolver `0x1404581d0`; size `0x4b8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ReferenceNames | Array | 0x4a8 | 0x144e1e3a0 |
| bExternalSyncMaster | Bool | 0x4a1 | 0x144e1e410 |
| bTickExternally | Bool | 0x4a0 | 0x144e1e460 |
| bPlaybackFinished | Bool | 0x49f | 0x144e1e4b0 |
| bPlaybackWaitingForSyncMaster | Bool | 0x49e | 0x144e1e500 |
| bPlaybackStarted | Bool | 0x49d | 0x144e1e550 |
| bJustUnpaused | Bool | 0x49c | 0x144e1e5a0 |
| bPaused | Bool | 0x49b | 0x144e1e5f0 |
| bPressedPlay | Bool | 0x49a | 0x144e1e640 |
| bPlayerSpawned | Bool | 0x499 | 0x144e1e690 |
| bInitialised | Bool | 0x498 | 0x144e1e6e0 |
| PlaybackPlayerID | Int | 0x494 | 0x144e1e728 |
| RecordedPlayerID | Int | 0x490 | 0x144e1e760 |
| NumSecondsBeforeStart | Float | 0x48c | 0x144e1e798 |
| RemovePlayerFrameFromLastLoop | Int | 0x488 | 0x144e1e7d0 |
| SyncMasterStartFrameOffset | Int | 0x484 | 0x144e1e808 |
| LastFrameSubmittedInputFor | Int | 0x480 | 0x144e1e840 |
| FrameOffset | Int | 0x47c | 0x144e1e878 |
| CurrentRecordingFrame | Int | 0x478 | 0x144e1e8b0 |
| FrameRecordStarted | Int | 0x474 | 0x144e1e8e8 |
| FirstFrameInRecording | Int | 0x470 | 0x144e1e920 |
| TakenOverPlayerController | Interface | 0x458 | 0x144e1e960 |
| RecordPlayerInterfaceObject | Interface | 0x448 | 0x144e1e9a0 |
| SyncMaster | Object | 0x440 | 0x144e1e9e0 |
| SelectedPlayerRequiredAssets | Array | 0x430 | 0x144e1ea20 |
| SelectedPlayerAddEvent | Object | 0x428 | 0x144e1eaa0 |
| StreamReader | Object | 0x420 | 0x144e1eae0 |
| bTakeOverPlayerController | Bool | 0x3e9 | 0x144e1eb20 |
| bSnapRecordPlayerPositionToRecordingStartPosition | Bool | 0x3e8 | 0x144e1eb70 |
| RecordData | Struct | 0x398 | 0x144e1ebc0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| Pause | 1 | 0x144e1e2e0 |
| PressPlay | 0 | 0x144e1e320 |
| PressStop | 0 | 0x144e1e360 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| Pause | 0x14045c180 | 0x14343dcc8 |
| PressPlay | 0x14045c210 | 0x14343dcd8 |
| PressStop | 0x14045c230 | 0x14343dce8 |

## NTRollbackChannel

Class params `0x143422090`; resolver `0x1404225b0`; size `0x88`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| RollbackNetworkInterface | Object | 0x68 | 0x144e18320 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackEngine

Class params `0x143424b90`; resolver `0x140422de0`; size `0x868`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| RecordingRetiredFrameHash | Map | 0x680 | 0x144e18568 |
| ServerResyncBaseFrame | Object | 0x678 | 0x144e18ca0 |
| SaveStream | Object | 0x668 | 0x144e18ce0 |
| LoadStream | Object | 0x660 | 0x144e18d20 |
| RequestedRetiredFrameStates | Array | 0x620 | 0x144e186a8 |
| RetiredFrameCompressor | Struct | 0x5c8 | 0x144e18da0 |
| RetiredFrameStates | Array | 0x5b8 | 0x144e18a28 |
| ArchivedRetiredFrameStates | Array | 0x5a8 | 0x144e18b28 |
| LocalInputEvents | Array | 0x598 | 0x144e18be8 |
| LocalPlayerRemoveEvents | Array | 0x588 | 0x144e18ea0 |
| PermanentLocalPlayerAddEvents | Array | 0x578 | 0x144e18ed8 |
| LocalPlayerAddEvents | Array | 0x568 | 0x144e18f90 |
| GlobalManagerData | Array | 0x558 | 0x144e18fc8 |
| ActorInitialisers | Array | 0x548 | 0x144e19080 |
| SerialisationReferenceLibrary | Object | 0x540 | 0x144e19130 |
| InputRegister | Struct | 0x518 | 0x144e19170 |
| DesyncLogger | Struct | 0x478 | 0x144e191b0 |
| PipelineFrameEvaluator | Struct | 0x408 | 0x144e191f0 |
| GameStateSerialiser | Struct | 0x3b8 | 0x144e19230 |
| FrameHashGenerator | Struct | 0x358 | 0x144e19270 |
| RollbackWorker | Struct | 0x1f8 | 0x144e192b0 |
| FrameStatePool | Struct | 0x1d0 | 0x144e192f0 |
| PublicFrameHistory | Struct | 0x170 | 0x144e19330 |
| InputPredictor | Object | 0x168 | 0x144e19370 |
| BackgroundEngineInterface | Object | 0x160 | 0x144e193b0 |
| EngineInterface | Object | 0x158 | 0x144e193f0 |
| OpenChannels | Array | 0x148 | 0x144e190b8 |
| NetDriver | Object | 0x140 | 0x144e19470 |
| MinimumInputFrameNumber | Int | 0x138 | 0x144e194b0 |
| InputEventsFromRecordings | Array | 0x118 | 0x144e194e8 |
| LastInterimFrameState | Object | 0xf0 | 0x144e19560 |
| UniqueSessionData | Struct | 0xc8 | 0x144e195a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetCurrentFrameNumber | 4 | 0x144e18a60 |
| GetNumberOfReadyPlayers | 4 | 0x144e18aa0 |
| IsDroppingFrames | 1 | 0x144e18b60 |
| IsDroppingInput | 1 | 0x144e18c20 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetCurrentFrameNumber | 0x1404276e0 | 0x1434281b0 |
| GetNumberOfReadyPlayers | 0x140427710 | 0x1434281c0 |
| IsDroppingFrames | 0x140427740 | 0x1434281d0 |
| IsDroppingInput | 0x140427770 | 0x1434281e0 |

## NTRollbackMachine

Class params `0x14342a160`; resolver `0x140427ec0`; size `0x100`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| InitParams | Struct | 0x58 | 0x144e19d60 |
| Connections | Array | 0x48 | 0x144e19be8 |
| StreamReader | Object | 0x40 | 0x144e19de0 |
| RollbackEngine | Object | 0x38 | 0x144e19e20 |
| MachineName | Str | 0x28 | 0x144e19d28 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackMachineConnection

Class params `0x14342a640`; resolver `0x140428050`; size `0x48`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| DestinationConnection | Object | 0x30 | 0x144e19eb0 |
| RollbackNetworkInterface | Object | 0x28 | 0x144e19ef0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackMachineGroup

Class params `0x14342b880`; resolver `0x140428360`; size `0xa0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| FutureFrames | Map | 0x48 | 0x144e1a068 |
| MachineConnections | Array | 0x38 | 0x144e1a168 |
| Machines | Array | 0x28 | 0x144e1a268 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackMachineGroupConnected

Class params `0x143428210`; resolver `0x1404285b0`; size `0xa0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackMachineGroupLocal

Class params `0x143428450`; resolver `0x1404277b0`; size `0xa0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackNetworkInterface

Class params `0x143429c30`; resolver `0x140428150`; size `0x330`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ReceivedRetiredFrameStatePackets | Array | 0x2f0 | 0x144e1a718 |
| FrameHistoryFromGameStatePacket | Struct | 0x2d8 | 0x144e1ae50 |
| ReceivedSessionData | Struct | 0x2a0 | 0x144e1ae90 |
| PlayersToAddFromClient | Array | 0x230 | 0x144e1a798 |
| OwnedPlayerAddEvents | Array | 0x220 | 0x144e1a858 |
| ReceivedOutputEventPackets | Array | 0x1c0 | 0x144e1a8d8 |
| ReceivedInputEventPackets | Array | 0x1b0 | 0x144e1a958 |
| StreamReference | Object | 0x70 | 0x144e1afd0 |
| RollbackEngine | Object | 0x68 | 0x144e1b010 |
| AvgLag | Float | 0x60 | 0x144e1a9d8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackObjectFactory

Class params `0x143429f00`; resolver `0x140427e10`; size `0x50`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| World | Object | 0x40 | 0x144e1b050 |
| DefaultRollbackObjectFactoryClass | Struct | 0x28 | 0x144e1b090 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackObjectProvider

Class params `0x143423d20`; resolver `0x140422ce0`; size `0x28`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackPlayerController

Class params `0x14343a280`; resolver `0x140457d50`; size `0x28`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackRecording

Class params `0x14342a0a0`; resolver `0x140427f60`; size `0x40`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ClientStreams | Array | 0x30 | 0x144e1abb8 |
| ServerStream | Object | 0x28 | 0x144e1b110 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackRecordingStream

Class params `0x14342a4b0`; resolver `0x140427d60`; size `0x38`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| RecordingBytes | Array | 0x28 | 0x144e1ace8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackRecordingStreamReader

Class params `0x14342af60`; resolver `0x140428230`; size `0xe0`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| Header | Struct | 0x50 | 0x144e1b240 |
| SourceStream | Object | 0x48 | 0x144e1b280 |
| RollbackObjectProvider | Interface | 0x38 | 0x144e1b2c0 |
| RollbackEngine | Object | 0x30 | 0x144e1b300 |
| StreamReference | Object | 0x28 | 0x144e1b340 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackRecordingStreamWriter

Class params `0x14342b1a0`; resolver `0x140428400`; size `0xa8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| Header | Struct | 0x38 | 0x144e1b380 |
| RollbackEngine | Object | 0x30 | 0x144e1b3c0 |
| StreamReference | Object | 0x28 | 0x144e1b400 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTRollbackRecordingTestBlueprint

Class params `0x14343c740`; resolver `0x1404588e0`; size `0xc8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| TestRecording | Object | 0xb0 | 0x144e205a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| EvaluateTestState | 104 | 0x144e20240 |
| HasPlaybackStarted | 1 | 0x144e202d0 |
| IsPlaybackComplete | 1 | 0x144e20360 |
| StartPlayback | 24 | 0x144e20420 |
| StartRecording | 16 | 0x144e204a0 |
| StopPlayback | 0 | 0x144e204e0 |
| StopRecording | 0 | 0x144e20520 |
| TogglePauseRecording | 0 | 0x144e20560 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| HasPlaybackStarted | 0x14045c120 | 0x14343e990 |
| IsPlaybackComplete | 0x14045c150 | 0x14343e9a0 |
| StartPlayback | 0x14045c250 | 0x14343e9b0 |
| StartRecording | 0x14045c340 | 0x14343e9c0 |
| StopPlayback | 0x14045c440 | 0x14343e9d0 |
| StopRecording | 0x14045c460 | 0x14343e9e0 |
| TogglePauseRecording | 0x14045c480 | 0x14343e9f0 |

## NTRollbackWorldSettings, game

Class params `0x14343b6d0`; resolver `0x140458490`; size `0x5a8`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LevelSessionOptions | Object | 0x5a0 | 0x144e20610 |
| bUseRollbackEngineInThisMap | Bool | 0x599 | 0x144e20650 |
| bFixedUpMapCollision | Bool | 0x598 | 0x144e206a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTServerPlaybackManager

Class params `0x1434396a0`; resolver `0x140457340`; size `0x180`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bSeekInProgress | Bool | 0x179 | 0x144e20710 |
| bInitialised | Bool | 0x178 | 0x144e20760 |
| RollbackEngine | Object | 0x170 | 0x144e207b0 |
| PreviousReferenceFrame | Object | 0x168 | 0x144e207f0 |
| CurrentReferenceFrame | Object | 0x160 | 0x144e20830 |
| ReferenceInputPredictor | Object | 0x158 | 0x144e20870 |
| ReferenceEngineInterface | Object | 0x150 | 0x144e208b0 |
| CurrentFrame | Struct | 0xe8 | 0x144e208f0 |
| CheckpointFrames | Map | 0x98 | 0x144e20930 |
| CurrentFrameNumber | Int | 0x94 | 0x144e209e0 |
| RingBufferStartIndex | Int | 0x90 | 0x144e20a18 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTSessionOptions

Class params `0x1433f67c0`; resolver `0x1403d27e0`; size `0x38`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| StartingGameplayEvents | Array | 0x28 | 0x144e0b0e8 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTTestPlayerState

Class params `0x143409b20`; resolver `0x1403ea370`; size `0x400`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| UnrealPlayerID | Int | 0x3f0 | 0x144e13bd0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## NTWorldSingleton

Class params `0x14343aa80`; resolver `0x140457a80`; size `0x420`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| BufferedGameplayEvents | Array | 0x408 | 0x144e213e0 |
| BufferedOutputEvents | Array | 0x3f8 | 0x144e21460 |
| CurrentState | Object | 0x3f0 | 0x144e214e0 |
| RollbackEngine | Object | 0x3e8 | 0x144e21520 |
| GameplayEventCallback | MulticastDelegate | 0x3a8 | 0x144e21560 |
| OutputEventCallback | MulticastDelegate | 0x398 | 0x144e215a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetRollbackEngine | 8 | 0x144e213a0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| GetRollbackEngine | 0x14045c100 | 0x1434401c0 |

## OnlineSession

Class params `0x1441909f0`; resolver `0x1404e1170`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## OnlineSessionClient

Class params `0x143491490`; resolver `0x1404de170`; size `0x190`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bHandlingDisconnect | Bool | 0x189 | 0x144e2ae80 |
| bIsFromInvite | Bool | 0x188 | 0x144e2af00 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## Pawn

Class params `0x1441a7610`; resolver `0x140f5b4c0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| LastControlInputVector | Struct | 0x3e8 | 0x1451c3410 |
| ControlInputVector | Struct | 0x3dc | 0x1451c3450 |
| Controller | Object | 0x3d0 | 0x1451c3490 |
| LastHitBy | Object | 0x3c8 | 0x1451c34d0 |
| RemoteViewPitch | Byte | 0x3c0 | 0x1451c3510 |
| PlayerState | Object | 0x3b8 | 0x1451c3550 |
| AIControllerClass | Class | 0x3b0 | 0x1451c3590 |
| AutoPossessAI | Enum | 0x3a9 | 0x1451c35e0 |
| AutoPossessPlayer | Byte | 0x3a8 | 0x1451c3660 |
| BaseEyeHeight | Float | 0x3a4 | 0x1451c36a0 |
| bCanAffectNavigationGeneration | Bool | unresolved | 0x1451c36e0 |
| bUseControllerRotationRoll | Bool | unresolved | 0x1451c3730 |
| bUseControllerRotationYaw | Bool | unresolved | 0x1451c3780 |
| bUseControllerRotationPitch | Bool | unresolved | 0x1451c37d0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| AddControllerPitchInput | 4 | 0x1451c2500 |
| AddControllerRollInput | 4 | 0x1451c2580 |
| AddControllerYawInput | 4 | 0x1451c2600 |
| AddMovementInput | 20 | 0x1451c2700 |
| ConsumeMovementInputVector | 12 | 0x1451c2780 |
| DetachFromControllerPendingDestroy | 0 | 0x1451c27c0 |
| GetBaseAimRotation | 12 | 0x1451c2840 |
| GetControlRotation | 12 | 0x1451c2940 |
| GetController | 8 | 0x1451c28c0 |
| GetLastMovementInputVector | 12 | 0x1451c29c0 |
| GetMovementBaseActor | 16 | 0x1451c2a80 |
| GetMovementComponent | 8 | 0x1451c2b00 |
| GetNavAgentLocation | 12 | 0x1451c2b80 |
| GetPendingMovementInputVector | 12 | 0x1451c2c00 |
| IsControlled | 1 | 0x1451c2c90 |
| IsLocallyControlled | 1 | 0x1451c2d20 |
| IsMoveInputIgnored | 1 | 0x1451c2db0 |
| IsPlayerControlled | 1 | 0x1451c2e40 |
| K2_GetMovementInputVector | 12 | 0x1451c2ec0 |
| LaunchPawn | 16 | 0x1451c2fe0 |
| OnRep_Controller | 0 | 0x1451c3020 |
| OnRep_PlayerState | 0 | 0x1451c3060 |
| PawnMakeNoise | 32 | 0x1451c31b0 |
| ReceivePossessed | 8 | 0x1451c3230 |
| ReceiveUnpossessed | 8 | 0x1451c32b0 |
| SetCanAffectNavigationGeneration | 2 | 0x1451c3390 |
| SpawnDefaultController | 0 | 0x1451c33d0 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## PlatformGameInstance

Class params `0x1440e1490`; resolver `0x14133b380`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ApplicationReceivedScreenOrientationChangedNotificationDelegate | MulticastDelegate | 0x160 | 0x145110b30 |
| ApplicationReceivedLocalNotificationDelegate | MulticastDelegate | 0x150 | 0x145110b70 |
| ApplicationReceivedRemoteNotificationDelegate | MulticastDelegate | 0x140 | 0x145110bb0 |
| ApplicationFailedToRegisterForRemoteNotificationsDelegate | MulticastDelegate | 0x130 | 0x145110bf0 |
| ApplicationRegisteredForUserNotificationsDelegate | MulticastDelegate | 0x120 | 0x145110c30 |
| ApplicationRegisteredForRemoteNotificationsDelegate | MulticastDelegate | 0x110 | 0x145110c70 |
| ApplicationReceivedStartupArgumentsDelegate | MulticastDelegate | 0x100 | 0x145110cb0 |
| ApplicationShouldUnloadResourcesDelegate | MulticastDelegate | 0xf0 | 0x145110cf0 |
| ApplicationWillTerminateDelegate | MulticastDelegate | 0xe0 | 0x145110d30 |
| ApplicationHasEnteredForegroundDelegate | MulticastDelegate | 0xd0 | 0x145110d70 |
| ApplicationWillEnterBackgroundDelegate | MulticastDelegate | 0xc0 | 0x145110db0 |
| ApplicationHasReactivatedDelegate | MulticastDelegate | 0xb0 | 0x145110df0 |
| ApplicationWillDeactivateDelegate | MulticastDelegate | 0xa0 | 0x145110e30 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## Player

Class params `0x1441ac3c0`; resolver `0x1426fb8c0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| ConfiguredLanSpeed | Int | 0x40 | 0x1451ca0d0 |
| ConfiguredInternetSpeed | Int | 0x3c | 0x1451ca108 |
| CurrentNetSpeed | Int | 0x38 | 0x1451ca140 |
| PlayerController | Object | 0x30 | 0x1451ca1a0 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|

| Native function | Exec wrapper | Binding record |
|---|---|---|

## PlayerController

Class params `0x1441b1060`; resolver `0x14036acd0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| SpawnLocation | Struct | 0x6d8 | 0x1451d2650 |
| bIsLocalPlayerController | Bool | 0x6d4 | 0x1451d2690 |
| SpectatorPawn | Object | 0x6c8 | 0x1451d2710 |
| CurrentTouchInterface | Object | 0x670 | 0x1451d2750 |
| bShouldPerformFullTickWhenPaused | Bool | unresolved | 0x1451d2790 |
| InactiveStateInputComponent | Object | 0x650 | 0x1451d2810 |
| LastCompletedSeamlessTravelCount | UInt16 | 0x5da | 0x1451d2198 |
| SeamlessTravelCount | UInt16 | 0x5d8 | 0x1451d23d8 |
| HitResultTraceDistance | Float | 0x5d4 | 0x1451d2498 |
| CurrentClickTraceChannel | Byte | 0x5d3 | 0x1451d2850 |
| DefaultClickTraceChannel | Byte | 0x5d2 | 0x1451d2890 |
| CurrentMouseCursor | Byte | 0x5d1 | 0x1451d28d0 |
| DefaultMouseCursor | Byte | 0x5d0 | 0x1451d2910 |
| ClickEventKeys | Array | 0x5c0 | 0x1451d2598 |
| ForceFeedbackScale | Float | 0x5bc | 0x1451d26d8 |
| bForceFeedbackEnabled | Bool | unresolved | 0x1451d2990 |
| bEnableTouchOverEvents | Bool | unresolved | 0x1451d2a10 |
| bEnableMouseOverEvents | Bool | unresolved | 0x1451d2a90 |
| bEnableTouchEvents | Bool | unresolved | 0x1451d2b10 |
| bEnableClickEvents | Bool | unresolved | 0x1451d2b90 |
| bShowMouseCursor | Bool | unresolved | 0x1451d2c10 |
| InputRollScale | Float | 0x5b4 | 0x1451d27d8 |
| InputPitchScale | Float | 0x5b0 | 0x1451d29d8 |
| InputYawScale | Float | 0x5ac | 0x1451d2a58 |
| NetConnection | Object | 0x598 | 0x1451d2c90 |
| PendingSwapConnection | Object | 0x590 | 0x1451d2cd0 |
| NetPlayerIndex | Byte | 0x554 | 0x1451d2d10 |
| bPlayerIsWaiting | Bool | unresolved | 0x1451d2d50 |
| ActiveForceFeedbackEffects | Array | 0x4d0 | 0x1451d2ad8 |
| PlayerInput | Object | 0x4c8 | 0x1451d2e10 |
| CheatClass | Class | 0x4c0 | 0x1451d2e50 |
| CheatManager | Object | 0x4b8 | 0x1451d2ed0 |
| ClientCap | Int | 0x4b0 | 0x1451d2b58 |
| LastSpectatorSyncRotation | Struct | 0x4a4 | 0x1451d2f10 |
| LastSpectatorSyncLocation | Struct | 0x498 | 0x1451d2f50 |
| LastSpectatorStateSynchTime | Float | 0x494 | 0x1451d2bd8 |
| HiddenPrimitiveComponents | Array | 0x480 | 0x1451d2c58 |
| HiddenActors | Array | 0x470 | 0x1451d2d98 |
| SmoothTargetViewRotationSpeed | Float | 0x464 | 0x1451d2e98 |
| TargetViewRotation | Struct | 0x44c | 0x1451d3010 |
| bAutoManageActiveCameraTarget | Bool | 0x448 | 0x1451d3050 |
| PlayerCameraManagerClass | Class | 0x440 | 0x1451d30c0 |
| PlayerCameraManager | Object | 0x438 | 0x1451d3110 |
| MyHUD | Object | 0x430 | 0x1451d3150 |
| ControllingDirTrackInst | Object | 0x428 | 0x1451d3190 |
| AcknowledgedPawn | Object | 0x420 | 0x1451d31d0 |
| Player | Object | 0x418 | 0x1451d3210 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| ActivateTouchInterface | 8 | 0x1451cc950 |
| AddPitchInput | 4 | 0x1451cc990 |
| AddRollInput | 4 | 0x1451cc9d0 |
| AddYawInput | 4 | 0x1451cca10 |
| Camera | 8 | 0x1451ccac0 |
| CanRestartPlayer | 1 | 0x1451ccb80 |
| ClearAudioListenerAttenuationOverride | 0 | 0x1451ccbc0 |
| ClearAudioListenerOverride | 0 | 0x1451ccc00 |
| ClientAddTextureStreamingLoc | 20 | 0x1451ccd00 |
| ClientCancelPendingMapChange | 0 | 0x1451ccd40 |
| ClientCapBandwidth | 4 | 0x1451ccd80 |
| ClientClearCameraLensEffects | 0 | 0x1451ccdc0 |
| ClientCommitMapChange | 0 | 0x1451cce00 |
| ClientEnableNetworkVoice | 1 | 0x1451ccec0 |
| ClientEndOnlineSession | 0 | 0x1451ccf00 |
| ClientFlushLevelStreaming | 0 | 0x1451ccf40 |
| ClientForceGarbageCollection | 0 | 0x1451ccf80 |
| ClientGameEnded | 16 | 0x1451cd080 |
| ClientGotoState | 8 | 0x1451cd0c0 |
| ClientIgnoreLookInput | 1 | 0x1451cd180 |
| ClientIgnoreMoveInput | 1 | 0x1451cd240 |
| ClientMessage | 32 | 0x1451cd280 |
| ClientMutePlayer | 40 | 0x1451cd300 |
| ClientPlayCameraAnim | 40 | 0x1451cd570 |
| ClientPlayCameraShake | 32 | 0x1451cd6b0 |
| ClientPlayForceFeedback | 24 | 0x1451cd830 |
| ClientPlaySound | 16 | 0x1451cd8b0 |
| ClientPlaySoundAtLocation | 32 | 0x1451cd9e0 |
| ClientPrepareMapChange | 16 | 0x1451cdb20 |
| ClientPrestreamTextures | 24 | 0x1451cdc20 |
| ClientReceiveLocalizedMessage | 40 | 0x1451cde10 |
| ClientRepObjRef | 8 | 0x1451cde90 |
| ClientReset | 0 | 0x1451cded0 |
| ClientRestart | 8 | 0x1451cdf50 |
| ClientRetryClientRestart | 8 | 0x1451cdfd0 |
| ClientReturnToMainMenu | 16 | 0x1451ce010 |
| ClientReturnToMainMenuWithTextReason | 24 | 0x1451ce050 |
| ClientSetBlockOnAsyncLoading | 0 | 0x1451ce090 |
| ClientSetCameraFade | 24 | 0x1451ce250 |
| ClientSetCameraMode | 8 | 0x1451ce290 |
| ClientSetCinematicMode | 4 | 0x1451ce4d0 |
| ClientSetForceMipLevelsToBeResident | 16 | 0x1451ce550 |
| ClientSetHUD | 8 | 0x1451ce610 |
| ClientSetSpectatorWaiting | 1 | 0x1451ce6d0 |
| ClientSetViewTarget | 32 | 0x1451ce790 |
| ClientSpawnCameraLensEffect | 8 | 0x1451ce850 |
| ClientStartOnlineSession | 0 | 0x1451ce890 |
| ClientStopCameraAnim | 8 | 0x1451ce910 |
| ClientStopCameraShake | 16 | 0x1451cea50 |
| ClientStopForceFeedback | 16 | 0x1451cead0 |
| ClientTeamMessage | 40 | 0x1451ceb50 |
| ClientTravel | 40 | 0x1451cec90 |
| ClientTravelInternal | 40 | 0x1451cedd0 |
| ClientUnmutePlayer | 40 | 0x1451cee50 |
| ClientUpdateLevelStreamingStatus | 16 | 0x1451cf010 |
| ClientUpdateMultipleLevelsStreamingStatus | 16 | 0x1451cf090 |
| ClientVoiceHandshakeComplete | 0 | 0x1451cf0d0 |
| ClientWasKicked | 24 | 0x1451cf110 |
| ConsoleKey | 24 | 0x1451cf190 |
| DeprojectMousePositionToWorld | 28 | 0x1451cf2d0 |
| DeprojectScreenPositionToWorld | 36 | 0x1451cf410 |
| EnableCheats | 0 | 0x1451cf450 |
| FOV | 4 | 0x1451cf490 |
| GetFocalLocation | 12 | 0x1451cf510 |
| GetHUD | 8 | 0x1451d00d0 |
| GetHitResultUnderCursor | 184 | 0x1451cf6d0 |
| GetHitResultUnderCursorByChannel | 184 | 0x1451cf890 |
| GetHitResultUnderCursorForObjects | 200 | 0x1451cfa50 |
| GetHitResultUnderFinger | 184 | 0x1451cfc50 |
| GetHitResultUnderFingerByChannel | 184 | 0x1451cfe50 |
| GetHitResultUnderFingerForObjects | 208 | 0x1451d0050 |
| GetInputAnalogKeyState | 32 | 0x1451d0150 |
| GetInputAnalogStickState | 12 | 0x1451d01d0 |
| GetInputKeyTimeDown | 32 | 0x1451d0250 |
| GetInputMotionState | 48 | 0x1451d0390 |
| GetInputMouseDelta | 8 | 0x1451d03d0 |
| GetInputTouchState | 16 | 0x1451d04d0 |
| GetInputVectorKeyState | 40 | 0x1451d0590 |
| GetMousePosition | 12 | 0x1451d0650 |
| GetSpectatorPawn | 8 | 0x1451d06d0 |
| GetViewportSize | 8 | 0x1451d0710 |
| IsInputKeyDown | 32 | 0x1451d0810 |
| LocalTravel | 16 | 0x1451d0850 |
| OnServerStartedVisualLogger | 1 | 0x1451d0910 |
| Pause | 0 | 0x1451d0950 |
| PlayDynamicForceFeedback | 40 | 0x1451d0c10 |
| PlayHapticEffect | 24 | 0x1451d0d90 |
| ProjectWorldLocationToScreen | 24 | 0x1451d0f50 |
| RestartLevel | 0 | 0x1451d0f90 |
| SendToConsole | 16 | 0x1451d0fd0 |
| ServerAcknowledgePossession | 8 | 0x1451d1050 |
| ServerCamera | 8 | 0x1451d1090 |
| ServerChangeName | 16 | 0x1451d10d0 |
| ServerCheckClientPossession | 0 | 0x1451d1110 |
| ServerCheckClientPossessionReliable | 0 | 0x1451d1150 |
| ServerMutePlayer | 40 | 0x1451d11d0 |
| ServerNotifyLoadedWorld | 8 | 0x1451d1210 |
| ServerPause | 0 | 0x1451d1250 |
| ServerRestartPlayer | 0 | 0x1451d1290 |
| ServerSetSpectatorLocation | 24 | 0x1451d1350 |
| ServerSetSpectatorWaiting | 1 | 0x1451d1410 |
| ServerShortTimeout | 0 | 0x1451d1450 |
| ServerToggleAILogging | 0 | 0x1451d1490 |
| ServerUnmutePlayer | 40 | 0x1451d1510 |
| ServerUpdateCamera | 16 | 0x1451d1590 |
| ServerUpdateLevelVisibility | 16 | 0x1451d1650 |
| ServerUpdateMultipleLevelsVisibility | 16 | 0x1451d16d0 |
| ServerVerifyViewTarget | 0 | 0x1451d1710 |
| ServerViewNextPlayer | 0 | 0x1451d1750 |
| ServerViewPrevPlayer | 0 | 0x1451d1790 |
| ServerViewSelf | 20 | 0x1451d1810 |
| SetAudioListenerAttenuationOverride | 24 | 0x1451d18d0 |
| SetAudioListenerOverride | 32 | 0x1451d19d0 |
| SetCinematicMode | 5 | 0x1451d1c90 |
| SetControllerLightColor | 4 | 0x1451d1d10 |
| SetDisableHaptics | 1 | 0x1451d1dd0 |
| SetHapticsByValue | 12 | 0x1451d1e90 |
| SetMouseCursorWidget | 16 | 0x1451d1f50 |
| SetMouseLocation | 8 | 0x1451d1f90 |
| SetName | 16 | 0x1451d1fd0 |
| SetViewTargetWithBlend | 24 | 0x1451d2110 |
| SetVirtualJoystickVisibility | 1 | 0x1451d21d0 |
| StartFire | 1 | 0x1451d2250 |
| StopHapticEffect | 1 | 0x1451d2310 |
| SwitchLevel | 16 | 0x1451d2350 |
| ToggleSpeaking | 1 | 0x1451d2410 |
| WasInputKeyJustPressed | 32 | 0x1451d2510 |
| WasInputKeyJustReleased | 32 | 0x1451d2610 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| ActivateTouchInterface | 0x14272fa20 | 0x1441b6aa0 |
| AddPitchInput | 0x14272fab0 | 0x1441b6ab0 |
| AddRollInput | 0x14272fb30 | 0x1441b6ac0 |
| AddYawInput | 0x14272fbb0 | 0x1441b6ad0 |
| Camera | 0x14272fc30 | 0x1441b6ae0 |
| CanRestartPlayer | 0x14272fcc0 | 0x1441b6af0 |
| ClearAudioListenerAttenuationOverride | 0x14272fcf0 | 0x1441b6b00 |
| ClearAudioListenerOverride | 0x14272fd10 | 0x1441b6b10 |
| ClientAddTextureStreamingLoc | 0x14272fd30 | 0x1441b6b20 |
| ClientCancelPendingMapChange | 0x14272fe50 | 0x1441b6b30 |
| ClientCapBandwidth | 0x14272fe70 | 0x1441b6b40 |
| ClientClearCameraLensEffects | 0x14272ff00 | 0x1441b6b50 |
| ClientCommitMapChange | 0x14272ff20 | 0x1441b6b60 |
| ClientEnableNetworkVoice | 0x14272ff40 | 0x1441b6b70 |
| ClientEndOnlineSession | 0x14272ffd0 | 0x1441b6b80 |
| ClientFlushLevelStreaming | 0x14272fff0 | 0x1441b6b90 |
| ClientForceGarbageCollection | 0x142730010 | 0x1441b6ba0 |
| ClientGameEnded | 0x142730030 | 0x1441b6bb0 |
| ClientGotoState | 0x142730100 | 0x1441b6bc0 |
| ClientIgnoreLookInput | 0x142730190 | 0x1441b6bd0 |
| ClientIgnoreMoveInput | 0x142730220 | 0x1441b6be0 |
| ClientMessage | 0x1427302b0 | 0x1441b6bf0 |
| ClientMutePlayer | 0x1427303e0 | 0x1441b6c00 |
| ClientPlayCameraAnim | 0x142730520 | 0x1441b6c10 |
| ClientPlayCameraShake | 0x1427307c0 | 0x1441b6c20 |
| ClientPlayForceFeedback | 0x142730920 | 0x1441b6c30 |
| ClientPlaySound | 0x142730a80 | 0x1441b6c40 |
| ClientPlaySoundAtLocation | 0x142730b80 | 0x1441b6c50 |
| ClientPrepareMapChange | 0x142730cd0 | 0x1441b6c60 |
| ClientPrestreamTextures | 0x142730de0 | 0x1441b6c70 |
| ClientReceiveLocalizedMessage | 0x142730f30 | 0x1441b6c80 |
| ClientRepObjRef | 0x1427310b0 | 0x1441b6c90 |
| ClientReset | 0x142731140 | 0x1441b6ca0 |
| ClientRestart | 0x142731160 | 0x1441b6cb0 |
| ClientRetryClientRestart | 0x1427311f0 | 0x1441b6cc0 |
| ClientReturnToMainMenu | 0x142731280 | 0x1441b6cd0 |
| ClientReturnToMainMenuWithTextReason | 0x142731330 | 0x1441b6ce0 |
| ClientSetBlockOnAsyncLoading | 0x142731400 | 0x1441b6cf0 |
| ClientSetCameraFade | 0x142731420 | 0x1441b6d00 |
| ClientSetCameraMode | 0x1427315b0 | 0x1441b6d10 |
| ClientSetCinematicMode | 0x142731640 | 0x1441b6d20 |
| ClientSetForceMipLevelsToBeResident | 0x1427317b0 | 0x1441b6d30 |
| ClientSetHUD | 0x1427318b0 | 0x1441b6d40 |
| ClientSetSpectatorWaiting | 0x142731940 | 0x1441b6d50 |
| ClientSetViewTarget | 0x1427319d0 | 0x1441b6d60 |
| ClientSpawnCameraLensEffect | 0x142731af0 | 0x1441b6d70 |
| ClientStartOnlineSession | 0x142731b80 | 0x1441b6d80 |
| ClientStopCameraAnim | 0x142731ba0 | 0x1441b6d90 |
| ClientStopCameraShake | 0x1427221a0 | 0x1441b6da0 |
| ClientStopForceFeedback | 0x142731c30 | 0x1441b6db0 |
| ClientTeamMessage | 0x142731d00 | 0x1441b6dc0 |
| ClientTravel | 0x142731e70 | 0x1441b6dd0 |
| ClientTravelInternal | 0x142731ff0 | 0x1441b6de0 |
| ClientUnmutePlayer | 0x142732170 | 0x1441b6df0 |
| ClientUpdateLevelStreamingStatus | 0x1427322b0 | 0x1441b6e00 |
| ClientUpdateMultipleLevelsStreamingStatus | 0x142732460 | 0x1441b6e10 |
| ClientVoiceHandshakeComplete | 0x142732510 | 0x1441b6e20 |
| ClientWasKicked | 0x142732530 | 0x1441b6e30 |
| ConsoleKey | 0x142732600 | 0x1441b6e40 |
| DeprojectMousePositionToWorld | 0x1427326f0 | 0x1441b6e50 |
| DeprojectScreenPositionToWorld | 0x1427327f0 | 0x1441b6e60 |
| EnableCheats | 0x142732970 | 0x1441b6e70 |
| FOV | 0x142732990 | 0x1441b6e80 |
| GetFocalLocation | 0x142732a10 | 0x1441b6e90 |
| GetHitResultUnderCursor | 0x142732a80 | 0x1441b6ea0 |
| GetHitResultUnderCursorByChannel | 0x142732be0 | 0x1441b6eb0 |
| GetHitResultUnderCursorForObjects | 0x142732d40 | 0x1441b6ec0 |
| GetHitResultUnderFinger | 0x142732ed0 | 0x1441b6ed0 |
| GetHitResultUnderFingerByChannel | 0x142733070 | 0x1441b6ee0 |
| GetHitResultUnderFingerForObjects | 0x142733210 | 0x1441b6ef0 |
| GetHUD | 0x142732a50 | 0x1441b6f00 |
| GetInputAnalogKeyState | 0x1427333e0 | 0x1441b6f10 |
| GetInputAnalogStickState | 0x1427334e0 | 0x1441b6f20 |
| GetInputKeyTimeDown | 0x142733600 | 0x1441b6f30 |
| GetInputMotionState | 0x142733700 | 0x1441b6f40 |
| GetInputMouseDelta | 0x142733890 | 0x1441b6f50 |
| GetInputTouchState | 0x142733970 | 0x1441b6f60 |
| GetInputVectorKeyState | 0x142733af0 | 0x1441b6f70 |
| GetMousePosition | 0x142733c00 | 0x1441b6f80 |
| GetSpectatorPawn | 0x142733cf0 | 0x1441b6f90 |
| GetViewportSize | 0x142733d10 | 0x1441b6fa0 |
| IsInputKeyDown | 0x142733df0 | 0x1441b6fb0 |
| LocalTravel | 0x142733ef0 | 0x1441b6fc0 |
| OnServerStartedVisualLogger | 0x142733fa0 | 0x1441b6fd0 |
| Pause | 0x142734030 | 0x1441b6fe0 |
| PlayDynamicForceFeedback | 0x142734050 | 0x1441b6ff0 |
| PlayHapticEffect | 0x1427342e0 | 0x1441b7000 |
| ProjectWorldLocationToScreen | 0x142734430 | 0x1441b7010 |
| RestartLevel | 0x142734560 | 0x1441b7020 |
| SendToConsole | 0x142734580 | 0x1441b7030 |
| ServerAcknowledgePossession | 0x142734630 | 0x1441b7040 |
| ServerCamera | 0x1427346f0 | 0x1441b7050 |
| ServerChangeName | 0x1427347b0 | 0x1441b7060 |
| ServerCheckClientPossession | 0x142734880 | 0x1441b7070 |
| ServerCheckClientPossessionReliable | 0x1427348d0 | 0x1441b7080 |
| ServerMutePlayer | 0x142734920 | 0x1441b7090 |
| ServerNotifyLoadedWorld | 0x142734a90 | 0x1441b70a0 |
| ServerPause | 0x142734b40 | 0x1441b70b0 |
| ServerRestartPlayer | 0x142734b90 | 0x1441b70c0 |
| ServerSetSpectatorLocation | 0x142734be0 | 0x1441b70d0 |
| ServerSetSpectatorWaiting | 0x142734d10 | 0x1441b70e0 |
| ServerShortTimeout | 0x142734dd0 | 0x1441b70f0 |
| ServerToggleAILogging | 0x142734e20 | 0x1441b7100 |
| ServerUnmutePlayer | 0x142734e70 | 0x1441b7110 |
| ServerUpdateCamera | 0x142734fe0 | 0x1441b7120 |
| ServerUpdateLevelVisibility | 0x142735100 | 0x1441b7130 |
| ServerUpdateMultipleLevelsVisibility | 0x1427351f0 | 0x1441b7140 |
| ServerVerifyViewTarget | 0x1427352b0 | 0x1441b7150 |
| ServerViewNextPlayer | 0x142735300 | 0x1441b7160 |
| ServerViewPrevPlayer | 0x142735350 | 0x1441b7170 |
| ServerViewSelf | 0x1427353a0 | 0x1441b7180 |
| SetAudioListenerAttenuationOverride | 0x1427354d0 | 0x1441b7190 |
| SetAudioListenerOverride | 0x1427355a0 | 0x1441b71a0 |
| SetCinematicMode | 0x1427356c0 | 0x1441b71b0 |
| SetControllerLightColor | 0x142735880 | 0x1441b71c0 |
| SetDisableHaptics | 0x1427358f0 | 0x1441b71d0 |
| SetHapticsByValue | 0x142735980 | 0x1441b71e0 |
| SetMouseCursorWidget | 0x142735a80 | 0x1441b71f0 |
| SetMouseLocation | 0x142735b40 | 0x1441b7200 |
| SetName | 0x142735c00 | 0x1441b7210 |
| SetViewTargetWithBlend | 0x142735cb0 | 0x1441b7220 |
| SetVirtualJoystickVisibility | 0x142735e30 | 0x1441b7230 |
| StartFire | 0x142735ec0 | 0x1441b7240 |
| StopHapticEffect | 0x142735f40 | 0x1441b7250 |
| SwitchLevel | 0x142735fc0 | 0x1441b7260 |
| ToggleSpeaking | 0x142736070 | 0x1441b7270 |
| WasInputKeyJustPressed | 0x142736100 | 0x1441b7280 |
| WasInputKeyJustReleased | 0x142736200 | 0x1441b7290 |

## PlayerState

Class params `0x1441bc860`; resolver `0x1413b05f0`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| bShouldUpdateReplicatedPing | Bool | 0x460 | 0x1451d4250 |
| PlayerNamePrivate | Str | 0x440 | 0x1451d3f18 |
| UniqueId | Struct | 0x3f8 | 0x1451d42d0 |
| SavedNetworkAddress | Str | 0x3e0 | 0x1451d3f98 |
| EngineMessageClass | Class | 0x3d0 | 0x1451d4310 |
| StartTime | Int | 0x3c8 | 0x1451d4298 |
| bFromPreviousLevel | Bool | unresolved | 0x1451d4390 |
| bIsInactive | Bool | unresolved | 0x1451d4410 |
| bIsABot | Bool | unresolved | 0x1451d4490 |
| bOnlySpectator | Bool | unresolved | 0x1451d4500 |
| bIsSpectator | Bool | unresolved | 0x1451d4570 |
| PlayerId | Int | 0x3c0 | 0x1451d4358 |
| PlayerName | Str | 0x3a0 | 0x1451d43d8 |
| Ping | Byte | 0x39c | 0x1451d45f0 |
| Score | Float | 0x398 | 0x1451d4458 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| GetPlayerName | 16 | 0x1451d3fd0 |
| OnRep_PlayerId | 0 | 0x1451d4050 |
| OnRep_PlayerName | 0 | 0x1451d4090 |
| OnRep_Score | 0 | 0x1451d40d0 |
| OnRep_UniqueId | 0 | 0x1451d4110 |
| OnRep_bIsInactive | 0 | 0x1451d4010 |
| ReceiveCopyProperties | 8 | 0x1451d4190 |
| ReceiveOverrideWith | 8 | 0x1451d4210 |

| Native function | Exec wrapper | Binding record |
|---|---|---|

## World

Class params `0x144200730`; resolver `0x14137a060`; size `unresolved`.

| Property | Type | Offset | Descriptor |
|---|---|---|---|
| WorldSingleton | Object | 0x8d8 | 0x145214c50 |
| PSCPool | Struct | 0x880 | 0x145214c90 |
| bAreConstraintsDirty | Bool | unresolved | 0x145214cd0 |
| WorldComposition | Object | 0x808 | 0x145214d50 |
| DeferredParameterStorage | Struct | 0x2c0 | 0x145214d90 |
| CanvasForDrawMaterialToRenderTarget | Object | 0x1b0 | 0x145214dd0 |
| CanvasForRenderingToTarget | Object | 0x1a8 | 0x145214e10 |
| ParameterCollectionInstances | Array | 0x198 | 0x145214958 |
| OwningGameInstance | Object | 0x190 | 0x145214e90 |
| CurrentLevel | Object | 0x188 | 0x145214ed0 |
| LevelCollections | Array | 0x170 | 0x1452149d8 |
| Levels | Array | 0x160 | 0x145214a58 |
| AvoidanceManager | Object | 0x158 | 0x145214f90 |
| AISystem | Object | 0x150 | 0x145214fd0 |
| GameState | Object | 0x148 | 0x145215010 |
| AuthorityGameMode | Object | 0x140 | 0x145215050 |
| NavigationSystem | Object | 0x138 | 0x145215090 |
| DefaultPhysicsVolume | Object | 0x118 | 0x1452150d0 |
| MyParticleEventManager | Object | 0x110 | 0x145215110 |
| DemoNetDriver | Object | 0x108 | 0x145215150 |
| CurrentLevelPendingInvisibility | Object | 0x100 | 0x145215190 |
| CurrentLevelPendingVisibility | Object | 0xf8 | 0x1452151d0 |
| StreamingLevelsPrefix | Str | 0xe8 | 0x145214ad8 |
| StreamingLevelsToConsider | Set | 0x98 | 0x145214bd8 |
| StreamingLevels | Array | 0x88 | 0x145214d18 |
| PerModuleDataObjects | Array | 0x78 | 0x145215290 |
| ExtraReferencedObjects | Array | 0x68 | 0x1452152c8 |
| PhysicsCollisionHandler | Object | 0x60 | 0x145215380 |
| NetworkManager | Object | 0x58 | 0x1452153c0 |
| ForegroundLineBatcher | Object | 0x50 | 0x145215400 |
| PersistentLineBatcher | Object | 0x48 | 0x145215440 |
| LineBatcher | Object | 0x40 | 0x145215480 |
| NetDriver | Object | 0x38 | 0x1452154c0 |
| PersistentLevel | Object | 0x30 | 0x145215500 |

| Function | Parameter bytes | Descriptor |
|---|---:|---|
| HandleTimelineScrubbed | 0 | 0x145214c10 |

| Native function | Exec wrapper | Binding record |
|---|---|---|
| HandleTimelineScrubbed | 0x142774100 | 0x144202ab0 |

