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
	const short* note = GetNoteInfo();
	const int size = GetNoteSize();

	for (int y = 0; y < size; y++) {
		if(note[size - 1 - y]) ScreenPrint(HEARTBEAT_NOTE_POSITION_X, HEARTBEAT_NOTE_POSITION_Y + y, noteImg);
	}
	ScreenPrint(HEARTBEAT_NOTE_POSITION_X, HEARTBEAT_NOTE_POSITION_Y + size - 1, lineImg);
}

const char HeartChar[] = "♥";
const char EmptyHeartChar[] = "♡";
void PrintHPBar() {
	int maxHp = 100; // todo = maxHP 필드 player 구조체에 추가
	int nowHp = player->hp;
	
	SetColor(4);
	int barLength = (int)(HPBAR_MAX_LENGTH * nowHp) / maxHp;
	if (barLength < 0) barLength = 0;
	for (int i = 0; i < barLength; i++) {
		ScreenPrint(HPBAR_POSITION_X + i * 2, HPBAR_POSITION_Y, HeartChar);
	}
	for (int i = barLength; i < HPBAR_MAX_LENGTH; i ++) {
		ScreenPrint(HPBAR_POSITION_X + i * 2, HPBAR_POSITION_Y, EmptyHeartChar);
	}
	SetColor(15);
}

const Rect InfoUIRect = {
	.x = 2,
	.y = 2,
	.width = 11,
	.height = 22,
};

const Point printPoint_Stage = {
	.x = 4,
	.y = 3,
};

const Point printPoint_BPM = {
	.x = 4,
	.y = 7
};

const Point printPoint_Score = {
	.x = 4,
	.y = 13,
};

void PrintBuffer(int x, int y, const char* format, ...) {
	va_list args;
	va_start(args, format);

	char buffer[11];
	vsprintf_s(buffer, sizeof(buffer), format, args);

	va_end(args);

	ScreenPrint(x, y, buffer);

}


int currentWorldNumber = 1;
void PrintInfo() {
	Point p;
	
	p = printPoint_BPM;
	PrintBuffer(p.x, p.y, "BPM");
	PrintBuffer(p.x, p.y + 1, "%d", GetBPM());

	p = printPoint_Score;
	ScreenPrint(p.x, p.y, "Score");
	PrintBuffer(p.x, p.y + 1, "%d", GetScore());

	p = printPoint_Stage;
	PrintBuffer(p.x, p.y, "Stage %d", 1);
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
	PrintInfo();
}

