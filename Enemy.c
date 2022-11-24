#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"
#include "Point.h"

#include "Entity.h"
#include "Enemy.h"

#include "Player.h"
#include "Debug.h"

#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"

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
		.x = enemy->base.entity.pos.x - (enemy->AttackRange.width / 2),
		.y = enemy->base.entity.pos.y - enemy->AttackRange.height,
		.width = enemy->AttackRange.width,
		.height = enemy->AttackRange.height * 2 + 1
	};

	//가로범위
	Rect horizontalDetectRect = {
		.x = enemy->base.entity.pos.x - enemy->AttackRange.height,
		.y = enemy->base.entity.pos.y - (enemy->AttackRange.width / 2),
		.width = enemy->AttackRange.height * 2 + 1,
		.height = enemy->AttackRange.width
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

void EnemyAttack(Enemy* enemy) {
	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		MeleeEnemyAttack(enemy);
		break;

	case ArcherEnemyType:
		ArcherEnemyAttack(enemy);
		break;

	case BomberEnemyType:
		BomberEnemyAttack(enemy);
		break;
	}
}

void EnemyOnDeath(Enemy* enemy)
{
#ifdef DEBUG
	DebugPrint("Enemy Dead!");
#endif
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
	Enemy* newEnemy;

	switch (type) {
	case MeleeEnemyType:
		newEnemy = CreateMeleeEnemy(spawnPoint);
		break;

	case ArcherEnemyType:
		newEnemy = CreateArcherEnemy(spawnPoint);
		break;

	case BomberEnemyType:
		newEnemy = CreateBomberEnemy(spawnPoint);
		break;
	}

	VectorInsert(enemies, newEnemy);
	QuadTreeInsert(enemiesTree, newEnemy);
}

void UpdateEnemy(Enemy* enemy) {
	//사거리 내로 들어오면 우선 공격하기
	if (IsPlayerInRange(enemy)) {
		LookAt(enemy, player->base.entity.pos);
		EnemyAttack(enemy);
	}
}

bool isEnemyDead(Enemy* enemy) {
	return (bool)(enemy->hp <= 0);
}

bool isEnemy(Entity* entity) {
	enum EntityType type = enemy->base.entity.type;
	return (bool)(MeleeEnemyType <= type && type <= BomberEnemyType);
}
