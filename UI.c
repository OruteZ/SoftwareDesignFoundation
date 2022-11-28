#include "World.h"
#include "Screen.h"
#include "Game.h"
#include "Player.h"
#include "Debug.h"
#define PlayerHpInfoPosX (5)
#define PlayerHpInfoPosY  (5)
#define ScoreInfoPosX (5)
#define ScoreInfoPosY (10)
void InfoPrint(int x, int y, char* string, int value)
{
	ScreenPrint(x, y, string);
	ScreenPrint(x + strlen(string), y, value);
}
void PlayerStateInfo()
{
	InfoPrint(PlayerHpInfoPosX, PlayerHpInfoPosY, "HP : ", player->hp);
}
void ScoreStateInfo()
{
	//Score�� game�� ��������, EnemyOnDeath ���� 10�� ������Ű���� ����
	InfoPrint(ScoreInfoPosX, ScoreInfoPosY, "Score : ", score);
}
