/* Partial reflected layouts for decompiler annotation only. */
/* Opaque gaps include unknown native state. Not a runtime SDK. */
/* Source SHA256: 41ab697b4edd3061baff37568de6e9501427374a859b048b3595f29297bfd306 */
typedef unsigned char ue420_byte;
#pragma pack(push, 1)

/* Class params 0x143d5f4f0; size 0x70. */
struct UE420_ConsoleSettings {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_MaxScrollbackSize[0x8]; /* +0x28: MaxScrollbackSize (Int, flags 0x10000000044001) */
    ue420_byte at_0030_ManualAutoCompleteList[0x10]; /* +0x30: ManualAutoCompleteList (Array, flags 0x10000000004001) */
    ue420_byte at_0040_AutoCompleteMapPaths[0x10]; /* +0x40: AutoCompleteMapPaths (Array, flags 0x10000000004001) */
    ue420_byte at_0050_BackgroundOpacityPercentage[0x4]; /* +0x50: BackgroundOpacityPercentage (Float, flags 0x10000000004001) */
    ue420_byte at_0054_bOrderTopToBottom[0x4]; /* +0x54: bOrderTopToBottom (Bool, flags 0x10000000004001) */
    ue420_byte at_0058_InputColor[0x4]; /* +0x58: InputColor (Struct, flags 0x10000000004001) */
    ue420_byte at_005c_HistoryColor[0x4]; /* +0x5c: HistoryColor (Struct, flags 0x10000000004001) */
    ue420_byte at_0060_AutoCompleteCommandColor[0x4]; /* +0x60: AutoCompleteCommandColor (Struct, flags 0x10000000004001) */
    ue420_byte at_0064_AutoCompleteCVarColor[0x4]; /* +0x64: AutoCompleteCVarColor (Struct, flags 0x10000000004001) */
    ue420_byte at_0068_AutoCompleteFadedColor[0x8]; /* +0x68: AutoCompleteFadedColor (Struct, flags 0x10000000004001) */
};

/* Class params 0x1440f3ae0; size 0x418. */
struct UE420_Controller {
    ue420_byte unknown_0000[0x3a0];
    ue420_byte at_03a0_PlayerState[0x10]; /* +0x3a0: PlayerState (Object, flags 0x10000100000034) */
    ue420_byte at_03b0_OnInstigatedAnyDamage[0x10]; /* +0x3b0: OnInstigatedAnyDamage (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_03c0_StateName[0x8]; /* +0x3c0: StateName (Name, flags 0x10000000000000) */
    ue420_byte at_03c8_Pawn[0x10]; /* +0x3c8: Pawn (Object, flags 0x40000100000020) */
    ue420_byte at_03d8_Character[0x8]; /* +0x3d8: Character (Object, flags 0x40000000000000) */
    ue420_byte at_03e0_TransformComponent[0x20]; /* +0x3e0: TransformComponent (Object, flags 0x40000000080008) */
    ue420_byte at_0400_ControlRotation[0x18]; /* +0x400: ControlRotation (Struct, flags 0x20080000000000) */
};

/* Class params 0x1440fd7e0; size 0xb70. */
struct UE420_DemoNetDriver {
    ue420_byte unknown_0000[0x5f0];
    ue420_byte at_05f0_RollbackNetStartupActors[0x3e4]; /* +0x5f0: RollbackNetStartupActors (Map, flags 0x10000000002000) */
    ue420_byte at_09d4_CheckpointSaveMaxMSPerFrame[0x34]; /* +0x9d4: CheckpointSaveMaxMSPerFrame (Float, flags 0x40000000004000) */
    ue420_byte at_0a08_bIsLocalReplay[0x168]; /* +0xa08: bIsLocalReplay (Bool, flags 0x10000000000000) */
};

/* Class params 0x143d5e700; size 0x108. */
struct UE420_GameMapsSettings {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_EditorStartupMap[0x18]; /* +0x28: EditorStartupMap (Struct, flags 0x10000000004001) */
    ue420_byte at_0040_LocalMapOptions[0x10]; /* +0x40: LocalMapOptions (Str, flags 0x10040000004001) */
    ue420_byte at_0050_TransitionMap[0x18]; /* +0x50: TransitionMap (Struct, flags 0x10040000004001) */
    ue420_byte at_0068_bUseSplitscreen[0x1]; /* +0x68: bUseSplitscreen (Bool, flags 0x10000000004001) */
    ue420_byte at_0069_TwoPlayerSplitscreenLayout[0x1]; /* +0x69: TwoPlayerSplitscreenLayout (Byte, flags 0x10000000004001) */
    ue420_byte at_006a_ThreePlayerSplitscreenLayout[0x1]; /* +0x6a: ThreePlayerSplitscreenLayout (Byte, flags 0x10000000004001) */
    ue420_byte at_006b_bOffsetPlayerGamepadIds[0x5]; /* +0x6b: bOffsetPlayerGamepadIds (Bool, flags 0x10000000004001) */
    ue420_byte at_0070_GameInstanceClass[0x18]; /* +0x70: GameInstanceClass (Struct, flags 0x10000002004001) */
    ue420_byte at_0088_GameDefaultMap[0x18]; /* +0x88: GameDefaultMap (Struct, flags 0x40000000004001) */
    ue420_byte at_00a0_ServerDefaultMap[0x18]; /* +0xa0: ServerDefaultMap (Struct, flags 0x40040000004001) */
    ue420_byte at_00b8_GlobalDefaultGameMode[0x18]; /* +0xb8: GlobalDefaultGameMode (Struct, flags 0x40000002004001) */
    ue420_byte at_00d0_GlobalDefaultServerGameMode[0x18]; /* +0xd0: GlobalDefaultServerGameMode (Struct, flags 0x40040000004001) */
    ue420_byte at_00e8_GameModeMapPrefixes[0x10]; /* +0xe8: GameModeMapPrefixes (Array, flags 0x40040000004001) */
    ue420_byte at_00f8_GameModeClassAliases[0x10]; /* +0xf8: GameModeClassAliases (Array, flags 0x40040000004001) */
};

/* Class params 0x144117b30; size 0x480. */
struct UE420_GameMode {
    ue420_byte unknown_0000[0x438];
    ue420_byte at_0438_MatchState[0xc]; /* +0x438: MatchState (Name, flags 0x20080000002000) */
    ue420_byte at_0444_NumSpectators[0x4]; /* +0x444: NumSpectators (Int, flags 0x10000000000014) */
    ue420_byte at_0448_NumPlayers[0x4]; /* +0x448: NumPlayers (Int, flags 0x10000000000014) */
    ue420_byte at_044c_NumBots[0x4]; /* +0x44c: NumBots (Int, flags 0x10000000000014) */
    ue420_byte at_0450_MinRespawnDelay[0x4]; /* +0x450: MinRespawnDelay (Float, flags 0x10000000000015) */
    ue420_byte at_0454_NumTravellingPlayers[0x4]; /* +0x454: NumTravellingPlayers (Int, flags 0x10000000000014) */
    ue420_byte at_0458_EngineMessageClass[0x8]; /* +0x458: EngineMessageClass (Class, flags 0x14000000000000) */
    ue420_byte at_0460_InactivePlayerArray[0x10]; /* +0x460: InactivePlayerArray (Array, flags 0x10000000000000) */
    ue420_byte at_0470_InactivePlayerStateLifeSpan[0x4]; /* +0x470: InactivePlayerStateLifeSpan (Float, flags 0x20080000000001) */
    ue420_byte at_0474_MaxInactivePlayers[0x4]; /* +0x474: MaxInactivePlayers (Int, flags 0x20080000000001) */
    ue420_byte at_0478_bHandleDedicatedServerReplays[0x8]; /* +0x478: bHandleDedicatedServerReplays (Bool, flags 0x20080000004000) */
};

/* Class params 0x144167240; size 0x1c8. */
struct UE420_LocalPlayer {
    ue420_byte unknown_0000[0x70];
    ue420_byte at_0070_ViewportClient[0x24]; /* +0x70: ViewportClient (Object, flags 0x10000000000000) */
    ue420_byte at_0094_AspectRatioAxisConstraint[0x4]; /* +0x94: AspectRatioAxisConstraint (Byte, flags 0x10000000004000) */
    ue420_byte at_0098_PendingLevelPlayerControllerClass[0x70]; /* +0x98: PendingLevelPlayerControllerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0108_ControllerId[0xc0]; /* +0x108: ControllerId (Int, flags 0x40000000000000) */
};

/* Class params 0x14396cfe0; size 0x1f0. */
struct UE420_MBAFKManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_KickTime[0x4]; /* +0x28: KickTime (Float, flags 0x40000000000001) */
    ue420_byte at_002c_MenuKickTime[0x4]; /* +0x2c: MenuKickTime (Float, flags 0x40000000000001) */
    ue420_byte at_0030_LastChanceCountdown[0x4]; /* +0x30: LastChanceCountdown (Float, flags 0x40000000000001) */
    ue420_byte at_0034_ActivationTimeOnJoin[0x4]; /* +0x34: ActivationTimeOnJoin (Float, flags 0x40000000000001) */
    ue420_byte at_0038_WorldSingleton[0x8]; /* +0x38: WorldSingleton (Object, flags 0x40000000002000) */
    ue420_byte at_0040_GameInstance[0x8]; /* +0x40: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0048_LocalPlayerInfo[0x1a0]; /* +0x48: LocalPlayerInfo (Struct, flags 0x40000000002000) */
    ue420_byte at_01e8_bWasMatchInProgress[0x8]; /* +0x1e8: bWasMatchInProgress (Bool, flags 0x40000000002000) */
};

/* Class params 0x14396d230; size 0x2f8. */
struct UE420_MBAFKWarningOverlay {
    ue420_byte unknown_0000[0x2d8];
    ue420_byte at_02d8_AFKManager[0x8]; /* +0x2d8: AFKManager (Object, flags 0x40000000002000) */
    ue420_byte at_02e0_GameInstance[0x8]; /* +0x2e0: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_02e8_LastChanceCountdownTimerHandle[0x8]; /* +0x2e8: LastChanceCountdownTimerHandle (Struct, flags 0x40000000002000) */
    ue420_byte at_02f0_LastChanceCountdown[0x8]; /* +0x2f0: LastChanceCountdown (Int, flags 0x40000000002000) */
};

/* Class params 0x14396a110; size 0xb8. */
struct UE420_MBAchievementsManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_LocalPlayerId[0x28]; /* +0x30: LocalPlayerId (Struct, flags 0x40000000002000) */
    ue420_byte at_0058_GameInstance[0x60]; /* +0x58: GameInstance (Object, flags 0x40000000002000) */
};

/* Class params 0x143981db0; size 0x3a8. */
struct UE420_MBBaseReticleActor {
    ue420_byte unknown_0000[0x398];
    ue420_byte at_0398_ReticleWidget[0x8]; /* +0x398: ReticleWidget (Object, flags 0x1000000009001d) */
    ue420_byte at_03a0_PlayerController[0x8]; /* +0x3a0: PlayerController (Object, flags 0x20080000002000) */
};

/* Class params 0x14448ab40; size 0x40. */
struct UE420_MBCaptureFlagManagerData {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_NumCapsRequiredToWin[0x4]; /* +0x30: NumCapsRequiredToWin (Int, flags 0x10000000000015) */
    ue420_byte at_0034_NumRemainingCapsWhenMatchmakingClosed[0x4]; /* +0x34: NumRemainingCapsWhenMatchmakingClosed (Int, flags 0x10000000000001) */
    ue420_byte at_0038_CapsGapWhenMatchmakingClosed[0x8]; /* +0x38: CapsGapWhenMatchmakingClosed (Int, flags 0x10000000000001) */
};

/* Class params 0x14448c690; size 0xad8. */
struct UE420_MBCapturePointManagerData {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_PointsOnPlayerDeath[0x4]; /* +0x30: PointsOnPlayerDeath (Int, flags 0x10000000000015) */
    ue420_byte at_0034_PointsOnMinionEnemyPortal[0x4]; /* +0x34: PointsOnMinionEnemyPortal (Int, flags 0x10000000000015) */
    ue420_byte at_0038_PointsOnCapturePointTick[0x4]; /* +0x38: PointsOnCapturePointTick (Int, flags 0x10000000000015) */
    ue420_byte at_003c_PointsOnCapturePointCaptured[0x4]; /* +0x3c: PointsOnCapturePointCaptured (Int, flags 0x10000000000015) */
    ue420_byte at_0040_GivePlayersCurrencyOverTime[0x4]; /* +0x40: GivePlayersCurrencyOverTime (Bool, flags 0x10000000000015) */
    ue420_byte at_0044_GivePlayersCurrencyCooldown[0x4]; /* +0x44: GivePlayersCurrencyCooldown (Float, flags 0x10000000000015) */
    ue420_byte at_0048_GivePlayersCurrencyAmount[0x4]; /* +0x48: GivePlayersCurrencyAmount (Int, flags 0x10000000000015) */
    ue420_byte at_004c_PointsRequiredToWin[0x4]; /* +0x4c: PointsRequiredToWin (Int, flags 0x10000000000001) */
    ue420_byte at_0050_PointsRequiredToWinOnOvertime[0x4]; /* +0x50: PointsRequiredToWinOnOvertime (Int, flags 0x10000000000001) */
    ue420_byte at_0054_NumRemainingPointsWhenMatchmakingClosed[0x4]; /* +0x54: NumRemainingPointsWhenMatchmakingClosed (Int, flags 0x10000000000001) */
    ue420_byte at_0058_PointsGapWhenMatchmakingClosed[0x4]; /* +0x58: PointsGapWhenMatchmakingClosed (Int, flags 0x10000000000001) */
    ue420_byte at_005c_NumCapturePoints[0x4]; /* +0x5c: NumCapturePoints (Int, flags 0x10000000000015) */
    ue420_byte at_0060_NumPointsToActivateEachRound[0x10]; /* +0x60: NumPointsToActivateEachRound (Array, flags 0x10000000000015) */
    ue420_byte at_0070_NumPointsRemainingWaves[0x10]; /* +0x70: NumPointsRemainingWaves (Array, flags 0x10000000000015) */
    ue420_byte at_0080_CustomObjectiveActivationList[0x10]; /* +0x80: CustomObjectiveActivationList (Struct, flags 0x10000000000001) */
    ue420_byte at_0090_KingOfTheHill[0x1]; /* +0x90: KingOfTheHill (Bool, flags 0x10000000000015) */
    ue420_byte at_0091_CycleCapturePoints[0x3]; /* +0x91: CycleCapturePoints (Bool, flags 0x10000000000015) */
    ue420_byte at_0094_CycleWaitInitial[0x4]; /* +0x94: CycleWaitInitial (Float, flags 0x10000000000015) */
    ue420_byte at_0098_bInfiniteCycleActiveTime[0x4]; /* +0x98: bInfiniteCycleActiveTime (Bool, flags 0x10000000000015) */
    ue420_byte at_009c_CycleActiveTime[0x4]; /* +0x9c: CycleActiveTime (Float, flags 0x10000000000015) */
    ue420_byte at_00a0_CycleInactiveTime[0x4]; /* +0xa0: CycleInactiveTime (Float, flags 0x10000000000015) */
    ue420_byte at_00a4_SelectNextCapturePointsTimeThreshold[0x4]; /* +0xa4: SelectNextCapturePointsTimeThreshold (Float, flags 0x10000000000015) */
    ue420_byte at_00a8_bUseMaxAcheivablePoints[0x4]; /* +0xa8: bUseMaxAcheivablePoints (Bool, flags 0x10000000000015) */
    ue420_byte at_00ac_MaxAcheivablePoints[0x4]; /* +0xac: MaxAcheivablePoints (Int, flags 0x10000000000015) */
    ue420_byte at_00b0_NumRemainingPointsNearlyEndedVO[0x4]; /* +0xb0: NumRemainingPointsNearlyEndedVO (Int, flags 0x10000000000001) */
    ue420_byte at_00b4_PointsGapForCloseGame[0x4]; /* +0xb4: PointsGapForCloseGame (Int, flags 0x10000000000001) */
    ue420_byte at_00b8_NearlyWonVO[0x350]; /* +0xb8: NearlyWonVO (Struct, flags 0x10000000000001) */
    ue420_byte at_0408_NearlyLostVO[0x350]; /* +0x408: NearlyLostVO (Struct, flags 0x10000000000001) */
    ue420_byte at_0758_CloseScoreVO[0x350]; /* +0x758: CloseScoreVO (Struct, flags 0x10000000000001) */
    ue420_byte at_0aa8_EnemyStartCaptureVO[0x10]; /* +0xaa8: EnemyStartCaptureVO (Array, flags 0x10000000000001) */
    ue420_byte at_0ab8_EnemyFinishCaptureVO[0x10]; /* +0xab8: EnemyFinishCaptureVO (Array, flags 0x10000000000001) */
    ue420_byte at_0ac8_AllyFinishCaptureVO[0x10]; /* +0xac8: AllyFinishCaptureVO (Array, flags 0x10000000000001) */
};

/* Class params 0x144488290; size 0x1b8. */
struct UE420_MBCapturePointManagerState {
    ue420_byte unknown_0000[0x90];
    ue420_byte at_0090_Points[0x10]; /* +0x90: Points (Array, flags 0x10000000000014) */
    ue420_byte at_00a0_CapturePointTimer[0x4]; /* +0xa0: CapturePointTimer (Float, flags 0x10000000000014) */
    ue420_byte at_00a4_CapturePointsActive[0x4]; /* +0xa4: CapturePointsActive (Bool, flags 0x10000000000014) */
    ue420_byte at_00a8_NumTimesCyclicCapturePointsActive[0x4]; /* +0xa8: NumTimesCyclicCapturePointsActive (Int, flags 0x10000000000014) */
    ue420_byte at_00ac_GiveCurrencyTimer[0x4]; /* +0xac: GiveCurrencyTimer (Float, flags 0x40000000000000) */
    ue420_byte at_00b0_CurrentRound[0x4]; /* +0xb0: CurrentRound (Int, flags 0x40000000000000) */
    ue420_byte at_00b4_PointsRequiredToWinOverride[0x4]; /* +0xb4: PointsRequiredToWinOverride (Int, flags 0x40000000000000) */
    ue420_byte at_00b8_CurrentControlPointsIndices[0x10]; /* +0xb8: CurrentControlPointsIndices (Array, flags 0x40000000000000) */
    ue420_byte at_00c8_NextControlPointsIndices[0x10]; /* +0xc8: NextControlPointsIndices (Array, flags 0x40000000000000) */
    ue420_byte at_00d8_PreviousSingleActiveControlPointIndex[0x8]; /* +0xd8: PreviousSingleActiveControlPointIndex (Int, flags 0x40000000000000) */
    ue420_byte at_00e0_NumPointsToActivateEachRoundOverride[0x10]; /* +0xe0: NumPointsToActivateEachRoundOverride (Array, flags 0x40000000000000) */
    ue420_byte at_00f0_CapturePointTeamIds[0x10]; /* +0xf0: CapturePointTeamIds (Array, flags 0x40000000000000) */
    ue420_byte at_0100_CapturePoints[0x10]; /* +0x100: CapturePoints (Array, flags 0x2040000000000000) */
    ue420_byte at_0110_OnCapturedMulticasters[0x10]; /* +0x110: OnCapturedMulticasters (Array, flags 0x2040008000000000) */
    ue420_byte at_0120_OnLostMulticasters[0x10]; /* +0x120: OnLostMulticasters (Array, flags 0x2040008000000000) */
    ue420_byte at_0130_OnEnteredMulticasters[0x10]; /* +0x130: OnEnteredMulticasters (Array, flags 0x2040008000000000) */
    ue420_byte at_0140_OnExitedMulticasters[0x10]; /* +0x140: OnExitedMulticasters (Array, flags 0x2040008000000000) */
    ue420_byte at_0150_bIsActive[0x1]; /* +0x150: bIsActive (Bool, flags 0x40000000000000) */
    ue420_byte at_0151_bSetInitialCycle[0x1]; /* +0x151: bSetInitialCycle (Bool, flags 0x40000000000000) */
    ue420_byte at_0152_bAllowPlayerSlotRefilling[0x1]; /* +0x152: bAllowPlayerSlotRefilling (Bool, flags 0x40000000000000) */
    ue420_byte at_0153_bPlayedNearlyEndedVO[0x1]; /* +0x153: bPlayedNearlyEndedVO (Bool, flags 0x40000000000000) */
    ue420_byte at_0154_bPauseTimer[0x4]; /* +0x154: bPauseTimer (Bool, flags 0x40000000000000) */
    ue420_byte at_0158_TimerDelegates[0x10]; /* +0x158: TimerDelegates (Array, flags 0x40008000000000) */
    ue420_byte at_0168_PhaseEndDelegates[0x10]; /* +0x168: PhaseEndDelegates (Array, flags 0x40008000000000) */
    ue420_byte at_0178_PointsReachedDelegates[0x10]; /* +0x178: PointsReachedDelegates (Array, flags 0x40008000000000) */
    ue420_byte at_0188_PointsActivated[0x10]; /* +0x188: PointsActivated (MulticastDelegate, flags 0x2040000000080000) */
    ue420_byte at_0198_bIsOvertime[0x1]; /* +0x198: bIsOvertime (Bool, flags 0x40000000000000) */
    ue420_byte at_0199_bKioskModeEndGame[0x3]; /* +0x199: bKioskModeEndGame (Bool, flags 0x40000000000000) */
    ue420_byte at_019c_CurrentWaveIndex[0x4]; /* +0x19c: CurrentWaveIndex (Int, flags 0x40000000000000) */
    ue420_byte at_01a0_bSelectNextCapturePointsPending[0x1]; /* +0x1a0: bSelectNextCapturePointsPending (Bool, flags 0x40000000000000) */
    ue420_byte at_01a1_bInfiniteCycleActiveTime[0x7]; /* +0x1a1: bInfiniteCycleActiveTime (Bool, flags 0x40000000000000) */
    ue420_byte at_01a8_PointsOnPlayerDeathConditions[0x10]; /* +0x1a8: PointsOnPlayerDeathConditions (Array, flags 0x40000000000000) */
};

/* Class params 0x143997eb0; size 0x400. */
struct UE420_MBCapturePointManagerWidget {
    ue420_byte unknown_0000[0x390];
    ue420_byte at_0390_CapturePointIconWidgets[0x10]; /* +0x390: CapturePointIconWidgets (Array, flags 0x1000800000000c) */
    ue420_byte at_03a0_CapturePointManagerProxy[0x8]; /* +0x3a0: CapturePointManagerProxy (Object, flags 0x10000000002014) */
    ue420_byte at_03a8_AllyTeamPoints[0x4]; /* +0x3a8: AllyTeamPoints (Int, flags 0x10000000002014) */
    ue420_byte at_03ac_EnemyTeamPoints[0x4]; /* +0x3ac: EnemyTeamPoints (Int, flags 0x10000000002014) */
    ue420_byte at_03b0_PointsRequiredToWin[0x4]; /* +0x3b0: PointsRequiredToWin (Int, flags 0x10000000002014) */
    ue420_byte at_03b4_NumCapturePointsOwnedByAllies[0x4]; /* +0x3b4: NumCapturePointsOwnedByAllies (Int, flags 0x10000000002014) */
    ue420_byte at_03b8_NumCapturePointsOwnedByEnemies[0x8]; /* +0x3b8: NumCapturePointsOwnedByEnemies (Int, flags 0x10000000002014) */
    ue420_byte at_03c0_CapturePointWidgetData[0x10]; /* +0x3c0: CapturePointWidgetData (Array, flags 0x10000000002014) */
    ue420_byte at_03d0_PreMatchCountdownTimerInt[0x4]; /* +0x3d0: PreMatchCountdownTimerInt (Int, flags 0x10000000002014) */
    ue420_byte at_03d4_CapturePointTimerInt[0x4]; /* +0x3d4: CapturePointTimerInt (Int, flags 0x10000000002014) */
    ue420_byte at_03d8_bCapturePointsActive[0x1]; /* +0x3d8: bCapturePointsActive (Bool, flags 0x10000000002014) */
    ue420_byte at_03d9_bGameStarted[0x3]; /* +0x3d9: bGameStarted (Bool, flags 0x10000000002014) */
    ue420_byte at_03dc_AllyTeamPointsLastFrame[0x4]; /* +0x3dc: AllyTeamPointsLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03e0_EnemyTeamPointsLastFrame[0x4]; /* +0x3e0: EnemyTeamPointsLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03e4_PointsRequiredToWinLastFrame[0x4]; /* +0x3e4: PointsRequiredToWinLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03e8_AllyTeamIdLastFrame[0x4]; /* +0x3e8: AllyTeamIdLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03ec_PreMatchCountdownTimerIntLastFrame[0x4]; /* +0x3ec: PreMatchCountdownTimerIntLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03f0_CapturePointTimerIntLastFrame[0x6]; /* +0x3f0: CapturePointTimerIntLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_03f6_bGameStartedLastFrame[0x1]; /* +0x3f6: bGameStartedLastFrame (Bool, flags 0x40000000002000) */
    ue420_byte at_03f7_bInitialised[0x1]; /* +0x3f7: bInitialised (Bool, flags 0x40000000002000) */
    ue420_byte at_03f8_bIsWaitingForPlayersLastFrame[0x1]; /* +0x3f8: bIsWaitingForPlayersLastFrame (Bool, flags 0x40000000002000) */
    ue420_byte at_03f9_bInfiniteCycleActiveTimeLastFrame[0x7]; /* +0x3f9: bInfiniteCycleActiveTimeLastFrame (Bool, flags 0x40000000002000) */
};

/* Class params 0x1444b0bf0; size 0xe0. */
struct UE420_MBCommonLevelObjectActorState {
    ue420_byte unknown_0000[0x88];
    ue420_byte at_0088_GameModeManagerObj[0x8]; /* +0x88: GameModeManagerObj (Object, flags 0x2040000000000000) */
    ue420_byte at_0090_TeamInfoArray[0x10]; /* +0x90: TeamInfoArray (Array, flags 0x40000000000000) */
    ue420_byte at_00a0_TeamStatsArray[0x10]; /* +0xa0: TeamStatsArray (Array, flags 0x40000000000000) */
    ue420_byte at_00b0_NextSpawnPointIndex[0x4]; /* +0xb0: NextSpawnPointIndex (Int, flags 0x40000000000000) */
    ue420_byte at_00b4_WinningTeam[0x4]; /* +0xb4: WinningTeam (Int, flags 0x40000000000000) */
    ue420_byte at_00b8_AssignedSpawnPoints[0x10]; /* +0xb8: AssignedSpawnPoints (Array, flags 0x40000000000000) */
    ue420_byte at_00c8_GameStartFrameNumber[0x4]; /* +0xc8: GameStartFrameNumber (Int, flags 0x40000000000000) */
    ue420_byte at_00cc_GameTimer[0x4]; /* +0xcc: GameTimer (Float, flags 0x40000000000000) */
    ue420_byte at_00d0_GlobalTimeDilation[0x4]; /* +0xd0: GlobalTimeDilation (Float, flags 0x40000000000000) */
    ue420_byte at_00d4_EndGameTimeDilationTimer[0x4]; /* +0xd4: EndGameTimeDilationTimer (Float, flags 0x40000000000000) */
    ue420_byte at_00d8_bGameStarted[0x1]; /* +0xd8: bGameStarted (Bool, flags 0x40000000000000) */
    ue420_byte at_00d9_bGameEnded[0x1]; /* +0xd9: bGameEnded (Bool, flags 0x40000000000000) */
    ue420_byte at_00da_bAllowPlayerSlotRefilling[0x6]; /* +0xda: bAllowPlayerSlotRefilling (Bool, flags 0x40000000000000) */
};

/* Class params 0x1439a83e0; size 0x50. */
struct UE420_MBConnectionManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_WorldSingleton[0x8]; /* +0x28: WorldSingleton (Object, flags 0x40000000002000) */
    ue420_byte at_0030_GameInstance[0x8]; /* +0x30: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0038_PlayerInfos[0x10]; /* +0x38: PlayerInfos (Array, flags 0x40000000002000) */
    ue420_byte at_0048_bDisconnectWarningShown[0x8]; /* +0x48: bDisconnectWarningShown (Bool, flags 0x40000000002000) */
};

/* Class params 0x1439aae40; size 0x1c8. */
struct UE420_MBCrowdManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_CrowdEventData[0x50]; /* +0x30: CrowdEventData (Map, flags 0x10000000000015) */
    ue420_byte at_0080_LocalPlayerNearbyEvent[0x10]; /* +0x80: LocalPlayerNearbyEvent (Struct, flags 0x10000000000001) */
    ue420_byte at_0090_LocalPlayerKillstreakEvent[0x8]; /* +0x90: LocalPlayerKillstreakEvent (Struct, flags 0x10000000000001) */
    ue420_byte at_0098_CrowdList[0x10]; /* +0x98: CrowdList (Array, flags 0x20080000000000) */
    ue420_byte at_00a8_VisualEventList[0x50]; /* +0xa8: VisualEventList (Map, flags 0x20080000000000) */
    ue420_byte at_00f8_WorldSingleton[0x8]; /* +0xf8: WorldSingleton (Object, flags 0x20080000000000) */
    ue420_byte at_0100_GameInstance[0x8]; /* +0x100: GameInstance (Object, flags 0x20080000000000) */
    ue420_byte at_0108_ActorMessageHandlers[0xc0]; /* +0x108: ActorMessageHandlers (Array, flags 0x20080000002000) */
};

/* Class params 0x1439aea40; size 0x288. */
struct UE420_MBCustomGameManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_OnSessionUpdated[0x10]; /* +0x28: OnSessionUpdated (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0038_OnCustomGameNameChanged[0x10]; /* +0x38: OnCustomGameNameChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0048_OnCustomGameTeamNameChanged[0x10]; /* +0x48: OnCustomGameTeamNameChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0058_OnMemberTeamChanged[0x10]; /* +0x58: OnMemberTeamChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0068_OnMemberSetTeamRequestFailed[0x10]; /* +0x68: OnMemberSetTeamRequestFailed (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0078_OnlineSessionManager[0x8]; /* +0x78: OnlineSessionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0080_MemberList[0x60]; /* +0x80: MemberList (Array, flags 0x40000000000000) */
    ue420_byte at_00e0_Teams[0x30]; /* +0xe0: Teams (Struct, flags 0x40000000000000) */
    ue420_byte at_0110_SpectatorTeam[0x18]; /* +0x110: SpectatorTeam (Struct, flags 0x40000000000000) */
    ue420_byte at_0128_MapRoster[0x10]; /* +0x128: MapRoster (Array, flags 0x40000000000000) */
    ue420_byte at_0138_CurrentMapIndex[0x8]; /* +0x138: CurrentMapIndex (Int, flags 0x40000000000000) */
    ue420_byte at_0140_CachedMapRosterString[0x10]; /* +0x140: CachedMapRosterString (Str, flags 0x40000000000000) */
    ue420_byte at_0150_LastServerAddress[0x10]; /* +0x150: LastServerAddress (Str, flags 0x40000000000000) */
    ue420_byte at_0160_GameName[0x10]; /* +0x160: GameName (Str, flags 0x40000000000000) */
    ue420_byte at_0170_Privacy[0x4]; /* +0x170: Privacy (Enum, flags 0x40000000000000) */
    ue420_byte at_0174_MaxMapRosterSize[0x4]; /* +0x174: MaxMapRosterSize (Int, flags 0x40000000000000) */
    ue420_byte at_0178_bTeamsLocked[0x1]; /* +0x178: bTeamsLocked (Bool, flags 0x40000000000000) */
    ue420_byte at_0179_bIsLobbyLeader[0x1]; /* +0x179: bIsLobbyLeader (Bool, flags 0x40000000000000) */
    ue420_byte at_017a_bCreateSessionPending[0x1]; /* +0x17a: bCreateSessionPending (Bool, flags 0x40000000000000) */
    ue420_byte at_017b_bShowCustomGameDebug[0x1]; /* +0x17b: bShowCustomGameDebug (Bool, flags 0x40000000000000) */
    ue420_byte at_017c_bAcceptInvitePending[0x4]; /* +0x17c: bAcceptInvitePending (Bool, flags 0x40000000000000) */
    ue420_byte at_0180_PendingPlayerIdRequests[0x10]; /* +0x180: PendingPlayerIdRequests (Array, flags 0x40000000002000) */
    ue420_byte at_0190_Participants[0xf8]; /* +0x190: Participants (Array, flags 0x40000000002000) */
};

/* Class params 0x1439bc120; size 0x488. */
struct UE420_MBCustomQueueMenu {
    ue420_byte unknown_0000[0x448];
    ue420_byte at_0448_SavedCustomQueue[0x40]; /* +0x448: SavedCustomQueue (Str, flags 0xa0080000006014) */
};

/* Class params 0x1439ba260; size 0x800. */
struct UE420_MBDeathReplayManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_PlayerClassAssetType[0x8]; /* +0x30: PlayerClassAssetType (Name, flags 0x10000000000001) */
    ue420_byte at_0038_DeathReplayDurationBeforeEndOfDeathSloMo[0x4]; /* +0x38: DeathReplayDurationBeforeEndOfDeathSloMo (Float, flags 0x10000000000001) */
    ue420_byte at_003c_DeathReplayDurationAfterEndOfDeathSloMo[0x4]; /* +0x3c: DeathReplayDurationAfterEndOfDeathSloMo (Float, flags 0x10000000000001) */
    ue420_byte at_0040_ContactTagCheckForVictimPOVTrackingAttacker[0x40]; /* +0x40: ContactTagCheckForVictimPOVTrackingAttacker (Struct, flags 0x10000000000001) */
    ue420_byte at_0080_ContactTagCheckForVictimPOVTrackingMinion[0x40]; /* +0x80: ContactTagCheckForVictimPOVTrackingMinion (Struct, flags 0x10000000000001) */
    ue420_byte at_00c0_CloseRangeKillMaxDistance[0x8]; /* +0xc0: CloseRangeKillMaxDistance (Float, flags 0x10000000000001) */
    ue420_byte at_00c8_CloseRangeKillContactTagCheck[0x40]; /* +0xc8: CloseRangeKillContactTagCheck (Struct, flags 0x10000000000001) */
    ue420_byte at_0108_CloseRangeKillFrameSloMo[0x28]; /* +0x108: CloseRangeKillFrameSloMo (Struct, flags 0x10000000000001) */
    ue420_byte at_0130_LongRangeKillMinDistance[0x8]; /* +0x130: LongRangeKillMinDistance (Float, flags 0x10000000000001) */
    ue420_byte at_0138_LongRangeKillContactTagCheck[0x40]; /* +0x138: LongRangeKillContactTagCheck (Struct, flags 0x10000000000001) */
    ue420_byte at_0178_LongRangeKillNoCastContactTagCheck[0x40]; /* +0x178: LongRangeKillNoCastContactTagCheck (Struct, flags 0x10000000000001) */
    ue420_byte at_01b8_MinTelegraphTimeForLongRangeCast[0x8]; /* +0x1b8: MinTelegraphTimeForLongRangeCast (Float, flags 0x10000000000001) */
    ue420_byte at_01c0_LongRangeCastFrameSloMo[0x28]; /* +0x1c0: LongRangeCastFrameSloMo (Struct, flags 0x10000000000001) */
    ue420_byte at_01e8_LongRangeKillFrameSloMo[0x28]; /* +0x1e8: LongRangeKillFrameSloMo (Struct, flags 0x10000000000001) */
    ue420_byte at_0210_DefaultKillFrameSloMo[0x70]; /* +0x210: DefaultKillFrameSloMo (Struct, flags 0x10000000000001) */
    ue420_byte at_0280_World[0x8]; /* +0x280: World (Object, flags 0x40000000000000) */
    ue420_byte at_0288_WorldSingleton[0x8]; /* +0x288: WorldSingleton (Object, flags 0x40000000000000) */
    ue420_byte at_0290_PlayerAssetHandler[0x8]; /* +0x290: PlayerAssetHandler (Object, flags 0x40000000000000) */
    ue420_byte at_0298_ReplayInputPredictor[0x8]; /* +0x298: ReplayInputPredictor (Object, flags 0x40000000000000) */
    ue420_byte at_02a0_BackgroundEngineInterface[0x8]; /* +0x2a0: BackgroundEngineInterface (Object, flags 0x40000000000000) */
    ue420_byte at_02a8_ReplayCameraManager[0x8]; /* +0x2a8: ReplayCameraManager (Object, flags 0x40000000000000) */
    ue420_byte at_02b0_DeathReplayBufferStream[0x48]; /* +0x2b0: DeathReplayBufferStream (Struct, flags 0x40000000000000) */
    ue420_byte at_02f8_DeathReplayBufferPlayback[0xe8]; /* +0x2f8: DeathReplayBufferPlayback (Struct, flags 0x40000000000000) */
    ue420_byte at_03e0_LastLocalPlayerDeath[0x50]; /* +0x3e0: LastLocalPlayerDeath (Struct, flags 0x40000000000000) */
    ue420_byte at_0430_DeathReplayEventTimeline[0x18]; /* +0x430: DeathReplayEventTimeline (Struct, flags 0x40000000000000) */
    ue420_byte at_0448_DeathReplayLoadingSchedule[0xa8]; /* +0x448: DeathReplayLoadingSchedule (Struct, flags 0x40000000000000) */
    ue420_byte at_04f0_DeathReplayStartFrame[0x4]; /* +0x4f0: DeathReplayStartFrame (Int, flags 0x40000000000000) */
    ue420_byte at_04f4_LastDeathReplayFrameNumber[0x4]; /* +0x4f4: LastDeathReplayFrameNumber (Int, flags 0x40000000000000) */
    ue420_byte at_04f8_PendingDeathReplayLoadFrame[0x8]; /* +0x4f8: PendingDeathReplayLoadFrame (Int, flags 0x40000000000000) */
    ue420_byte at_0500_ProcessedLoadFrames[0x50]; /* +0x500: ProcessedLoadFrames (Set, flags 0x40000000000000) */
    ue420_byte at_0550_DeathReplayTimer[0x4]; /* +0x550: DeathReplayTimer (Float, flags 0x40000000000000) */
    ue420_byte at_0554_DeathReplayDuration[0x4]; /* +0x554: DeathReplayDuration (Float, flags 0x40000000000000) */
    ue420_byte at_0558_DeathReplayState[0x8]; /* +0x558: DeathReplayState (Enum, flags 0x40000000000000) */
    ue420_byte at_0560_DeathReplayInfo[0x218]; /* +0x560: DeathReplayInfo (Struct, flags 0x40000000000000) */
    ue420_byte at_0778_PlayerIds[0x10]; /* +0x778: PlayerIds (Array, flags 0x40000000000000) */
    ue420_byte at_0788_NextTimeDilationKey[0x8]; /* +0x788: NextTimeDilationKey (Int, flags 0x40000000000000) */
    ue420_byte at_0790_ActiveTimeDilationHandles[0x50]; /* +0x790: ActiveTimeDilationHandles (Map, flags 0x40000000000000) */
    ue420_byte at_07e0_LatestRollbackEngine[0xc]; /* +0x7e0: LatestRollbackEngine (Object, flags 0x40000000000000) */
    ue420_byte at_07ec_bDeathReplayPending[0x1]; /* +0x7ec: bDeathReplayPending (Bool, flags 0x40000000000000) */
    ue420_byte at_07ed_bDeathReplayCameraSetupPending[0x1]; /* +0x7ed: bDeathReplayCameraSetupPending (Bool, flags 0x40000000000000) */
    ue420_byte at_07ee_bValidDeathReplayInfo[0x1]; /* +0x7ee: bValidDeathReplayInfo (Bool, flags 0x40000000000000) */
    ue420_byte at_07ef_bSupportsPlayback[0x1]; /* +0x7ef: bSupportsPlayback (Bool, flags 0x40000000000000) */
    ue420_byte at_07f0_bDelayedStateChangePending[0x1]; /* +0x7f0: bDelayedStateChangePending (Bool, flags 0x40000000000000) */
    ue420_byte at_07f1_bIsChangingState[0x1]; /* +0x7f1: bIsChangingState (Bool, flags 0x40000000000000) */
    ue420_byte at_07f2_bReplayBufferDisabled[0x6]; /* +0x7f2: bReplayBufferDisabled (Bool, flags 0x40000000000000) */
    ue420_byte at_07f8_DelayedStateChangeTimerHandle[0x8]; /* +0x7f8: DelayedStateChangeTimerHandle (Struct, flags 0x40000000000000) */
};

/* Class params 0x1439c96c0; size 0x70. */
struct UE420_MBEventsManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_GameInstance[0x8]; /* +0x28: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0030_PopupScreenClassName[0x18]; /* +0x30: PopupScreenClassName (Struct, flags 0x40000000004000) */
    ue420_byte at_0048_PopupScreenClass[0x8]; /* +0x48: PopupScreenClass (Class, flags 0x44000000000000) */
    ue420_byte at_0050_PopupScreen[0x20]; /* +0x50: PopupScreen (Object, flags 0x40000000080008) */
};

/* Class params 0x1439cab20; size 0x548. */
struct UE420_MBFECustomGameMapSlotButton {
    ue420_byte unknown_0000[0x478];
    ue420_byte at_0478_Controller_ClearMap[0x18]; /* +0x478: Controller_ClearMap (Struct, flags 0x10000000000005) */
    ue420_byte at_0490_Keyboard_ClearMap[0x18]; /* +0x490: Keyboard_ClearMap (Struct, flags 0x10000000000005) */
    ue420_byte at_04a8_Controller_AddMap[0x18]; /* +0x4a8: Controller_AddMap (Struct, flags 0x10000000000005) */
    ue420_byte at_04c0_Keyboard_AddMap[0x18]; /* +0x4c0: Keyboard_AddMap (Struct, flags 0x10000000000005) */
    ue420_byte at_04d8_Controller_Next[0x18]; /* +0x4d8: Controller_Next (Struct, flags 0x10000000000005) */
    ue420_byte at_04f0_Keyboard_Next[0x18]; /* +0x4f0: Keyboard_Next (Struct, flags 0x10000000000005) */
    ue420_byte at_0508_Controller_Previous[0x18]; /* +0x508: Controller_Previous (Struct, flags 0x10000000000005) */
    ue420_byte at_0520_Keyboard_Previous[0x18]; /* +0x520: Keyboard_Previous (Struct, flags 0x10000000000005) */
    ue420_byte at_0538_MapIndex[0x8]; /* +0x538: MapIndex (Int, flags 0x20080000000014) */
    ue420_byte at_0540_OnlineSessionManager[0x8]; /* +0x540: OnlineSessionManager (Object, flags 0x20080000002000) */
};

/* Class params 0x1439caf00; size 0x480. */
struct UE420_MBFECustomGameMapsMenu {
    ue420_byte unknown_0000[0x448];
    ue420_byte at_0448_MapSlotButtonWidgetClass[0x8]; /* +0x448: MapSlotButtonWidgetClass (Class, flags 0x14000000010001) */
    ue420_byte at_0450_MapSlotContainer[0x8]; /* +0x450: MapSlotContainer (Object, flags 0x1000000008000d) */
    ue420_byte at_0458_DefaultMapName[0x8]; /* +0x458: DefaultMapName (Name, flags 0x10000000000015) */
    ue420_byte at_0460_OnlineSessionManager[0x8]; /* +0x460: OnlineSessionManager (Object, flags 0x20080000002000) */
    ue420_byte at_0468_CustomGameManager[0x8]; /* +0x468: CustomGameManager (Object, flags 0x20080000002000) */
    ue420_byte at_0470_MapSlotButtons[0x10]; /* +0x470: MapSlotButtons (Array, flags 0x20088000002008) */
};

/* Class params 0x1439cc480; size 0x4c8. */
struct UE420_MBFECustomGameMenu {
    ue420_byte unknown_0000[0x448];
    ue420_byte at_0448_TeamOrder[0x10]; /* +0x448: TeamOrder (Array, flags 0x10000000010001) */
    ue420_byte at_0458_NumQueueSlots[0x8]; /* +0x458: NumQueueSlots (Int, flags 0x10000000010001) */
    ue420_byte at_0460_TeamSlotButtonWidgetClass[0x8]; /* +0x460: TeamSlotButtonWidgetClass (Class, flags 0x14000000010001) */
    ue420_byte at_0468_SpectatorSlotButtonWidgetClass[0x8]; /* +0x468: SpectatorSlotButtonWidgetClass (Class, flags 0x14000000010001) */
    ue420_byte at_0470_QueuedTeamSlotButtonWidgetClass[0x8]; /* +0x470: QueuedTeamSlotButtonWidgetClass (Class, flags 0x14000000010001) */
    ue420_byte at_0478_QueuedSpectatorSlotButtonWidgetClass[0x8]; /* +0x478: QueuedSpectatorSlotButtonWidgetClass (Class, flags 0x14000000010001) */
    ue420_byte at_0480_TeamSlotButtonContainers[0x10]; /* +0x480: TeamSlotButtonContainers (Array, flags 0x1000800000000d) */
    ue420_byte at_0490_QueuedTeamSlotButtonContainers[0x10]; /* +0x490: QueuedTeamSlotButtonContainers (Array, flags 0x1000800000000d) */
    ue420_byte at_04a0_OnlineSessionManager[0x8]; /* +0x4a0: OnlineSessionManager (Object, flags 0x20080000002000) */
    ue420_byte at_04a8_CustomGameManager[0x8]; /* +0x4a8: CustomGameManager (Object, flags 0x20080000002000) */
    ue420_byte at_04b0_TeamSlotButtonLists[0x18]; /* +0x4b0: TeamSlotButtonLists (Array, flags 0x20088000002000) */
};

/* Class params 0x1439d2870; size 0x4c8. */
struct UE420_MBFECustomGameTeamSlotButton {
    ue420_byte unknown_0000[0x478];
    ue420_byte at_0478_AvatarTexture[0x8]; /* +0x478: AvatarTexture (Object, flags 0x10000000000014) */
    ue420_byte at_0480_TeamId[0x8]; /* +0x480: TeamId (Int, flags 0x10000000000014) */
    ue420_byte at_0488_PlayerName[0x10]; /* +0x488: PlayerName (Str, flags 0x10000000000014) */
    ue420_byte at_0498_PlayerPresence[0x10]; /* +0x498: PlayerPresence (Str, flags 0x10000000000014) */
    ue420_byte at_04a8_bIsOccupied[0x1]; /* +0x4a8: bIsOccupied (Bool, flags 0x10000000000014) */
    ue420_byte at_04a9_bIsHost[0x1]; /* +0x4a9: bIsHost (Bool, flags 0x10000000000014) */
    ue420_byte at_04aa_bIsLocal[0x1]; /* +0x4aa: bIsLocal (Bool, flags 0x10000000000014) */
    ue420_byte at_04ab_bCanSwitchNextTeam[0x1]; /* +0x4ab: bCanSwitchNextTeam (Bool, flags 0x10000000000014) */
    ue420_byte at_04ac_bCanSwitchPrevTeam[0x4]; /* +0x4ac: bCanSwitchPrevTeam (Bool, flags 0x10000000000014) */
    ue420_byte at_04b0_NetId[0x10]; /* +0x4b0: NetId (Str, flags 0x20080000000014) */
    ue420_byte at_04c0_ViewMode[0x8]; /* +0x4c0: ViewMode (Enum, flags 0x20080000000014) */
};

/* Class params 0x1439d2ac0; size 0x440. */
struct UE420_MBFECustomQueueScreen {
    ue420_byte unknown_0000[0x440];
};

/* Class params 0x1439dfc30; size 0x470. */
struct UE420_MBFEKioskPlayerReadyScreen {
    ue420_byte unknown_0000[0x440];
    ue420_byte at_0440_BackgroundWidgetClass[0x8]; /* +0x440: BackgroundWidgetClass (Class, flags 0x14000000000015) */
    ue420_byte at_0448_bIsPlayerReady[0x1]; /* +0x448: bIsPlayerReady (Bool, flags 0x10000000002014) */
    ue420_byte at_0449_bStartMatchCountdownActive[0x3]; /* +0x449: bStartMatchCountdownActive (Bool, flags 0x10000000002014) */
    ue420_byte at_044c_StartMatchCountdownRemaining[0x4]; /* +0x44c: StartMatchCountdownRemaining (Int, flags 0x10000000002014) */
    ue420_byte at_0450_PlayerName[0x10]; /* +0x450: PlayerName (Str, flags 0x10000000002014) */
    ue420_byte at_0460_bIsPlayerReadyLastFrame[0x1]; /* +0x460: bIsPlayerReadyLastFrame (Bool, flags 0x40000000002000) */
    ue420_byte at_0461_bStartMatchCountdownActiveLastFrame[0x3]; /* +0x461: bStartMatchCountdownActiveLastFrame (Bool, flags 0x40000000002000) */
    ue420_byte at_0464_StartMatchCountdownRemainingLastFrame[0x4]; /* +0x464: StartMatchCountdownRemainingLastFrame (Int, flags 0x40000000002000) */
    ue420_byte at_0468_BackgroundWidget[0x8]; /* +0x468: BackgroundWidget (Object, flags 0x40000000082008) */
};

/* Class params 0x1439f5190; size 0x408. */
struct UE420_MBFriendsListWidget {
    ue420_byte unknown_0000[0x390];
    ue420_byte at_0390_FriendWidgetClass[0x8]; /* +0x390: FriendWidgetClass (Class, flags 0x14000000000001) */
    ue420_byte at_0398_ReadFriendsFrequency[0x4]; /* +0x398: ReadFriendsFrequency (Float, flags 0x10000000000001) */
    ue420_byte at_039c_ReadFriendsRetryFrequency[0x4]; /* +0x39c: ReadFriendsRetryFrequency (Float, flags 0x10000000000001) */
    ue420_byte at_03a0_FriendWidgetContainer[0x8]; /* +0x3a0: FriendWidgetContainer (Object, flags 0x1000000008000d) */
    ue420_byte at_03a8_OnlineSessionManager[0x8]; /* +0x3a8: OnlineSessionManager (Object, flags 0x20080000002000) */
    ue420_byte at_03b0_PartyManager[0x8]; /* +0x3b0: PartyManager (Object, flags 0x20080000002000) */
    ue420_byte at_03b8_SizeBox[0x8]; /* +0x3b8: SizeBox (Object, flags 0x20080000082008) */
    ue420_byte at_03c0_FriendWidgetData[0x10]; /* +0x3c0: FriendWidgetData (Array, flags 0x20080000002014) */
    ue420_byte at_03d0_FriendWidgets[0x10]; /* +0x3d0: FriendWidgets (Array, flags 0x2008800000201c) */
    ue420_byte at_03e0_FriendWidgetsInView[0x10]; /* +0x3e0: FriendWidgetsInView (Array, flags 0x20080000002014) */
    ue420_byte at_03f0_FriendListUpdateCounter[0x4]; /* +0x3f0: FriendListUpdateCounter (Int, flags 0x20080000002000) */
    ue420_byte at_03f4_bReadFriendsEnabled[0x1]; /* +0x3f4: bReadFriendsEnabled (Bool, flags 0x20080000002000) */
    ue420_byte at_03f5_bReadFriendsPending[0x1]; /* +0x3f5: bReadFriendsPending (Bool, flags 0x20080000002000) */
    ue420_byte at_03f6_bFirstReadFriends[0x1]; /* +0x3f6: bFirstReadFriends (Bool, flags 0x20080000002000) */
    ue420_byte at_03f7_bForceBatchedAvatarRequests[0x11]; /* +0x3f7: bForceBatchedAvatarRequests (Bool, flags 0x20080000002000) */
};

/* Class params 0x1439f7980; size 0x318. */
struct UE420_MBFrontEnd {
    ue420_byte unknown_0000[0x38];
    ue420_byte at_0038_DefaultFrontendWidgetContainer[0x18]; /* +0x38: DefaultFrontendWidgetContainer (Struct, flags 0x40000000004000) */
    ue420_byte at_0050_CachedFrontendScreenClasses[0x10]; /* +0x50: CachedFrontendScreenClasses (Array, flags 0x40000000004000) */
    ue420_byte at_0060_FrontendObjectsToLoadAsync[0x10]; /* +0x60: FrontendObjectsToLoadAsync (Array, flags 0x40000000004000) */
    ue420_byte at_0070_LoadedObjects[0x10]; /* +0x70: LoadedObjects (Array, flags 0x40000000000000) */
    ue420_byte at_0080_CachedScreens[0x10]; /* +0x80: CachedScreens (Array, flags 0x40008000000008) */
    ue420_byte at_0090_TokenManager[0x88]; /* +0x90: TokenManager (Struct, flags 0x40008000000000) */
    ue420_byte at_0118_LatentActionManager[0xf0]; /* +0x118: LatentActionManager (Struct, flags 0x40000000000000) */
    ue420_byte at_0208_WidgetContainer[0x8]; /* +0x208: WidgetContainer (Object, flags 0x40000000080008) */
    ue420_byte at_0210_ScreenStack[0x10]; /* +0x210: ScreenStack (Array, flags 0x40008000000008) */
    ue420_byte at_0220_WorldSingleton[0x8]; /* +0x220: WorldSingleton (Object, flags 0x40000000000000) */
    ue420_byte at_0228_PendingScreenPushWidgets[0x10]; /* +0x228: PendingScreenPushWidgets (Array, flags 0x40008000000000) */
    ue420_byte at_0238_PendingPushMenuWidgets[0x10]; /* +0x238: PendingPushMenuWidgets (Array, flags 0x40008000000008) */
    ue420_byte at_0248_PendingPopMenuCompleteCallback[0x10]; /* +0x248: PendingPopMenuCompleteCallback (Delegate, flags 0x40000000082000) */
    ue420_byte at_0258_bInPushTransition[0x1]; /* +0x258: bInPushTransition (Bool, flags 0x40000000000000) */
    ue420_byte at_0259_bInPopTransition[0x1]; /* +0x259: bInPopTransition (Bool, flags 0x40000000000000) */
    ue420_byte at_025a_bIsCameraTransitioning[0x1]; /* +0x25a: bIsCameraTransitioning (Bool, flags 0x40000000000000) */
    ue420_byte at_025b_bIsKeyCapturing[0x1]; /* +0x25b: bIsKeyCapturing (Bool, flags 0x40000000000000) */
    ue420_byte at_025c_bRestoringScreenStack[0x1]; /* +0x25c: bRestoringScreenStack (Bool, flags 0x40000000000000) */
    ue420_byte at_025d_bIsInitialisedToPlayerController[0x3]; /* +0x25d: bIsInitialisedToPlayerController (Bool, flags 0x40000000000000) */
    ue420_byte at_0260_SetUserFocusRefCount[0x8]; /* +0x260: SetUserFocusRefCount (Int, flags 0x40000000000000) */
    ue420_byte at_0268_RemainingSplashScreens[0x10]; /* +0x268: RemainingSplashScreens (Array, flags 0x40000000000000) */
    ue420_byte at_0278_PendingSplashScreen[0x18]; /* +0x278: PendingSplashScreen (Struct, flags 0x40000000000000) */
    ue420_byte at_0290_SplashPlayerController[0x8]; /* +0x290: SplashPlayerController (Object, flags 0x40000000000000) */
    ue420_byte at_0298_bCanCloseFinalSplashScreen[0x8]; /* +0x298: bCanCloseFinalSplashScreen (Bool, flags 0x40000000000000) */
    ue420_byte at_02a0_OnFinalSplashScreenComplete[0x10]; /* +0x2a0: OnFinalSplashScreenComplete (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_02b0_CurrentCameraTag[0x8]; /* +0x2b0: CurrentCameraTag (Name, flags 0x40000000000000) */
    ue420_byte at_02b8_CurrentExitMenuTokens[0x10]; /* +0x2b8: CurrentExitMenuTokens (Array, flags 0x40000000000000) */
    ue420_byte at_02c8_WatchZoneScreenClass[0x18]; /* +0x2c8: WatchZoneScreenClass (Struct, flags 0x40000000004000) */
    ue420_byte at_02e0_CustomQueueScreenClass[0x18]; /* +0x2e0: CustomQueueScreenClass (Struct, flags 0x40000000004000) */
    ue420_byte at_02f8_bIsInStartScreen[0x8]; /* +0x2f8: bIsInStartScreen (Bool, flags 0x40000000000000) */
    ue420_byte at_0300_PendingScreenPopWidgets[0x18]; /* +0x300: PendingScreenPopWidgets (Array, flags 0x40008000000000) */
};

/* Class params 0x143a09070; size 0xa68. */
struct UE420_MBGameInstance {
    ue420_byte unknown_0000[0x170];
    ue420_byte at_0170_NetworkConnectionLostReason[0x4]; /* +0x170: NetworkConnectionLostReason (Enum, flags 0x10000000000004) */
    ue420_byte at_0174_MapIndex[0x4]; /* +0x174: MapIndex (Int, flags 0x10000000000014) */
    ue420_byte at_0178_AIPlayers[0x10]; /* +0x178: AIPlayers (Array, flags 0x10000000000004) */
    ue420_byte at_0188_OnCheckCanPlayResponseDelegate[0x10]; /* +0x188: OnCheckCanPlayResponseDelegate (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0198_LoadTime[0x20]; /* +0x198: LoadTime (Float, flags 0x10000000000000) */
    ue420_byte at_01b8_OnlineSessionManager[0x8]; /* +0x1b8: OnlineSessionManager (Object, flags 0x20080000000000) */
    ue420_byte at_01c0_bAnalyticsEnabled[0x1]; /* +0x1c0: bAnalyticsEnabled (Bool, flags 0x20080000000000) */
    ue420_byte at_01c1_bPendingCheckCanPlay[0x7]; /* +0x1c1: bPendingCheckCanPlay (Bool, flags 0x20080000000000) */
    ue420_byte at_01c8_HeroStatusList[0x8]; /* +0x1c8: HeroStatusList (Object, flags 0x20080000010015) */
    ue420_byte at_01d0_ApplicationDeactivatedSoundMix[0x8]; /* +0x1d0: ApplicationDeactivatedSoundMix (Object, flags 0x20080000010015) */
    ue420_byte at_01d8_TickMontagesDistance[0x4]; /* +0x1d8: TickMontagesDistance (Float, flags 0x20080000010015) */
    ue420_byte at_01dc_bApplicationActivated[0x34]; /* +0x1dc: bApplicationActivated (Bool, flags 0x40000000002000) */
    ue420_byte at_0210_PlayFabMatchmakingManager[0x8]; /* +0x210: PlayFabMatchmakingManager (Object, flags 0x40000000000000) */
    ue420_byte at_0218_PlayFabBackfillingManager[0x8]; /* +0x218: PlayFabBackfillingManager (Object, flags 0x40000000000000) */
    ue420_byte at_0220_PlayFabServerMigrationManager[0x8]; /* +0x220: PlayFabServerMigrationManager (Object, flags 0x40000000000000) */
    ue420_byte at_0228_PlayFabRegionManager[0x8]; /* +0x228: PlayFabRegionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0230_MultiplayerBuildId[0x10]; /* +0x230: MultiplayerBuildId (Str, flags 0x40000000000000) */
    ue420_byte at_0240_BuildJsonString[0x10]; /* +0x240: BuildJsonString (Str, flags 0x40000000000000) */
    ue420_byte at_0250_bGettingMultiplayerBuildId[0x8]; /* +0x250: bGettingMultiplayerBuildId (Bool, flags 0x40000000000000) */
    ue420_byte at_0258_PlayerAccountManager[0x8]; /* +0x258: PlayerAccountManager (Object, flags 0x40000000000000) */
    ue420_byte at_0260_UpdateManager[0x8]; /* +0x260: UpdateManager (Object, flags 0x40000000000000) */
    ue420_byte at_0268_OnlinePlayerIdManager[0x8]; /* +0x268: OnlinePlayerIdManager (Object, flags 0x40000000000000) */
    ue420_byte at_0270_PlayerAvatarManager[0x8]; /* +0x270: PlayerAvatarManager (Object, flags 0x40000000000000) */
    ue420_byte at_0278_LeaderboardManager[0x8]; /* +0x278: LeaderboardManager (Object, flags 0x40000000000000) */
    ue420_byte at_0280_QuestionManager[0x8]; /* +0x280: QuestionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0288_ReplayStreamingManager[0x8]; /* +0x288: ReplayStreamingManager (Object, flags 0x40000000000000) */
    ue420_byte at_0290_AzureFileCache[0x8]; /* +0x290: AzureFileCache (Object, flags 0x40000000000000) */
    ue420_byte at_0298_GameServerManager[0x8]; /* +0x298: GameServerManager (Object, flags 0x40000000000000) */
    ue420_byte at_02a0_MusicManager[0x8]; /* +0x2a0: MusicManager (Object, flags 0x40000000000000) */
    ue420_byte at_02a8_LoadingScreenManager[0x8]; /* +0x2a8: LoadingScreenManager (Object, flags 0x40000000000000) */
    ue420_byte at_02b0_MapLoadingManager[0x8]; /* +0x2b0: MapLoadingManager (Object, flags 0x40000000000000) */
    ue420_byte at_02b8_WatchZoneManager[0x8]; /* +0x2b8: WatchZoneManager (Object, flags 0x40000000000000) */
    ue420_byte at_02c0_SystemMessageManager[0x8]; /* +0x2c0: SystemMessageManager (Object, flags 0x40000000000000) */
    ue420_byte at_02c8_EventsManager[0x8]; /* +0x2c8: EventsManager (Object, flags 0x40000000000000) */
    ue420_byte at_02d0_KioskModeManager[0x8]; /* +0x2d0: KioskModeManager (Object, flags 0x40000000000000) */
    ue420_byte at_02d8_QuestsManager[0x8]; /* +0x2d8: QuestsManager (Object, flags 0x40000000000000) */
    ue420_byte at_02e0_MapModsManager[0x8]; /* +0x2e0: MapModsManager (Object, flags 0x40000000000000) */
    ue420_byte at_02e8_AchievementsManager[0x8]; /* +0x2e8: AchievementsManager (Object, flags 0x40000000000000) */
    ue420_byte at_02f0_LeaverStatusManager[0x8]; /* +0x2f0: LeaverStatusManager (Object, flags 0x40000000000000) */
    ue420_byte at_02f8_PlayFabReporter[0x8]; /* +0x2f8: PlayFabReporter (Object, flags 0x40000000000000) */
    ue420_byte at_0300_OnlineStatusMessages[0x8]; /* +0x300: OnlineStatusMessages (Object, flags 0x40000000000000) */
    ue420_byte at_0308_PlayerAssetManager[0x8]; /* +0x308: PlayerAssetManager (Object, flags 0x40000000000000) */
    ue420_byte at_0310_NumAsyncPackages[0x8]; /* +0x310: NumAsyncPackages (Int, flags 0x40000000000000) */
    ue420_byte at_0318_AsyncLoadedPackages[0x10]; /* +0x318: AsyncLoadedPackages (Array, flags 0x40000000000000) */
    ue420_byte at_0328_AsyncLoadedWorlds[0x10]; /* +0x328: AsyncLoadedWorlds (Array, flags 0x40000000000000) */
    ue420_byte at_0338_bIsLocalPlayerAFK[0x8]; /* +0x338: bIsLocalPlayerAFK (Bool, flags 0x40000000002000) */
    ue420_byte at_0340_DefaultLoadingScreenManagerClassName[0x18]; /* +0x340: DefaultLoadingScreenManagerClassName (Struct, flags 0x40000000004000) */
    ue420_byte at_0358_DefaultSystemMessageManagerClassName[0x18]; /* +0x358: DefaultSystemMessageManagerClassName (Struct, flags 0x40000000004000) */
    ue420_byte at_0370_DefaultOnlineStatusMessagesPath[0x18]; /* +0x370: DefaultOnlineStatusMessagesPath (Struct, flags 0x40000000004000) */
    ue420_byte at_0388_PlayerClassLookupTable[0x8]; /* +0x388: PlayerClassLookupTable (Object, flags 0x40000000000000) */
    ue420_byte at_0390_PlayerClassLoadStatus[0x4]; /* +0x390: PlayerClassLoadStatus (Struct, flags 0x40000000000000) */
    ue420_byte at_0394_DynamicResolutionModeOnStartup[0x4]; /* +0x394: DynamicResolutionModeOnStartup (Int, flags 0x40000000000000) */
    ue420_byte at_0398_SeparateTranslucencyEnabledOnStartup[0x4]; /* +0x398: SeparateTranslucencyEnabledOnStartup (Int, flags 0x40000000000000) */
    ue420_byte at_039c_bHasLoadedFirstMap[0x5bc]; /* +0x39c: bHasLoadedFirstMap (Bool, flags 0x40000000000000) */
    ue420_byte at_0958_KioskType[0x8]; /* +0x958: KioskType (Enum, flags 0x40000000002000) */
    ue420_byte at_0960_KioskPlayerName[0x20]; /* +0x960: KioskPlayerName (Str, flags 0x40000000002000) */
    ue420_byte at_0980_MapStatusList[0x30]; /* +0x980: MapStatusList (Array, flags 0x40000000002000) */
    ue420_byte at_09b0_ServerConnectionType[0x4]; /* +0x9b0: ServerConnectionType (Enum, flags 0x40000000002000) */
    ue420_byte at_09b4_TimeToNextServerOpen[0x4]; /* +0x9b4: TimeToNextServerOpen (Float, flags 0x40000000002000) */
    ue420_byte at_09b8_ServerConnectionChangedMulticast[0x98]; /* +0x9b8: ServerConnectionChangedMulticast (MulticastDelegate, flags 0x40000000082000) */
    ue420_byte at_0a50_ServerWorkInProgressObjectsList[0x10]; /* +0xa50: ServerWorkInProgressObjectsList (Array, flags 0x40000000002000) */
    ue420_byte at_0a60_DataTableManager[0x8]; /* +0xa60: DataTableManager (Object, flags 0x40000000002000) */
};

/* Class params 0x14445ca50; size 0x28. */
struct UE420_MBGameModeManagerState {
    ue420_byte unknown_0000[0x28];
};

/* Class params 0x143a178b0; size 0xc8. */
struct UE420_MBGameServerManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_GameInstance[0x8]; /* +0x30: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0038_TeamSlotManagers[0x10]; /* +0x38: TeamSlotManagers (Array, flags 0x40000000000000) */
    ue420_byte at_0048_ActiveMatchmakingRequestIds[0x10]; /* +0x48: ActiveMatchmakingRequestIds (Array, flags 0x40000000000000) */
    ue420_byte at_0058_bAllowSlotRefilling[0x1]; /* +0x58: bAllowSlotRefilling (Bool, flags 0x40000000000000) */
    ue420_byte at_0059_bEnableSlotRefilling[0x1]; /* +0x59: bEnableSlotRefilling (Bool, flags 0x40000000000000) */
    ue420_byte at_005a_bEnableAnalytics[0x6]; /* +0x5a: bEnableAnalytics (Bool, flags 0x40000000000000) */
    ue420_byte at_0060_SourceMatchId[0x10]; /* +0x60: SourceMatchId (Str, flags 0x40000000000000) */
    ue420_byte at_0070_bServerAllocated[0x58]; /* +0x70: bServerAllocated (Bool, flags 0x40000000000000) */
};

/* Class params 0x143a1c410; size 0x240. */
struct UE420_MBGraffitiBaseWidget {
    ue420_byte unknown_0000[0x1a0];
    ue420_byte at_01a0_WatchControllingPlayerTokens[0x10]; /* +0x1a0: WatchControllingPlayerTokens (Array, flags 0x10000000000005) */
    ue420_byte at_01b0_WatchControllingPlayerAttributes[0x10]; /* +0x1b0: WatchControllingPlayerAttributes (Array, flags 0x10000000000005) */
    ue420_byte at_01c0_WatchOwnerProxyTokens[0x10]; /* +0x1c0: WatchOwnerProxyTokens (Array, flags 0x10000000000005) */
    ue420_byte at_01d0_WatchOwnerProxyAttributes[0x10]; /* +0x1d0: WatchOwnerProxyAttributes (Array, flags 0x10000000000005) */
    ue420_byte at_01e0_CommonLevelObjectProxy[0x8]; /* +0x1e0: CommonLevelObjectProxy (Object, flags 0x10000000002004) */
    ue420_byte at_01e8_bCanTickWhilstOwnerHidden[0x1]; /* +0x1e8: bCanTickWhilstOwnerHidden (Bool, flags 0x10000000000005) */
    ue420_byte at_01e9_bNeedsReceiveOutputEvent[0x1]; /* +0x1e9: bNeedsReceiveOutputEvent (Bool, flags 0x20080000000000) */
    ue420_byte at_01ea_bNeedsGameOvertimeEvent[0x1]; /* +0x1ea: bNeedsGameOvertimeEvent (Bool, flags 0x20080000000000) */
    ue420_byte at_01eb_bRegisterSpectatorDelegates[0x5]; /* +0x1eb: bRegisterSpectatorDelegates (Bool, flags 0x20080000000000) */
    ue420_byte at_01f0_CachedOwningPlayerController[0x8]; /* +0x1f0: CachedOwningPlayerController (Object, flags 0x40000000002000) */
    ue420_byte at_01f8_WidgetOwnerProxy[0x8]; /* +0x1f8: WidgetOwnerProxy (Object, flags 0x40000000002000) */
    ue420_byte at_0200_ControllingPlayerProxyLastFrame[0x8]; /* +0x200: ControllingPlayerProxyLastFrame (Object, flags 0x40000000002000) */
    ue420_byte at_0208_OwnerProxyLastFrame[0x8]; /* +0x208: OwnerProxyLastFrame (Object, flags 0x40000000002000) */
    ue420_byte at_0210_CachedSpectatorType[0x1]; /* +0x210: CachedSpectatorType (Enum, flags 0x40000000002000) */
    ue420_byte at_0211_CachedSpectatorCameraMode[0x2f]; /* +0x211: CachedSpectatorCameraMode (Enum, flags 0x40000000002000) */
};

/* Class params 0x143a24e40; size 0xa8. */
struct UE420_MBHeroesBanterSystem {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_DelayFromCharacterSelection[0x8]; /* +0x30: DelayFromCharacterSelection (Struct, flags 0x40000000000001) */
    ue420_byte at_0038_TimeBetweenBanters[0x8]; /* +0x38: TimeBetweenBanters (Struct, flags 0x40000000000001) */
    ue420_byte at_0040_Banters[0x10]; /* +0x40: Banters (Array, flags 0x40000000000001) */
    ue420_byte at_0050_ActiveBanterIds[0x10]; /* +0x50: ActiveBanterIds (Array, flags 0x40000000000000) */
    ue420_byte at_0060_GameInstance[0x8]; /* +0x60: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0068_WorldSingleton[0x8]; /* +0x68: WorldSingleton (Object, flags 0x40000000002000) */
    ue420_byte at_0070_EffectsPluginVO[0x8]; /* +0x70: EffectsPluginVO (Object, flags 0x40000000002000) */
    ue420_byte at_0078_ActiveBanters[0x10]; /* +0x78: ActiveBanters (Array, flags 0x40008000002000) */
    ue420_byte at_0088_ActivePlayers[0x10]; /* +0x88: ActivePlayers (Array, flags 0x40000000002000) */
    ue420_byte at_0098_TimeToTryPlayBanter[0x4]; /* +0x98: TimeToTryPlayBanter (Float, flags 0x40000000002000) */
    ue420_byte at_009c_RemainingTimeBetweenBanters[0x4]; /* +0x9c: RemainingTimeBetweenBanters (Float, flags 0x40000000002000) */
    ue420_byte at_00a0_bMatchStarted[0x8]; /* +0xa0: bMatchStarted (Bool, flags 0x40000000002000) */
};

/* Class params 0x1444f8570; size 0x40. */
struct UE420_MBInputEventApplyKioskModeHandicap {
    ue420_byte unknown_0000[0x38];
    ue420_byte at_0038_Multiplier[0x4]; /* +0x38: Multiplier (Float, flags 0x10000000000000) */
    ue420_byte at_003c_HandicapType[0x4]; /* +0x3c: HandicapType (Enum, flags 0x10000000000000) */
};

/* Class params 0x1444f5670; size 0x38. */
struct UE420_MBInputEventKioskModeEndGame {
    ue420_byte unknown_0000[0x38];
};

/* Class params 0x143a3ca10; size 0x398. */
struct UE420_MBKioskModeEndGameWidget {
    ue420_byte unknown_0000[0x390];
    ue420_byte at_0390_KioskModeManager[0x8]; /* +0x390: KioskModeManager (Object, flags 0x20080000002014) */
};

/* Class params 0x1445010f0; size 0x40. */
struct UE420_MBKioskModeHandicapsData {
    ue420_byte unknown_0000[0x40];
};

/* Class params 0x144501800; size 0x68. */
struct UE420_MBKioskModeHandicapsStateWrapper {
    ue420_byte unknown_0000[0x40];
    ue420_byte at_0040_StateStruct[0x28]; /* +0x40: StateStruct (Struct, flags 0x10000000000000) */
};

/* Class params 0x143a43060; size 0x398. */
struct UE420_MBKioskModeHandicapsWidget {
    ue420_byte unknown_0000[0x390];
    ue420_byte at_0390_KioskModeManager[0x8]; /* +0x390: KioskModeManager (Object, flags 0x20080000002014) */
};

/* Class params 0x143a43560; size 0x110. */
struct UE420_MBKioskModeManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_TypesBlueprintObjectRef[0x18]; /* +0x28: TypesBlueprintObjectRef (Struct, flags 0x10000000004000) */
    ue420_byte at_0040_SeedsRequiredToWin[0x30]; /* +0x40: SeedsRequiredToWin (Struct, flags 0x40000000000001) */
    ue420_byte at_0070_CPPointsRequiredToWin[0x8]; /* +0x70: CPPointsRequiredToWin (Int, flags 0x40000000000001) */
    ue420_byte at_0078_AdditionalCustomisations[0x10]; /* +0x78: AdditionalCustomisations (Array, flags 0x40000000000001) */
    ue420_byte at_0088_HeroCustomisations[0x10]; /* +0x88: HeroCustomisations (Array, flags 0x40000000000001) */
    ue420_byte at_0098_KioskModeHandicapAAction[0x8]; /* +0x98: KioskModeHandicapAAction (Name, flags 0x40000000000001) */
    ue420_byte at_00a0_KioskModeHandicapBAction[0x8]; /* +0xa0: KioskModeHandicapBAction (Name, flags 0x40000000000001) */
    ue420_byte at_00a8_KioskModeIncDamageAction[0x8]; /* +0xa8: KioskModeIncDamageAction (Name, flags 0x40000000000001) */
    ue420_byte at_00b0_KioskModeDecDamageAction[0x8]; /* +0xb0: KioskModeDecDamageAction (Name, flags 0x40000000000001) */
    ue420_byte at_00b8_KioskModeIncDefenceAction[0x8]; /* +0xb8: KioskModeIncDefenceAction (Name, flags 0x40000000000001) */
    ue420_byte at_00c0_KioskModeDecDefenceAction[0x8]; /* +0xc0: KioskModeDecDefenceAction (Name, flags 0x40000000000001) */
    ue420_byte at_00c8_DamageMultiplierData[0xc]; /* +0xc8: DamageMultiplierData (Struct, flags 0x40000000000001) */
    ue420_byte at_00d4_DefenceMultiplierData[0xc]; /* +0xd4: DefenceMultiplierData (Struct, flags 0x40000000000001) */
    ue420_byte at_00e0_HandicapsWidgetClass[0x8]; /* +0xe0: HandicapsWidgetClass (Class, flags 0x44000000000001) */
    ue420_byte at_00e8_EndGameCountdown[0x8]; /* +0xe8: EndGameCountdown (Int, flags 0x40000000000001) */
    ue420_byte at_00f0_EndGameWidgetClass[0x8]; /* +0xf0: EndGameWidgetClass (Class, flags 0x44000000000001) */
    ue420_byte at_00f8_ResetToDefaultSettingsMaps[0x10]; /* +0xf8: ResetToDefaultSettingsMaps (Array, flags 0x40000000000001) */
    ue420_byte at_0108_GameInstance[0x8]; /* +0x108: GameInstance (Object, flags 0x40000000002000) */
};

/* Class params 0x143a439e0; size 0x528. */
struct UE420_MBKioskRollbackGameMode {
    ue420_byte unknown_0000[0x518];
    ue420_byte at_0518_NumPlayersRequired[0x4]; /* +0x518: NumPlayersRequired (Int, flags 0x10000000000015) */
    ue420_byte at_051c_StartMatchCountdownDuration[0x4]; /* +0x51c: StartMatchCountdownDuration (Int, flags 0x10000000000015) */
    ue420_byte at_0520_bUseKioskPlayerName[0x4]; /* +0x520: bUseKioskPlayerName (Bool, flags 0x10000000000015) */
    ue420_byte at_0524_NumPlayersRequiredOverride[0x4]; /* +0x524: NumPlayersRequiredOverride (Int, flags 0x40000000002000) */
};

/* Class params 0x143a40020; size 0x4f0. */
struct UE420_MBKioskRollbackGameState {
    ue420_byte unknown_0000[0x488];
    ue420_byte at_0488_PlayerReadyScreenClasses[0x50]; /* +0x488: PlayerReadyScreenClasses (Map, flags 0x14000000010001) */
    ue420_byte at_04d8_DefaultPlayerReadyScreenClass[0x8]; /* +0x4d8: DefaultPlayerReadyScreenClass (Class, flags 0x14000000010001) */
    ue420_byte at_04e0_KioskStartMatchCountdownEndTimeSeconds[0x4]; /* +0x4e0: KioskStartMatchCountdownEndTimeSeconds (Float, flags 0x40000000000020) */
    ue420_byte at_04e4_bKioskStartMatchCountdownActive[0x4]; /* +0x4e4: bKioskStartMatchCountdownActive (Bool, flags 0x40000000000020) */
    ue420_byte at_04e8_CurrentPlayerReadyScreenClass[0x8]; /* +0x4e8: CurrentPlayerReadyScreenClass (Class, flags 0x44000000002000) */
};

/* Class params 0x143a41b70; size 0x120. */
struct UE420_MBLeaderboardManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_GameInstance[0x8]; /* +0x30: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0038_CachedLeaderboards[0x10]; /* +0x38: CachedLeaderboards (Array, flags 0x40000000002000) */
    ue420_byte at_0048_CachedFriendLeaderboards[0x10]; /* +0x48: CachedFriendLeaderboards (Array, flags 0x40000000002000) */
    ue420_byte at_0058_CachedLocalPlayerLeaderboardEntries[0x10]; /* +0x58: CachedLocalPlayerLeaderboardEntries (Array, flags 0x40000000002000) */
    ue420_byte at_0068_CachedHeroLeaderboards[0x10]; /* +0x68: CachedHeroLeaderboards (Array, flags 0x40000000002000) */
    ue420_byte at_0078_CachedLocalPlayerHeroLeaderboards[0x10]; /* +0x78: CachedLocalPlayerHeroLeaderboards (Array, flags 0x40000000002000) */
    ue420_byte at_0088_PendingLeaderboardRequests[0x10]; /* +0x88: PendingLeaderboardRequests (Array, flags 0x40000000002000) */
    ue420_byte at_0098_PendingLeaderboardAroundPlayerRequests[0x10]; /* +0x98: PendingLeaderboardAroundPlayerRequests (Array, flags 0x40000000002000) */
    ue420_byte at_00a8_PendingFriendLeaderboardRequests[0x10]; /* +0xa8: PendingFriendLeaderboardRequests (Array, flags 0x40000000002000) */
    ue420_byte at_00b8_PendingHeroLeaderboardRequests[0x10]; /* +0xb8: PendingHeroLeaderboardRequests (Array, flags 0x40000000002000) */
    ue420_byte at_00c8_PendingLocalPlayerHeroLeaderboardRequests[0x50]; /* +0xc8: PendingLocalPlayerHeroLeaderboardRequests (Array, flags 0x40000000002000) */
    ue420_byte at_0118_NumPostMatchSkillBatchesRemaining[0x4]; /* +0x118: NumPostMatchSkillBatchesRemaining (Int, flags 0x40000000000000) */
    ue420_byte at_011c_NumPostMatchStatsBatchesRemaining[0x4]; /* +0x11c: NumPostMatchStatsBatchesRemaining (Int, flags 0x40000000000000) */
};

/* Class params 0x143a42560; size 0xb0. */
struct UE420_MBLeaverStatusManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_OnLeaverStatusChangedMulticaster[0x10]; /* +0x28: OnLeaverStatusChangedMulticaster (MulticastDelegate, flags 0x10000000082000) */
    ue420_byte at_0038_GainedLeaverStatusMessageId[0x8]; /* +0x38: GainedLeaverStatusMessageId (Name, flags 0x40000000000001) */
    ue420_byte at_0040_GameInstance[0x8]; /* +0x40: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0048_WorldSingleton[0x8]; /* +0x48: WorldSingleton (Object, flags 0x40000000002000) */
    ue420_byte at_0050_LocalPlayerLeaverStatus[0x20]; /* +0x50: LocalPlayerLeaverStatus (Struct, flags 0x40000000002000) */
    ue420_byte at_0070_bHadLocalPlayerLeaverStatusWhenLoadedLevel[0x1]; /* +0x70: bHadLocalPlayerLeaverStatusWhenLoadedLevel (Bool, flags 0x40000000002000) */
    ue420_byte at_0071_bIsEnabled[0x7]; /* +0x71: bIsEnabled (Bool, flags 0x40000000002000) */
    ue420_byte at_0078_LeaverStatusConfig[0x38]; /* +0x78: LeaverStatusConfig (Struct, flags 0x40000000002000) */
};

/* Class params 0x143a4a580; size 0x2d0. */
struct UE420_MBLoadingScreenBaseWidget {
    ue420_byte unknown_0000[0x2b8];
    ue420_byte at_02b8_CachedGameInstance[0x8]; /* +0x2b8: CachedGameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_02c0_ObjectReferences[0x10]; /* +0x2c0: ObjectReferences (Array, flags 0x40000000002000) */
};

/* Class params 0x143a47080; size 0x1d0. */
struct UE420_MBLoadingScreenManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_DefaultLoadingScreenData[0x30]; /* +0x30: DefaultLoadingScreenData (Struct, flags 0x10000000010001) */
    ue420_byte at_0060_SoundMixModifier[0x28]; /* +0x60: SoundMixModifier (Object, flags 0x10000000010015) */
    ue420_byte at_0088_GameInstance[0x8]; /* +0x88: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0090_LoadingScreenWidget[0x38]; /* +0x90: LoadingScreenWidget (Object, flags 0x40000000082008) */
    ue420_byte at_00c8_LoadingLevelName[0x10]; /* +0xc8: LoadingLevelName (Str, flags 0x40000000002000) */
    ue420_byte at_00d8_LoadingMapName[0x8]; /* +0xd8: LoadingMapName (Name, flags 0x40000000002000) */
    ue420_byte at_00e0_PendingTravelURL[0x70]; /* +0xe0: PendingTravelURL (Struct, flags 0x40000000002000) */
    ue420_byte at_0150_LoadingScreenData[0x30]; /* +0x150: LoadingScreenData (Struct, flags 0x40000000002000) */
    ue420_byte at_0180_LoadingScreenRuntimeData[0x38]; /* +0x180: LoadingScreenRuntimeData (Struct, flags 0x40000000002000) */
    ue420_byte at_01b8_State[0x8]; /* +0x1b8: State (Enum, flags 0x40000000002000) */
    ue420_byte at_01c0_StartedLoading[0x8]; /* +0x1c0: StartedLoading (Struct, flags 0x40000000002000) */
    ue420_byte at_01c8_bHasFrontEndEverBeenLoaded[0x8]; /* +0x1c8: bHasFrontEndEverBeenLoaded (Bool, flags 0x40000000002000) */
};

/* Class params 0x143a4e5d0; size 0x98. */
struct UE420_MBMatchmakingConfigProvider {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_Profiles[0x50]; /* +0x28: Profiles (Map, flags 0x40000000000000) */
    ue420_byte at_0078_Rules[0x10]; /* +0x78: Rules (Array, flags 0x40000000000000) */
    ue420_byte at_0088_bPopulated[0x10]; /* +0x88: bPopulated (Bool, flags 0x40000000000000) */
};

/* Class params 0x143a4ef30; size 0x2f8. */
struct UE420_MBMatchmakingPanelWidget {
    ue420_byte unknown_0000[0x2d8];
    ue420_byte at_02d8_MatchmakingManager[0x8]; /* +0x2d8: MatchmakingManager (Object, flags 0x20080000002000) */
    ue420_byte at_02e0_OnlineSessionManager[0x8]; /* +0x2e0: OnlineSessionManager (Object, flags 0x20080000002000) */
    ue420_byte at_02e8_PartyManager[0x8]; /* +0x2e8: PartyManager (Object, flags 0x20080000002000) */
    ue420_byte at_02f0_State[0x1]; /* +0x2f0: State (Enum, flags 0x20080000002000) */
    ue420_byte at_02f1_bCanShowInCurrentMap[0x7]; /* +0x2f1: bCanShowInCurrentMap (Bool, flags 0x20080000002000) */
};

/* Class params 0x143a5e1f0; size 0x148. */
struct UE420_MBMusicManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_TypesBlueprintObjectRef[0x18]; /* +0x28: TypesBlueprintObjectRef (Struct, flags 0x10000000004000) */
    ue420_byte at_0040_bDisabledInPIE[0x8]; /* +0x40: bDisabledInPIE (Bool, flags 0x10000000010001) */
    ue420_byte at_0048_DefaultLevelLoadingMusic[0x8]; /* +0x48: DefaultLevelLoadingMusic (Object, flags 0x10000000010001) */
    ue420_byte at_0050_DontPlayDefaultLoadingMusicGameModes[0x10]; /* +0x50: DontPlayDefaultLoadingMusicGameModes (Array, flags 0x10000000010001) */
    ue420_byte at_0060_MusicFadeInTime[0x4]; /* +0x60: MusicFadeInTime (Float, flags 0x20080000000015) */
    ue420_byte at_0064_MusicFadeOutTime[0x4]; /* +0x64: MusicFadeOutTime (Float, flags 0x20080000000015) */
    ue420_byte at_0068_CapturePointScoreRemainingThreshold[0x10]; /* +0x68: CapturePointScoreRemainingThreshold (Array, flags 0x20080000000015) */
    ue420_byte at_0078_CapturePointScoreRemainingThresholdLookup[0x10]; /* +0x78: CapturePointScoreRemainingThresholdLookup (Array, flags 0x20080000000000) */
    ue420_byte at_0088_CapturePointScoreRemainingThresholdIndex[0x8]; /* +0x88: CapturePointScoreRemainingThresholdIndex (Int, flags 0x20080000000000) */
    ue420_byte at_0090_GameInstance[0x8]; /* +0x90: GameInstance (Object, flags 0x20080000000000) */
    ue420_byte at_0098_ActiveMusic[0x8]; /* +0x98: ActiveMusic (Object, flags 0x20080000080008) */
    ue420_byte at_00a0_LevelLoadingMusicState[0xa8]; /* +0xa0: LevelLoadingMusicState (Enum, flags 0x20080000002000) */
};

/* Class params 0x143a5f2b0; size 0x3b8. */
struct UE420_MBNotificationManagerWidget {
    ue420_byte unknown_0000[0x390];
    ue420_byte at_0390_InviteNotificationWidgetClass[0x8]; /* +0x390: InviteNotificationWidgetClass (Class, flags 0x14000000000015) */
    ue420_byte at_0398_NotificationContainer[0x8]; /* +0x398: NotificationContainer (Object, flags 0x1000000008200c) */
    ue420_byte at_03a0_OnlineSessionManager[0x8]; /* +0x3a0: OnlineSessionManager (Object, flags 0x40000000002000) */
    ue420_byte at_03a8_QueuedInviteIds[0x10]; /* +0x3a8: QueuedInviteIds (Array, flags 0x40000000002000) */
};

/* Class params 0x143a5fad0; size 0x128. */
struct UE420_MBOnlinePlayerIdManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_GameInstance[0x8]; /* +0x28: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0030_PendingPlayFabIdRequests[0x50]; /* +0x30: PendingPlayFabIdRequests (Map, flags 0x40008000002000) */
    ue420_byte at_0080_NativeIdToPlayFabId[0x50]; /* +0x80: NativeIdToPlayFabId (Map, flags 0x40000000002000) */
    ue420_byte at_00d0_PlayFabIdToNativeId[0x58]; /* +0xd0: PlayFabIdToNativeId (Map, flags 0x40000000002000) */
};

/* Class params 0x143a60bd0; size 0x208. */
struct UE420_MBOnlineSessionManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_OnReadFriendsCompleted[0x10]; /* +0x28: OnReadFriendsCompleted (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0038_OnOnlineLogout[0x10]; /* +0x38: OnOnlineLogout (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0048_OnOnlineLogin[0x10]; /* +0x48: OnOnlineLogin (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0058_OnControllerDisconnect[0x10]; /* +0x58: OnControllerDisconnect (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0068_OnControllerConnect[0x10]; /* +0x68: OnControllerConnect (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0078_OnInviteReceived[0x10]; /* +0x78: OnInviteReceived (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0088_OnInviteRemoved[0x10]; /* +0x88: OnInviteRemoved (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0098_bIsDebugLobby[0x20]; /* +0x98: bIsDebugLobby (Bool, flags 0x10000000000004) */
    ue420_byte at_00b8_CustomGameManager[0x8]; /* +0xb8: CustomGameManager (Object, flags 0x40000000000000) */
    ue420_byte at_00c0_PartyManager[0x8]; /* +0xc0: PartyManager (Object, flags 0x40000000000000) */
    ue420_byte at_00c8_VoiceChatManager[0x8]; /* +0xc8: VoiceChatManager (Object, flags 0x40000000000000) */
    ue420_byte at_00d0_DirectPartyVoiceChatManager[0x8]; /* +0xd0: DirectPartyVoiceChatManager (Object, flags 0x40000000000000) */
    ue420_byte at_00d8_GameInstance[0x8]; /* +0xd8: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_00e0_ActiveNativeId[0x20]; /* +0xe0: ActiveNativeId (Struct, flags 0x40000000000000) */
    ue420_byte at_0100_PendingInvites[0x50]; /* +0x100: PendingInvites (Map, flags 0x40000000000000) */
    ue420_byte at_0150_LastInviteId[0x4]; /* +0x150: LastInviteId (Int, flags 0x40000000000000) */
    ue420_byte at_0154_LastReadFriendsTime[0x4]; /* +0x154: LastReadFriendsTime (Float, flags 0x40000000000000) */
    ue420_byte at_0158_LastSeenInviteNotificationId[0xb0]; /* +0x158: LastSeenInviteNotificationId (Int, flags 0x40000000000000) */
};

/* Class params 0x143a6b830; size 0x1a8. */
struct UE420_MBPFBackfillingManager {
    ue420_byte unknown_0000[0x48];
    ue420_byte at_0048_GameInstance[0x8]; /* +0x48: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0050_MatchmakingConfigProvider[0x158]; /* +0x50: MatchmakingConfigProvider (Object, flags 0x40000000000000) */
};

/* Class params 0x143a720d0; size 0x458. */
struct UE420_MBPFMatchmakingManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_GameInstance[0x8]; /* +0x30: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0038_PartyManager[0x8]; /* +0x38: PartyManager (Object, flags 0x40000000000000) */
    ue420_byte at_0040_OnlineStatusMessages[0x8]; /* +0x40: OnlineStatusMessages (Object, flags 0x40000000000000) */
    ue420_byte at_0048_MatchmakingConfigProvider[0x320]; /* +0x48: MatchmakingConfigProvider (Object, flags 0x40000000000000) */
    ue420_byte at_0368_OnMatchmakingStarted[0x10]; /* +0x368: OnMatchmakingStarted (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0378_OnMatchmakingCancelled[0x10]; /* +0x378: OnMatchmakingCancelled (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0388_OnMatchmakingStatusChanged[0x10]; /* +0x388: OnMatchmakingStatusChanged (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0398_OnMatchmakingCancelComplete[0x10]; /* +0x398: OnMatchmakingCancelComplete (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_03a8_OnMatchmakingEstimateUpdated[0xb0]; /* +0x3a8: OnMatchmakingEstimateUpdated (MulticastDelegate, flags 0x40000000080000) */
};

/* Class params 0x143a74b80; size 0x140. */
struct UE420_MBPFRegionManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_OnRegionsPingedDelegate[0x98]; /* +0x30: OnRegionsPingedDelegate (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_00c8_GameInstance[0x78]; /* +0xc8: GameInstance (Object, flags 0x40000000000000) */
};

/* Class params 0x143a75330; size 0x188. */
struct UE420_MBPFServerMigrationManager {
    ue420_byte unknown_0000[0x60];
    ue420_byte at_0060_State[0x8]; /* +0x60: State (Enum, flags 0x40000000002000) */
    ue420_byte at_0068_GameInstance[0x8]; /* +0x68: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0070_ConnectedPlayersCount[0x8]; /* +0x70: ConnectedPlayersCount (Int, flags 0x40000000002000) */
    ue420_byte at_0078_MatchmakingConfigProvider[0x110]; /* +0x78: MatchmakingConfigProvider (Object, flags 0x40000000002000) */
};

/* Class params 0x143a69140; size 0x630. */
struct UE420_MBPartyManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_OnPartyUpdated[0x10]; /* +0x30: OnPartyUpdated (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0040_OnlineSessionManager[0x8]; /* +0x40: OnlineSessionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0048_OnlineStatusMessages[0x5e8]; /* +0x48: OnlineStatusMessages (Object, flags 0x40000000000000) */
};

/* Class params 0x143a69f20; size 0x3d0. */
struct UE420_MBPartyPanelWidget {
    ue420_byte unknown_0000[0x2d8];
    ue420_byte at_02d8_OnlineSessionManager[0x8]; /* +0x2d8: OnlineSessionManager (Object, flags 0x20080000002000) */
    ue420_byte at_02e0_PartyManager[0x8]; /* +0x2e0: PartyManager (Object, flags 0x20080000002000) */
    ue420_byte at_02e8_VoiceChatManager[0x8]; /* +0x2e8: VoiceChatManager (Object, flags 0x20080000002000) */
    ue420_byte at_02f0_MemberData[0x10]; /* +0x2f0: MemberData (Array, flags 0x20080000002014) */
    ue420_byte at_0300_LocalMemberData[0x80]; /* +0x300: LocalMemberData (Struct, flags 0x20080000002014) */
    ue420_byte at_0380_PartyUpdateCounter[0x20]; /* +0x380: PartyUpdateCounter (Int, flags 0x20080000002000) */
    ue420_byte at_03a0_bLoginPending[0x30]; /* +0x3a0: bLoginPending (Bool, flags 0x20080000002014) */
};

/* Class params 0x143a70950; size 0xa38. */
struct UE420_MBPlayerAccountManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_HeroBuildModCount[0x4]; /* +0x28: HeroBuildModCount (Int, flags 0x10000000004014) */
    ue420_byte at_002c_HeroBuildCount[0x4]; /* +0x2c: HeroBuildCount (Int, flags 0x10000000004014) */
    ue420_byte at_0030_HeroFreeBuildCount[0x8]; /* +0x30: HeroFreeBuildCount (Int, flags 0x10000000004014) */
    ue420_byte at_0038_AccountLevellingCsv[0x10]; /* +0x38: AccountLevellingCsv (Str, flags 0x10000000004000) */
    ue420_byte at_0048_HeroLevellingCsv[0x10]; /* +0x48: HeroLevellingCsv (Str, flags 0x10000000004000) */
    ue420_byte at_0058_CommonLevellingCsv[0x10]; /* +0x58: CommonLevellingCsv (Str, flags 0x10000000004000) */
    ue420_byte at_0068_CreditsTableCsv[0x10]; /* +0x68: CreditsTableCsv (Str, flags 0x10000000004000) */
    ue420_byte at_0078_PartsTableCsv[0x10]; /* +0x78: PartsTableCsv (Str, flags 0x10000000004000) */
    ue420_byte at_0088_StatManagerClass[0x78]; /* +0x88: StatManagerClass (Struct, flags 0x10000000004000) */
    ue420_byte at_0100_OnPartsChanged[0x10]; /* +0x100: OnPartsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0110_OnModsChanged[0x10]; /* +0x110: OnModsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0120_OnHeroBuildsChanged[0x10]; /* +0x120: OnHeroBuildsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0130_OnCreditsChanged[0x10]; /* +0x130: OnCreditsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0140_OnCustomisationChanged[0x10]; /* +0x140: OnCustomisationChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0150_OnCustomisationPurchased[0x10]; /* +0x150: OnCustomisationPurchased (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0160_OnCustomisationEquipped[0x10]; /* +0x160: OnCustomisationEquipped (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0170_OnPurchaseResult[0x10]; /* +0x170: OnPurchaseResult (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0180_OnAwardsGiven[0x10]; /* +0x180: OnAwardsGiven (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0190_OnTauntChanged[0x10]; /* +0x190: OnTauntChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01a0_OnTauntPurchased[0x10]; /* +0x1a0: OnTauntPurchased (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01b0_OnTauntEquipped[0x10]; /* +0x1b0: OnTauntEquipped (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01c0_OnTauntPurchaseFailure[0x10]; /* +0x1c0: OnTauntPurchaseFailure (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01d0_OnSkinChanged[0x10]; /* +0x1d0: OnSkinChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01e0_OnSkinPurchased[0x10]; /* +0x1e0: OnSkinPurchased (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_01f0_OnSkinEquipped[0x10]; /* +0x1f0: OnSkinEquipped (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0200_OnSkinPurchaseFailure[0x10]; /* +0x200: OnSkinPurchaseFailure (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0210_OnAchievementChanged[0x10]; /* +0x210: OnAchievementChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0220_OnEntitlementItemsChanged[0x10]; /* +0x220: OnEntitlementItemsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0230_OnModBuildFailure[0x10]; /* +0x230: OnModBuildFailure (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0240_OnModTrashFailure[0x10]; /* +0x240: OnModTrashFailure (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0250_OnNewModBuildMade[0x10]; /* +0x250: OnNewModBuildMade (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0260_OnCustomisationPurchaseFailure[0x10]; /* +0x260: OnCustomisationPurchaseFailure (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0270_OnPendingRequestsChanged[0x10]; /* +0x270: OnPendingRequestsChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0280_OnOnlineStatusChanged[0x10]; /* +0x280: OnOnlineStatusChanged (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0290_OnTutorialStatusCached[0x10]; /* +0x290: OnTutorialStatusCached (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_02a0_OnEulaStatusCached[0x10]; /* +0x2a0: OnEulaStatusCached (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_02b0_OnMatchPagesUpdated[0x10]; /* +0x2b0: OnMatchPagesUpdated (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_02c0_OnMatchDetailsUpdated[0x70]; /* +0x2c0: OnMatchDetailsUpdated (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0330_XPUpdateMulticasters[0x50]; /* +0x330: XPUpdateMulticasters (Map, flags 0x40008000000000) */
    ue420_byte at_0380_MostRecentXPUpdate[0x170]; /* +0x380: MostRecentXPUpdate (Struct, flags 0x40000000000000) */
    ue420_byte at_04f0_GameInstance[0x8]; /* +0x4f0: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_04f8_OnlineSessionManager[0x10]; /* +0x4f8: OnlineSessionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0508_bFakeOnlineResponses[0x1]; /* +0x508: bFakeOnlineResponses (Bool, flags 0x40000000002000) */
    ue420_byte at_0509_bIsFreeBuildAvailable[0x1]; /* +0x509: bIsFreeBuildAvailable (Bool, flags 0x40000000002000) */
    ue420_byte at_050a_bIsFreeBuildActive[0x6]; /* +0x50a: bIsFreeBuildActive (Bool, flags 0x40000000002000) */
    ue420_byte at_0510_AccountData[0x60]; /* +0x510: AccountData (Map, flags 0x40008000000000) */
    ue420_byte at_0570_PlayerIdMap[0x50]; /* +0x570: PlayerIdMap (Map, flags 0x40000000002000) */
    ue420_byte at_05c0_LocalPlayerId[0x28]; /* +0x5c0: LocalPlayerId (Struct, flags 0x40000000002000) */
    ue420_byte at_05e8_LocalPlayerLoginStatus[0x8]; /* +0x5e8: LocalPlayerLoginStatus (Enum, flags 0x40000000002000) */
    ue420_byte at_05f0_LocalPlayerLoggedInMulticaster[0x10]; /* +0x5f0: LocalPlayerLoggedInMulticaster (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0600_LocalPlayerLoggedOutMulticaster[0x10]; /* +0x600: LocalPlayerLoggedOutMulticaster (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0610_ModAssetMap[0x50]; /* +0x610: ModAssetMap (Map, flags 0x40000000002000) */
    ue420_byte at_0660_CustomisationAssetMap[0x50]; /* +0x660: CustomisationAssetMap (Map, flags 0x40000000002000) */
    ue420_byte at_06b0_TauntAssetMap[0x50]; /* +0x6b0: TauntAssetMap (Map, flags 0x40000000002000) */
    ue420_byte at_0700_SkinAssetMap[0x50]; /* +0x700: SkinAssetMap (Map, flags 0x40000000002000) */
    ue420_byte at_0750_AchievementAssetMap[0x50]; /* +0x750: AchievementAssetMap (Map, flags 0x40000000002000) */
    ue420_byte at_07a0_PlayerIdToDisplayName[0x50]; /* +0x7a0: PlayerIdToDisplayName (Map, flags 0x40000000002000) */
    ue420_byte at_07f0_bHasPendingDirtyUpdate[0x8]; /* +0x7f0: bHasPendingDirtyUpdate (Bool, flags 0x40000000000000) */
    ue420_byte at_07f8_ViewedMods[0x10]; /* +0x7f8: ViewedMods (Array, flags 0x40000000000000) */
    ue420_byte at_0808_ViewedCustomisations[0x10]; /* +0x808: ViewedCustomisations (Array, flags 0x40000000000000) */
    ue420_byte at_0818_ViewedTaunts[0x10]; /* +0x818: ViewedTaunts (Array, flags 0x40000000000000) */
    ue420_byte at_0828_TutorialStatus[0x8]; /* +0x828: TutorialStatus (Enum, flags 0x40000000000000) */
    ue420_byte at_0830_CompletedTutorials[0x10]; /* +0x830: CompletedTutorials (Array, flags 0x40000000000000) */
    ue420_byte at_0840_EulaStatus[0x4]; /* +0x840: EulaStatus (Enum, flags 0x40000000000000) */
    ue420_byte at_0844_CachedBuildModPartsCost[0x4]; /* +0x844: CachedBuildModPartsCost (Int, flags 0x40000000000000) */
    ue420_byte at_0848_CachedTrashModPartsCost[0x8]; /* +0x848: CachedTrashModPartsCost (Int, flags 0x40000000000000) */
    ue420_byte at_0850_CachedAccountXPData[0x30]; /* +0x850: CachedAccountXPData (Struct, flags 0x40000000000000) */
    ue420_byte at_0880_CachedHeroXPData[0x30]; /* +0x880: CachedHeroXPData (Struct, flags 0x40000000000000) */
    ue420_byte at_08b0_CachedCreditsData[0x18]; /* +0x8b0: CachedCreditsData (Struct, flags 0x40000000000000) */
    ue420_byte at_08c8_CachedPartsData[0x18]; /* +0x8c8: CachedPartsData (Struct, flags 0x40000000000000) */
    ue420_byte at_08e0_MaxStatsCacheMinutes[0x8]; /* +0x8e0: MaxStatsCacheMinutes (Float, flags 0x40000000000000) */
    ue420_byte at_08e8_StoreAssetList[0x8]; /* +0x8e8: StoreAssetList (Object, flags 0x40000000000000) */
    ue420_byte at_08f0_AchievementAssetList[0x8]; /* +0x8f0: AchievementAssetList (Object, flags 0x40000000000000) */
    ue420_byte at_08f8_PlayerClassTable[0x8]; /* +0x8f8: PlayerClassTable (Object, flags 0x40000000000000) */
    ue420_byte at_0900_StatsManager[0x8]; /* +0x900: StatsManager (Object, flags 0x40000000000000) */
    ue420_byte at_0908_AccountInformationStrings[0x10]; /* +0x908: AccountInformationStrings (Array, flags 0x40000000000000) */
    ue420_byte at_0918_PendingRequests[0x10]; /* +0x918: PendingRequests (Array, flags 0x40000000000000) */
    ue420_byte at_0928_CurrentOnlineStatus[0x4]; /* +0x928: CurrentOnlineStatus (Enum, flags 0x40000000000000) */
    ue420_byte at_092c_PIERequestFailureRate[0x4]; /* +0x92c: PIERequestFailureRate (Float, flags 0x40000000000000) */
    ue420_byte at_0930_DelayedPIEOnlineRequests[0x10]; /* +0x930: DelayedPIEOnlineRequests (Array, flags 0x40000000000000) */
    ue420_byte at_0940_SendPIEOnlineRequestTimer[0x18]; /* +0x940: SendPIEOnlineRequestTimer (Struct, flags 0x40000000000000) */
    ue420_byte at_0958_DirtyCharacterTimerHandle[0x8]; /* +0x958: DirtyCharacterTimerHandle (Struct, flags 0x40000000000000) */
    ue420_byte at_0960_PushingDirtyCharacterCustomisation[0x8]; /* +0x960: PushingDirtyCharacterCustomisation (Bool, flags 0x40000000000000) */
    ue420_byte at_0968_DirtyCharacterCustomisations[0x10]; /* +0x968: DirtyCharacterCustomisations (Array, flags 0x40000000000000) */
    ue420_byte at_0978_LastDirtyCharacterCustomisations[0x10]; /* +0x978: LastDirtyCharacterCustomisations (Array, flags 0x40000000000000) */
    ue420_byte at_0988_PendingMatchHistoryTeamMemberRefs[0x50]; /* +0x988: PendingMatchHistoryTeamMemberRefs (Map, flags 0x40000000000000) */
    ue420_byte at_09d8_PendingMatchTeamMemberCount[0x8]; /* +0x9d8: PendingMatchTeamMemberCount (Int, flags 0x40000000000000) */
    ue420_byte at_09e0_Server_PendingEndGameUpdate[0x58]; /* +0x9e0: Server_PendingEndGameUpdate (Struct, flags 0x40000000000000) */
};

/* Class params 0x143a87990; size 0x68. */
struct UE420_MBPlayerAssetHandler {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_PlayerLoadStatusDelegate[0x10]; /* +0x28: PlayerLoadStatusDelegate (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0038_PlayerClassTable[0x8]; /* +0x38: PlayerClassTable (Object, flags 0x40000000000000) */
    ue420_byte at_0040_PlayerAssetManager[0x8]; /* +0x40: PlayerAssetManager (Object, flags 0x40000000000000) */
    ue420_byte at_0048_GameInstance[0x8]; /* +0x48: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0050_PlayerRecords[0x10]; /* +0x50: PlayerRecords (Array, flags 0x40000000000000) */
    ue420_byte at_0060_OverrideRequestLevel[0x8]; /* +0x60: OverrideRequestLevel (Enum, flags 0x40000000000000) */
};

/* Class params 0x143a88450; size 0x158. */
struct UE420_MBPlayerAvatarManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_GameInstance[0x8]; /* +0x28: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0030_AvatarTextureRequests[0x10]; /* +0x30: AvatarTextureRequests (Array, flags 0x40008000002000) */
    ue420_byte at_0040_AvatarTextureBatchRequestQueue[0x10]; /* +0x40: AvatarTextureBatchRequestQueue (Array, flags 0x40008000002000) */
    ue420_byte at_0050_NextRequestId[0x8]; /* +0x50: NextRequestId (Int, flags 0x40000000002000) */
    ue420_byte at_0058_AvatarTextureSetMap[0x50]; /* +0x58: AvatarTextureSetMap (Map, flags 0x40000000002000) */
    ue420_byte at_00a8_PendingPlayerUserInfoRequests[0x50]; /* +0xa8: PendingPlayerUserInfoRequests (Map, flags 0x40008000002000) */
    ue420_byte at_00f8_CachedPlayerUserInfo[0x60]; /* +0xf8: CachedPlayerUserInfo (Map, flags 0x40000000002000) */
};

/* Class params 0x143a920c0; size 0x1098. */
struct UE420_MBPlayerController {
    ue420_byte unknown_0000[0xb18];
    ue420_byte at_0b18_DebugInputPriority[0x8]; /* +0xb18: DebugInputPriority (Int, flags 0x10000000000001) */
    ue420_byte at_0b20_DebugInputComponent[0x8]; /* +0xb20: DebugInputComponent (Object, flags 0x10000000080008) */
    ue420_byte at_0b28_FrontEndInputPriority[0x8]; /* +0xb28: FrontEndInputPriority (Int, flags 0x10000000000001) */
    ue420_byte at_0b30_FrontEndInputComponent[0x8]; /* +0xb30: FrontEndInputComponent (Object, flags 0x10000000080008) */
    ue420_byte at_0b38_ProfanityFilterComponent[0x8]; /* +0xb38: ProfanityFilterComponent (Object, flags 0x100000000a001d) */
    ue420_byte at_0b40_CameraTurnSpeed[0x4]; /* +0xb40: CameraTurnSpeed (Float, flags 0x10000000000005) */
    ue420_byte at_0b44_CameraFastTurnInputThreshold[0x4]; /* +0xb44: CameraFastTurnInputThreshold (Float, flags 0x10000000000005) */
    ue420_byte at_0b48_CameraFastTurnSpeed[0x4]; /* +0xb48: CameraFastTurnSpeed (Float, flags 0x10000000000005) */
    ue420_byte at_0b4c_CameraFastTurnBlendInTime[0x4]; /* +0xb4c: CameraFastTurnBlendInTime (Float, flags 0x10000000000005) */
    ue420_byte at_0b50_CameraFastTurnBlendOutTime[0x4]; /* +0xb50: CameraFastTurnBlendOutTime (Float, flags 0x10000000000005) */
    ue420_byte at_0b54_CameraFastTurnBlendAlpha[0x4]; /* +0xb54: CameraFastTurnBlendAlpha (Float, flags 0x10000000000000) */
    ue420_byte at_0b58_CameraDeltaCap[0x4]; /* +0xb58: CameraDeltaCap (Float, flags 0x10000000000005) */
    ue420_byte at_0b5c_CameraTiltSpeed[0x4]; /* +0xb5c: CameraTiltSpeed (Float, flags 0x10000000000005) */
    ue420_byte at_0b60_CameraFastTiltInputThreshold[0x4]; /* +0xb60: CameraFastTiltInputThreshold (Float, flags 0x10000000000005) */
    ue420_byte at_0b64_CameraFastTiltSpeed[0x4]; /* +0xb64: CameraFastTiltSpeed (Float, flags 0x10000000000005) */
    ue420_byte at_0b68_CameraFastTiltBlendInTime[0x4]; /* +0xb68: CameraFastTiltBlendInTime (Float, flags 0x10000000000005) */
    ue420_byte at_0b6c_CameraFastTiltBlendOutTime[0x4]; /* +0xb6c: CameraFastTiltBlendOutTime (Float, flags 0x10000000000005) */
    ue420_byte at_0b70_CameraFastTiltBlendAlpha[0x8]; /* +0xb70: CameraFastTiltBlendAlpha (Float, flags 0x10000000000000) */
    ue420_byte at_0b78_LockOnReticleActorClass[0x8]; /* +0xb78: LockOnReticleActorClass (Class, flags 0x14000000010015) */
    ue420_byte at_0b80_LockOnReticleActor[0x8]; /* +0xb80: LockOnReticleActor (Object, flags 0x10000000002014) */
    ue420_byte at_0b88_ActionTargetReticleActorClass[0x8]; /* +0xb88: ActionTargetReticleActorClass (Class, flags 0x14000000010015) */
    ue420_byte at_0b90_ActionTargetReticleActor[0x8]; /* +0xb90: ActionTargetReticleActor (Object, flags 0x10000000002014) */
    ue420_byte at_0b98_SpectatorManagerClass[0x8]; /* +0xb98: SpectatorManagerClass (Class, flags 0x14000000010001) */
    ue420_byte at_0ba0_CharacterSelectScreenClass[0x8]; /* +0xba0: CharacterSelectScreenClass (Class, flags 0x14000000010001) */
    ue420_byte at_0ba8_StatsScreenClass[0x8]; /* +0xba8: StatsScreenClass (Class, flags 0x14000000010001) */
    ue420_byte at_0bb0_InGameMenuScreenClass[0x8]; /* +0xbb0: InGameMenuScreenClass (Class, flags 0x14000000010001) */
    ue420_byte at_0bb8_ModScreenClass[0x8]; /* +0xbb8: ModScreenClass (Class, flags 0x14000000010001) */
    ue420_byte at_0bc0_bMatchmakingPanelHidden[0x8]; /* +0xbc0: bMatchmakingPanelHidden (Bool, flags 0x10000000010001) */
    ue420_byte at_0bc8_MatchmakingPanelHiddenToken[0x8]; /* +0xbc8: MatchmakingPanelHiddenToken (Name, flags 0x10000000010001) */
    ue420_byte at_0bd0_bPartyPanelHidden[0x8]; /* +0xbd0: bPartyPanelHidden (Bool, flags 0x10000000010001) */
    ue420_byte at_0bd8_PartyPanelHiddenToken[0x8]; /* +0xbd8: PartyPanelHiddenToken (Name, flags 0x10000000010001) */
    ue420_byte at_0be0_bPartyPanelDisabled[0x8]; /* +0xbe0: bPartyPanelDisabled (Bool, flags 0x10000000010001) */
    ue420_byte at_0be8_PartyPanelDisabledToken[0x8]; /* +0xbe8: PartyPanelDisabledToken (Name, flags 0x10000000010001) */
    ue420_byte at_0bf0_ChangeCharacterAnywhere[0x8]; /* +0xbf0: ChangeCharacterAnywhere (Bool, flags 0x10000000010005) */
    ue420_byte at_0bf8_MasterSoundClassMap[0x50]; /* +0xbf8: MasterSoundClassMap (Map, flags 0x10000000010015) */
    ue420_byte at_0c48_OnMikoHairTestUpdate[0x10]; /* +0xc48: OnMikoHairTestUpdate (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0c58_DebugContacts[0x50]; /* +0xc58: DebugContacts (Map, flags 0x14000000010001) */
    ue420_byte at_0ca8_ProfileLoadTest_CharIndex[0x4]; /* +0xca8: ProfileLoadTest_CharIndex (Int, flags 0x10000000002000) */
    ue420_byte at_0cac_bCosmeticKioskPlayerReadyStatus[0x4]; /* +0xcac: bCosmeticKioskPlayerReadyStatus (Bool, flags 0x10000000002000) */
    ue420_byte at_0cb0_OnChatUpdated[0x10]; /* +0xcb0: OnChatUpdated (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0cc0_OnChatWheelSelectionReceived[0x10]; /* +0xcc0: OnChatWheelSelectionReceived (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0cd0_TargetingSettings_KeyboardAndMouse[0x8]; /* +0xcd0: TargetingSettings_KeyboardAndMouse (Struct, flags 0x10000000000000) */
    ue420_byte at_0cd8_TargetingSettings_Controller[0x18]; /* +0xcd8: TargetingSettings_Controller (Struct, flags 0x10000000000000) */
    ue420_byte at_0cf0_LeaveReason[0x20]; /* +0xcf0: LeaveReason (Str, flags 0x10000000000000) */
    ue420_byte at_0d10_TargetableProxies[0x28]; /* +0xd10: TargetableProxies (Array, flags 0x20080000002000) */
    ue420_byte at_0d38_ComboRecords[0x10]; /* +0xd38: ComboRecords (Array, flags 0x40000000000000) */
    ue420_byte at_0d48_LastStickInput[0x8]; /* +0xd48: LastStickInput (Struct, flags 0x40000000000000) */
    ue420_byte at_0d50_MostRecentInputTimeStamp[0x4]; /* +0xd50: MostRecentInputTimeStamp (Float, flags 0x40000000002000) */
    ue420_byte at_0d54_bIsProvidingAnyFrontEndInput[0x4]; /* +0xd54: bIsProvidingAnyFrontEndInput (Bool, flags 0x40000000002000) */
    ue420_byte at_0d58_ChatWheelHistory[0x50]; /* +0xd58: ChatWheelHistory (Map, flags 0x40000000000000) */
    ue420_byte at_0da8_MostRecentAcknowledgeableChatType[0x4]; /* +0xda8: MostRecentAcknowledgeableChatType (Enum, flags 0x40000000000000) */
    ue420_byte at_0dac_MostRecentAcknowledgeableChatTimeStamp[0x4]; /* +0xdac: MostRecentAcknowledgeableChatTimeStamp (Float, flags 0x40000000000000) */
    ue420_byte at_0db0_ChatWheelSpamFilter[0x20]; /* +0xdb0: ChatWheelSpamFilter (Struct, flags 0x40000000000000) */
    ue420_byte at_0dd0_ChatActive[0x1]; /* +0xdd0: ChatActive (Bool, flags 0x40000000000000) */
    ue420_byte at_0dd1_CurrentChannel[0x7]; /* +0xdd1: CurrentChannel (Enum, flags 0x40000000000000) */
    ue420_byte at_0dd8_CurrentTarget[0x10]; /* +0xdd8: CurrentTarget (Str, flags 0x40000000000000) */
    ue420_byte at_0de8_CurrentMessage[0x10]; /* +0xde8: CurrentMessage (Str, flags 0x40000000000000) */
    ue420_byte at_0df8_PreviousChannel[0x8]; /* +0xdf8: PreviousChannel (Enum, flags 0x40000000000000) */
    ue420_byte at_0e00_ChatHistory[0x10]; /* +0xe00: ChatHistory (Array, flags 0x40000000000000) */
    ue420_byte at_0e10_TimerHandle_HideOldChat[0x8]; /* +0xe10: TimerHandle_HideOldChat (Struct, flags 0x40000000000000) */
    ue420_byte at_0e18_ChatIdGenerator[0x4]; /* +0xe18: ChatIdGenerator (Struct, flags 0x40000000000000) */
    ue420_byte at_0e1c_MutedChannels[0x4]; /* +0xe1c: MutedChannels (Int, flags 0x40000000000000) */
    ue420_byte at_0e20_MutedPlayers[0x10]; /* +0xe20: MutedPlayers (Array, flags 0x40000000000000) */
    ue420_byte at_0e30_ChatWidgets[0x10]; /* +0xe30: ChatWidgets (Array, flags 0x40008000000008) */
    ue420_byte at_0e40_ChatWheelWidgets[0x10]; /* +0xe40: ChatWheelWidgets (Array, flags 0x40008000000008) */
    ue420_byte at_0e50_MuteAudioTokens[0x10]; /* +0xe50: MuteAudioTokens (Array, flags 0x40000000000000) */
    ue420_byte at_0e60_EnabledCheats[0x18]; /* +0xe60: EnabledCheats (Array, flags 0x40000000000000) */
    ue420_byte at_0e78_CosmeticCharacterLockInState[0x8]; /* +0xe78: CosmeticCharacterLockInState (Enum, flags 0x40000000000000) */
    ue420_byte at_0e80_CosmeticCharacterClass[0x8]; /* +0xe80: CosmeticCharacterClass (Name, flags 0x40000000000000) */
    ue420_byte at_0e88_CosmeticSuperAbilityIndex[0x8]; /* +0xe88: CosmeticSuperAbilityIndex (Int, flags 0x40000000000000) */
    ue420_byte at_0e90_CosmeticMods[0x10]; /* +0xe90: CosmeticMods (Array, flags 0x40000000000000) */
    ue420_byte at_0ea0_CosmeticCustomisations[0x10]; /* +0xea0: CosmeticCustomisations (Array, flags 0x40000000000000) */
    ue420_byte at_0eb0_CosmeticUserData[0x10]; /* +0xeb0: CosmeticUserData (Struct, flags 0x40000000000000) */
    ue420_byte at_0ec0_CosmeticTaunts[0x10]; /* +0xec0: CosmeticTaunts (Array, flags 0x40000000000000) */
    ue420_byte at_0ed0_CosmeticSkins[0x10]; /* +0xed0: CosmeticSkins (Array, flags 0x40000000000000) */
    ue420_byte at_0ee0_CosmeticAssetSession[0x8]; /* +0xee0: CosmeticAssetSession (Object, flags 0x40000000000000) */
    ue420_byte at_0ee8_CosmeticTauntAssets[0x10]; /* +0xee8: CosmeticTauntAssets (Array, flags 0x40000000000000) */
    ue420_byte at_0ef8_LastSelectedModBuildIndices[0x50]; /* +0xef8: LastSelectedModBuildIndices (Map, flags 0x40000000000000) */
    ue420_byte at_0f48_CharacterSelectMulticaster[0x10]; /* +0xf48: CharacterSelectMulticaster (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0f58_CharacterLockInMulticaster[0x10]; /* +0xf58: CharacterLockInMulticaster (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0f68_SpectatorManager[0x9]; /* +0xf68: SpectatorManager (Object, flags 0x40000000000000) */
    ue420_byte at_0f71_bForceShowMouseCursor[0x1]; /* +0xf71: bForceShowMouseCursor (Bool, flags 0x40000000000000) */
    ue420_byte at_0f72_bResetCameraOnPosses[0x6]; /* +0xf72: bResetCameraOnPosses (Bool, flags 0x40000000002000) */
    ue420_byte at_0f78_FrontendInputChangedMulticaster[0x90]; /* +0xf78: FrontendInputChangedMulticaster (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_1008_bCanUseDebugCam[0x1]; /* +0x1008: bCanUseDebugCam (Bool, flags 0x40000000002000) */
    ue420_byte at_1009_AcceleratingLook_X[0x1]; /* +0x1009: AcceleratingLook_X (Bool, flags 0x40000000002000) */
    ue420_byte at_100a_AcceleratingLook_Y[0x2]; /* +0x100a: AcceleratingLook_Y (Bool, flags 0x40000000002000) */
    ue420_byte at_100c_AccelerationTimer_X[0x4]; /* +0x100c: AccelerationTimer_X (Float, flags 0x40000000002000) */
    ue420_byte at_1010_AccelerationTimer_Y[0x4]; /* +0x1010: AccelerationTimer_Y (Float, flags 0x40000000002000) */
    ue420_byte at_1014_bDebugLookControls[0x4]; /* +0x1014: bDebugLookControls (Bool, flags 0x40000000002000) */
    ue420_byte at_1018_JoinTime[0x8]; /* +0x1018: JoinTime (Float, flags 0x40000000002000) */
    ue420_byte at_1020_PendingChangeClassParams[0x68]; /* +0x1020: PendingChangeClassParams (Struct, flags 0x40000000002000) */
    ue420_byte at_1088_PendingChangeClassTimeRemaining[0x10]; /* +0x1088: PendingChangeClassTimeRemaining (Float, flags 0x40000000002000) */
};

/* Class params 0x144517ec0; size 0x15e0. */
struct UE420_MBPlayerState {
    ue420_byte unknown_0000[0x1190];
    ue420_byte at_1190_UnrealPlayerID[0x8]; /* +0x1190: UnrealPlayerID (Int, flags 0x10000000000000) */
    ue420_byte at_1198_PlayerName[0x10]; /* +0x1198: PlayerName (Str, flags 0x10000000000014) */
    ue420_byte at_11a8_NativePlayerId[0x18]; /* +0x11a8: NativePlayerId (Struct, flags 0x10000000000000) */
    ue420_byte at_11c0_RespawnTimer[0x8]; /* +0x11c0: RespawnTimer (Float, flags 0x10000000000000) */
    ue420_byte at_11c8_RespawnEventName[0x8]; /* +0x11c8: RespawnEventName (Name, flags 0x10000000000000) */
    ue420_byte at_11d0_DeathTimer[0x8]; /* +0x11d0: DeathTimer (Float, flags 0x10000000000000) */
    ue420_byte at_11d8_PlayerInputState[0x78]; /* +0x11d8: PlayerInputState (Struct, flags 0x10008000000014) */
    ue420_byte at_1250_StatisticsState[0xb0]; /* +0x1250: StatisticsState (Struct, flags 0x10000000000014) */
    ue420_byte at_1300_ModManagerState[0x30]; /* +0x1300: ModManagerState (Struct, flags 0x10000000000014) */
    ue420_byte at_1330_CameraManagerState[0x98]; /* +0x1330: CameraManagerState (Struct, flags 0x10000000000014) */
    ue420_byte at_13c8_TauntDefs[0x10]; /* +0x13c8: TauntDefs (Array, flags 0x10000000000000) */
    ue420_byte at_13d8_CustomisationDefs[0x10]; /* +0x13d8: CustomisationDefs (Array, flags 0x10000000000000) */
    ue420_byte at_13e8_CustomisationUserData[0x10]; /* +0x13e8: CustomisationUserData (Struct, flags 0x10000000000000) */
    ue420_byte at_13f8_SkinDefAssetPath[0x18]; /* +0x13f8: SkinDefAssetPath (Struct, flags 0x10000000000000) */
    ue420_byte at_1410_NextPlayerClassName[0x10]; /* +0x1410: NextPlayerClassName (Name, flags 0x10000000000000) */
    ue420_byte at_1420_OwnMoveDelta[0x30]; /* +0x1420: OwnMoveDelta (Struct, flags 0x10000000000000) */
    ue420_byte at_1450_TotalMoveDelta[0x30]; /* +0x1450: TotalMoveDelta (Struct, flags 0x10000000000000) */
    ue420_byte at_1480_LastUpdateFrame[0x4]; /* +0x1480: LastUpdateFrame (Int, flags 0x10000000000000) */
    ue420_byte at_1484_TargetingSettings_KeyboardAndMouse[0x8]; /* +0x1484: TargetingSettings_KeyboardAndMouse (Struct, flags 0x10000000000000) */
    ue420_byte at_148c_TargetingSettings_Controller[0x8]; /* +0x148c: TargetingSettings_Controller (Struct, flags 0x10000000000000) */
    ue420_byte at_1494_HealthRegenTimer[0x4]; /* +0x1494: HealthRegenTimer (Struct, flags 0x20080000000000) */
    ue420_byte at_1498_StaminaRegenTimer[0x4]; /* +0x1498: StaminaRegenTimer (Struct, flags 0x20080000000000) */
    ue420_byte at_149c_CurrentHealthIndex[0x4]; /* +0x149c: CurrentHealthIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14a0_CurrentStaminaIndex[0x4]; /* +0x14a0: CurrentStaminaIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14a4_CurrentRangeIndex[0x4]; /* +0x14a4: CurrentRangeIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14a8_CurrentAbilityIndex[0x4]; /* +0x14a8: CurrentAbilityIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14ac_CurrentSuperIndex[0x4]; /* +0x14ac: CurrentSuperIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14b0_CurrentPassivesIndex[0x8]; /* +0x14b0: CurrentPassivesIndex (Int, flags 0x20080000000000) */
    ue420_byte at_14b8_PassiveProccerIds[0x10]; /* +0x14b8: PassiveProccerIds (Array, flags 0x20080000000000) */
    ue420_byte at_14c8_MovementCurrentState[0x1]; /* +0x14c8: MovementCurrentState (Enum, flags 0x20080000000000) */
    ue420_byte at_14c9_MovementIsMounted[0x3]; /* +0x14c9: MovementIsMounted (Bool, flags 0x20080000000000) */
    ue420_byte at_14cc_MovementStateChangeTime[0x4]; /* +0x14cc: MovementStateChangeTime (Float, flags 0x20080000000000) */
    ue420_byte at_14d0_MovementIsTransitioning[0x8]; /* +0x14d0: MovementIsTransitioning (Bool, flags 0x20080000000000) */
    ue420_byte at_14d8_MovementPFXId[0x8]; /* +0x14d8: MovementPFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_14e0_MovementSFXId[0x8]; /* +0x14e0: MovementSFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_14e8_MovementStatePFXId[0x8]; /* +0x14e8: MovementStatePFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_14f0_MovementStateSFXId[0x8]; /* +0x14f0: MovementStateSFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_14f8_GrindingPFXId[0x8]; /* +0x14f8: GrindingPFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_1500_GrindingSFXId[0x8]; /* +0x1500: GrindingSFXId (Struct, flags 0x20080000000000) */
    ue420_byte at_1508_Effects_MovementSpeed[0x4]; /* +0x1508: Effects_MovementSpeed (Float, flags 0x20080000000000) */
    ue420_byte at_150c_Effects_TurnValue[0x4]; /* +0x150c: Effects_TurnValue (Float, flags 0x20080000000000) */
    ue420_byte at_1510_Effects_PreviousTurnValues[0x10]; /* +0x1510: Effects_PreviousTurnValues (Array, flags 0x20080000000000) */
    ue420_byte at_1520_Effects_SumTurnValues[0x4]; /* +0x1520: Effects_SumTurnValues (Float, flags 0x20080000000000) */
    ue420_byte at_1524_Effects_CurrentTurnIndex[0x4]; /* +0x1524: Effects_CurrentTurnIndex (Int, flags 0x20080000000000) */
    ue420_byte at_1528_ActiveCastBars[0x10]; /* +0x1528: ActiveCastBars (Array, flags 0x20080000000000) */
    ue420_byte at_1538_LastFrameControllingPlayerID[0x4]; /* +0x1538: LastFrameControllingPlayerID (Int, flags 0x20080000000000) */
    ue420_byte at_153c_ControllingPlayerID[0x4]; /* +0x153c: ControllingPlayerID (Int, flags 0x20080000000000) */
    ue420_byte at_1540_NextFrameControllingPlayerID[0x8]; /* +0x1540: NextFrameControllingPlayerID (Int, flags 0x20080000000000) */
    ue420_byte at_1548_CurrentSpawnPoint[0x8]; /* +0x1548: CurrentSpawnPoint (Object, flags 0x2040000000000000) */
    ue420_byte at_1550_ClaimedSpawnPoint[0x8]; /* +0x1550: ClaimedSpawnPoint (Struct, flags 0x40000000000000) */
    ue420_byte at_1558_ActorVisiblityList[0x10]; /* +0x1558: ActorVisiblityList (Array, flags 0x40000000000000) */
    ue420_byte at_1568_CurrentCameraYawBlendSpeed[0x4]; /* +0x1568: CurrentCameraYawBlendSpeed (Float, flags 0x40000000000000) */
    ue420_byte at_156c_SmoothCameraYaw[0x4]; /* +0x156c: SmoothCameraYaw (Float, flags 0x40000000000000) */
    ue420_byte at_1570_SmoothCameraYawLastFrame[0x4]; /* +0x1570: SmoothCameraYawLastFrame (Float, flags 0x40000000000000) */
    ue420_byte at_1574_LastCameraChangeFrame[0x4]; /* +0x1574: LastCameraChangeFrame (Int, flags 0x40000000000000) */
    ue420_byte at_1578_OnDeathMulticaster[0x10]; /* +0x1578: OnDeathMulticaster (MulticastDelegate, flags 0x2040000000080000) */
    ue420_byte at_1588_SourceRecordingStream[0x8]; /* +0x1588: SourceRecordingStream (Object, flags 0x4040000000000000) */
    ue420_byte at_1590_SourceRecordingActor[0x8]; /* +0x1590: SourceRecordingActor (Object, flags 0x4040000000000000) */
    ue420_byte at_1598_SpawnFrameNumber[0x4]; /* +0x1598: SpawnFrameNumber (Int, flags 0x40000000000000) */
    ue420_byte at_159c_DeathState[0x1]; /* +0x159c: DeathState (Enum, flags 0x40000000000000) */
    ue420_byte at_159d_bIsLivePlayer[0x1]; /* +0x159d: bIsLivePlayer (Bool, flags 0x40000000000000) */
    ue420_byte at_159e_bTeleportedThisFrame[0x2]; /* +0x159e: bTeleportedThisFrame (Bool, flags 0x40000000002000) */
    ue420_byte at_15a0_EnabledCheats[0x10]; /* +0x15a0: EnabledCheats (Array, flags 0x40000000000000) */
    ue420_byte at_15b0_FastHealthChangeProccerId[0x4]; /* +0x15b0: FastHealthChangeProccerId (Struct, flags 0x40000000000000) */
    ue420_byte at_15b4_bInputEnabled[0x1]; /* +0x15b4: bInputEnabled (Bool, flags 0x40000000000000) */
    ue420_byte at_15b5_bSpawnRespawnFX[0x3]; /* +0x15b5: bSpawnRespawnFX (Bool, flags 0x40000000000000) */
    ue420_byte at_15b8_GrindRailBoundsHandle[0x18]; /* +0x15b8: GrindRailBoundsHandle (Struct, flags 0x40000000000000) */
    ue420_byte at_15d0_bHasGameStarted[0x10]; /* +0x15d0: bHasGameStarted (Bool, flags 0x40000000000000) */
};

/* Class params 0x143a9c1c0; size 0x5e0. */
struct UE420_MBPlayerStateBase {
    ue420_byte unknown_0000[0x468];
    ue420_byte at_0468_MasterAccountId[0x10]; /* +0x468: MasterAccountId (Struct, flags 0x10000000000014) */
    ue420_byte at_0478_TitleAccountId[0x10]; /* +0x478: TitleAccountId (Struct, flags 0x10000000000014) */
    ue420_byte at_0488_PlayerClassName[0x8]; /* +0x488: PlayerClassName (Name, flags 0x10000000000034) */
    ue420_byte at_0490_PendingPlayerClassName[0x8]; /* +0x490: PendingPlayerClassName (Name, flags 0x10000000000034) */
    ue420_byte at_0498_SuperAbilityIndex[0x8]; /* +0x498: SuperAbilityIndex (Int, flags 0x10000000000034) */
    ue420_byte at_04a0_SelectedMods[0x10]; /* +0x4a0: SelectedMods (Array, flags 0x10000000000034) */
    ue420_byte at_04b0_SelectedTaunts[0x10]; /* +0x4b0: SelectedTaunts (Array, flags 0x10000000000034) */
    ue420_byte at_04c0_SelectedSkins[0x10]; /* +0x4c0: SelectedSkins (Array, flags 0x10000000000034) */
    ue420_byte at_04d0_SelectedCustomisations[0x10]; /* +0x4d0: SelectedCustomisations (Array, flags 0x10000000000034) */
    ue420_byte at_04e0_CustomUserData[0x10]; /* +0x4e0: CustomUserData (Struct, flags 0x10000000000034) */
    ue420_byte at_04f0_bHasSelectedCharacter[0x1]; /* +0x4f0: bHasSelectedCharacter (Bool, flags 0x10000000000034) */
    ue420_byte at_04f1_bIsSelectingCharacter[0x1]; /* +0x4f1: bIsSelectingCharacter (Bool, flags 0x10000000000034) */
    ue420_byte at_04f2_bIsFrontEndInputActive[0x1]; /* +0x4f2: bIsFrontEndInputActive (Bool, flags 0x10000000000034) */
    ue420_byte at_04f3_bIsProvidingAnyFrontEndInput[0x1]; /* +0x4f3: bIsProvidingAnyFrontEndInput (Bool, flags 0x10000000000034) */
    ue420_byte at_04f4_bServerSetInitialViewingCharacter[0x1]; /* +0x4f4: bServerSetInitialViewingCharacter (Bool, flags 0x10000000000034) */
    ue420_byte at_04f5_IsDev[0x1]; /* +0x4f5: IsDev (Bool, flags 0x10000000000034) */
    ue420_byte at_04f6_bHasBackfilled[0x2]; /* +0x4f6: bHasBackfilled (Bool, flags 0x10000000000034) */
    ue420_byte at_04f8_ServerSelectionPriority[0x4]; /* +0x4f8: ServerSelectionPriority (Int, flags 0x10000000000034) */
    ue420_byte at_04fc_bIsHost[0x1]; /* +0x4fc: bIsHost (Bool, flags 0x10000000000034) */
    ue420_byte at_04fd_bHasEverBeenServer[0x1]; /* +0x4fd: bHasEverBeenServer (Bool, flags 0x10000000000034) */
    ue420_byte at_04fe_bIsServerNow[0x1]; /* +0x4fe: bIsServerNow (Bool, flags 0x10000000000034) */
    ue420_byte at_04ff_bIsRollbackEngineReady[0x1]; /* +0x4ff: bIsRollbackEngineReady (Bool, flags 0x10000000000034) */
    ue420_byte at_0500_bIsWatchingServerSideReplay[0x1]; /* +0x500: bIsWatchingServerSideReplay (Bool, flags 0x10000000000034) */
    ue420_byte at_0501_bKioskPlayerReadyStatus[0x7]; /* +0x501: bKioskPlayerReadyStatus (Bool, flags 0x10000000000034) */
    ue420_byte at_0508_PlatformIdString[0x10]; /* +0x508: PlatformIdString (Str, flags 0x10000100000020) */
    ue420_byte at_0518_PlatformId[0x28]; /* +0x518: PlatformId (Struct, flags 0x10000000000000) */
    ue420_byte at_0540_MuteList[0x10]; /* +0x540: MuteList (Array, flags 0x10000000000000) */
    ue420_byte at_0550_bGloballyMuted[0x8]; /* +0x550: bGloballyMuted (Bool, flags 0x10000100000020) */
    ue420_byte at_0558_PartyMembers[0x10]; /* +0x558: PartyMembers (Array, flags 0x10000000000000) */
    ue420_byte at_0568_PreferredTeamId[0x4]; /* +0x568: PreferredTeamId (Int, flags 0x10000000000000) */
    ue420_byte at_056c_Rating[0x4]; /* +0x56c: Rating (Float, flags 0x10000000000000) */
    ue420_byte at_0570_Deviation[0x4]; /* +0x570: Deviation (Float, flags 0x10000000000000) */
    ue420_byte at_0574_Volatility[0x4]; /* +0x574: Volatility (Float, flags 0x10000000000000) */
    ue420_byte at_0578_Modifier[0x4]; /* +0x578: Modifier (Float, flags 0x10000000000000) */
    ue420_byte at_057c_bHasUnreportedData[0x4]; /* +0x57c: bHasUnreportedData (Bool, flags 0x10000000000000) */
    ue420_byte at_0580_LoadingData[0x28]; /* +0x580: LoadingData (Struct, flags 0x10000000000000) */
    ue420_byte at_05a8_bHasUnreportedLoadingTime[0x1]; /* +0x5a8: bHasUnreportedLoadingTime (Bool, flags 0x10000000000000) */
    ue420_byte at_05a9_bHasBeenAskedToCreateVoiceChatNetwork[0x27]; /* +0x5a9: bHasBeenAskedToCreateVoiceChatNetwork (Bool, flags 0x10000000000000) */
    ue420_byte at_05d0_bHasMicrophone[0x1]; /* +0x5d0: bHasMicrophone (Bool, flags 0x10000100000020) */
    ue420_byte at_05d1_bHasSpeakers[0x3]; /* +0x5d1: bHasSpeakers (Bool, flags 0x10000100000020) */
    ue420_byte at_05d4_TeamId[0x4]; /* +0x5d4: TeamId (Int, flags 0x40000100000020) */
    ue420_byte at_05d8_CharacterLockInState[0x1]; /* +0x5d8: CharacterLockInState (Enum, flags 0x40000100000020) */
    ue420_byte at_05d9_bTeamVoiceChatEnabled[0x1]; /* +0x5d9: bTeamVoiceChatEnabled (Bool, flags 0x40000100000020) */
    ue420_byte at_05da_bPartyVoiceChatEnabled[0x6]; /* +0x5da: bPartyVoiceChatEnabled (Bool, flags 0x40000100000020) */
};

/* Class params 0x143ab1f60; size 0x88. */
struct UE420_MBQuestionManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_TypesBlueprintObjectRef[0x18]; /* +0x28: TypesBlueprintObjectRef (Struct, flags 0x10000000004000) */
    ue420_byte at_0040_DebugQuestionListJson[0x18]; /* +0x40: DebugQuestionListJson (Text, flags 0x10000000010001) */
    ue420_byte at_0058_GameInstance[0x8]; /* +0x58: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0060_QuestionBuckets[0x10]; /* +0x60: QuestionBuckets (Array, flags 0x40000000002000) */
    ue420_byte at_0070_ResponseDelegate[0x18]; /* +0x70: ResponseDelegate (MulticastDelegate, flags 0x40000000080000) */
};

/* Class params 0x143ab3110; size 0x100. */
struct UE420_MBQuestsManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_TypesBlueprintObjectRef[0x18]; /* +0x30: TypesBlueprintObjectRef (Struct, flags 0x10000000004000) */
    ue420_byte at_0048_OnQuestsUpdatedMulticaster[0x20]; /* +0x48: OnQuestsUpdatedMulticaster (MulticastDelegate, flags 0x10000000082000) */
    ue420_byte at_0068_QuestList[0x10]; /* +0x68: QuestList (Array, flags 0x40008000000001) */
    ue420_byte at_0078_TaskTags[0x10]; /* +0x78: TaskTags (Array, flags 0x40000000000001) */
    ue420_byte at_0088_CurrencyRewardsData[0x10]; /* +0x88: CurrencyRewardsData (Array, flags 0x40000000000001) */
    ue420_byte at_0098_GameInstance[0x8]; /* +0x98: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_00a0_LocalPlayerId[0x28]; /* +0xa0: LocalPlayerId (Struct, flags 0x40000000002000) */
    ue420_byte at_00c8_PendingQuestTaskUpdates[0x10]; /* +0xc8: PendingQuestTaskUpdates (Array, flags 0x40000000002000) */
    ue420_byte at_00d8_QuestTaskUpdateTimerHandle[0x8]; /* +0xd8: QuestTaskUpdateTimerHandle (Struct, flags 0x40000000002000) */
    ue420_byte at_00e0_bHasRequestedLocalPlayerInitialQuests[0x8]; /* +0xe0: bHasRequestedLocalPlayerInitialQuests (Bool, flags 0x40000000002000) */
    ue420_byte at_00e8_CachedQuestsPlayerIds[0x10]; /* +0xe8: CachedQuestsPlayerIds (Array, flags 0x40000000002000) */
    ue420_byte at_00f8_PendingServerQuestTaskUpdateRequests[0x4]; /* +0xf8: PendingServerQuestTaskUpdateRequests (Int, flags 0x40000000002000) */
    ue420_byte at_00fc_bMatchCompleted[0x1]; /* +0xfc: bMatchCompleted (Bool, flags 0x40000000002000) */
    ue420_byte at_00fd_bIsDedicatedServer[0x1]; /* +0xfd: bIsDedicatedServer (Bool, flags 0x40000000002000) */
    ue420_byte at_00fe_bLocalPlayerLoginRegistered[0x2]; /* +0xfe: bLocalPlayerLoginRegistered (Bool, flags 0x40000000002000) */
};

/* Class params 0x143abc020; size 0x1d0. */
struct UE420_MBReplayStreamingManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_GameInstance[0x8]; /* +0x30: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0038_AzureFileCache[0x8]; /* +0x38: AzureFileCache (Object, flags 0x40000000002000) */
    ue420_byte at_0040_ReplayStreamIdGenerator[0x8]; /* +0x40: ReplayStreamIdGenerator (Struct, flags 0x40000000002000) */
    ue420_byte at_0048_ReplayAccountTag[0x8]; /* +0x48: ReplayAccountTag (Name, flags 0x40000000002000) */
    ue420_byte at_0050_bReplayUploaderRequestPending[0x1]; /* +0x50: bReplayUploaderRequestPending (Bool, flags 0x40000000002000) */
    ue420_byte at_0051_bReplayUploaderAccountCached[0x7]; /* +0x51: bReplayUploaderAccountCached (Bool, flags 0x40000000002000) */
    ue420_byte at_0058_ReplayUploaderAccountName[0x10]; /* +0x58: ReplayUploaderAccountName (Str, flags 0x40000000002000) */
    ue420_byte at_0068_ReplayUploaderAccountKey[0x10]; /* +0x68: ReplayUploaderAccountKey (Str, flags 0x40000000002000) */
    ue420_byte at_0078_bReplaysRequireAuthorisation[0x8]; /* +0x78: bReplaysRequireAuthorisation (Bool, flags 0x40000000002000) */
    ue420_byte at_0080_ActiveReplayStreams[0x10]; /* +0x80: ActiveReplayStreams (Array, flags 0x40008000002000) */
    ue420_byte at_0090_CloudReplayFileTimeout[0x4]; /* +0x90: CloudReplayFileTimeout (Float, flags 0x40000000004000) */
    ue420_byte at_0094_DefaultLiveStreamPlaybackDelay[0x4]; /* +0x94: DefaultLiveStreamPlaybackDelay (Float, flags 0x40000000004000) */
    ue420_byte at_0098_PrepareMatchTimeout[0x8]; /* +0x98: PrepareMatchTimeout (Float, flags 0x40000000004000) */
    ue420_byte at_00a0_CloudReplayMatchData[0x38]; /* +0xa0: CloudReplayMatchData (Struct, flags 0x40000000002000) */
    ue420_byte at_00d8_CloudReplayFileInfo[0xa8]; /* +0xd8: CloudReplayFileInfo (Struct, flags 0x40000000002000) */
    ue420_byte at_0180_bIsCloudMatchPending[0x4]; /* +0x180: bIsCloudMatchPending (Bool, flags 0x40000000002000) */
    ue420_byte at_0184_NumPendingAvatarTextures[0x4]; /* +0x184: NumPendingAvatarTextures (Int, flags 0x40000000002000) */
    ue420_byte at_0188_NumPendingPlayerNames[0x8]; /* +0x188: NumPendingPlayerNames (Int, flags 0x40000000002000) */
    ue420_byte at_0190_TimerHandle_PrepareMatchTimeout[0x8]; /* +0x190: TimerHandle_PrepareMatchTimeout (Struct, flags 0x40000000002000) */
    ue420_byte at_0198_ReplayDownloadRetryDelay[0x10]; /* +0x198: ReplayDownloadRetryDelay (Array, flags 0x40000000004000) */
    ue420_byte at_01a8_PendingReplayStreamId[0x4]; /* +0x1a8: PendingReplayStreamId (Struct, flags 0x40000000002000) */
    ue420_byte at_01ac_NumRequestsFailed[0x4]; /* +0x1ac: NumRequestsFailed (Int, flags 0x40000000002000) */
    ue420_byte at_01b0_LastDownloadRequestTime[0x8]; /* +0x1b0: LastDownloadRequestTime (Float, flags 0x40000000002000) */
    ue420_byte at_01b8_TimerHandle_ContinueReplayStreamUpdate[0x8]; /* +0x1b8: TimerHandle_ContinueReplayStreamUpdate (Struct, flags 0x40000000002000) */
    ue420_byte at_01c0_PendingDownloads[0x10]; /* +0x1c0: PendingDownloads (Array, flags 0x40000000002000) */
};

/* Class params 0x143ac5100; size 0x50. */
struct UE420_MBRollbackObjectFactory {
    ue420_byte unknown_0000[0x50];
};

/* Class params 0x143ac1550; size 0x7e0. */
struct UE420_MBScriptManagerProxy {
    ue420_byte unknown_0000[0x3c0];
    ue420_byte at_03c0_CurrentScriptState[0x8]; /* +0x3c0: CurrentScriptState (Enum, flags 0x10000000000014) */
    ue420_byte at_03c8_ScriptActorList[0x10]; /* +0x3c8: ScriptActorList (Array, flags 0x10000000000014) */
    ue420_byte at_03d8_DefaultControllerClass[0x8]; /* +0x3d8: DefaultControllerClass (Class, flags 0x14000000000015) */
    ue420_byte at_03e0_EnemyClassOverrides[0x50]; /* +0x3e0: EnemyClassOverrides (Map, flags 0x14000000000015) */
    ue420_byte at_0430_CameraResetWaitFrames[0x4]; /* +0x430: CameraResetWaitFrames (Int, flags 0x10000000000015) */
    ue420_byte at_0434_CameraTransitionWaitFrames[0x4]; /* +0x434: CameraTransitionWaitFrames (Int, flags 0x10000000000015) */
    ue420_byte at_0438_bEnableCutsceneController[0x8]; /* +0x438: bEnableCutsceneController (Bool, flags 0x10000000000001) */
    ue420_byte at_0440_DefaultPromptWidget[0x8]; /* +0x440: DefaultPromptWidget (Class, flags 0x14000000000015) */
    ue420_byte at_0448_LastCameraID[0x8]; /* +0x448: LastCameraID (Int, flags 0x10000000000014) */
    ue420_byte at_0450_LatentMovementAxisX[0x8]; /* +0x450: LatentMovementAxisX (Name, flags 0x10000000000015) */
    ue420_byte at_0458_LatentMovementAxisY[0x8]; /* +0x458: LatentMovementAxisY (Name, flags 0x10000000000015) */
    ue420_byte at_0460_PauseTokens[0x10]; /* +0x460: PauseTokens (Array, flags 0x10000000000015) */
    ue420_byte at_0470_ActiveTokens[0x10]; /* +0x470: ActiveTokens (Array, flags 0x10000000000001) */
    ue420_byte at_0480_TokenLists[0x50]; /* +0x480: TokenLists (Map, flags 0x10000000000005) */
    ue420_byte at_04d0_ScriptPlayerClassLookupTable[0x50]; /* +0x4d0: ScriptPlayerClassLookupTable (Map, flags 0x10000000000015) */
    ue420_byte at_0520_CharacterToAIVariables[0x50]; /* +0x520: CharacterToAIVariables (Map, flags 0x10000000000005) */
    ue420_byte at_0570_CharacterToBehavior[0x50]; /* +0x570: CharacterToBehavior (Map, flags 0x10000000000005) */
    ue420_byte at_05c0_BehaviorToSkillLevel[0x50]; /* +0x5c0: BehaviorToSkillLevel (Map, flags 0x10000000000005) */
    ue420_byte at_0610_BBVar_CombatMode[0x8]; /* +0x610: BBVar_CombatMode (Name, flags 0x10000000000015) */
    ue420_byte at_0618_BBVar_ConbatRange[0x8]; /* +0x618: BBVar_ConbatRange (Name, flags 0x10000000000015) */
    ue420_byte at_0620_BBVar_ReturnHome[0x8]; /* +0x620: BBVar_ReturnHome (Name, flags 0x10000000000015) */
    ue420_byte at_0628_BBVar_HomeLocation[0x8]; /* +0x628: BBVar_HomeLocation (Name, flags 0x10000000000015) */
    ue420_byte at_0630_BBVar_EnemyTarget[0x8]; /* +0x630: BBVar_EnemyTarget (Name, flags 0x10000000000015) */
    ue420_byte at_0638_BBVar_Special1[0x8]; /* +0x638: BBVar_Special1 (Name, flags 0x10000000000015) */
    ue420_byte at_0640_BBVar_Special2[0x8]; /* +0x640: BBVar_Special2 (Name, flags 0x10000000000015) */
    ue420_byte at_0648_BBVar_Special3[0x8]; /* +0x648: BBVar_Special3 (Name, flags 0x10000000000015) */
    ue420_byte at_0650_BBVar_ChanceToEvade[0x8]; /* +0x650: BBVar_ChanceToEvade (Name, flags 0x10000000000015) */
    ue420_byte at_0658_BBVar_PatrolPath[0x8]; /* +0x658: BBVar_PatrolPath (Name, flags 0x10000000000015) */
    ue420_byte at_0660_PatrolPath[0x8]; /* +0x660: PatrolPath (Object, flags 0x1200000008001d) */
    ue420_byte at_0668_RetreatPoints[0x8]; /* +0x668: RetreatPoints (Object, flags 0x1200000008001d) */
    ue420_byte at_0670_bNonScriptedCombatStart[0x1]; /* +0x670: bNonScriptedCombatStart (Bool, flags 0x10000000000015) */
    ue420_byte at_0671_bHideStatusText[0x7]; /* +0x671: bHideStatusText (Bool, flags 0x10000000000015) */
    ue420_byte at_0678_CutsceneController[0x8]; /* +0x678: CutsceneController (Object, flags 0x10000000000014) */
    ue420_byte at_0680_CurrentPreparedPlayerProxy[0x8]; /* +0x680: CurrentPreparedPlayerProxy (Object, flags 0x20080000002000) */
    ue420_byte at_0688_bDoneInit[0x1]; /* +0x688: bDoneInit (Bool, flags 0x40000000002000) */
    ue420_byte at_0689_bMatchStarted[0x7]; /* +0x689: bMatchStarted (Bool, flags 0x40000000002000) */
    ue420_byte at_0690_ScriptCharacters[0x10]; /* +0x690: ScriptCharacters (Array, flags 0x40000000002000) */
    ue420_byte at_06a0_SpawnedControllers[0x10]; /* +0x6a0: SpawnedControllers (Array, flags 0x40000000002000) */
    ue420_byte at_06b0_PendingControllersToDestroy[0x10]; /* +0x6b0: PendingControllersToDestroy (Array, flags 0x40000000002000) */
    ue420_byte at_06c0_PlayerController[0x8]; /* +0x6c0: PlayerController (Object, flags 0x40000000002000) */
    ue420_byte at_06c8_AIPlayerProxy[0x8]; /* +0x6c8: AIPlayerProxy (Object, flags 0x40000000002000) */
    ue420_byte at_06d0_bCameraReseting[0x4]; /* +0x6d0: bCameraReseting (Bool, flags 0x40000000002000) */
    ue420_byte at_06d4_CameraResetTimerFrames[0x4]; /* +0x6d4: CameraResetTimerFrames (Int, flags 0x40000000002000) */
    ue420_byte at_06d8_AIInputsToPress[0x10]; /* +0x6d8: AIInputsToPress (Array, flags 0x40000000002000) */
    ue420_byte at_06e8_AIInputsToRelease[0x10]; /* +0x6e8: AIInputsToRelease (Array, flags 0x40000000002000) */
    ue420_byte at_06f8_InCinematicMode[0x1]; /* +0x6f8: InCinematicMode (Bool, flags 0x40000000002000) */
    ue420_byte at_06f9_DialogConfirmed[0x1]; /* +0x6f9: DialogConfirmed (Bool, flags 0x40000000002000) */
    ue420_byte at_06fa_CameraTransitioning[0x1]; /* +0x6fa: CameraTransitioning (Bool, flags 0x40000000002000) */
    ue420_byte at_06fb_CameraTransitioned[0x1]; /* +0x6fb: CameraTransitioned (Bool, flags 0x40000000002000) */
    ue420_byte at_06fc_CameraBlendTimer[0x4]; /* +0x6fc: CameraBlendTimer (Float, flags 0x40000000002000) */
    ue420_byte at_0700_CameraBlendTime[0x8]; /* +0x700: CameraBlendTime (Float, flags 0x40000000002000) */
    ue420_byte at_0708_FadeCameraData[0x18]; /* +0x708: FadeCameraData (Struct, flags 0x40000000002000) */
    ue420_byte at_0720_NumCameras[0x8]; /* +0x720: NumCameras (Int, flags 0x40000000002000) */
    ue420_byte at_0728_CameraIdMap[0x50]; /* +0x728: CameraIdMap (Map, flags 0x40000000002000) */
    ue420_byte at_0778_PendingLatentInput[0x20]; /* +0x778: PendingLatentInput (Struct, flags 0x40000000002000) */
    ue420_byte at_0798_PendingLatentInputList[0x10]; /* +0x798: PendingLatentInputList (Array, flags 0x40000000002000) */
    ue420_byte at_07a8_InputsThisFrame[0x10]; /* +0x7a8: InputsThisFrame (Array, flags 0x40000000002000) */
    ue420_byte at_07b8_StickInputThisFrame[0xc]; /* +0x7b8: StickInputThisFrame (Struct, flags 0x40000000002000) */
    ue420_byte at_07c4_StickInput[0xc]; /* +0x7c4: StickInput (Struct, flags 0x40000000002000) */
    ue420_byte at_07d0_ScriptedPlayerTokens[0x10]; /* +0x7d0: ScriptedPlayerTokens (Array, flags 0x40000000000000) */
};

/* Class params 0x14453c0a0; size 0x1b8. */
struct UE420_MBSeedManagerActorState {
    ue420_byte unknown_0000[0x90];
    ue420_byte at_0090_LastNearEndState[0x4]; /* +0x90: LastNearEndState (Enum, flags 0x40000000000000) */
    ue420_byte at_0094_SeedsRequiredToWinOverride[0x4]; /* +0x94: SeedsRequiredToWinOverride (Int, flags 0x40000000000000) */
    ue420_byte at_0098_State[0x1]; /* +0x98: State (Enum, flags 0x40000000000000) */
    ue420_byte at_0099_LastChangeStateReason[0x3]; /* +0x99: LastChangeStateReason (Enum, flags 0x40000000000000) */
    ue420_byte at_009c_StateTimer[0x4]; /* +0x9c: StateTimer (Float, flags 0x40000000000000) */
    ue420_byte at_00a0_SeedCountTeam0[0x4]; /* +0xa0: SeedCountTeam0 (Int, flags 0x40000000000000) */
    ue420_byte at_00a4_SeedCountTeam1[0x4]; /* +0xa4: SeedCountTeam1 (Int, flags 0x40000000000000) */
    ue420_byte at_00a8_HeldSeedsCounterTeam0[0x4]; /* +0xa8: HeldSeedsCounterTeam0 (Int, flags 0x40000000000000) */
    ue420_byte at_00ac_HeldSeedsCounterTeam1[0x4]; /* +0xac: HeldSeedsCounterTeam1 (Int, flags 0x40000000000000) */
    ue420_byte at_00b0_ShowMinimapIconsTimer[0x8]; /* +0xb0: ShowMinimapIconsTimer (Float, flags 0x40000000000000) */
    ue420_byte at_00b8_ActiveSeedHandInIndices[0x10]; /* +0xb8: ActiveSeedHandInIndices (Array, flags 0x40000000000000) */
    ue420_byte at_00c8_PreviousSingleActiveSeedHandInIndex[0x8]; /* +0xc8: PreviousSingleActiveSeedHandInIndex (Int, flags 0x40000000000000) */
    ue420_byte at_00d0_SeedHandInSpawnsPerWaveOverride[0x10]; /* +0xd0: SeedHandInSpawnsPerWaveOverride (Array, flags 0x40000000000000) */
    ue420_byte at_00e0_CurrentHandInWaveIndex[0x4]; /* +0xe0: CurrentHandInWaveIndex (Int, flags 0x40000000000000) */
    ue420_byte at_00e4_NumSeedsInGame[0x4]; /* +0xe4: NumSeedsInGame (Int, flags 0x40000000000000) */
    ue420_byte at_00e8_NumSeedsInPickups[0x4]; /* +0xe8: NumSeedsInPickups (Int, flags 0x40000000000000) */
    ue420_byte at_00ec_MapIconsSpawned[0x4]; /* +0xec: MapIconsSpawned (Bool, flags 0x40000000000000) */
    ue420_byte at_00f0_ActiveSeedPlants[0x10]; /* +0xf0: ActiveSeedPlants (Array, flags 0x2040000000000000) */
    ue420_byte at_0100_SeedHandIns[0x10]; /* +0x100: SeedHandIns (Array, flags 0x2040000000000000) */
    ue420_byte at_0110_PlayerInfos[0x50]; /* +0x110: PlayerInfos (Map, flags 0x40000000000000) */
    ue420_byte at_0160_bBackfillingEnabled[0x1]; /* +0x160: bBackfillingEnabled (Bool, flags 0x40000000000000) */
    ue420_byte at_0161_bIsOvertime[0x1]; /* +0x161: bIsOvertime (Bool, flags 0x40000000000000) */
    ue420_byte at_0162_bKioskModeEndGame[0x1]; /* +0x162: bKioskModeEndGame (Bool, flags 0x40000000000000) */
    ue420_byte at_0163_bForceCentralHandInPointNextTime[0x1]; /* +0x163: bForceCentralHandInPointNextTime (Bool, flags 0x40000000000000) */
    ue420_byte at_0164_bPauseTimer[0x4]; /* +0x164: bPauseTimer (Bool, flags 0x40000000000000) */
    ue420_byte at_0168_TimerDelegates[0x10]; /* +0x168: TimerDelegates (Array, flags 0x40008000000000) */
    ue420_byte at_0178_PointsReachedDelegates[0x10]; /* +0x178: PointsReachedDelegates (Array, flags 0x40008000000000) */
    ue420_byte at_0188_PowerCellGameplayEvents[0x10]; /* +0x188: PowerCellGameplayEvents (Array, flags 0x2040008000000000) */
    ue420_byte at_0198_PowerCellDestroyed[0x10]; /* +0x198: PowerCellDestroyed (MulticastDelegate, flags 0x2040000000080000) */
    ue420_byte at_01a8_PointsOnPlayerDeathConditions[0x10]; /* +0x1a8: PointsOnPlayerDeathConditions (Array, flags 0x40000000000000) */
};

/* Class params 0x1444c5580; size 0x70. */
struct UE420_MBSessionOptions {
    ue420_byte unknown_0000[0x38];
    ue420_byte at_0038_IgnoreCooldowns[0x1]; /* +0x38: IgnoreCooldowns (Bool, flags 0x10000000000015) */
    ue420_byte at_0039_InfiniteSuper[0x1]; /* +0x39: InfiniteSuper (Bool, flags 0x10000000000015) */
    ue420_byte at_003a_InfiniteStamina[0x1]; /* +0x3a: InfiniteStamina (Bool, flags 0x10000000000015) */
    ue420_byte at_003b_AllowCheats[0x5]; /* +0x3b: AllowCheats (Bool, flags 0x10000000000015) */
    ue420_byte at_0040_PlayerMods[0x10]; /* +0x40: PlayerMods (Array, flags 0x4010000000000015) */
    ue420_byte at_0050_ActiveMapModIds[0x20]; /* +0x50: ActiveMapModIds (Array, flags 0x10000000000015) */
};

/* Class params 0x143ad0680; size 0x4f8. */
struct UE420_MBSpawnAreaGateProxy {
    ue420_byte unknown_0000[0x4b0];
    ue420_byte at_04b0_bFadeStarted[0x4]; /* +0x4b0: bFadeStarted (Bool, flags 0x10000000000000) */
    ue420_byte at_04b4_MaxTimeDeltaForJustPassedDelegate[0x4]; /* +0x4b4: MaxTimeDeltaForJustPassedDelegate (Float, flags 0x10000000000001) */
    ue420_byte at_04b8_bIsOpen[0x4]; /* +0x4b8: bIsOpen (Bool, flags 0x40000000002000) */
    ue420_byte at_04bc_CurrentCountdownStage[0x4]; /* +0x4bc: CurrentCountdownStage (Int, flags 0x40000000002000) */
    ue420_byte at_04c0_CountdownVOStages[0x10]; /* +0x4c0: CountdownVOStages (Array, flags 0x40008000002000) */
    ue420_byte at_04d0_RollbackGameState[0x8]; /* +0x4d0: RollbackGameState (Object, flags 0x40000000002000) */
    ue420_byte at_04d8_LastTimeSetOnTextComponent[0x8]; /* +0x4d8: LastTimeSetOnTextComponent (Int, flags 0x40000000002000) */
    ue420_byte at_04e0_CountdownTexts[0x10]; /* +0x4e0: CountdownTexts (Array, flags 0x40008000002008) */
    ue420_byte at_04f0_LastRollbackMatchState[0x8]; /* +0x4f0: LastRollbackMatchState (Name, flags 0x40000000002000) */
};

/* Class params 0x144549fd0; size 0x7c0. */
struct UE420_MBSpawnPointState {
    ue420_byte unknown_0000[0x7b8];
    ue420_byte at_07b8_SpawningPlayerStateId[0x8]; /* +0x7b8: SpawningPlayerStateId (Struct, flags 0x40000000000000) */
};

/* Class params 0x143addbf0; size 0x208. */
struct UE420_MBSystemMessageManager {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_MessageInfo[0x50]; /* +0x28: MessageInfo (Map, flags 0x10000000010015) */
    ue420_byte at_0078_XboxMessageInfo[0x50]; /* +0x78: XboxMessageInfo (Map, flags 0x10000000010015) */
    ue420_byte at_00c8_PCMessageInfo[0x50]; /* +0xc8: PCMessageInfo (Map, flags 0x10000000010015) */
    ue420_byte at_0118_DefaultMessageScreenClass[0x8]; /* +0x118: DefaultMessageScreenClass (Class, flags 0x14000000010015) */
    ue420_byte at_0120_GameInstance[0x10]; /* +0x120: GameInstance (Object, flags 0x40000000002000) */
    ue420_byte at_0130_CurrentMessageId[0x8]; /* +0x130: CurrentMessageId (Name, flags 0x40000000002000) */
    ue420_byte at_0138_CurrentMessageQueueData[0x98]; /* +0x138: CurrentMessageQueueData (Struct, flags 0x40008000002000) */
    ue420_byte at_01d0_MessageQueue[0x10]; /* +0x1d0: MessageQueue (Array, flags 0x40008000002000) */
    ue420_byte at_01e0_MessageTimeoutHandle[0x8]; /* +0x1e0: MessageTimeoutHandle (Struct, flags 0x40000000002000) */
    ue420_byte at_01e8_MessageQueueTimerHandle[0x8]; /* +0x1e8: MessageQueueTimerHandle (Struct, flags 0x40000000002000) */
    ue420_byte at_01f0_bForceMessageQueueing[0x1]; /* +0x1f0: bForceMessageQueueing (Bool, flags 0x40000000002000) */
    ue420_byte at_01f1_bInRemoveAndQueueCurrentSystemMessage[0x17]; /* +0x1f1: bInRemoveAndQueueCurrentSystemMessage (Bool, flags 0x40000000002000) */
};

/* Class params 0x143ae9390; size 0xd8. */
struct UE420_MBUpdateManager {
    ue420_byte unknown_0000[0x40];
    ue420_byte at_0040_BlueprintOnUpdateAvailable[0x10]; /* +0x40: BlueprintOnUpdateAvailable (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_0050_GameInstance[0x8]; /* +0x50: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0058_bTitleDataCache_IsUpdateAvailable[0x1]; /* +0x58: bTitleDataCache_IsUpdateAvailable (Bool, flags 0x40000000000000) */
    ue420_byte at_0059_bPlatform_IsUpdateAvailable[0x7]; /* +0x59: bPlatform_IsUpdateAvailable (Bool, flags 0x40000000000000) */
    ue420_byte at_0060_UpdateMessagesTable[0x8]; /* +0x60: UpdateMessagesTable (Name, flags 0x40000000004000) */
    ue420_byte at_0068_Text_NewUpdateAvailableKey[0x10]; /* +0x68: Text_NewUpdateAvailableKey (Str, flags 0x40000000004000) */
    ue420_byte at_0078_Text_QuitKey[0x10]; /* +0x78: Text_QuitKey (Str, flags 0x40000000004000) */
    ue420_byte at_0088_Text_MatchmakingKey[0x10]; /* +0x88: Text_MatchmakingKey (Str, flags 0x40000000004000) */
    ue420_byte at_0098_Text_MatchmakingCancelledKey[0x10]; /* +0x98: Text_MatchmakingCancelledKey (Str, flags 0x40000000004000) */
    ue420_byte at_00a8_Text_PartiesKey[0x30]; /* +0xa8: Text_PartiesKey (Str, flags 0x40000000004000) */
};

/* Class params 0x143aec3b0; size 0x178. */
struct UE420_MBVoiceChatManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_OnVoiceChatTalkerDataUpdated[0x10]; /* +0x30: OnVoiceChatTalkerDataUpdated (MulticastDelegate, flags 0x10000000080000) */
    ue420_byte at_0040_OnTeamVoiceChatEnabledChanged[0x10]; /* +0x40: OnTeamVoiceChatEnabledChanged (MulticastDelegate, flags 0x10000000080000) */
    ue420_byte at_0050_OnPartyVoiceChatEnabledChanged[0x88]; /* +0x50: OnPartyVoiceChatEnabledChanged (MulticastDelegate, flags 0x10000000080000) */
    ue420_byte at_00d8_OnlineSessionManager[0x8]; /* +0xd8: OnlineSessionManager (Object, flags 0x40000000000000) */
    ue420_byte at_00e0_PartyManager[0x8]; /* +0xe0: PartyManager (Object, flags 0x40000000000000) */
    ue420_byte at_00e8_bPartyVoiceChatEnabled[0x1]; /* +0xe8: bPartyVoiceChatEnabled (Bool, flags 0x40000000000000) */
    ue420_byte at_00e9_bTeamVoiceChatEnabled[0x1]; /* +0xe9: bTeamVoiceChatEnabled (Bool, flags 0x40000000000000) */
    ue420_byte at_00ea_bLocalPlayersMuted[0x1]; /* +0xea: bLocalPlayersMuted (Bool, flags 0x40000000000000) */
    ue420_byte at_00eb_bInMatch[0x1]; /* +0xeb: bInMatch (Bool, flags 0x40000000000000) */
    ue420_byte at_00ec_bLocalHasSpeakers[0x1]; /* +0xec: bLocalHasSpeakers (Bool, flags 0x40000000000000) */
    ue420_byte at_00ed_bLocalHasMicrophone[0x1]; /* +0xed: bLocalHasMicrophone (Bool, flags 0x40000000000000) */
    ue420_byte at_00ee_bRefreshHeadsetStatus[0x1]; /* +0xee: bRefreshHeadsetStatus (Bool, flags 0x40000000000000) */
    ue420_byte at_00ef_bTalkerDataNeedsRefresh[0x1]; /* +0xef: bTalkerDataNeedsRefresh (Bool, flags 0x40000000000000) */
    ue420_byte at_00f0_bConnectedToMatchNetwork[0x1]; /* +0xf0: bConnectedToMatchNetwork (Bool, flags 0x40000000000000) */
    ue420_byte at_00f1_bConnectedToPartyNetwork[0x7]; /* +0xf1: bConnectedToPartyNetwork (Bool, flags 0x40000000000000) */
    ue420_byte at_00f8_TalkerData[0x80]; /* +0xf8: TalkerData (Array, flags 0x40000000000000) */
};

/* Class params 0x143aede50; size 0x270. */
struct UE420_MBWatchZoneManager {
    ue420_byte unknown_0000[0x50];
    ue420_byte at_0050_GameInstance[0x8]; /* +0x50: GameInstance (Object, flags 0x40000000000000) */
    ue420_byte at_0058_PlayerAvatarManager[0xa8]; /* +0x58: PlayerAvatarManager (Object, flags 0x40000000000000) */
    ue420_byte at_0100_FeaturedOnlineResponses[0x10]; /* +0x100: FeaturedOnlineResponses (Array, flags 0x40000000000000) */
    ue420_byte at_0110_MatchRequestGenerator[0x8]; /* +0x110: MatchRequestGenerator (Struct, flags 0x40000000000000) */
    ue420_byte at_0118_MatchRequests[0x50]; /* +0x118: MatchRequests (Array, flags 0x40008000000000) */
    ue420_byte at_0168_ReplayBlobs[0x100]; /* +0x168: ReplayBlobs (Map, flags 0x40000000000000) */
    ue420_byte at_0268_PlayerInfoToRequestAtOnce[0x8]; /* +0x268: PlayerInfoToRequestAtOnce (Int, flags 0x40000000000000) */
};

/* Class params 0x143af5ee0; size 0xc98. */
struct UE420_MBWorldSingleton {
    ue420_byte unknown_0000[0x4d0];
    ue420_byte at_04d0_EmptyPlayerDataClassName[0x18]; /* +0x4d0: EmptyPlayerDataClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_04e8_LoadedEmptyPlayerDataClass[0x8]; /* +0x4e8: LoadedEmptyPlayerDataClass (Class, flags 0x14000000000000) */
    ue420_byte at_04f0_DefaultPIEPlayerDataClassName[0x18]; /* +0x4f0: DefaultPIEPlayerDataClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0508_DebugPlayerControllerClassName[0x18]; /* +0x508: DebugPlayerControllerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0520_DefaultEffectsManagerClassName[0x18]; /* +0x520: DefaultEffectsManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0538_LoadedEffectsManagerClass[0x8]; /* +0x538: LoadedEffectsManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0540_DefaultAudioImportanceSystemClassName[0x18]; /* +0x540: DefaultAudioImportanceSystemClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0558_LoadedAudioImportanceSystemClass[0x8]; /* +0x558: LoadedAudioImportanceSystemClass (Class, flags 0x14000000000000) */
    ue420_byte at_0560_DefaultHeroesBanterSystemClassName[0x18]; /* +0x560: DefaultHeroesBanterSystemClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0578_LoadedHeroesBanterSystemClass[0x8]; /* +0x578: LoadedHeroesBanterSystemClass (Class, flags 0x14000000000000) */
    ue420_byte at_0580_DefaultLocalPlayerProximityVOClassName[0x18]; /* +0x580: DefaultLocalPlayerProximityVOClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0598_LoadedLocalPlayerProximityVOClass[0x8]; /* +0x598: LoadedLocalPlayerProximityVOClass (Class, flags 0x14000000000000) */
    ue420_byte at_05a0_DefaultReplayManagerClassName[0x18]; /* +0x5a0: DefaultReplayManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_05b8_LoadedReplayManagerClass[0x8]; /* +0x5b8: LoadedReplayManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_05c0_DefaultDeathTipsManagerClassName[0x18]; /* +0x5c0: DefaultDeathTipsManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_05d8_LoadedDeathTipsManagerClass[0x8]; /* +0x5d8: LoadedDeathTipsManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_05e0_DefaultAFKManagerClassName[0x18]; /* +0x5e0: DefaultAFKManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_05f8_LoadedAFKManagerClass[0x8]; /* +0x5f8: LoadedAFKManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0600_DefaultGameFlowManagerClassName[0x18]; /* +0x600: DefaultGameFlowManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0618_LoadedGameFlowManagerClass[0x8]; /* +0x618: LoadedGameFlowManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0620_DefaultAudioGameFlowManagerClassName[0x18]; /* +0x620: DefaultAudioGameFlowManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0638_LoadedAudioGameFlowManagerClass[0x8]; /* +0x638: LoadedAudioGameFlowManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0640_DefaultCrowdManagerClassName[0x18]; /* +0x640: DefaultCrowdManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0658_LoadedCrowdManagerClass[0x8]; /* +0x658: LoadedCrowdManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_0660_DefaultConnectionManagerClassName[0x18]; /* +0x660: DefaultConnectionManagerClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0678_LoadedConnectionManagerClass[0x40]; /* +0x678: LoadedConnectionManagerClass (Class, flags 0x14000000000000) */
    ue420_byte at_06b8_bCommonInitialised[0x8]; /* +0x6b8: bCommonInitialised (Bool, flags 0x20080000000000) */
    ue420_byte at_06c0_WidgetManager[0x8]; /* +0x6c0: WidgetManager (Object, flags 0x40000000080008) */
    ue420_byte at_06c8_GraffitiManager[0x8]; /* +0x6c8: GraffitiManager (Object, flags 0x40000000000000) */
    ue420_byte at_06d0_FrontEnd[0x8]; /* +0x6d0: FrontEnd (Object, flags 0x40000000000000) */
    ue420_byte at_06d8_PerformanceManager[0x8]; /* +0x6d8: PerformanceManager (Object, flags 0x40000000000000) */
    ue420_byte at_06e0_AsyncLoadsRemaining[0x8]; /* +0x6e0: AsyncLoadsRemaining (Int, flags 0x40000000000000) */
    ue420_byte at_06e8_RollbackObjectFactory[0x8]; /* +0x6e8: RollbackObjectFactory (Object, flags 0x40000000000000) */
    ue420_byte at_06f0_EngineInterface[0x8]; /* +0x6f0: EngineInterface (Object, flags 0x40000000000000) */
    ue420_byte at_06f8_ReplayManager[0x8]; /* +0x6f8: ReplayManager (Object, flags 0x40000000000000) */
    ue420_byte at_0700_DeathTipsManager[0x8]; /* +0x700: DeathTipsManager (Object, flags 0x40000000000000) */
    ue420_byte at_0708_StatsManager[0x8]; /* +0x708: StatsManager (Object, flags 0x40000000000000) */
    ue420_byte at_0710_AFKManager[0x8]; /* +0x710: AFKManager (Object, flags 0x40000000000000) */
    ue420_byte at_0718_HighlightLikingManager[0x8]; /* +0x718: HighlightLikingManager (Object, flags 0x40000000002000) */
    ue420_byte at_0720_GameFlowManager[0x8]; /* +0x720: GameFlowManager (Object, flags 0x40000000000000) */
    ue420_byte at_0728_AudioGameFlowManager[0x8]; /* +0x728: AudioGameFlowManager (Object, flags 0x40000000000000) */
    ue420_byte at_0730_GlobalTimeDilationManager[0x8]; /* +0x730: GlobalTimeDilationManager (Object, flags 0x40000000000000) */
    ue420_byte at_0738_PlayerInfoTracker[0x8]; /* +0x738: PlayerInfoTracker (Object, flags 0x40000000000000) */
    ue420_byte at_0740_AIManager[0x8]; /* +0x740: AIManager (Object, flags 0x40000000000000) */
    ue420_byte at_0748_VisualEventManager[0x8]; /* +0x748: VisualEventManager (Object, flags 0x40000000000000) */
    ue420_byte at_0750_ServerProfiler[0x8]; /* +0x750: ServerProfiler (Object, flags 0x40000000000000) */
    ue420_byte at_0758_ActorMessagePlugin[0x8]; /* +0x758: ActorMessagePlugin (Object, flags 0x40000000000000) */
    ue420_byte at_0760_GlobalManagerMessagePlugin[0x8]; /* +0x760: GlobalManagerMessagePlugin (Object, flags 0x40000000000000) */
    ue420_byte at_0768_IncomingContactsPlugin[0x8]; /* +0x768: IncomingContactsPlugin (Object, flags 0x40000000000000) */
    ue420_byte at_0770_EffectsPlugin_VO[0x8]; /* +0x770: EffectsPlugin_VO (Object, flags 0x40000000000000) */
    ue420_byte at_0778_EffectsProxyActor[0x8]; /* +0x778: EffectsProxyActor (Object, flags 0x40000000000000) */
    ue420_byte at_0780_EffectsManager[0x8]; /* +0x780: EffectsManager (Object, flags 0x40000000000000) */
    ue420_byte at_0788_AudioImportanceSystem[0x8]; /* +0x788: AudioImportanceSystem (Object, flags 0x40000000000000) */
    ue420_byte at_0790_HeroesBanterSystem[0x8]; /* +0x790: HeroesBanterSystem (Object, flags 0x40000000000000) */
    ue420_byte at_0798_LocalPlayerProximityVO[0x8]; /* +0x798: LocalPlayerProximityVO (Object, flags 0x40000000000000) */
    ue420_byte at_07a0_AudioSpeakerSystem[0x8]; /* +0x7a0: AudioSpeakerSystem (Object, flags 0x40000000000000) */
    ue420_byte at_07a8_CrowdManager[0x8]; /* +0x7a8: CrowdManager (Object, flags 0x40000000000000) */
    ue420_byte at_07b0_ServerPlaybackManager[0x8]; /* +0x7b0: ServerPlaybackManager (Object, flags 0x40000000000000) */
    ue420_byte at_07b8_HostMigrationManager[0x58]; /* +0x7b8: HostMigrationManager (Struct, flags 0x40000000000000) */
    ue420_byte at_0810_ConnectionManager[0x8]; /* +0x810: ConnectionManager (Object, flags 0x40000000000000) */
    ue420_byte at_0818_GameplayManager[0x8]; /* +0x818: GameplayManager (Object, flags 0x40000000000000) */
    ue420_byte at_0820_ActiveActorsMap[0x50]; /* +0x820: ActiveActorsMap (Map, flags 0x40000000000000) */
    ue420_byte at_0870_CommonLevelObjectProxy[0x8]; /* +0x870: CommonLevelObjectProxy (Object, flags 0x40000000000000) */
    ue420_byte at_0878_CachedMiniMapWorldObject[0x8]; /* +0x878: CachedMiniMapWorldObject (Object, flags 0x40000000000000) */
    ue420_byte at_0880_RecordingReader[0x8]; /* +0x880: RecordingReader (Object, flags 0x40000000000000) */
    ue420_byte at_0888_RecordingWriter[0x8]; /* +0x888: RecordingWriter (Object, flags 0x40000000000000) */
    ue420_byte at_0890_ActorInitialisers[0x10]; /* +0x890: ActorInitialisers (Array, flags 0x40000000000000) */
    ue420_byte at_08a0_LocalPlayerActorIds[0x10]; /* +0x8a0: LocalPlayerActorIds (Array, flags 0x40000000000000) */
    ue420_byte at_08b0_LocalPlayerStates[0x10]; /* +0x8b0: LocalPlayerStates (Array, flags 0x40000000000000) */
    ue420_byte at_08c0_PendingDestroyProxies[0x10]; /* +0x8c0: PendingDestroyProxies (Array, flags 0x40000000000000) */
    ue420_byte at_08d0_MinimalTickProxies[0x10]; /* +0x8d0: MinimalTickProxies (Array, flags 0x40008000000000) */
    ue420_byte at_08e0_PredictedNextFrameState[0x8]; /* +0x8e0: PredictedNextFrameState (Object, flags 0x40000000000000) */
    ue420_byte at_08e8_RollbackEnginePublicFrameHistoryExtension[0xa5]; /* +0x8e8: RollbackEnginePublicFrameHistoryExtension (Struct, flags 0x40000000000000) */
    ue420_byte at_098d_bIsInSpectatorMode[0x3]; /* +0x98d: bIsInSpectatorMode (Bool, flags 0x40000000000000) */
    ue420_byte at_0990_MachineGroup[0x8]; /* +0x990: MachineGroup (Object, flags 0x40000000000000) */
    ue420_byte at_0998_EventletCompiler[0x8]; /* +0x998: EventletCompiler (Object, flags 0x40000000000000) */
    ue420_byte at_09a0_Machines[0x10]; /* +0x9a0: Machines (Array, flags 0x40000000000000) */
    ue420_byte at_09b0_PublicFrameHistoryMultiplexer[0x40]; /* +0x9b0: PublicFrameHistoryMultiplexer (Struct, flags 0x40000000000000) */
    ue420_byte at_09f0_bUpdateGlobalManager[0x1]; /* +0x9f0: bUpdateGlobalManager (Bool, flags 0x40000000002000) */
    ue420_byte at_09f1_bWaitForPlayerClassesToLoad[0x7]; /* +0x9f1: bWaitForPlayerClassesToLoad (Bool, flags 0x40000000000000) */
    ue420_byte at_09f8_PreLoadPlayerAssetHandler[0x8]; /* +0x9f8: PreLoadPlayerAssetHandler (Object, flags 0x40000000000000) */
    ue420_byte at_0a00_PlayerClassesLoaded[0x4]; /* +0xa00: PlayerClassesLoaded (Int, flags 0x40000000000000) */
    ue420_byte at_0a04_RequestedClasses[0x4]; /* +0xa04: RequestedClasses (Int, flags 0x40000000000000) */
    ue420_byte at_0a08_PlayerClassLoadStartTime[0xc8]; /* +0xa08: PlayerClassLoadStartTime (Float, flags 0x40000000000000) */
    ue420_byte at_0ad0_LocalPlayerTeam[0x8]; /* +0xad0: LocalPlayerTeam (Int, flags 0x40000000000000) */
    ue420_byte at_0ad8_OnLocalPlayerTeamChanged[0x10]; /* +0xad8: OnLocalPlayerTeamChanged (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0ae8_OnReplayStatusChanged[0x10]; /* +0xae8: OnReplayStatusChanged (MulticastDelegate, flags 0x40000000080000) */
    ue420_byte at_0af8_GameStatus[0x8]; /* +0xaf8: GameStatus (Enum, flags 0x40000000000000) */
    ue420_byte at_0b00_PlayerClassRecords[0x10]; /* +0xb00: PlayerClassRecords (Array, flags 0x40000000000000) */
    ue420_byte at_0b10_GlobalManagerObjectProxies[0x10]; /* +0xb10: GlobalManagerObjectProxies (Array, flags 0x40000000000000) */
    ue420_byte at_0b20_ProxyActorFactory[0x58]; /* +0xb20: ProxyActorFactory (Struct, flags 0x40000000000000) */
    ue420_byte at_0b78_GameStateInterpolationAlpha[0x18]; /* +0xb78: GameStateInterpolationAlpha (Float, flags 0x40000000000000) */
    ue420_byte at_0b90_bIsCharacterSelectScreenOpen[0xc0]; /* +0xb90: bIsCharacterSelectScreenOpen (Bool, flags 0x40000000000000) */
    ue420_byte at_0c50_ChatIdGenerator[0x8]; /* +0xc50: ChatIdGenerator (Struct, flags 0x40000000000000) */
    ue420_byte at_0c58_ChatLog[0x20]; /* +0xc58: ChatLog (Array, flags 0x40000000000000) */
    ue420_byte at_0c78_bAreProxyActorStatesStale[0x1]; /* +0xc78: bAreProxyActorStatesStale (Bool, flags 0x40000000000000) */
    ue420_byte at_0c79_bGameEndFrameRetired[0x1f]; /* +0xc79: bGameEndFrameRetired (Bool, flags 0x40000000000000) */
};

/* Class params 0x1433f63a0; size 0x50. */
struct UE420_NTEngineInterface {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_DefaultSessionOptionsClassName[0x18]; /* +0x30: DefaultSessionOptionsClassName (Struct, flags 0x10000000004000) */
    ue420_byte at_0048_SessionRandomGeneratorSeed[0x8]; /* +0x48: SessionRandomGeneratorSeed (Int, flags 0x20080000000000) */
};

/* Class params 0x1433f7db0; size 0x138. */
struct UE420_NTGameState {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_TargetRequestManager[0x10]; /* +0x28: TargetRequestManager (Struct, flags 0x10008000000000) */
    ue420_byte at_0038_AssetLoadRequestManager[0x30]; /* +0x38: AssetLoadRequestManager (Struct, flags 0x10000000000000) */
    ue420_byte at_0068_ActorMap[0x50]; /* +0x68: ActorMap (Map, flags 0x2020080000000000) */
    ue420_byte at_00b8_EventManager[0x8]; /* +0xb8: EventManager (Object, flags 0x2020080000000000) */
    ue420_byte at_00c0_GlobalManagerObjects[0x10]; /* +0xc0: GlobalManagerObjects (Array, flags 0x2040000000000000) */
    ue420_byte at_00d0_NextSpawnIndexForActorId[0x8]; /* +0xd0: NextSpawnIndexForActorId (Int16, flags 0x40000000002000) */
    ue420_byte at_00d8_ActorsPendingRemoval[0x10]; /* +0xd8: ActorsPendingRemoval (Array, flags 0x40000000002000) */
    ue420_byte at_00e8_ActorsRemovedThisFrame[0x10]; /* +0xe8: ActorsRemovedThisFrame (Array, flags 0x40000000002000) */
    ue420_byte at_00f8_PreUpdateCallbacks[0x10]; /* +0xf8: PreUpdateCallbacks (Array, flags 0x40008000002000) */
    ue420_byte at_0108_OutputEvents[0x10]; /* +0x108: OutputEvents (Array, flags 0x40000000002000) */
    ue420_byte at_0118_GameplayEvents[0x10]; /* +0x118: GameplayEvents (Array, flags 0x40000000002000) */
    ue420_byte at_0128_ActorsToSpawn[0x10]; /* +0x128: ActorsToSpawn (Array, flags 0x40008000002000) */
};

/* Class params 0x1433fdca0; size 0x30. */
struct UE420_NTGlobalManagerObjectData {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_StateClass[0x8]; /* +0x28: StateClass (Class, flags 0x14000000010001) */
};

/* Class params 0x1434390d0; size 0x3b8. */
struct UE420_NTGlobalManagerObjectProxy {
    ue420_byte unknown_0000[0x398];
    ue420_byte at_0398_GlobalManagerData[0x8]; /* +0x398: GlobalManagerData (Object, flags 0x1200000008081d) */
    ue420_byte at_03a0_DefaultManagerDataClass[0x8]; /* +0x3a0: DefaultManagerDataClass (Class, flags 0x14000000010001) */
    ue420_byte at_03a8_ActorData[0x8]; /* +0x3a8: ActorData (Object, flags 0x12000020080008) */
    ue420_byte at_03b0_CurrentState[0x8]; /* +0x3b0: CurrentState (Object, flags 0x10000000000014) */
};

/* Class params 0x1433fad50; size 0x80. */
struct UE420_NTGlobalManagerObjectState {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_ManagerData[0x8]; /* +0x28: ManagerData (Object, flags 0x4020080000000014) */
    ue420_byte at_0030_AnalyticsEventlets[0x10]; /* +0x30: AnalyticsEventlets (Array, flags 0x20080000002000) */
    ue420_byte at_0040_ManagerId[0x8]; /* +0x40: ManagerId (Int, flags 0x40000000000000) */
    ue420_byte at_0048_TimerManager[0x18]; /* +0x48: TimerManager (Struct, flags 0x40008000000000) */
    ue420_byte at_0060_RandomGenerator[0x8]; /* +0x60: RandomGenerator (Struct, flags 0x40000000000000) */
    ue420_byte at_0068_bManagerCallbacksHaveBeenExecutedThisFrame[0x18]; /* +0x68: bManagerCallbacksHaveBeenExecutedThisFrame (Bool, flags 0x40000000002000) */
};

/* Class params 0x1433a93f0; size 0x98. */
struct UE420_NTKioskModeConfig {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_ServerIP[0x10]; /* +0x28: ServerIP (Str, flags 0x10000000004000) */
    ue420_byte at_0038_ClientTeamId[0x8]; /* +0x38: ClientTeamId (Int, flags 0x10000000004000) */
    ue420_byte at_0040_ClientPlayerName[0x10]; /* +0x40: ClientPlayerName (Str, flags 0x10000000004000) */
    ue420_byte at_0050_ClientIsDev[0x8]; /* +0x50: ClientIsDev (Int, flags 0x10000000004000) */
    ue420_byte at_0058_TutorialMap[0x10]; /* +0x58: TutorialMap (Str, flags 0x10000000004000) */
    ue420_byte at_0068_TutorialMapOptions[0x10]; /* +0x68: TutorialMapOptions (Str, flags 0x10000000004000) */
    ue420_byte at_0078_DojoMap[0x10]; /* +0x78: DojoMap (Str, flags 0x10000000004000) */
    ue420_byte at_0088_DojoMapOptions[0x10]; /* +0x88: DojoMapOptions (Str, flags 0x10000000004000) */
};

/* Class params 0x1433c9ab0; size 0x160. */
struct UE420_NTPlayerAssetManager {
    ue420_byte unknown_0000[0x30];
    ue420_byte at_0030_AssetTypes[0xf0]; /* +0x30: AssetTypes (Array, flags 0x10000000004000) */
    ue420_byte at_0120_GameInstance[0x40]; /* +0x120: GameInstance (Object, flags 0x40000000000000) */
};

/* Class params 0x1433ca3b0; size 0x6e8. */
struct UE420_NTPlayerController {
    ue420_byte unknown_0000[0x6e8];
};

/* Class params 0x14343b870; size 0x4b8. */
struct UE420_NTRecordPlayer {
    ue420_byte unknown_0000[0x398];
    ue420_byte at_0398_RecordData[0x50]; /* +0x398: RecordData (Struct, flags 0x10008000000015) */
    ue420_byte at_03e8_bSnapRecordPlayerPositionToRecordingStartPosition[0x1]; /* +0x3e8: bSnapRecordPlayerPositionToRecordingStartPosition (Bool, flags 0x10000000000801) */
    ue420_byte at_03e9_bTakeOverPlayerController[0x37]; /* +0x3e9: bTakeOverPlayerController (Bool, flags 0x10000000000801) */
    ue420_byte at_0420_StreamReader[0x8]; /* +0x420: StreamReader (Object, flags 0x40000000002000) */
    ue420_byte at_0428_SelectedPlayerAddEvent[0x8]; /* +0x428: SelectedPlayerAddEvent (Object, flags 0x40000000002000) */
    ue420_byte at_0430_SelectedPlayerRequiredAssets[0x10]; /* +0x430: SelectedPlayerRequiredAssets (Array, flags 0x40000000002000) */
    ue420_byte at_0440_SyncMaster[0x8]; /* +0x440: SyncMaster (Object, flags 0x40000000002000) */
    ue420_byte at_0448_RecordPlayerInterfaceObject[0x10]; /* +0x448: RecordPlayerInterfaceObject (Interface, flags 0x44000000002000) */
    ue420_byte at_0458_TakenOverPlayerController[0x18]; /* +0x458: TakenOverPlayerController (Interface, flags 0x44000000002000) */
    ue420_byte at_0470_FirstFrameInRecording[0x4]; /* +0x470: FirstFrameInRecording (Int, flags 0x40000000002000) */
    ue420_byte at_0474_FrameRecordStarted[0x4]; /* +0x474: FrameRecordStarted (Int, flags 0x40000000002000) */
    ue420_byte at_0478_CurrentRecordingFrame[0x4]; /* +0x478: CurrentRecordingFrame (Int, flags 0x40000000002000) */
    ue420_byte at_047c_FrameOffset[0x4]; /* +0x47c: FrameOffset (Int, flags 0x40000000002000) */
    ue420_byte at_0480_LastFrameSubmittedInputFor[0x4]; /* +0x480: LastFrameSubmittedInputFor (Int, flags 0x40000000002000) */
    ue420_byte at_0484_SyncMasterStartFrameOffset[0x4]; /* +0x484: SyncMasterStartFrameOffset (Int, flags 0x40000000002000) */
    ue420_byte at_0488_RemovePlayerFrameFromLastLoop[0x4]; /* +0x488: RemovePlayerFrameFromLastLoop (Int, flags 0x40000000002000) */
    ue420_byte at_048c_NumSecondsBeforeStart[0x4]; /* +0x48c: NumSecondsBeforeStart (Float, flags 0x40000000002000) */
    ue420_byte at_0490_RecordedPlayerID[0x4]; /* +0x490: RecordedPlayerID (Int, flags 0x40000000002000) */
    ue420_byte at_0494_PlaybackPlayerID[0x4]; /* +0x494: PlaybackPlayerID (Int, flags 0x40000000002000) */
    ue420_byte at_0498_bInitialised[0x1]; /* +0x498: bInitialised (Bool, flags 0x40000000002000) */
    ue420_byte at_0499_bPlayerSpawned[0x1]; /* +0x499: bPlayerSpawned (Bool, flags 0x40000000002000) */
    ue420_byte at_049a_bPressedPlay[0x1]; /* +0x49a: bPressedPlay (Bool, flags 0x40000000002000) */
    ue420_byte at_049b_bPaused[0x1]; /* +0x49b: bPaused (Bool, flags 0x40000000002000) */
    ue420_byte at_049c_bJustUnpaused[0x1]; /* +0x49c: bJustUnpaused (Bool, flags 0x40000000002000) */
    ue420_byte at_049d_bPlaybackStarted[0x1]; /* +0x49d: bPlaybackStarted (Bool, flags 0x40000000002000) */
    ue420_byte at_049e_bPlaybackWaitingForSyncMaster[0x1]; /* +0x49e: bPlaybackWaitingForSyncMaster (Bool, flags 0x40000000002000) */
    ue420_byte at_049f_bPlaybackFinished[0x1]; /* +0x49f: bPlaybackFinished (Bool, flags 0x40000000002000) */
    ue420_byte at_04a0_bTickExternally[0x1]; /* +0x4a0: bTickExternally (Bool, flags 0x40000000002000) */
    ue420_byte at_04a1_bExternalSyncMaster[0x7]; /* +0x4a1: bExternalSyncMaster (Bool, flags 0x40000000002000) */
    ue420_byte at_04a8_ReferenceNames[0x10]; /* +0x4a8: ReferenceNames (Array, flags 0x40000000004000) */
};

/* Class params 0x143422090; size 0x88. */
struct UE420_NTRollbackChannel {
    ue420_byte unknown_0000[0x68];
    ue420_byte at_0068_RollbackNetworkInterface[0x20]; /* +0x68: RollbackNetworkInterface (Object, flags 0x40000000000000) */
};

/* Class params 0x143424b90; size 0x868. */
struct UE420_NTRollbackEngine {
    ue420_byte unknown_0000[0xc8];
    ue420_byte at_00c8_UniqueSessionData[0x28]; /* +0xc8: UniqueSessionData (Struct, flags 0x40000000000000) */
    ue420_byte at_00f0_LastInterimFrameState[0x28]; /* +0xf0: LastInterimFrameState (Object, flags 0x40000000000000) */
    ue420_byte at_0118_InputEventsFromRecordings[0x20]; /* +0x118: InputEventsFromRecordings (Array, flags 0x40000000000000) */
    ue420_byte at_0138_MinimumInputFrameNumber[0x8]; /* +0x138: MinimumInputFrameNumber (Int, flags 0x40000000000000) */
    ue420_byte at_0140_NetDriver[0x8]; /* +0x140: NetDriver (Object, flags 0x40000000000000) */
    ue420_byte at_0148_OpenChannels[0x10]; /* +0x148: OpenChannels (Array, flags 0x40000000000000) */
    ue420_byte at_0158_EngineInterface[0x8]; /* +0x158: EngineInterface (Object, flags 0x40000000000000) */
    ue420_byte at_0160_BackgroundEngineInterface[0x8]; /* +0x160: BackgroundEngineInterface (Object, flags 0x40000000000000) */
    ue420_byte at_0168_InputPredictor[0x8]; /* +0x168: InputPredictor (Object, flags 0x40000000000000) */
    ue420_byte at_0170_PublicFrameHistory[0x60]; /* +0x170: PublicFrameHistory (Struct, flags 0x40000000000000) */
    ue420_byte at_01d0_FrameStatePool[0x28]; /* +0x1d0: FrameStatePool (Struct, flags 0x40000000000000) */
    ue420_byte at_01f8_RollbackWorker[0x160]; /* +0x1f8: RollbackWorker (Struct, flags 0x40000000000000) */
    ue420_byte at_0358_FrameHashGenerator[0x60]; /* +0x358: FrameHashGenerator (Struct, flags 0x40000000000000) */
    ue420_byte at_03b8_GameStateSerialiser[0x50]; /* +0x3b8: GameStateSerialiser (Struct, flags 0x40000000000000) */
    ue420_byte at_0408_PipelineFrameEvaluator[0x70]; /* +0x408: PipelineFrameEvaluator (Struct, flags 0x40000000000000) */
    ue420_byte at_0478_DesyncLogger[0xa0]; /* +0x478: DesyncLogger (Struct, flags 0x40000000000000) */
    ue420_byte at_0518_InputRegister[0x28]; /* +0x518: InputRegister (Struct, flags 0x40000000000000) */
    ue420_byte at_0540_SerialisationReferenceLibrary[0x8]; /* +0x540: SerialisationReferenceLibrary (Object, flags 0x40000000000000) */
    ue420_byte at_0548_ActorInitialisers[0x10]; /* +0x548: ActorInitialisers (Array, flags 0x40000000000000) */
    ue420_byte at_0558_GlobalManagerData[0x10]; /* +0x558: GlobalManagerData (Array, flags 0x40000000000000) */
    ue420_byte at_0568_LocalPlayerAddEvents[0x10]; /* +0x568: LocalPlayerAddEvents (Array, flags 0x40000000000000) */
    ue420_byte at_0578_PermanentLocalPlayerAddEvents[0x10]; /* +0x578: PermanentLocalPlayerAddEvents (Array, flags 0x40000000000000) */
    ue420_byte at_0588_LocalPlayerRemoveEvents[0x10]; /* +0x588: LocalPlayerRemoveEvents (Array, flags 0x40000000000000) */
    ue420_byte at_0598_LocalInputEvents[0x10]; /* +0x598: LocalInputEvents (Array, flags 0x40000000000000) */
    ue420_byte at_05a8_ArchivedRetiredFrameStates[0x10]; /* +0x5a8: ArchivedRetiredFrameStates (Array, flags 0x40000000000000) */
    ue420_byte at_05b8_RetiredFrameStates[0x10]; /* +0x5b8: RetiredFrameStates (Array, flags 0x40000000000000) */
    ue420_byte at_05c8_RetiredFrameCompressor[0x58]; /* +0x5c8: RetiredFrameCompressor (Struct, flags 0x40000000000000) */
    ue420_byte at_0620_RequestedRetiredFrameStates[0x40]; /* +0x620: RequestedRetiredFrameStates (Array, flags 0x40000000000000) */
    ue420_byte at_0660_LoadStream[0x8]; /* +0x660: LoadStream (Object, flags 0x40000000000000) */
    ue420_byte at_0668_SaveStream[0x10]; /* +0x668: SaveStream (Object, flags 0x40000000000000) */
    ue420_byte at_0678_ServerResyncBaseFrame[0x8]; /* +0x678: ServerResyncBaseFrame (Object, flags 0x40000000000000) */
    ue420_byte at_0680_RecordingRetiredFrameHash[0x1e8]; /* +0x680: RecordingRetiredFrameHash (Map, flags 0x40000000000000) */
};

/* Class params 0x14342a160; size 0x100. */
struct UE420_NTRollbackMachine {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_MachineName[0x10]; /* +0x28: MachineName (Str, flags 0x10000000000000) */
    ue420_byte at_0038_RollbackEngine[0x8]; /* +0x38: RollbackEngine (Object, flags 0x10000000000000) */
    ue420_byte at_0040_StreamReader[0x8]; /* +0x40: StreamReader (Object, flags 0x10000000000000) */
    ue420_byte at_0048_Connections[0x10]; /* +0x48: Connections (Array, flags 0x10000000000000) */
    ue420_byte at_0058_InitParams[0xa8]; /* +0x58: InitParams (Struct, flags 0x40000000000000) */
};

/* Class params 0x14342a640; size 0x48. */
struct UE420_NTRollbackMachineConnection {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_RollbackNetworkInterface[0x8]; /* +0x28: RollbackNetworkInterface (Object, flags 0x40000000000000) */
    ue420_byte at_0030_DestinationConnection[0x18]; /* +0x30: DestinationConnection (Object, flags 0x40000000000000) */
};

/* Class params 0x14342b880; size 0xa0. */
struct UE420_NTRollbackMachineGroup {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_Machines[0x10]; /* +0x28: Machines (Array, flags 0x20080000000000) */
    ue420_byte at_0038_MachineConnections[0x10]; /* +0x38: MachineConnections (Array, flags 0x20080000000000) */
    ue420_byte at_0048_FutureFrames[0x58]; /* +0x48: FutureFrames (Map, flags 0x20080000000000) */
};

/* Class params 0x143428210; size 0xa0. */
struct UE420_NTRollbackMachineGroupConnected {
    ue420_byte unknown_0000[0xa0];
};

/* Class params 0x143428450; size 0xa0. */
struct UE420_NTRollbackMachineGroupLocal {
    ue420_byte unknown_0000[0xa0];
};

/* Class params 0x143429c30; size 0x330. */
struct UE420_NTRollbackNetworkInterface {
    ue420_byte unknown_0000[0x60];
    ue420_byte at_0060_AvgLag[0x8]; /* +0x60: AvgLag (Float, flags 0x10000000000000) */
    ue420_byte at_0068_RollbackEngine[0x8]; /* +0x68: RollbackEngine (Object, flags 0x40000000000000) */
    ue420_byte at_0070_StreamReference[0x140]; /* +0x70: StreamReference (Object, flags 0x40000000000000) */
    ue420_byte at_01b0_ReceivedInputEventPackets[0x10]; /* +0x1b0: ReceivedInputEventPackets (Array, flags 0x40000000000000) */
    ue420_byte at_01c0_ReceivedOutputEventPackets[0x60]; /* +0x1c0: ReceivedOutputEventPackets (Array, flags 0x40000000000000) */
    ue420_byte at_0220_OwnedPlayerAddEvents[0x10]; /* +0x220: OwnedPlayerAddEvents (Array, flags 0x40000000000000) */
    ue420_byte at_0230_PlayersToAddFromClient[0x70]; /* +0x230: PlayersToAddFromClient (Array, flags 0x40000000000000) */
    ue420_byte at_02a0_ReceivedSessionData[0x38]; /* +0x2a0: ReceivedSessionData (Struct, flags 0x40000000000000) */
    ue420_byte at_02d8_FrameHistoryFromGameStatePacket[0x18]; /* +0x2d8: FrameHistoryFromGameStatePacket (Struct, flags 0x40000000000000) */
    ue420_byte at_02f0_ReceivedRetiredFrameStatePackets[0x40]; /* +0x2f0: ReceivedRetiredFrameStatePackets (Array, flags 0x40000000000000) */
};

/* Class params 0x143429f00; size 0x50. */
struct UE420_NTRollbackObjectFactory {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_DefaultRollbackObjectFactoryClass[0x18]; /* +0x28: DefaultRollbackObjectFactoryClass (Struct, flags 0x40000000004000) */
    ue420_byte at_0040_World[0x10]; /* +0x40: World (Object, flags 0x40000000000000) */
};

/* Class params 0x143423d20; size 0x28. */
struct UE420_NTRollbackObjectProvider {
    ue420_byte unknown_0000[0x28];
};

/* Class params 0x14343a280; size 0x28. */
struct UE420_NTRollbackPlayerController {
    ue420_byte unknown_0000[0x28];
};

/* Class params 0x14342a0a0; size 0x40. */
struct UE420_NTRollbackRecording {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_ServerStream[0x8]; /* +0x28: ServerStream (Object, flags 0x10000000000001) */
    ue420_byte at_0030_ClientStreams[0x10]; /* +0x30: ClientStreams (Array, flags 0x10000000000001) */
};

/* Class params 0x14342a4b0; size 0x38. */
struct UE420_NTRollbackRecordingStream {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_RecordingBytes[0x10]; /* +0x28: RecordingBytes (Array, flags 0x40000000000000) */
};

/* Class params 0x14342af60; size 0xe0. */
struct UE420_NTRollbackRecordingStreamReader {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_StreamReference[0x8]; /* +0x28: StreamReference (Object, flags 0x40000000000000) */
    ue420_byte at_0030_RollbackEngine[0x8]; /* +0x30: RollbackEngine (Object, flags 0x40000000000000) */
    ue420_byte at_0038_RollbackObjectProvider[0x10]; /* +0x38: RollbackObjectProvider (Interface, flags 0x44000000000000) */
    ue420_byte at_0048_SourceStream[0x8]; /* +0x48: SourceStream (Object, flags 0x40000000000000) */
    ue420_byte at_0050_Header[0x90]; /* +0x50: Header (Struct, flags 0x40000000000000) */
};

/* Class params 0x14342b1a0; size 0xa8. */
struct UE420_NTRollbackRecordingStreamWriter {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_StreamReference[0x8]; /* +0x28: StreamReference (Object, flags 0x40000000000000) */
    ue420_byte at_0030_RollbackEngine[0x8]; /* +0x30: RollbackEngine (Object, flags 0x40000000000000) */
    ue420_byte at_0038_Header[0x70]; /* +0x38: Header (Struct, flags 0x40000000000000) */
};

/* Class params 0x14343c740; size 0xc8. */
struct UE420_NTRollbackRecordingTestBlueprint {
    ue420_byte unknown_0000[0xb0];
    ue420_byte at_00b0_TestRecording[0x18]; /* +0xb0: TestRecording (Object, flags 0x10000000000015) */
};

/* Class params 0x1434396a0; size 0x180. */
struct UE420_NTServerPlaybackManager {
    ue420_byte unknown_0000[0x90];
    ue420_byte at_0090_RingBufferStartIndex[0x4]; /* +0x90: RingBufferStartIndex (Int, flags 0x40000000000000) */
    ue420_byte at_0094_CurrentFrameNumber[0x4]; /* +0x94: CurrentFrameNumber (Int, flags 0x40000000000000) */
    ue420_byte at_0098_CheckpointFrames[0x50]; /* +0x98: CheckpointFrames (Map, flags 0x40000000000000) */
    ue420_byte at_00e8_CurrentFrame[0x68]; /* +0xe8: CurrentFrame (Struct, flags 0x40000000000000) */
    ue420_byte at_0150_ReferenceEngineInterface[0x8]; /* +0x150: ReferenceEngineInterface (Object, flags 0x40000000000000) */
    ue420_byte at_0158_ReferenceInputPredictor[0x8]; /* +0x158: ReferenceInputPredictor (Object, flags 0x40000000000000) */
    ue420_byte at_0160_CurrentReferenceFrame[0x8]; /* +0x160: CurrentReferenceFrame (Object, flags 0x40000000000000) */
    ue420_byte at_0168_PreviousReferenceFrame[0x8]; /* +0x168: PreviousReferenceFrame (Object, flags 0x40000000000000) */
    ue420_byte at_0170_RollbackEngine[0x8]; /* +0x170: RollbackEngine (Object, flags 0x40000000000000) */
    ue420_byte at_0178_bInitialised[0x1]; /* +0x178: bInitialised (Bool, flags 0x40000000000000) */
    ue420_byte at_0179_bSeekInProgress[0x7]; /* +0x179: bSeekInProgress (Bool, flags 0x40000000000000) */
};

/* Class params 0x1433f67c0; size 0x38. */
struct UE420_NTSessionOptions {
    ue420_byte unknown_0000[0x28];
    ue420_byte at_0028_StartingGameplayEvents[0x10]; /* +0x28: StartingGameplayEvents (Array, flags 0x4010000000000015) */
};

/* Class params 0x143409b20; size 0x400. */
struct UE420_NTTestPlayerState {
    ue420_byte unknown_0000[0x3f0];
    ue420_byte at_03f0_UnrealPlayerID[0x10]; /* +0x3f0: UnrealPlayerID (Int, flags 0x10000000000000) */
};

/* Class params 0x14343aa80; size 0x420. */
struct UE420_NTWorldSingleton {
    ue420_byte unknown_0000[0x398];
    ue420_byte at_0398_OutputEventCallback[0x10]; /* +0x398: OutputEventCallback (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_03a8_GameplayEventCallback[0x40]; /* +0x3a8: GameplayEventCallback (MulticastDelegate, flags 0x10000010080000) */
    ue420_byte at_03e8_RollbackEngine[0x8]; /* +0x3e8: RollbackEngine (Object, flags 0x20080000000000) */
    ue420_byte at_03f0_CurrentState[0x8]; /* +0x3f0: CurrentState (Object, flags 0x20080000000000) */
    ue420_byte at_03f8_BufferedOutputEvents[0x10]; /* +0x3f8: BufferedOutputEvents (Array, flags 0x20080000000000) */
    ue420_byte at_0408_BufferedGameplayEvents[0x18]; /* +0x408: BufferedGameplayEvents (Array, flags 0x20080000000000) */
};

/* Class params 0x143491490; size 0x190. */
struct UE420_OnlineSessionClient {
    ue420_byte unknown_0000[0x188];
    ue420_byte at_0188_bIsFromInvite[0x1]; /* +0x188: bIsFromInvite (Bool, flags 0x20080000002000) */
    ue420_byte at_0189_bHandlingDisconnect[0x7]; /* +0x189: bHandlingDisconnect (Bool, flags 0x20080000002000) */
};

#pragma pack(pop)
