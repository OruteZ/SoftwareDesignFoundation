#include "Point.h"
#include "MeleeEnemy.h"
MeleeEnemy* CreateMeleeEnemy(Point p)
{
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	meleeEnemy->base.entity.type = _MeleeEnemy;
	meleeEnemy->base.entity.pos.x = p.x;
	meleeEnemy->base.entity.pos.y = p.y;
	meleeEnemy->base.mortal.attackCooldown = 1.0;
	meleeEnemy->base.mortal.baseDamage = 15;
	meleeEnemy->base.mortal.hp = 40;
	meleeEnemy->base.mortal.moveSpeed = 1.0;
	meleeEnemy->base.mortal.playerSearchRange =
		Rect_new(meleeEnemy->base.entity.pos.x - 10, meleeEnemy->base.entity.pos.y - 10, 20, 20);
	return meleeEnemy;
}