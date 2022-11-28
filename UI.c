#include "World.h"
#include "Screen.h"
#include "Game.h"
#include "Player.h"
#include "Debug.h"
#include "HeartBeat.h"

#define HEARTBEAT_NOTE_POSITION_X (111)
#define HEARTBEAT_NOTE_POSITION_Y (2)

#define HPBAR_POSITION_X (8)
#define HPBAR_POSITION_Y (1)
#define HPBAR_MAX_LENGTH (100)

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

const char HeartChar[] = "|";
void PrintHPBar() {
	int maxHp = 100; // todo = maxHP 필드 player 구조체에 추가
	int nowHp = player->hp;
	
	int barLength = (int)(HPBAR_MAX_LENGTH * nowHp) / maxHp;
	for (int i = 0; i < barLength; i++) {
		ScreenPrint(HPBAR_POSITION_X + i, HPBAR_POSITION_Y, HeartChar);
	}
}


void RenderUI() {
	PrintHPBar();
	RenderHeatBeatNote();
}

