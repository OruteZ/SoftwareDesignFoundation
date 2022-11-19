#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"

#include "Entity.h"
#include "Enemy.h"

#include "Player.h"

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
	//몬스터 처치 이펙트	
}
void EnemyOnHit(Enemy* enemy, int damage)
{
	enemy->hp -= damage;
	if (enemy->hp <= 0)
	{
		EnemyOnDeath(enemy);
	}
}
