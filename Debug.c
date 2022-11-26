#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

#include <Windows.h>

#include "Screen.h"

// NEVER BE LESS THAN OR EQUAL TO 25
#define DEBUG_STARTING_LINE 30
#define DEBUG_MAX_LINES 20

int current_debug_line = 0;
HANDLE* screenBuffers;

void DebugInit() {
	screenBuffers = ScreenReturnBufferHandles_Unsafe();
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
	SetConsoleCursorPosition(screenBuffers[0], current_debug_coord);
	SetConsoleCursorPosition(screenBuffers[1], current_debug_coord);

	WriteFile(screenBuffers[0], buffer_line_number, strlen(buffer_line_number), NULL, NULL);
	WriteFile(screenBuffers[0], buffer, strlen(buffer), NULL, NULL);
	WriteFile(screenBuffers[1], buffer_line_number, strlen(buffer_line_number), NULL, NULL);
	WriteFile(screenBuffers[1], buffer, strlen(buffer), NULL, NULL);
}
#endif

