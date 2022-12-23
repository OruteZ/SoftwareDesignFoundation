#include "UpgradeUI.h"
#include "Game.h"
#include "Time.h"
#include "Screen.h"
#include "Keyboard.h"

#include <stdlib.h>
#include <string.h>

#define BUTTON_WIDTH (11)
#define BUTTON_HEIGHT (25)

const int VerticalLineUnicode = 0x2502; //⏐
const int HorizontalLineUnicode = 0x2501; //⏤

const int VertexUnicode1 = 0x2511; //⏋
const int VertexUnicode2 = 0x2519; //⏌
const int VertexUnicode3 = 0x2515; //⎿
const int VertexUnicode4 = 0x250D; //⎾

int Upgrades[3] = { 0, };
char UpgradeText[NUMBER_OF_UPGARDES][18] = {
	"Potion",
	"MaxHP",
	"Damage",
	"Attack Speed",
	"Move Speed",
	"Bullet",
};


int UpgradeAmount[NUMBER_OF_UPGARDES] = {
	1, //Potion
	12, //MaxHp, 무조건 2의 배수
	5, //Damage
	10, // ATK Speed
	5, // Move Speed
	5, // Bullet
};

int currentCursor = 2;


int randInt(int start, int end) {
	int length = end - start + 1;

	int result = (rand() % length) + start;
	return result;
}

//3개의 업그레이드를 골라서 반환합니다.
void SelectRandomUpgrade() {
	int number = -1;
	bool isAlreadySelected;
	Upgrades[0] = Upgrades[1] = Upgrades[2] = -1;
	for (int i = 0; i < 3; i++) {

selectUpgrade:
		number = rand() % NUMBER_OF_UPGARDES;
		isAlreadySelected = false;
		for (int j = 0; j < i; j++) {
			if (Upgrades[i] != number) continue;

			isAlreadySelected = true;
			break;
		}
		if (isAlreadySelected)
			goto selectUpgrade;
		
		Upgrades[i] = number;
	}
}

void DrawButtonFrame(int number) {
	int color;
	if (number == currentCursor) color = FOREGROUND_RED | FOREGROUND_GREEN;
	else color = 15;

	//세로선
	for (int y = 1; y < BUTTON_HEIGHT - 1; y++) {
		SetScreenCell((number - 1) * BUTTON_WIDTH, y, VerticalLineUnicode, color);
		SetScreenCell(number * BUTTON_WIDTH - 1, y, VerticalLineUnicode, color);
	}

	//가로선
	for (int x = (number - 1) * BUTTON_WIDTH + 1; x < number * BUTTON_WIDTH - 1; x++) {
		SetScreenCell(x, 0, HorizontalLineUnicode, color);
		SetScreenCell(x, BUTTON_HEIGHT - 1, HorizontalLineUnicode, color);
	}

	SetScreenCell((number - 1) * BUTTON_WIDTH, 0, VertexUnicode4, color);
	SetScreenCell((number - 1) * BUTTON_WIDTH, BUTTON_HEIGHT - 1, VertexUnicode3, color);
	SetScreenCell(number * BUTTON_WIDTH - 1, BUTTON_HEIGHT - 1, VertexUnicode2, color);
	SetScreenCell(number * BUTTON_WIDTH - 1, 0, VertexUnicode1, color);
}

void DrawUpgradeText(int number) {
	int color;
	if (number == currentCursor) color = FOREGROUND_RED | FOREGROUND_GREEN;
	else color = 15;

	int middleX = ((2 * number - 1) * BUTTON_WIDTH);
	int middleY = BUTTON_HEIGHT / 2;

	int upgradeType = Upgrades[number - 1];

	int stringLength = strlen(UpgradeText[upgradeType]);
	int amountLength = 2;

	int stringStartPoint = middleX - (stringLength) / 2;
	int amountStartPoint = middleX - (amountLength) / 2;

	char* stringBuffer = UpgradeText[upgradeType];
	char* amountBuffer = (char*)malloc(sizeof(char) * 10);
	itoa(UpgradeAmount[upgradeType], amountBuffer, 10);

	ScreenPrintColor(stringStartPoint, middleY, stringBuffer, color);

	ScreenPrintColor(amountStartPoint, middleY + 1, "+", color);
	ScreenPrintColor(amountStartPoint + 1, middleY + 1, amountBuffer, color);
	free(amountBuffer);
}

void AcceptUpgrade() {
	Upgrade((UpgradeType)Upgrades[currentCursor - 1]);
#ifdef DEBUG
	DebugPrint("%d", Upgrades[currentCursor - 1]);
#endif // DEBUG

}

void StartUpgradeUI() {
#ifdef DEBUG
	DebugPrint("Start Upgrade UI Call");
#endif

	GameState = UpgradeMenu;

	srand((unsigned int)(Time.time * 10));

	Upgrades[0] = -1;
	Upgrades[1] = -1;
	Upgrades[2] = -1;
	SelectRandomUpgrade();

	currentCursor = 1;
}

void UpdateUpgradeUI() {
	if (GetKeyDown('A')) currentCursor--;
	if (GetKeyDown('D')) currentCursor++;

	if (currentCursor < 1) currentCursor = 1;
	if (currentCursor > 3) currentCursor = 3;

	if (GetKeyDown(VK_RETURN)) {
		AcceptUpgrade();
		ExitUpgradeUI();
	}
}

void RenderUpgradeUI() {
	for (int i = 1; i <= 3; i++) {
		DrawButtonFrame(i);
		DrawUpgradeText(i);
	}
	ScreenPrintColor(20, 20, "Press Enter to select upgrade", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void ExitUpgradeUI() {
	GameState = Dungeon;
}

int GetUpgradeAmount(UpgradeType upgrade) {
	return UpgradeAmount[(int)upgrade];
}
