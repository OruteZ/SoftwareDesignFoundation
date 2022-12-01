#pragma once

#ifdef DEBUG
#include<Windows.h>
HANDLE ScreenReturnBufferHandle_Unsafe();
#endif

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();

// ��ũ���� ��(���簢��, width = 2, height = 1)�� �����Ѵ�.
// �β� 2�� ����ϴ� ���簢�� ó�� ���̴� ���� (��: ��) �� ����Ҷ� ����Ѵ�.
// �� �Լ��� x * 2 �� �ϹǷ� �̸� x ��ǥ�� �ø��� �ʵ��� �Ѵ�.
void SetScreenCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute);

// ��ǥ�� �������� ���ڿ��� ����Ѵ�.
// attribute�� ���� ������. 
// ���� ������ https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes ����.
void ScreenPrintColor(const int x, const int y, const char* str, const unsigned short attribute);

// ������� �� ��. ScreenPrintColor() ����� �����Ѵ�.
void ScreenPrint(const int x, const int y, const char* str);

// ���� ������ https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes ����.
void SetColor(unsigned short color);

#ifdef DEBUG
#include <Windows.h>
//void FillCanvasWithRandomCells();
//void FillCanvasWithTestString();
#endif // DEBUG

