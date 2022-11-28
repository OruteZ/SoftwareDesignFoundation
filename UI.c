#include "World.h"
#include "Screen.h"
#include "Game.h"
#include "Player.h"
#include "Debug.h"
#include "HeartBeat.h"
#include "Rect.h"
#include "Point.h"

#define HEARTBEAT_NOTE_POSITION_X (121)
#define HEARTBEAT_NOTE_POSITION_Y (2)

#define HPBAR_POSITION_X (18)
#define HPBAR_POSITION_Y (3)
#define HPBAR_MAX_LENGTH (50)

const char noteImg[] = "ⓣⓣⓣⓣ";
const char lineImg[] = "--------";
void RenderHeatBeatNote() {
	const short* note = heartBeat->note;
	const int size = heartBeat->noteSize;

	for (int y = 0; y < size; y++) {
		if(note[size - 1 - y]) ScreenPrint(HEARTBEAT_NOTE_POSITION_X, HEARTBEAT_NOTE_POSITION_Y + y, noteImg);
	}
	ScreenPrint(HEARTBEAT_NOTE_POSITION_X, HEARTBEAT_NOTE_POSITION_Y + size - 1, lineImg);
}

const char HeartChar[] = "♥";
void PrintHPBar() {
	int maxHp = 100; // todo = maxHP 필드 player 구조체에 추가
	int nowHp = player->hp;
	
	SetColor(4);
	int barLength = (int)(HPBAR_MAX_LENGTH * nowHp) / maxHp;
	for (int i = 0; i < barLength; i++) {
		ScreenPrint(HPBAR_POSITION_X + i * 2, HPBAR_POSITION_Y, HeartChar);
	}
	SetColor(15);
}

const Rect InfoUIRect = {
	.x = 2,
	.y = 2,
	.width = 11,
	.height = 22,
};

const Point printPoint_BPM = {
	.x = 4,
	.y = 7
};

const Point printPoint_Score = {
	.x = 4,
	.y = 13,
};


void PrintInfo() {
	Point p = printPoint_BPM;
	ScreenPrint(p.x, p.y, "BPM : %d", GetBPM());
}

void PrintInfoUIBox() {
	for (int x = InfoUIRect.x + 2; x < InfoUIRect.x + InfoUIRect.width; x += 2) {
		ScreenPrint(x, InfoUIRect.y, "─");
		ScreenPrint(x, InfoUIRect.y + InfoUIRect.height, "─");
	}

	for (int y = InfoUIRect.y + 1; y < InfoUIRect.y + InfoUIRect.height; y++) {
		ScreenPrint(InfoUIRect.x, y, "│");
		ScreenPrint(InfoUIRect.x + InfoUIRect.width, y, "│");
	}

	ScreenPrint(InfoUIRect.x, InfoUIRect.y, "┌");
	ScreenPrint(InfoUIRect.x + InfoUIRect.width, InfoUIRect.y, "┐");
	ScreenPrint(InfoUIRect.x, InfoUIRect.y + InfoUIRect.height, "└");
	ScreenPrint(InfoUIRect.x + InfoUIRect.width, InfoUIRect.y + InfoUIRect.height, "┘");
}

void RenderUI() {
	PrintHPBar();
	RenderHeatBeatNote();
	PrintInfoUIBox();
}

