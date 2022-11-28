#include "World.h"
#include "Screen.h"
#include "Game.h"
#include "Player.h"
#include "Debug.h"
#include "HeartBeat.h"
#define PlayerHpInfoPosX (10)
#define PlayerHpInfoPosY  (5)

#define PlayerAttackDamageInfoPosX (10)
#define PlayerAttackDamageInfoPosY (10)

#define ExpInfoPosX (5)
#define ExpInfoPosY (15)

#define LevelInfoPosX (15)
#define LevelInfoPosY (15)

#define BPMInfoPosX (5)
#define BPMInfoPosY (20)

#define ComboInfoPosX (15)
#define ComboInfoPoxY (20)

#define ScoreInfoPosX (10)
#define ScoreInfoPosY (30)

void InfoPrint(int x, int y, char* string, int value)
{
	ScreenPrint(x, y, string);
	ScreenPrint(x + strlen(string), y, value);
}
void PlayerStateInfo()
{
	InfoPrint(PlayerHpInfoPosX, PlayerHpInfoPosY, "HP : ", player->hp);
	InfoPrint(PlayerAttackDamageInfoPosX, PlayerAttackDamageInfoPosY, "Power : ", player->baseDamage);
	InfoPrint(ExpInfoPosX, ExpInfoPosY, "Exp : ", player->exp);
	InfoPrint(LevelInfoPosX, LevelInfoPosY, "Level : ", player->level);
}
void HeartBeatInfo()
{
	InfoPrint(BPMInfoPosX, BPMInfoPosY, "BPM : ", GetBPM());
	InfoPrint(ComboInfoPosX, ComboInfoPoxY, "Combo : ", GetCombo());
}
void ScoreStateInfo()
{
	//Score는 game에 전역선언, EnemyOnDeath 에서 10씩 증가시키도록 설정
	InfoPrint(ScoreInfoPosX, ScoreInfoPosY, "Score : ", score);
}
void UpdateUI()
{
	PlayerStateInfo();
	HeartBeatInfo();
	ScoreStateInfo();
}