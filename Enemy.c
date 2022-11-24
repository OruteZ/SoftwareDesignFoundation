#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"

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

	}
}

bool IsPlayerInRange() {

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

void CreateEnemy(EnemyBehaviorType type, Point spawnPoint) {
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

}

bool isEnemyDead(Enemy* enemy) {
	return (bool)(enemy->hp <= 0);
}
