#include "Point.h"
#include "ArcherEnemy.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy;
	archerEnemy->base.entity.type = _ArcherEnemy;
	archerEnemy->base.entity.pos.x = p.x;
	archerEnemy->base.entity.pos.y = p.y;
	archerEnemy->base.mortal.attackCooldown = 3.0f;
	archerEnemy->base.mortal.baseDamage = 10;
	archerEnemy->base.mortal.hp = 30;
	archerEnemy->base.mortal.moveSpeed = 2.0f;
	archerEnemy->arrowSpeed = 0.5f;
	archerEnemy->base.mortal.attackRange =
		Rect_new(archerEnemy->base.entity.pos.x - 1, archerEnemy->base.entity.pos.y, 10, 2);
	return archerEnemy;
}
