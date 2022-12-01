#include "Screen.h"

#include <stdlib.h>

#include <Windows.h>

//int g_nScreenIndex = 0;
//HANDLE g_hScreen[2];


/*
	FOR EVERY 2-WIDTH CHARACTER
	SECOND CELL IS FILLED WITH SOMETHING.

	TO CHANGE 'SOMETHING', modify ScreenClear() ScreenPrintColor();
*/

struct {
	HANDLE console_handle;
#ifdef DEBUG
	CHAR_INFO grid[DEBUG_SCREEN_HEIGHT][SCREEN_WIDTH];
#else
	CHAR_INFO grid[SCREEN_HEIGHT][SCREEN_WIDTH];
#endif // DEBUG
	int width;
	int height;
	COORD origin;
	COORD size;

	unsigned short attribute;
} screen = {
	.height = SCREEN_HEIGHT,
	.width = SCREEN_WIDTH,
	.origin = {.X = 0, .Y = 0},
#ifdef DEBUG
	.size = {.X = SCREEN_WIDTH, .Y = DEBUG_SCREEN_HEIGHT},
#else
	.size = {.X = SCREEN_WIDTH, .Y = SCREEN_HEIGHT},
#endif

	.attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};



#ifdef DEBUG
HANDLE ScreenReturnBufferHandle_Unsafe() {
	return screen.console_handle;
}
#endif

void ScreenInit()
{
	screen.console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cci;

	system("mode con:cols=120 lines=50");

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(screen.console_handle, &cci);

	ScreenClear();
}

void ScreenFlipping()
{
	SMALL_RECT write_region = {
		.Left = screen.origin.X,
		.Top = screen.origin.Y,
		.Right = screen.size.X,
		.Bottom = screen.size.Y
	};
	WriteConsoleOutputW(screen.console_handle, (CHAR_INFO*)screen.grid, screen.size, screen.origin, &write_region);
}

void ScreenClear()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			screen.grid[i][j].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			screen.grid[i][j].Char.UnicodeChar = ' ';
		}
	}
}

void ScreenRelease()
{
	//CloseHandle(g_hScreen[0]);
	//CloseHandle(g_hScreen[1]);
	CloseHandle(screen.console_handle);
}

void SetScreenCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute) {
	if (!(0 <= x && x < SCREEN_WIDTH &&
		0 <= y && y < SCREEN_HEIGHT)) return;
	screen.grid[y][2 * x].Attributes = attribute;
	screen.grid[y][2 * x + 1].Attributes = attribute;

	screen.grid[y][2 * x].Char.UnicodeChar = unicode;
	screen.grid[y][2 * x + 1].Char.UnicodeChar = 0x0000;
}
#define EUC_KR 51949
#define CANVAS_CHAR_BUFFER_SIZE 256
#include "wcwidth.h"
void ScreenPrintColor(const int x, const int y, const char* str, const unsigned short attribute) {
#ifdef DEBUG
	if (y >= DEBUG_SCREEN_HEIGHT) return;
#else
	if (y >= SCREEN_HEIGHT) return;
#endif
	WCHAR buffer[CANVAS_CHAR_BUFFER_SIZE];
	MultiByteToWideChar(EUC_KR, MB_PRECOMPOSED, str, -1, buffer, CANVAS_CHAR_BUFFER_SIZE);

	for (int i = 0, j = x; i < CANVAS_CHAR_BUFFER_SIZE && j < SCREEN_WIDTH; i++, j++) {
		if (buffer[i] == '\0') return;
		screen.grid[y][j].Attributes = screen.attribute;
		screen.grid[y][j].Char.UnicodeChar = buffer[i];

		// if character requires more than 1 width, advance while filling canvas.grid.Char with '\0'
		const int width = mk_wcwidth(buffer[i]);
		for (int i = 1; i < width; i++) {
			j++;
			if (j >= SCREEN_WIDTH) return;
			screen.grid[y][j].Attributes = screen.attribute;
			screen.grid[y][j].Char.UnicodeChar = ' ';
		}
	}
}
void ScreenPrint(const int x, const int y, const char* str)
{
	ScreenPrintColor(x, y, str, screen.attribute);
}

void SetColor(unsigned short color)
{
	screen.attribute = color;
}

#ifdef DEBUG
void FillCanvasWithRandomCells() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
			SetScreenCell(j, i, 0x25a0, rand() % 0x0100);
		}
	}
}
void FillCanvasWithTestString() {
	char temp[] = "가나다라마바사";

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		ScreenPrintColor(0, i, temp, rand() % 0x0100);
	}
}
#endif // DEBUG

