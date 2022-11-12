#include "Point.h"
#include "BomberEnemy.h"

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy;
	bomberEnemy->base.entity.type = _BomberEnemy;
	bomberEnemy->base.entity.pos.x = p.x;
	bomberEnemy->base.entity.pos.y = p.y;
	bomberEnemy->base.mortal.attackCooldown = 0;
	bomberEnemy->base.mortal.baseDamage = 50;
	bomberEnemy->base.mortal.hp = 30;
	bomberEnemy->base.mortal.moveSpeed = 0.5f;
	bomberEnemy->blastRadius = 3.0f; //���� ���� ����
	return bomberEnemy;
}