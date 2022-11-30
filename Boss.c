#include "Boss.h"

#include "Rect.h"


//----------변경 변수---------------
int bossMaxHP = 10000;
int bossBaseDamage = 10;

double bossOnHitEffectDuration = 0.1f;
//------------------------------------

bool isBossExist = false;

int bossNowHP;

int bossWidth;
int bossHeight;

Rect BossRect;

double bossOnHitCooldown = 0;

//public:
int GetBossHP() { return bossNowHP; }
Rect GetBossRect() { return BossRect; }
bool BossOnHit(int damage) {
	bossNowHP -= damage;
	bossOnHitCooldown = bossOnHitEffectDuration;
	return (bossNowHP <= 0);
}
bool BossHitEffect() {
	return bossOnHitCooldown > 0;
}
bool isBossDead() {
	return bossNowHP < 0;
}
void BossSpawn(Point p) {
	bossNowHP = bossMaxHP;

	BossRect.x = p.x - (bossWidth / 2);
	BossRect.y = p.y - (bossHeight / 2);
	BossRect.height = bossHeight;
	BossRect.width = bossWidth;

	isBossExist = true;
}
void BossUpdate() {}

//private:
