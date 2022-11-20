#pragma once

#ifdef DEBUG
#include<Windows.h>
HANDLE* ScreenReturnBufferHandles_Unsafe();
#endif

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char* string);


//FOREGROUND_RED
//FOREGROUND_GREEN
//FOREGROUND_BLUE
//FOREGROUND_INTENSITY
//BACKGROUND_RED
//BACKGROUND_GREEN
//BACKGROUND_BLUE
//BACKGROUND_INTENSITY

// example: cyan background, yellow text!
// BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
void SetColor(unsigned short color);