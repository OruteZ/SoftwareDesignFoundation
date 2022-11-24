#include "Point.h"
#include "BomberEnemy.h"

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy = (BomberEnemy*)malloc(sizeof(BomberEnemy));
	bomberEnemy->base.entity.type = EnemyType;
	bomberEnemy->base.entity.pos.x = p.x;
	bomberEnemy->base.entity.pos.y = p.y;
	bomberEnemy->base.enemy.attackDelay = 1;
	bomberEnemy->base.enemy.baseDamage = 50;
	bomberEnemy->base.enemy.hp = 30;
	bomberEnemy->base.enemy.moveSpeed = 0.5f;
	bomberEnemy->base.enemy.detectionRadius = 15;
	return bomberEnemy;
}


//#include "BomberEnemyAttack.h"
//double bomberAttackCooldown;
//void CalculateBomberAttackCooldown(BomberEnemy* bomberEnemy)
//{
//	bomberAttackCooldown -= Time.deltaTime;
//
//	if (bomberAttackCooldown > 0)
//	{
//		bomberEnemy->base.entity.enemyState = Attack;
//	}
//}
//void BomberEnemyAttack(BomberEnemy* bomberEnemy)
//{
//	bomberAttackCooldown = bomberEnemy->base.mortal.attackCooldown;
//	if (RectContainsPoint(bomberEnemy->base.mortal.attackRange, player->base.entity.pos))
//	{
//		if (bomberAttackCooldown < 0)
//		{
//			PlayerOnHit(bomberEnemy->base.mortal.baseDamage);
//			bomberEnemy->base.entity.enemyState = Idle;
//		}
//	}
//}
//
//#include "SetBomberAttackRange.h"
//void SetBomberAttackRange(BomberEnemy* bomberEnemy)
//{
//	Point playerPos = player->base.entity.pos;
//	Point bomberEnemyPos = bomberEnemy->base.entity.pos;
//	if (RectContainsPoint(bomberEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
//	{
//		//make bomberAttackRange
//		bomberEnemy->base.mortal.attackRange =
//			CreateRect(bomberEnemy->base.entity.pos.x - 3, bomberEnemy->base.entity.pos.y - 3, 6, 6);
//	}
//}
