#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

#include <Windows.h>

#include "Screen.h"

// NEVER BE LESS THAN OR EQUAL TO 25
#define DEBUG_STARTING_LINE 30
#define DEBUG_MAX_LINES 20

int current_debug_line = 0;
HANDLE screenBuffer;

void DebugInit() {
	screenBuffer = ScreenReturnBufferHandle_Unsafe();
}
void DebugPrint(const char* format , ...) {
	va_list args;
	va_start(args, format);

	char buffer_line_number[9];
	sprintf_s(buffer_line_number, sizeof(buffer_line_number), "%05d: ", current_debug_line);
	char buffer[256];
	vsprintf_s(buffer, sizeof(buffer), format, args);

	va_end(args);
	COORD current_debug_coord = { .X = 0, .Y = DEBUG_STARTING_LINE + current_debug_line++ % DEBUG_MAX_LINES };
	ScreenPrint(current_debug_coord.X, current_debug_coord.Y, buffer_line_number);
	ScreenPrint(current_debug_coord.X + 7, current_debug_coord.Y, buffer);
	//SetConsoleCursorPosition(screenBuffer, current_debug_coord);

	//WriteFile(screenBuffer, buffer_line_number, strlen(buffer_line_number), NULL, NULL);
	//WriteFile(screenBuffer, buffer, strlen(buffer), NULL, NULL);
}
#endif

