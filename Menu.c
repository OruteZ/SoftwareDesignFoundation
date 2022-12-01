#include "Keyboard.h"
#include "World.h"
#include<Windows.h>
#include <stdio.h>
#include <time.h>
#include "Point.h"
#include "Screen.h"
#include "Game.h"
#include "Debug.h"

//MainMenu Keys
#define StartButtonPosX (20)
#define StartButtonPosY (24)
#define EndButtonPosX (50)
#define EndButtonPosY (24)
#define StartButtonSelectionArrowPosX (StartButtonPosX - 4)
#define StartButtonSelectionArrowPosY StartButtonPosY
#define EndButtonSelectionArrowPosX (EndButtonPosX - 4)
#define EndButtonSelectionArrowPosY EndButtonPosY 

//GaimOverMenu Keys
#define GoToMainButtonPosX (20)
#define GoToMainButtonPosY (24)
#define GameOverEndButtonPosX (50)
#define GameOverEndButtonPosY (24)
#define GoToMainButtonSelectionArrowPosX (GoToMainButtonPosX - 4)
#define GoToMainButtonSelectionArrowPosY GoToMainButtonPosY
#define GameOverEndButtonSelectionArrowPosX (GameOverEndButtonPosX - 4)
#define GameOverEndButtonSelectionArrowPosY GameOverEndButtonPosY 

enum MenuType {
	Main,
	GameOver,
} menuState;

typedef enum ButtonType {
	Main_StartButton,
	Main_QuitButton,

	GameOver_RetryMainButton,
	GameOver_QuitButton,
}button;

button nowButton = Main_StartButton;

void ChangeButton_ToLeft() {
	if		(nowButton == Main_QuitButton)
		nowButton = Main_StartButton;

	else if (nowButton == GameOver_QuitButton)
		nowButton = GameOver_RetryMainButton;
}

void ChangeButton_ToRight() {
	if (nowButton == Main_StartButton)
		nowButton = Main_QuitButton;

	else if (nowButton == GameOver_RetryMainButton)
		nowButton = GameOver_QuitButton;
}

void SelectButton() {
	switch (nowButton) {
	case Main_StartButton:
		StartNextWorld();
		GameState = Dungeon;
		break;
	case Main_QuitButton:
	case GameOver_QuitButton:
		GameState = Exiting;
		break;
	case GameOver_RetryMainButton:
		GameState = Menu;
		menuState = Main;
		nowButton = Main_StartButton;
		break;
	default:
		break;
	}
}

void UpdateMenu() {
	if (GetKeyDown('A')) ChangeButton_ToLeft();
	if (GetKeyDown('D')) ChangeButton_ToRight();
	if (GetKeyDown(VK_SPACE)) SelectButton();
}

//MainMenu
void RenderMainButton()
{
	ScreenPrint(StartButtonPosX, StartButtonPosY, "Game Start");
	ScreenPrint(EndButtonPosX, EndButtonPosY, "Quit");
}
void RenderMainStartArrow()
{
	ScreenPrint(StartButtonSelectionArrowPosX, StartButtonSelectionArrowPosY, "->");
}
void RenderMainQuitArrow()
{
	ScreenPrint(EndButtonSelectionArrowPosX, EndButtonSelectionArrowPosY, "->");
}
void RenderMainTitle()
{
	ScreenPrintColor(10, 10, "###   ##                   #                          ##     #               ", FOREGROUND_RED);
	ScreenPrintColor(10, 11, "#  #   #                   #                           #                     ", FOREGROUND_RED);
	ScreenPrintColor(10, 12, "#  #   #     ##    ##    ###  # ##   ##   ###    ###   #    ##    ###    ##  ", FOREGROUND_RED);
	ScreenPrintColor(10, 13, "###    #    #  #  #  #  #  #  ##    #  #  #  #  #  #   #     #    #  #  #  # ", FOREGROUND_RED);
	ScreenPrintColor(10, 14, "#  #   #    #  #  #  #  #  #  #     ####  #  #  #  #   #     #    #  #  #### ", FOREGROUND_RED);
	ScreenPrintColor(10, 15, "#  #   #    #  #  #  #  #  #  #     #     #  #  # ##   #     #    #  #  #    ", FOREGROUND_RED);
	ScreenPrintColor(10, 16, "###   ###    ##    ##    ###  #      ##   #  #   # #  ###   ###   #  #   ### ", FOREGROUND_RED);
}

//GameOvers
void RenderGameOverButton() {
	ScreenPrint(GoToMainButtonPosX, GoToMainButtonPosY, "Go to main menu");
	ScreenPrint(GameOverEndButtonPosX, GameOverEndButtonPosY, "Quit");
}
void RenderRetryArrow() {
	ScreenPrint(GoToMainButtonSelectionArrowPosX, GoToMainButtonSelectionArrowPosY, "->");

}
void RenderGameOverEndArrow() {
	ScreenPrint(GameOverEndButtonSelectionArrowPosX, GameOverEndButtonSelectionArrowPosY, "->");
}
void RenderGameOver() {}

void RenderButtonArrow()
{
	if (nowButton == Main_StartButton) RenderMainStartArrow();
	else if (nowButton == Main_QuitButton) RenderMainQuitArrow();
	else if (nowButton == GameOver_RetryMainButton) RenderRetryArrow();
	else if (nowButton == GameOver_QuitButton) RenderGameOverEndArrow();
}

void RenderMenu() {
	if (menuState == Main) {
		RenderMainTitle();
		RenderMainButton();
	}
	else if (menuState == GameOver) {
		RenderGameOver();
		RenderGameOverButton();
	}
	RenderButtonArrow();
}

void StartMainMenu() {
	menuState = Main;
	nowButton = Main_StartButton;
}

void StartGameOverMenu() {
	menuState = GameOver;
	nowButton = GameOver_RetryMainButton;
}