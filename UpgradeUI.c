#include "UpgradeUI.h"
#include "Game.h"
#include "Time.h"
#include "Screen.h"

#include <stdlib.h>

#define BUTTON_WIDTH (11)
#define BUTTON_HEIGHT (25)

const int VerticalLineUnicode = 0x2502; //⏐
const int HorizontalLineUnicode = 0x2501; //⏤

const int VertexUnicode1 = 0x2511; //⏋
const int VertexUnicode2 = 0x2519; //⏌
const int VertexUnicode3 = 0x2515; //⎿
const int VertexUnicode4 = 0x250D; //⎾

int Upgrades[3] = { 0, };
char UpgradeText[NUMBER_OF_UPGARDES][50] = {
	"포션을 추가로 하나 얻습니다.",
	"최대 HP가 증가합니다.",
	"가하는 데미지가 증가합니다.",
	"공격속도가 증가합니다.",
	"이동속도가 증가합니다.",
	"추가 총알을 제공받습니다.",
};

//3개의 업그레이드를 골라서 반환합니다.
void SelectRandomUpgrade() {
	int number = -1;
	bool isAlreadySelected;
	for (int i = 0; i < 3; i++) {
		//고른적 없는 번호가 나올때까지 반복
		do {
			number = rand() % NUMBER_OF_UPGARDES;
			isAlreadySelected = false;
			for (int j = 0; j < i; j++) isAlreadySelected = (Upgrades[j] == number);
		} while (isAlreadySelected);
		
		Upgrades[i] = number;
	}
}

void DrawButtonFrame(int number) {
	//세로선
	for (int y = 1; y < BUTTON_HEIGHT - 1; y++) {
		SetScreenCell((number - 1) * BUTTON_WIDTH, y, VerticalLineUnicode, 15);
		SetScreenCell(number * BUTTON_WIDTH - 1, y, VerticalLineUnicode, 15);
	}

	//가로선
	for (int x = (number - 1) * BUTTON_WIDTH + 1; x < number * BUTTON_WIDTH - 1; x++) {
		SetScreenCell(x, 0, HorizontalLineUnicode, 15);
		SetScreenCell(x, BUTTON_HEIGHT - 1, HorizontalLineUnicode, 15);
	}

	SetScreenCell((number - 1) * BUTTON_WIDTH, 0, VertexUnicode4, 15);
	SetScreenCell((number - 1) * BUTTON_WIDTH, BUTTON_HEIGHT - 1, VertexUnicode3, 15);
	SetScreenCell(number * BUTTON_WIDTH - 1, BUTTON_HEIGHT - 1, VertexUnicode2, 15);
	SetScreenCell(number * BUTTON_WIDTH - 1, 0, VertexUnicode1, 15);
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
}

void UpdateUpgradeUI() {
	
}

void RenderUpgradeUI() {
	for (int i = 1; i <= 3; i++) 
		DrawButtonFrame(i);
}

void ExitUpgradeUI() {

}