#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"
#include "Point.h"
#include "Time.h"

#include "Entity.h"
#include "Enemy.h"

#include "Player.h"
#include "Debug.h"

#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"

#include "HeartBeat.h"

bool isEnemyDead(Enemy* enemy);
bool canEnemyMove(Enemy* enemy);
bool isEnemy(Entity* entity);
bool canEnemyAttack(Enemy* enemy);

void LookAt(Enemy* enemy, Point target);
bool IsPlayerInRange(Enemy* enemy);
void EnemyMove(Enemy* enemy, Point direction);
void EnemyAttack(Enemy* enemy);
void CalEnemyCooldown(Enemy* enemy);

void LookAt(Enemy* enemy, Point target) {
	int deltaX = target.x - enemy->base.entity.pos.x;
	int deltaY = target.y - enemy->base.entity.pos.y;

	if (abs(deltaX) > abs(deltaY)) {
		if (deltaX < 0) enemy->facing = Direction.west;
		else enemy->facing = Direction.east;
	}

	else {
		if (deltaY < 0) enemy->facing = Direction.south;
		else enemy->facing = Direction.north;
	}
}

bool IsPlayerInRange(Enemy* enemy) {
	Point playerPos = player->base.entity.pos;

	//세로범위
	Rect verticalDetectRect = {
		.x = enemy->base.entity.pos.x - (enemy->attackWidth / 2),
		.y = enemy->base.entity.pos.y - enemy->attackHeight,
		.width = enemy->attackWidth,
		.height = enemy->attackHeight * 2 + 1
	};

	//가로범위
	Rect horizontalDetectRect = {
		.x = enemy->base.entity.pos.x - enemy->attackHeight,
		.y = enemy->base.entity.pos.y - (enemy->attackWidth / 2),
		.width = enemy->attackHeight * 2 + 1,
		.height = enemy->attackWidth
	};

	return (bool)(
		RectContainsPoint(&verticalDetectRect, &playerPos)||
		RectContainsPoint(&horizontalDetectRect, &playerPos)
		);
}

void EnemyMove(Enemy* enemy, Point direction) {
	Point* nextPosition = DuplicatePoint(&enemy->base.entity.pos);
	PointAdd(nextPosition, &direction);
	Rect nextPositionRect = {
		.x = nextPosition->x,
		.y = nextPosition->y,
		.width = 1,
		.height = 1
	};
	
	Vector* vector = QuadTreeQuery(enemiesTree, nextPositionRect);
	if (vector->length <= 0 && !(GetTile(*nextPosition) & FLAG_COLLIDE_WITH_BODY)) {
		enemy->base.entity.pos = *nextPosition;
	}

	DeletePoint(nextPosition);
	DeleteVector(vector);
}

bool canEnemyAttack(Enemy* enemy) {
	return enemy->attackDelay <= 0;
}

void EnemyReadyAttack(Enemy* enemy) {
	//색깔 print 가능한 다음에
}

void EnemyAttack(Enemy* enemy) {
	if (!canEnemyAttack(enemy)) {
		return;
	}

	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		MeleeEnemyAttack((MeleeEnemy*)enemy);
		break;

	case ArcherEnemyType:
		//ArcherEnemyAttack((ArcherEnemy*)enemy);
		break;

	case BomberEnemyType:
		BomberEnemyAttack((BomberEnemy*)enemy);
		break;
	}
}

void CalEnemyCooldown(Enemy* enemy) {
	enemy->attackDelay -= Time.deltaTime;
	enemy->moveCoolDown -= Time.deltaTime;
}

void EnemyOnDeath(Enemy* enemy)
{
#ifdef DEBUG
	DebugPrint("Enemy Dead!");
#endif
	score += 10;
}

void EnemyOnHit(Enemy* enemy, int damage)
{
	enemy->hp -= damage;
#ifdef DEBUG
	DebugPrint("Enemy hitted! hp remains : %d", enemy->hp);
#endif

	if (enemy->hp <= 0)	{
		EnemyOnDeath(enemy);
	}
}

void CreateEnemy(enum EntityType type, Point spawnPoint) {
	Enemy* newEnemy = NULL;

	switch (type) {
	case MeleeEnemyType:
		newEnemy = (Enemy*)CreateMeleeEnemy(spawnPoint);
		break;

	case ArcherEnemyType:
		newEnemy = (Enemy*)CreateArcherEnemy(spawnPoint);
		break;

	case BomberEnemyType:
		newEnemy = (Enemy*)CreateBomberEnemy(spawnPoint);
		break;

	default: break;
	}

	newEnemy->ReadyToAttack = false;

#ifdef DEBUG
	DebugPrint("%d %d", newEnemy->base.entity.type, type);
#endif
	VectorInsert(enemies, newEnemy);
	//QuadTreeInsert(enemiesTree, newEnemy);
}

void UpdateEnemy(Enemy* enemy) {
	//사거리 내로 들어오면 우선 공격하기
	if (IsPlayerInRange(enemy) && BPMCall()) {
		LookAt(enemy, GetPlayerPos());
		EnemyReadyAttack(enemy);
	}
	CalEnemyCooldown(enemy);
}

bool isEnemyDead(Enemy* enemy) {
	return (bool)(enemy->hp <= 0);
}

bool isEnemy(Entity* entity) {
	enum EntityType type = entity->type;
	return (bool)(MeleeEnemyType <= type && type <= BomberEnemyType);
}

bool canEnemyMove(Enemy* enemy) {
	return enemy->moveCoolDown <= 0;
}

