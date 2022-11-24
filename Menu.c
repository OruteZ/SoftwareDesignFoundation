#include "Keyboard.h"
#include "World.h"
#include<Windows.h>
#include <stdio.h>
#include <time.h>
#include "Point.h"
#include "Screen.h"
#include "Game.h"
#define StartButtonPosX 30
#define StartButtonPosY 80
#define EndButtonPosX 60
#define EndButtonPosY 80

void Button()
{
	Point p;
	p.x = StartButtonPosX;
	p.y = StartButtonPosY;
	ScreenPrint(p.x, p.y, "Game Start");
	p.x = EndButtonPosX;
	p.y = EndButtonPosY;
	ScreenPrint(p.x, p.y, "Quit");
}

void CursorMove()
{
	Point p;
	p.x = StartButtonPosX - 5;
	p.y = StartButtonPosY;
	if (GetKeyDown('A'))
	{
		ScreenPrint(p.x, p.y, "  ");
		p.x = StartButtonPosX - 5;
		p.y = StartButtonPosY;
		ScreenPrint(p.x, p.y, "->");
	}
	else if (GetKeyDown('D'))
	{
		ScreenPrint(p.x, p.y, "  ");
		p.x = EndButtonPosX - 5;
		p.y = EndButtonPosY;
		ScreenPrint(p.x, p.y, "->");
	}
}

void GameEnd(Point p)
{
	if (p.x == EndButtonPosX - 5 && p.y == EndButtonPosY)
	{
		if (GetKeyDown(VK_RETURN))
		{
			//게임 종료
			
		}
	}
}
void GameStart(Point p)
{
	if (p.x == StartButtonPosX - 5 && p.y == StartButtonPosY)
	{
		if (GetKeyDown(VK_RETURN))
		{
			GameState = Dungeon;

		}
	}
}