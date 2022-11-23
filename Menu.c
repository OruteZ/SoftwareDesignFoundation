#include "Keyboard.h"
#include "World.h"
#include <stdio.h>
#include <time.h>

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
COORD GetCurrentCursorPos()
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

void Button()
{
	COORD curPos = GetCurrentCursorPos();
	SetCurrentCursorPos(15, 15);
	printf("게임 시작");
	SetCurrentCursorPos(25, 15);
	printf("종료"); 
}

void CursorMove()
{
	COORD curPos = GetCurrentCursorPos();
	if (GetKeyDown("A"))
	{
		printf(" ");
		SetCurrentCursorPos(14, 15);
		printf("->");
	}
	else if (GetKeyDown("D"))
	{
		printf(" ");
		SetCurrentCursorPos(24, 15);
		printf("->");
	}
}