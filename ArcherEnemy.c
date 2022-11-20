#include "Point.h"
#include "Time.h"
#include "ArcherEnemy.h"
#include "Player.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = (ArcherEnemy*)malloc(sizeof(ArcherEnemy));
	archerEnemy->base.entity.type = _ArcherEnemy;
	archerEnemy->base.entity.pos.x = p.x;
	archerEnemy->base.entity.pos.y = p.y;
	archerEnemy->base.enemy.attackDelay= 3.0f;
	archerEnemy->base.enemy.baseDamage = 10;
	archerEnemy->base.enemy.hp = 30;
	archerEnemy->base.enemy.moveSpeed = 2.0f;
	archerEnemy->arrowSpeed = 0.5f;
	archerEnemy->base.enemy.detectionRadius = 20;

	return archerEnemy;
}