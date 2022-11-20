#include "Point.h"
#include "MeleeEnemy.h"
MeleeEnemy* CreateMeleeEnemy(Point p)
{
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	meleeEnemy->base.entity.type = _MeleeEnemy;
	meleeEnemy->base.entity.pos.x = p.x;
	meleeEnemy->base.entity.pos.y = p.y;
	meleeEnemy->base.enemy.attackDelay = 1.0;
	meleeEnemy->base.enemy.baseDamage = 15;
	meleeEnemy->base.enemy.hp = 40;
	meleeEnemy->base.enemy.moveSpeed = 1.0;
	meleeEnemy->base.enemy.detectionRadius = 10;
	return meleeEnemy;
}