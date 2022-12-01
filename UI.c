﻿#include "UI.h"

#include "Point.h"
#include "Rect.h"

#include "Screen.h"
#include "Game.h"

#include "Player.h"
#include "HeartBeat.h"

#ifdef DEBUG
#include "Debug.h"
#endif // DEBUG

#define BPMPosX (68)
#define LeftArrowPosX (73)
#define RightArrowPosX (76)

//const char HeartChar[] = "♥";
//const char EmptyHeartChar[] = "♡";

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
	ScreenPrintColor(BPMPosX, 2, "140", FOREGROUND_BLUE);
	ScreenPrintColor(BPMPosX, 3, "120", FOREGROUND_BLUE);
	ScreenPrintColor(BPMPosX, 4, "100", FOREGROUND_BLUE);
	ScreenPrintColor(BPMPosX, 5, " 80", FOREGROUND_BLUE);
	ScreenPrintColor(BPMPosX, 6, " 60", FOREGROUND_BLUE);
	if (GetNowBpmLevel() == 4)
	{
		SetScreenCell(LeftArrowPosX, 1, 0x2190, BACKGROUND_BLUE);
		SetScreenCell(RightArrowPosX, 1, 0x2190, BACKGROUND_BLUE);
	}
	else if(GetNowBpmLevel() == 3)
	{
		SetScreenCell(LeftArrowPosX, 2, 0x2192, FOREGROUND_BLUE);
		SetScreenCell(RightArrowPosX, 2, 0x2190, FOREGROUND_BLUE);
	}
	else if (GetNowBpmLevel() == 2)
	{
		SetScreenCell(LeftArrowPosX, 3, 0x2192, FOREGROUND_BLUE);
		SetScreenCell(RightArrowPosX, 3, 0x2190, FOREGROUND_BLUE);
	}
	else if (GetNowBpmLevel() == 1)
	{
		SetScreenCell(LeftArrowPosX, 4, 0x2192, FOREGROUND_BLUE);
		SetScreenCell(RightArrowPosX, 4, 0x2190, FOREGROUND_BLUE);
	}
	else if (GetNowBpmLevel() == 0)
	{
		SetScreenCell(LeftArrowPosX, 5, 0x2192, FOREGROUND_BLUE);
		SetScreenCell(RightArrowPosX, 5, 0x2190, FOREGROUND_BLUE);
	}
}

void RenderHealth() {
	int MHPPLACEHOLDER = 30;
	int max_health_indicator_height = MHPPLACEHOLDER / 8;
	int health_bar_full_cell_count = player->hp / 2;
	int health_bar_partial_cell_status = player->hp % 2;

	Point health_bar_start = { .x = 6, .y = 23 };

	for (int i = 0; i < health_bar_full_cell_count; i++) {
		SetScreenCell(health_bar_start.x, health_bar_start.y - i, ' ', BACKGROUND_RED | BACKGROUND_INTENSITY);
	}

	if (health_bar_partial_cell_status) {
		SetScreenCell(health_bar_start.x * 2, health_bar_start.y - health_bar_full_cell_count, 0x2584, BACKGROUND_RED | BACKGROUND_INTENSITY);
		SetScreenCell(health_bar_start.x * 2 + 1, health_bar_start.y - health_bar_full_cell_count, 0x2584, BACKGROUND_RED | BACKGROUND_INTENSITY);
	}
}

void RenderUI() {
	RenderUIFrame();
	RenderHealth();
	RenderBPM();
}
