#include "UI.h"

#include "Point.h"
#include "Rect.h"

#include "Screen.h"
#include "Game.h"

#include "Player.h"
#include "HeartBeat.h"

#ifdef DEBUG
#include "Debug.h"
#endif // DEBUG

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

void RenderUI() {
	RenderUIFrame();
}
