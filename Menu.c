#include "Keyboard.h"
#include "World.h"
#include<Windows.h>
#include <stdio.h>
#include <time.h>
#include "Point.h"
#include "Screen.h"
#include "Game.h"
#include "Debug.h"
#define StartButtonPosX (20)
#define StartButtonPosY (24)
#define EndButtonPosX (50)
#define EndButtonPosY (24)
#define StartButtonSelectionArrowPosX (StartButtonPosX - 4)
#define StartButtonSelectionArrowPosY StartButtonPosY
#define EndButtonSelectionArrowPosX (EndButtonPosX - 4)
#define EndButtonSelectionArrowPosY EndButtonPosY 

Point p;
bool CanArrowMove = true;

//--------------------------------------
typedef enum ButtonType {
	StartButton,
	EndButton,
}button;

button nowButton = StartButton;

void ChangeButton() {
	if (nowButton == StartButton) nowButton = EndButton;
	else if (nowButton == EndButton) nowButton = StartButton;
#ifdef DEBUG
	DebugPrint("%d", nowButton);
#endif
}

void UpdateMenu() {
	if (GetKeyDown('A')) ChangeButton();
	if (GetKeyDown('D')) ChangeButton();
}
//---------------------------------------


void RenderButton()
{
	
	(StartButtonPosX, StartButtonPosY, "Game Start");
	ScreenPrint(EndButtonPosX, EndButtonPosY, "Quit");
}
void RenderStartArrow()
{
	ScreenPrint(StartButtonSelectionArrowPosX, StartButtonSelectionArrowPosY, "->");
}
void RenderEndArrow()
{
	ScreenPrint(EndButtonSelectionArrowPosX, EndButtonSelectionArrowPosY, "->");
}

void RenderTitle()
{
	ScreenPrint(10, 10, " ###   ##                   #                          ##     #              ");
	ScreenPrint(10, 11, "#  #   #                   #                           #                     ");
	ScreenPrint(10, 12, "#  #   #     ##    ##    ###  # ##   ##   ###    ###   #    ##    ###    ##  ");
	ScreenPrint(10, 13, "###    #    #  #  #  #  #  #  ##    #  #  #  #  #  #   #     #    #  #  #  # ");
	ScreenPrint(10, 14, "#  #   #    #  #  #  #  #  #  #     ####  #  #  #  #   #     #    #  #  #### ");
	ScreenPrint(10, 15, "#  #   #    #  #  #  #  #  #  #     #     #  #  # ##   #     #    #  #  #    ");
	ScreenPrint(10, 16, "###   ###    ##    ##    ###  #      ##   #  #   # #  ###   ###   #  #   ### ");
	}
/*
	void StartButtonArrowMove()
	{
		p.x = StartButtonSelectionArrowPosX;
		p.y = StartButtonSelectionArrowPosY;
		ScreenPrint(StartButtonSelectionArrowPosX, StartButtonSelectionArrowPosY, "->");
	}
	void EndButtonArrowMove()
	{
		p.x = EndButtonSelectionArrowPosX;
		p.y = EndButtonSelectionArrowPosY;
		ScreenPrint(EndButtonSelectionArrowPosX, EndButtonSelectionArrowPosY, "->");
	}
	*/

void RenderButtonArrow()
{
	if (nowButton == StartButton) {
		RenderStartArrow();
#ifdef DEBUG
		DebugPrint("Start");
#endif
	}
	else if (nowButton == EndButton) {
		RenderEndArrow();
#ifdef DEBUG
		DebugPrint("END  ");
#endif
	}
}


void GameEnd()
{
	if (p.x == EndButtonSelectionArrowPosX && p.y == EndButtonSelectionArrowPosY)
	{
		if (GetKeyDown(VK_RETURN))
		{
			//게임 종료
			exit(0);
		}
	}
}
void GameStart()
{
	if (p.x == StartButtonPosX - 5 && p.y == StartButtonPosY)
	{
		if (GetKeyDown(VK_RETURN))
		{
			GameState = Dungeon;

		}
	}
}

void RenderMenu() {
	RenderTitle();
	RenderButton();
	RenderButtonArrow();
}