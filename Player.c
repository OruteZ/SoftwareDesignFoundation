#include "Player.h"
#include "Keyboard.h"
#include "Point.h"
#include "World.h"
#include "QuadTree.h"
#include "Rect.h"
#include "Game.h"
#include "Time.h"
#include "Enemy.h"
#include "Debug.h"
#include "Particle.h"
#include "Camera.h"
#include "HeartBeat.h"
#include "ExpOrb.h"
#include "UpgradeUI.h"

//-----------------인벤토리 / 아이템 관련 인스펙터 창-----------------------
#define KINDS_OF_ITEM (2)
#define BULLET_ID (0)
#define POTION_ID (1)

const char bulletKey = 'J';
const char potionKey = 'U';

const int potionHealAmount = 10;
//--------------------------------------------------------------------------

//---------------------플레이어 스텟 관련 인스펙터 창 ----------------------
double playerBaseAttackSpeed = 1 / 1; // attack per beat
double playerBaseMoveSpeed = 8 / 1; // block per beat
int playerBaseAttackDamage = 10;

int basePlayerMaxHP = 22; //플레이어 기본 최대체력
int MaxHPUpperLinit = 44; //플레이어 최대체력 상한선
//---------------------------------------------------------------------------

//---------------------플레이어 레벨업 관련 인스펙터 창 ---------------------
#define MAX_LEVEL (5)
//각 레벨마다 레벨업을 위한 필요 경험치다.
int essentialExpToLevelUp[MAX_LEVEL] = {
	100,
	120,
	150,
	190,
	250,
};
//---------------------------------------------------------------------------

Player* player;
int score;
bool playerDeadFlag = false;

BOOL canPlayerMeleeAttack = TRUE;
bool canPlayerRangeAttack = true;

BOOL canPlayerMove = TRUE;
double playerMoveCooldown;
double playerAttackCooldown;

double basePlayerAttackDelay = 0.15f; // 3frame

int score;

int Inventory[KINDS_OF_ITEM] = { 0 };

//-------------------------------------------------------------------
void CalculatePlayerCooldown();
void PlayerMove(Point dir);
Rect CreatePlayerAttackRect(Point middle, Point direction);
void PlayerMeleeAttack();
void PlayerRangeAttack();
void CheckExpOrb(Point nowPoint);
void UpExp(int exp);
void UpScore(int baseScore);
void CheckExpOrb(Point nowPoint);
void LevelUp();
void DrinkPotion();
void UseItem(int ID);

//public :
Player* CreatePlayer(Point spawnPoint)
{
	Player* _player = (Player*)malloc(sizeof(Player));
	if (_player == NULL) exit(-1);

	score = 0;

	_player->base.entity.type = PlayerType;
	_player->base.entity.pos.x = 0;
	_player->base.entity.pos.y = 0;

	_player->attackSpeed = 10.0f;
	_player->baseDamage = 20;
	_player->hp = basePlayerMaxHP;
	_player->maxHp = basePlayerMaxHP;
	_player->moveSpeed = 12.0f;

	_player->exp = 0;
	_player->level = 0;
	_player->facing = Direction.north;

	_player->attackHeight = 1;
	_player->attackWidth = 3;

	playerDeadFlag = false;
	playerMoveCooldown = 0;
	playerAttackCooldown = 0;

	for (int i = 0; i < KINDS_OF_ITEM; i++) {
		Inventory[i] = 0;
	}

	//테스트용
	Inventory[BULLET_ID] = 100;

	return _player;

}
void UpdatePlayer() {
	if (player == NULL) return;

	if (GetKey('W')) PlayerMove(Direction.south);
	if (GetKey('A')) PlayerMove(Direction.west);
	if (GetKey('S')) PlayerMove(Direction.north);
	if (GetKey('D')) PlayerMove(Direction.east);

	if (GetKeyDown(VK_SPACE)) PlayerMeleeAttack();

	if (GetKeyDown(bulletKey)) UseItem(BULLET_ID);
	if (GetKeyDown(potionKey)) UseItem(POTION_ID);

	CalculatePlayerCooldown();

#ifdef DEBUG
	if (GetKeyDown('P')) LevelUp();
#endif
}
Point GetPlayerPos() { return player->base.entity.pos; }
void PlayerOnHit(int damage) {
	player->hp -= damage;
	if (player->hp <= 0) {
		playerDeadFlag = true;
	}

	//CameraShake();

#ifdef DEBUG
	DebugPrint("Player On Hit");
#endif
}
bool IsPlayerDead() { return playerDeadFlag; }
void ResetPlayerStatusByBPM(int BPM) {
	double BeatPerSecond = 60.0f / BPM;

	player->attackSpeed = playerBaseAttackSpeed * BeatPerSecond;
	player->baseDamage = playerBaseAttackDamage * BeatPerSecond;
	player->moveSpeed = playerBaseMoveSpeed * BeatPerSecond;
}
int GetScore() { return score; }

//private :
void CalculatePlayerCooldown() {
	basePlayerAttackDelay -= GameTime.deltaTime;
	playerMoveCooldown -= GameTime.deltaTime;

	if (basePlayerAttackDelay < 0) {
		canPlayerMeleeAttack = TRUE;
		canPlayerRangeAttack = true;
	}
	if (playerMoveCooldown < 0) canPlayerMove = TRUE;
}

void PlayerMove(Point dir) {
	if (!canPlayerMove) return;

	Point destPos = player->base.entity.pos;
	PointAdd(&destPos, &dir);

	if (GetTile(destPos) & FLAG_COLLIDE_WITH_BODY) return;
	
	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		if (PointEquals(&destPos, &e->base.entity.pos)) return;
	}

	player->base.entity.pos = destPos;
	player->facing = dir;

	ExpOrb* orb = FindOrb(destPos);
	if (orb != NULL) {
		int exp = GetExp(orb);
		UpExp(exp);
	}

	canPlayerMove = FALSE;
	playerMoveCooldown = 1 / (player->moveSpeed);
}
Rect CreatePlayerAttackRect(Point middle, Point direction) {
	Rect result;
	if (direction.x == 0) { //상하 공격 -> 가로라인
		result.x = middle.x - (player->attackWidth / 2);
		result.y = middle.y - (player->attackHeight / 2);

		result.height = player->attackHeight;
		result.width = player->attackWidth;
	}

	else { //좌우공격 -> 세로라인
		result.x = middle.x - (player->attackHeight / 2);
		result.y = middle.y - (player->attackWidth / 2);

		result.height = player->attackWidth;
		result.width = player->attackHeight;
	}

	return result;
}
void PlayerMeleeAttack() {
	if (!canPlayerMeleeAttack) return;

	Point attackPoint = player->base.entity.pos;
	PointAdd(&attackPoint, &player->facing);


	Rect attackRect = CreatePlayerAttackRect(attackPoint, player->facing);
	CreateParticle(player->facing, attackPoint, MeleeAttackParticleType, player->baseDamage);


	/* 차후 쿼드트리 사용시 변경
	Vector* hitted_enemys = QuadTreeQuery(enemiesTree, attackRect);

	int len = hitted_enemys->length;
	for (int i = 0; i < len; i++) 
	{
		Enemy* e = (Enemy*)(hitted_enemys->entities)[i];

		if (e->base.entity.type != _Player)
		{
			// m -> getDamage(); -> 임시
		}
	}

	DeleteVector(hitted_enemys);
	*/

	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		if (e == NULL) continue;
		if (isEnemyDead(e)) continue;

		if (RectContainsPoint(&attackRect, &e->base.entity.pos)) {
			if (EnemyOnHit(e, player->baseDamage)) {
				UpScore(1);
				UpExp(10);
			}
		}
	}


	playerAttackCooldown = 1 - (player->attackSpeed);

	if (playerMoveCooldown < basePlayerAttackDelay) {
		canPlayerMove = FALSE;
		playerMoveCooldown = basePlayerAttackDelay;
	}

#ifdef DEBUG
	DebugPrint("Player Attacked");
#endif
}
void UpExp(int exp) {
	player->exp += exp;
	while (player->exp > essentialExpToLevelUp[player->level]) {
		LevelUp();
	}
}
void UpScore(int baseScore) {
	score += GetBPM() * baseScore;

	if (score > 200) StartNextWorld();
}
void CheckExpOrb(Point nowPoint) {
	for (int i = 0; i < expOrbs->length; i++) {
		ExpOrb* orb = expOrbs->entities[i];
		if (orb == NULL) continue;
		if (orb->isDead) continue;

		int exp = GetExp(orb);
		UpExp(exp);
	}
}

void LevelUp() {
	//if (player->exp < essentialExpToLevelUp[player->level]) return;

	Inventory[BULLET_ID]++;

	StartUpgradeUI();

	player->exp -= essentialExpToLevelUp[player->level++];
}

//----------인벤토리 + 아이템 시스템-----------------

void UseItem(int ID) {
	if (Inventory[ID] == 0) return;
	else Inventory[ID]--;

	switch (ID) {
	case BULLET_ID: 
		PlayerRangeAttack();
		break;

	case POTION_ID: 
		DrinkPotion();
		break;

	default: break;
	}
}

void DrinkPotion() {
	player->hp += potionHealAmount;
	if (player->hp > player->maxHp) {
		player->hp = player->maxHp;
	}
}

void PlayerRangeAttack() {
	if (!canPlayerRangeAttack) return;

	CreateParticle(player->facing, player->base.entity.pos, RangeAttackParticleType, player->baseDamage);

#ifdef DEBUG
	DebugPrint("Created Range Particle");
#endif

	canPlayerRangeAttack = false;
	playerAttackCooldown = 1 - (player->attackSpeed);
	if (playerMoveCooldown < basePlayerAttackDelay) {
		canPlayerMove = FALSE;
		playerMoveCooldown = basePlayerAttackDelay;
	}
}

//--------------레벨업 시스템------------------------

void Upgrade_Potion() {
	Inventory[POTION_ID] += GetUpgradeAmount(PotionUpgradeType);
}
void Upgrade_MaxHP() {
	if (player->maxHp >= MaxHPUpperLinit) return;
	player->maxHp += GetUpgradeAmount(MaxHPUpgradeType);
}
void Upgrade_Damage() {
	player->baseDamage += GetUpgradeAmount(DamageUpgradeType);
}
void Upgrade_AtkSpeed() {
	player->attackSpeed += GetUpgradeAmount(AtkSpeedUpgradeType);
}
void Upgrade_MoveSpeed() { player->moveSpeed += GetUpgradeAmount(MoveSpeedUpgradeType);}
void Upgrade_Bullet() { Inventory[BULLET_ID] += GetUpgradeAmount(BulletUpgradeType); }

void Upgrade(int upgrade) {
	switch ((UpgradeType)upgrade) {
	case PotionUpgradeType:
		Upgrade_Potion();
		break;

	case MaxHPUpgradeType:
		Upgrade_MaxHP();
		break;

	case DamageUpgradeType:
		Upgrade_Damage();
		break;

	case AtkSpeedUpgradeType:
		Upgrade_AtkSpeed();
		break;

	case MoveSpeedUpgradeType:
		Upgrade_MoveSpeed();
		break;

	case BulletUpgradeType:
		Upgrade_Bullet();
		break;
	}
}