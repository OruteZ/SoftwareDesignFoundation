#include "Point.h"
#include "ArcherEnemy.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = (ArcherEnemy*)malloc(sizeof(ArcherEnemy));
	archerEnemy->base.entity.type = _ArcherEnemy;
	archerEnemy->base.entity.pos.x = p.x;
	archerEnemy->base.entity.pos.y = p.y;
	archerEnemy->base.mortal.attackCooldown = 3.0f;
	archerEnemy->base.mortal.baseDamage = 10;
	archerEnemy->base.mortal.hp = 30;
	archerEnemy->base.mortal.moveSpeed = 2.0f;
	archerEnemy->arrowSpeed = 0.5f;
	return archerEnemy;
}
