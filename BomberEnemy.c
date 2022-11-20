#include "Point.h"
#include "BomberEnemy.h"

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy = (BomberEnemy*)malloc(sizeof(BomberEnemy));
	bomberEnemy->base.entity.type = _BomberEnemy;
	bomberEnemy->base.entity.pos.x = p.x;
	bomberEnemy->base.entity.pos.y = p.y;
	bomberEnemy->base.enemy.attackDelay = 1;
	bomberEnemy->base.enemy.baseDamage = 50;
	bomberEnemy->base.enemy.hp = 30;
	bomberEnemy->base.enemy.moveSpeed = 0.5f;
	bomberEnemy->base.enemy.detectionRadius = 15;
	return bomberEnemy;
}
