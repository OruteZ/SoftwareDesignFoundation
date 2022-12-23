#include "Keyboard.h"
#include "World.h"
#include<Windows.h>
#include <stdio.h>
#include <time.h>
#include "Point.h"
#include "Screen.h"
#include "Game.h"
#include "Debug.h"
#include "Player.h"
#include "Menu.h"

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
#define GAMEOVER_RETRY_BUTTON_X (20)
#define GAMEOVER_RETRY_BUTTON_Y (24)
#define GAMEOVER_QUIT_BUTTON_X (50)
#define GAMEOVER_QUIT_BUTTON_Y (24)
#define GAMEOVER_RETRY_ARROW_POS_X (GAMEOVER_RETRY_BUTTON_X - 4)
#define GAMEOVER_RETRY_ARROW_POS_Y GAMEOVER_RETRY_BUTTON_Y
#define GAMEOVER_QUIT_ARROW_POS_X (GAMEOVER_QUIT_BUTTON_X - 4)
#define GAMEOVER_QUIT_ARROW_POS_Y GAMEOVER_QUIT_BUTTON_Y 

//GameClearMenu Keys
#define GAMECLEAR_RETRY_BUTTON_X (20)
#define GAMECLEAR_RETRY_BUTTON_Y (24)
#define GAMECLEAR_QUIT_BUTTON_X (50)
#define GAMECLEAR_QUIT_BUTTON_Y (24)
#define GAMECLEAR_RETRY_ARROW_POS_X (GAMECLEAR_RETRY_BUTTON_X - 4)
#define GAMECLEAR_RETRY_ARROW_POS_Y GAMECLEAR_RETRY_BUTTON_Y
#define GAMECLEAR_QUIT_ARROW_POS_X (GAMECLEAR_QUIT_BUTTON_X - 4)
#define GAMECLEAR_QUIT_ARROW_POS_Y GAMECLEAR_QUIT_BUTTON_Y 

enum MenuType {
	Main,
	GameOver,
	GameClear
} menuState;

typedef enum ButtonType {
	Main_StartButton,
	Main_QuitButton,

	GameOver_RetryMainButton,
	GameOver_QuitButton,

	GameClear_RetryMainButton,
	GameClear_QuitButton,
}button;

button nowButton = Main_StartButton;

int clearScore = 0;

void ChangeButton_ToLeft() {
	if (nowButton == Main_QuitButton)
		nowButton = Main_StartButton;

	else if (nowButton == GameOver_QuitButton)
		nowButton = GameOver_RetryMainButton;

	else if (nowButton == GameClear_QuitButton)
		nowButton = GameClear_RetryMainButton;
}
void ChangeButton_ToRight() {
	if (nowButton == Main_StartButton)
		nowButton = Main_QuitButton;

	else if (nowButton == GameOver_RetryMainButton)
		nowButton = GameOver_QuitButton;

	else if (nowButton == GameClear_RetryMainButton)
		nowButton = GameClear_QuitButton;
}

void SelectButton() {
	switch (nowButton) {
	case Main_StartButton:
		StartNextWorld();
		GameState = Dungeon;
		break;
	case GameOver_RetryMainButton:
	case GameClear_RetryMainButton:
		GameState = Menu;
		menuState = Main;
		nowButton = Main_StartButton;
		break;

	//--------------------------------------
	case Main_QuitButton:
	case GameOver_QuitButton:
	case GameClear_QuitButton:
		GameState = Exiting;
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
	ScreenPrint(GAMEOVER_RETRY_BUTTON_X, GAMEOVER_RETRY_BUTTON_Y, "RETRY");
	ScreenPrint(GAMEOVER_QUIT_BUTTON_X, GAMEOVER_QUIT_BUTTON_Y, "QUIT");
}
void RenderGameOverRetryArrow() {
	ScreenPrint(GAMEOVER_RETRY_ARROW_POS_X, GAMEOVER_RETRY_ARROW_POS_Y, "->");
}
void RenderGameOverEndArrow() {
	ScreenPrint(GAMEOVER_QUIT_ARROW_POS_X, GAMEOVER_QUIT_ARROW_POS_Y, "->");
}
void RenderGameOver() {}

//GAMECLEAR
void RenderGameClearButton() {
	ScreenPrintColor(GAMECLEAR_RETRY_BUTTON_X, GAMECLEAR_RETRY_BUTTON_Y, "MAIN MENU", 15);
	ScreenPrintColor(GAMECLEAR_QUIT_BUTTON_X, GAMECLEAR_QUIT_BUTTON_Y, "QUIT", 15);
}
void RenderGameClearRetryArrow() {
	ScreenPrintColor(GAMECLEAR_RETRY_ARROW_POS_X, GAMECLEAR_RETRY_ARROW_POS_Y, "->", 15);
}
void RenderGameClearEndArrow() {
	ScreenPrint(GAMECLEAR_QUIT_ARROW_POS_X, GAMECLEAR_QUIT_ARROW_POS_Y, "->");
}
void RenderGameClear() {
	char arr[20];
	sprintf(arr, "%d", clearScore);

	ScreenPrintColor(20, 12, "Game Clear with Score : ", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	ScreenPrintColor(45, 12, arr, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void RenderButtonArrow()
{
	if (nowButton == Main_StartButton) RenderMainStartArrow();
	else if (nowButton == Main_QuitButton) RenderMainQuitArrow();

	else if (nowButton == GameOver_RetryMainButton) RenderGameOverRetryArrow();
	else if (nowButton == GameOver_QuitButton) RenderGameOverEndArrow();

	else if (nowButton == GameClear_RetryMainButton) RenderGameClearRetryArrow();
	else if (nowButton == GameClear_QuitButton) RenderGameClearEndArrow();
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
	else if (menuState == GameClear) {
		RenderGameClear();
		RenderGameClearButton();
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

void StartGameClearMenu() {
	menuState = GameClear;
	nowButton = GameClear_RetryMainButton;
}

void SetClearScore(int score) {
	clearScore = score;
}
