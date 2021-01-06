#ifndef GUARD_BERRY_CRUSH_H
#define GUARD_BERRY_CRUSH_H

enum {
    BCTEXT_AREYOUREADY,
    BCTEXT_WAITFOROTHERS,
    BCTEXT_GAINEDPOWDER,
    BCTEXT_RECORDINGRESULTS,
    BCTEXT_ASKPLAYAGAIN,
    BCTEXT_CANCEL_NOBERRIES,
    BCTEXT_CANCEL_DROPPEDOUT,
    BCTEXT_TIMEUP,
    BCTEXT_COMMSTANDBY,
};

enum {
    BCCMD_BeginNormalPaletteFade = 1,
    BCCMD_WaitPaletteFade,
    BCCMD_PrintMessage,
    BCCMD_InitGfx,
    BCCMD_TeardownGfx,
    BCCMD_SignalReadyToBegin,
    BCCMD_AskPickBerry,
    BCCMD_GoToBerryPouch,
    BCCMD_WaitForOthersToPickBerries,
    BCCMD_DropBerriesIntoCrusher,
    BCCMD_DropLid,
    BCCMD_Countdown,
    BCCMD_PlayGame_Master,
    BCCMD_PlayGame_Slave,
    BCCMD_FinishGame,
    BCCMD_HandleTimeUp,
    BCCMD_TabulateResults,
    BCCMD_ShowResults,
    BCCMD_SaveTheGame,
    BCCMD_AskPlayAgain,
    BCCMD_CommunicatePlayAgainResponses,
    BCCMD_FadeOutToPlayAgain,
    BCCMD_PlayAgainFailureMessage,
    BCCMD_GracefulExit,
    BCCMD_Quit,
};

struct BerryCrushGame_Player
{
    u16 berryId;
    u16 unk2;
    union
    {
        u8 as_2d_bytes[2][8];
        u16 as_hwords[8];
    } unk4;
    u8 unk14[12];
};

struct BerryCrushGame_5C
{
    u16 unk00;
    u8 unk02_0:1;
    u8 unk02_1:1;
    u8 pushedAButton:1;
    u8 unk02_3:5;
    s8 unk03;
    u16 unk04;
    u16 unk06;
    u16 unk08;
    u16 unk0A;
};

struct __attribute__((packed, aligned(2))) BerryCrushGame_4E
{
    u16 unk0;
    struct BerryCrushGame_5C data;
};

union BerryCrushGame_68
{
    struct BerryCrushGame_68_x
    {
        struct BerryCrushGame_68_x_SubStruct
        {
            s32 unk00;
            u16 unk04;
            s16 unk06;
            u16 unk08;
            u16 unk0A;
            // 0: Number of A presses
            // 1: Neatness
            u16 stats[2][5];
            u8 filler20[16];
        } unk00;
        u8 unk30[12];
        struct BerryCrushGame_Player others[4];
        u8 fillerBC[20];
    } as_four_players;
    struct BerryCrushGame_68_y
    {
        u8 filler00[28];
        struct BerryCrushGame_Player players[5];
        u8 fillerBC[20];
    } as_five_players;
};

struct BerryCrushPlayerSeatCoords
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
};

struct BerryCrushGame_138
{
    u8 animBerryIdx;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 minutes;
    s16 secondsInt;
    s16 secondsFrac;
    const struct BerryCrushPlayerSeatCoords * seatCoords[5];
    struct Sprite *coreSprite;
    struct Sprite *impactSprites[5];
    struct Sprite *berrySprites[5];
    struct Sprite *sparkleSprites[11];
    struct Sprite *timerSprites[2];
    u8 unk80;
    u8 filler81;
    u8 unk82;
    u8 unk83[5];
};

struct BerryCrushGame
{
    MainCallback savedCallback;
    u32 (*cmdCallback)(struct BerryCrushGame *, u8 *);
    u8 localId;
    u8 playerCount;
    u8 taskId;
    u8 textSpeed;
    u8 cmdState;
    u8 unkD;
    u8 nextCmd;
    u8 afterPalFadeCmd;
    u16 unk10;
    u16 gameState;
    u16 unk14;
    u16 pressingSpeed;
    s16 unk18;
    s16 unk1A;
    int powder;
    s32 unk20;
    u8 unk24;
    u8 unk25_0:1;
    u8 unk25_1:1;
    u8 unk25_2:1;
    u8 unk25_3:1;
    u8 unk25_4:1;
    u8 unk25_5:3;
    u16 unk26;
    u16 timer;
    s16 depth;
    s16 vibration;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    u8 commandParams[10];
    u16 sendCmd[7];
    u16 recvCmd[7];
    struct BerryCrushGame_5C localState;
    union BerryCrushGame_68 unk68;
    struct BerryCrushGame_138 spritesManager;
    u8 bg1Buffer[0x1000];
    u8 unk11C0[0x1000];
    u8 bg2Buffer[0x1000];
    u8 bg3Buffer[0x1000];
};

#define BERRYCRUSH_PLAYER_NAME(game, i)                        \
    ((u8 *)(game)                                    \
    + offsetof(struct BerryCrushGame, unk68)         \
    + offsetof(struct BerryCrushGame_68_x, unk30)    \
    + sizeof(struct BerryCrushGame_Player) * (i))

struct BerryCrushGame *GetBerryCrushGame(void);
void StartBerryCrush(MainCallback callback);
u32 ExitBerryCrushWithCallback(MainCallback callback);
void CB2_BerryCrush_GoToBerryPouch(void);
void BerryCrush_SetVBlankCallback(void);
void BerryCrush_UnsetVBlankCallback(void);
void BerryCrush_UpdateSav2Records(void);
void BerryCrush_RunOrScheduleCommand(u16 command, u8 runMode, u8 *params);
void BerryCrush_SetPaletteFadeParams(u8 *params, bool8 communicateAfter, u32 selectedPals, s8 delay, u8 startY, u8 targetY, u16 palette);
int sub_814D9CC(struct BerryCrushGame *arg0);
int BerryCrush_InitBgs(void);
int BerryCrush_TeardownBgs(void);
void BerryCrush_CreateBerrySprites(struct BerryCrushGame *arg0, struct BerryCrushGame_138 *arg1);
void BerryCrushFreeBerrySpriteGfx(struct BerryCrushGame *arg0, struct BerryCrushGame_138 *arg1);
void sub_814DC5C(struct BerryCrushGame *arg0, struct BerryCrushGame_138 *arg1);
bool32 sub_814DE50(struct BerryCrushGame *arg0, struct BerryCrushGame_138 *arg1);
bool32 sub_814E644(struct BerryCrushGame *arg0, struct BerryCrushGame_138 *arg1);
void sub_814E80C(struct BerryCrushGame *arg0);
void sub_814DA04(struct BerryCrushGame *arg0);
void BerryCrush_HideTimerSprites(struct BerryCrushGame_138 *arg0);
void SpriteCB_DropBerryIntoCrusher(struct Sprite * sprite);
void ShowBerryCrushRankings(void);

#endif //GUARD_BERRY_CRUSH_H
