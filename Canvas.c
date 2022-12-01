#include "Canvas.h"
#include <Windows.h>

// by GRID CELLS! actual width is *2 of this.
#define CANVAS_WIDTH (40 * 2)
#define CANVAS_HEIGHT 25

struct {
	HANDLE console_handle;
	CHAR_INFO grid[CANVAS_HEIGHT][CANVAS_WIDTH];
	int width;
	int height;
	COORD origin;
	COORD size;
} canvas = {
	.height = CANVAS_HEIGHT,
	.width = CANVAS_WIDTH,
	.origin = {.X = 0, .Y = 0},
	.size = {.X = CANVAS_WIDTH, .Y = CANVAS_HEIGHT},
};
void InitCanvas() {
	canvas.console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	ClearCanvas();
}
void ClearCanvas() {
	for (int i = 0; i < CANVAS_HEIGHT; i++) {
		for (int j = 0; j < CANVAS_WIDTH; j++) {
			canvas.grid[i][j].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			canvas.grid[i][j].Char.UnicodeChar = 0x00;
		}
	}
}
void PrintCanvas() {
	SMALL_RECT write_region = {
		.Left = canvas.origin.X,
		.Top = canvas.origin.Y,
		.Right = canvas.size.X,
		.Bottom = canvas.size.Y
	};
	WriteConsoleOutputW(canvas.console_handle, canvas.grid, canvas.size, canvas.origin, &write_region);
}
//public
void SetCanvasCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute) {
	if (!(0 <= x && x < CANVAS_WIDTH &&
		0 <= y && y < CANVAS_HEIGHT)) return;
	canvas.grid[y][2 * x].Attributes = attribute;
	canvas.grid[y][2 * x + 1].Attributes = attribute;

	canvas.grid[y][2 * x].Char.UnicodeChar = unicode;
	canvas.grid[y][2 * x + 1].Char.UnicodeChar = 0x0000;
}
#define EUC_KR 51949
#define CANVAS_CHAR_BUFFER_SIZE 256
#include "wcwidth.h"
//public
void CanvasPrintString(const int x, const int y, const char* str, const unsigned short attribute) {
	if (y >= CANVAS_HEIGHT) return;
	WCHAR buffer[CANVAS_CHAR_BUFFER_SIZE];
	MultiByteToWideChar(EUC_KR, MB_PRECOMPOSED, str, -1, buffer, CANVAS_CHAR_BUFFER_SIZE);

	for (int i = 0, j = x; i < CANVAS_CHAR_BUFFER_SIZE && j < CANVAS_WIDTH; i++, j++) {
		if (buffer[i] == '\0') return;
		canvas.grid[y][j].Attributes = attribute;
		canvas.grid[y][j].Char.UnicodeChar = buffer[i];

		// if character requires more than 1 width, advance while filling canvas.grid.Char with '\0'
		const int width = mk_wcwidth(buffer[i]);
		for (int i = 1; i < width; i++) {
			j++;
			if (j >= CANVAS_WIDTH) return;
			canvas.grid[y][j].Attributes = attribute;
			canvas.grid[y][j].Char.UnicodeChar = ' ';
		}
	}
}
void CanvasPrintStringAtCell(const int x, const int y, const char* str, const unsigned short attribute) {
	CanvasPrintString(x * 2, y, str, attribute);
}

#ifdef DEBUG
void FillCanvasWithRandomCells() {
	for (int i = 0; i < CANVAS_HEIGHT; i++) {
		for (int j = 0; j < CANVAS_WIDTH / 2; j++) {
			SetCanvasCell(j, i, 0x25a0, rand() % 0x0100);
		}
	}
}
void FillCanvasWithTestString() {
	char temp[] = "가나다라마바사";

	for (int i = 0; i < CANVAS_HEIGHT; i++) {
		CanvasPrintString(0, i, temp, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}
#endif // DEBUG

