#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"

#include "Entity.h"
#include "Enemy.h"

#include "Player.h"
#include "Debug.h"

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

bool isEnemyDead(Enemy* enemy)
{
	return (bool)(enemy->hp <= 0);
}
