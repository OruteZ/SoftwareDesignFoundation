﻿#include "UI.h"

#include "Point.h"
#include "Rect.h"

#include "Screen.h"
#include "Game.h"

#include "Player.h"
#include "HeartBeat.h"
#include "Enemy.h"
#include "Time.h"

#ifdef DEBUG
#include "Debug.h"
#endif // DEBUG

#define BPMPosX (34 * 2)
#define LeftArrowPosX 33
#define RightArrowPosX 36


#define PlayerHpPosX 5
#define	PlayerHpPosY 23
#define PlayerLevelPosX 3
#define PlayerLevelPosY 2
#define PlayerExpPosX 3
#define PlayerExpPosY 3
#define PlayerBaseDamagePosX 3
#define PlayerBaseDamagePosY 4
#define ScorePosX 3
#define ScorePosY 6

#define MoveKeyInfoPosX 3
#define MoveKeyInfoPosY 8
#define MeleeAttackKeyInfoPosX 3
#define MeleeAttackKeyInfoPosY 10
#define RangeAttackKeyInfoPosX 3
#define RangeAttackKeyInfoPosY 12
#define BeatKeyInfoPosX 3
#define BeatKeyInfoPosY 14
#define PotionKeyInfoPosX 3
#define PotionKeyInfoPosY 16
//const char HeartChar[] = "♥";
//const char EmptyHeartChar[] = "♡";

void InfoPrint(int x, int y, char* str, int info, const unsigned short attribute)
{
	char arr[20];
	sprintf(arr, "%d", info);
	ScreenPrintColor(x, y, str, attribute);
	ScreenPrintColor(x + strlen(str), y, arr, attribute);
}

void RenderUIFrame() {
	// top & bottom row
	for (int i = 0; i < SCREEN_WIDTH / 2 - 1; i++) {
		SetScreenCell(i, 0, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		SetScreenCell(i, SCREEN_HEIGHT - 1, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}

	// 4 vertcial walls
	for (int i = 1; i < SCREEN_HEIGHT - 1; i++) {
		SetScreenCell(0, i, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		SetScreenCell(7, i, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		SetScreenCell(SCREEN_WIDTH / 2 - 2 - 7, i, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		SetScreenCell(SCREEN_WIDTH / 2 - 2, i, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}

	// HeartBeat BPM / HeartBeat Note Divider`
	for (int i = 0; i < 6; i++) {
		Point origin = { .x = 32, .y = 8 };
		SetScreenCell(origin.x + i, origin.y, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}
}

void RenderBPM()
{
	ScreenPrintColor(BPMPosX, 2, "140", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(BPMPosX, 3, "120", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(BPMPosX, 4, "100", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(BPMPosX, 5, " 80", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(BPMPosX, 6, " 60", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	if (GetNowBpmLevel() == 4)
	{
		SetScreenCell(LeftArrowPosX, 2, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetScreenCell(RightArrowPosX, 2, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if(GetNowBpmLevel() == 3)
	{
		SetScreenCell(LeftArrowPosX, 3, 0x2192, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetScreenCell(RightArrowPosX, 3, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if (GetNowBpmLevel() == 2)
	{
		SetScreenCell(LeftArrowPosX, 4, 0x2192, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetScreenCell(RightArrowPosX, 4, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if (GetNowBpmLevel() == 1)
	{
		SetScreenCell(LeftArrowPosX, 5, 0x2192, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetScreenCell(RightArrowPosX, 5, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if (GetNowBpmLevel() == 0)
	{
		SetScreenCell(LeftArrowPosX, 6, 0x2192, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetScreenCell(RightArrowPosX, 6, 0x2190, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}

void RenderInfo()
{
	InfoPrint(PlayerHpPosX, PlayerHpPosY, "HP:",player->hp, FOREGROUND_RED);
	InfoPrint(PlayerLevelPosX, PlayerLevelPosY, "Level:", player->level, FOREGROUND_GREEN);
	InfoPrint(PlayerExpPosX, PlayerExpPosY, "EXP:", player->exp, FOREGROUND_GREEN);

	//score print
	char arr[20];
	sprintf(arr, "%d", GetScore());
	ScreenPrintColor(ScorePosX, ScorePosY, "Score", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(ScorePosX, ScorePosY+1, arr, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	InfoPrint(PlayerBaseDamagePosX, PlayerBaseDamagePosY, "Damage:", player->baseDamage, FOREGROUND_GREEN);
	ScreenPrintColor(MoveKeyInfoPosX, MoveKeyInfoPosY, "이동", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(MoveKeyInfoPosX, MoveKeyInfoPosY + 1, "WASD", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(MeleeAttackKeyInfoPosX, MeleeAttackKeyInfoPosY, "공격", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(MeleeAttackKeyInfoPosX, MeleeAttackKeyInfoPosY + 1, "J", FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(RangeAttackKeyInfoPosX, RangeAttackKeyInfoPosY, "화살", FOREGROUND_BLUE | FOREGROUND_GREEN);
	InfoPrint(RangeAttackKeyInfoPosX, RangeAttackKeyInfoPosY + 1, "K ", GetPlayerItemCount(BULLET_ID), FOREGROUND_BLUE | FOREGROUND_GREEN);
	ScreenPrintColor(BeatKeyInfoPosX,BeatKeyInfoPosY, "비트", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(BeatKeyInfoPosX, BeatKeyInfoPosY + 1, "SPACE", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	ScreenPrintColor(PotionKeyInfoPosX, PotionKeyInfoPosY, "포션", FOREGROUND_RED | FOREGROUND_GREEN);
	InfoPrint(PotionKeyInfoPosX, PotionKeyInfoPosY + 1, "L ", GetPlayerItemCount(POTION_ID), FOREGROUND_RED | FOREGROUND_GREEN);
}

void RenderHealth() {
	int max_health_indicator_height = player->maxHp / 4;
	int health_bar_full_cell_count = player->hp / 4;
	int health_bar_partial_cell_status = player->hp % 4;

	Point health_bar_start = { .x = 6, .y = 23 };

	for (int i = 0; i < health_bar_full_cell_count; i++) {
		SetScreenCell(health_bar_start.x, health_bar_start.y - i, ' ', BACKGROUND_RED | BACKGROUND_INTENSITY);
	}

	if (health_bar_partial_cell_status) {
		SetScreenHalfCell(health_bar_start.x * 2, health_bar_start.y - health_bar_full_cell_count, 0x2580 + health_bar_partial_cell_status * 2, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetScreenHalfCell(health_bar_start.x * 2 + 1, health_bar_start.y - health_bar_full_cell_count, 0x2580 + health_bar_partial_cell_status * 2, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	//if (health_bar_partial_cell_status) {
	//	SetScreenHalfCell(health_bar_start.x * 2, health_bar_start.y - health_bar_full_cell_count, 0x2586, FOREGROUND_RED | FOREGROUND_INTENSITY);
	//	SetScreenHalfCell(health_bar_start.x * 2 + 1, health_bar_start.y - health_bar_full_cell_count, 0x2586, FOREGROUND_RED | FOREGROUND_INTENSITY);
	//}

	// 2661 for empty heart
	SetScreenCell(health_bar_start.x, health_bar_start.y - max_health_indicator_height - 1, 0x2665, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

int judgeLevel = -1;
const char perfect[] = "Perfect!";
const char great[] = "Great!";
const char good[] = "Good!";
const char miss[] = "Miss...";
const double RenderCooldown = 0.5;

double currentNoteRenderTime = 0;
void ShowNoteJudge(int judgement) {
	if (judgement > -1) judgeLevel = judgement;
	currentNoteRenderTime = RenderCooldown;
}

double currentStageRenderTime = 0;
bool stageClearMsgTrigger = false;
int stageNum = 0;
void ShowClearStage() {
	stageClearMsgTrigger = true;
	currentStageRenderTime = 1;
}

void RenderNote() {
	currentNoteRenderTime -= Time.deltaTime;
	if (currentNoteRenderTime <= 0) judgeLevel = -1;

	Point notePrintPos = { .x = 33, .y = 10 };
	int noteUnicode = ' ';

	int size = GetNoteSize();
	bool* note = GetNoteInfo();

	for (int j = 0; j < 4; j++) {
		SetScreenCell(notePrintPos.x + j, notePrintPos.y + size - 1, ' ', BACKGROUND_GREEN);
	}
	switch (judgeLevel) {
	case -1:
		break;
	case 0:
		ScreenPrintColor(notePrintPos.x * 2, notePrintPos.y + size, miss, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	case 1:
		ScreenPrintColor(notePrintPos.x * 2, notePrintPos.y + size, good, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	case 2:
		ScreenPrintColor(notePrintPos.x * 2, notePrintPos.y + size, great, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	case 3:
		ScreenPrintColor(notePrintPos.x * 2, notePrintPos.y + size, perfect, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	}
	


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {

			if (note[size - i - 1]) {
				SetScreenCell(notePrintPos.x + j, notePrintPos.y + i, ' ', BACKGROUND_BLUE);
			}
		}
	}
}

void RenderUI() {
	RenderUIFrame();
	RenderHealth();
	RenderBPM();
	RenderInfo();
	RenderNote();

	if (stageClearMsgTrigger) {
		ScreenPrintColor(31, 12, "Stage Clear!!!", FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		currentStageRenderTime -= Time.deltaTime;
		if (currentStageRenderTime <= 0) stageClearMsgTrigger = false;
	}
}
