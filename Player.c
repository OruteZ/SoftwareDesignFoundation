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
#include "Boss.h"

//-----------------�κ��丮 / ������ ���� �ν����� â-----------------------
const char bulletKey = 'K';
const char potionKey = 'L';

const int potionHealAmount = 8;
//--------------------------------------------------------------------------

//---------------------�÷��̾� ���� ���� �ν����� â ----------------------
double playerBaseAttackSpeed = 1 / 1; // attack per second
double playerBaseMoveSpeed = 8 / 1; // block per beat
int playerBaseAttackDamage = 15;

int basePlayerMaxHP = 22; //�÷��̾� �⺻ �ִ�ü��
int MaxHPUpperLinit = 44; //�÷��̾� �ִ�ü�� ���Ѽ�
//---------------------------------------------------------------------------

//---------------------�÷��̾� ������ ���� �ν����� â ---------------------
#define MAX_LEVEL (5)
//�� �������� �������� ���� �ʿ� ����ġ��.
int essentialExpToLevelUp[MAX_LEVEL] = {
	30,
	70,
	110,
	160,
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

	//�׽�Ʈ��
	Inventory[BULLET_ID] = 0;

	return _player;

}
void UpdatePlayer() {
	if (player == NULL) return;

	if (GetKey('W')) PlayerMove(Direction.south);
	if (GetKey('A')) PlayerMove(Direction.west);
	if (GetKey('S')) PlayerMove(Direction.north);
	if (GetKey('D')) PlayerMove(Direction.east);

	if (GetKeyDown('J')) PlayerMeleeAttack();

	if (GetKeyDown(bulletKey)) UseItem(BULLET_ID);
	if (GetKeyDown(potionKey)) UseItem(POTION_ID);

	CalculatePlayerCooldown();

#ifdef DEBUG
	if (GetKeyDown('P')) LevelUp();
	if (GetKeyDown('V')) StartNextWorld();
	if (GetKeyDown('M')) {
		DebugPrint("%d %d", player->base.entity.pos.x, player->base.entity.pos.y);
	}
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
	//DebugPrint("Player On Hit");
#endif
}
bool IsPlayerDead() { return playerDeadFlag; }
void ResetPlayerStatusByBPM(int BPM) {
	player->attackSpeed = playerBaseAttackSpeed * (BPM / 90);
	player->baseDamage = playerBaseAttackDamage * (BPM / 90);
	player->moveSpeed = playerBaseMoveSpeed * (BPM / 90);
}
int GetScore() { return score; }
int GetPlayerItemCount(int id) {
	return Inventory[id];
}

//private :
void CalculatePlayerCooldown() {
	playerAttackCooldown -= GameTime.deltaTime;
	playerMoveCooldown -= GameTime.deltaTime;

	if (playerAttackCooldown < 0) {
		canPlayerMeleeAttack = TRUE;
		canPlayerRangeAttack = true;
	}
	if (playerMoveCooldown < 0) canPlayerMove = TRUE;
}
void PlayerMove(Point dir) {
	player->facing = dir;
	if (!canPlayerMove) return;

	Point destPos = player->base.entity.pos;
	PointAdd(&destPos, &dir);

	if (GetTile(destPos) & FLAG_COLLIDE_WITH_BODY) return;

	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		if (PointEquals(&destPos, &e->base.entity.pos)) return;
	}

	Rect bossRect = GetBossRect();
	if (RectContainsPoint(&bossRect, &destPos)) return;

	player->base.entity.pos = destPos;

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
	if (direction.x == 0) { //���� ���� -> ���ζ���
		result.x = middle.x - (player->attackWidth / 2);

		//�Ʒ��� ���� ��츸 height��ŭ ����
		result.y = middle.y;
		if (direction.y == -1) result.y -= (player->attackHeight / 2);

		result.height = player->attackHeight;
		result.width = player->attackWidth;
	}

	else { //�¿���� -> ���ζ���
		result.x = middle.x;
		if (direction.x == -1) result.x -= (player->attackHeight / 2);
		result.y = middle.y - (player->attackWidth / 2);

		result.height = player->attackWidth;
		result.width = player->attackHeight;
	}

	return result;
}
void PlayerMeleeAttack() {
	if (playerAttackCooldown > 0) return;

	Point attackPoint = player->base.entity.pos;
	PointAdd(&attackPoint, &player->facing);


	Rect attackRect = CreatePlayerAttackRect(attackPoint, player->facing);
	CreateParticle(player->facing, attackPoint, MeleeAttackParticleType, player->baseDamage);


	/* ���� ����Ʈ�� ���� ����
	Vector* hitted_enemys = QuadTreeQuery(enemiesTree, attackRect);

	int len = hitted_enemys->length;
	for (int i = 0; i < len; i++)
	{
		Enemy* e = (Enemy*)(hitted_enemys->entities)[i];

		if (e->base.entity.type != _Player)
		{
			// m -> getDamage(); -> �ӽ�
		}
	}

	DeleteVector(hitted_enemys);
	*/

	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		if (e == NULL) continue;
		if (IsEnemyDead(e)) continue;

		if (RectContainsPoint(&attackRect, &e->base.entity.pos)) {
			if (EnemyOnHit(e, player->baseDamage)) {
				UpScore(GetBPM());
				UpExp(10);
			}
		}
	}
	if (IsBossExist()) {
		Rect bossRect = GetBossRect();
		if (RectIsIntersectingRect(&attackRect, &bossRect)) {
			BossOnHit(player->baseDamage);
		}
#ifdef DEBUG
		else {
			DebugPrint("boss is not hitted");
		}
#endif // DEBUG

	}


	playerAttackCooldown = 1 / (player->attackSpeed);

	if (playerMoveCooldown < basePlayerAttackDelay) {
		canPlayerMove = FALSE;
		playerMoveCooldown = basePlayerAttackDelay;
	}

#ifdef DEBUG
	//DebugPrint("Player Attacked");
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
	/*if (player->exp < essentialExpToLevelUp[player->level] ||
		player->level >= MAX_LEVEL) return;*/

	Inventory[BULLET_ID]++;

	StartUpgradeUI();

	player->exp -= essentialExpToLevelUp[player->level++];
	if (player->exp < 0) player->exp = 0;
}

//----------�κ��丮 + ������ �ý���-----------------

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

	Point point_infront = player->base.entity.pos;
	PointAdd(&point_infront, &player->facing);
	CreateParticle(player->facing, point_infront, RangeAttackParticleType, player->baseDamage * 2);

#ifdef DEBUG
	DebugPrint("Created Range Particle");
#endif
}

//--------------������ �ý���------------------------

void Upgrade_Potion() {
	Inventory[POTION_ID] += GetUpgradeAmount(PotionUpgradeType);
}
void Upgrade_MaxHP() {
	if (player->maxHp >= MaxHPUpperLinit) return;

	player->maxHp += GetUpgradeAmount(MaxHPUpgradeType);
	player->hp += GetUpgradeAmount(MaxHPUpgradeType);
}
void Upgrade_Damage() {
	playerBaseAttackDamage += GetUpgradeAmount(DamageUpgradeType);
	ResetPlayerStatusByBPM(GetBPM());
}
void Upgrade_AtkSpeed() {
	playerBaseAttackSpeed += GetUpgradeAmount(AtkSpeedUpgradeType);
	ResetPlayerStatusByBPM(GetBPM());
}
void Upgrade_MoveSpeed() {
	playerBaseMoveSpeed += GetUpgradeAmount(MoveSpeedUpgradeType);
	ResetPlayerStatusByBPM(GetBPM());
}
void Upgrade_Bullet() {
	Inventory[BULLET_ID] += GetUpgradeAmount(BulletUpgradeType);
}

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