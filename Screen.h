#pragma once

#define SCREEN_WIDTH (40 * 2)
#define SCREEN_HEIGHT 25
#ifdef DEBUG
#define DEBUG_SCREEN_HEIGHT 51
#endif // DEBUG


void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();

// 스크린의 셀(정사각형, width = 2, height = 1)을 설정한다.
// 두께 2를 사용하는 정사각형 처럼 보이는 문자 (예: ■) 를 출력할때 사용한다.
// 이 함수가 x * 2 를 하므로 미리 x 좌표를 늘리지 않도록 한다.
void SetScreenCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute);

// 좌표를 시작으로 문자열을 출력한다.
// attribute는 색상 정보다. 
// 색상 정보는 https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes 참고.
void ScreenPrintColor(const int x, const int y, const char* str, const unsigned short attribute);

// 사용하지 말 것. ScreenPrintColor() 사용을 권장한다.
void ScreenPrint(const int x, const int y, const char* str);

// 색상 정보는 https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes 참고.
void SetColor(unsigned short color);

#ifdef DEBUG
#include <Windows.h>
HANDLE ScreenReturnBufferHandle_Unsafe();
//void FillCanvasWithRandomCells();
//void FillCanvasWithTestString();
#endif // DEBUG

