#include "Point.h"
#include "MeleeEnemy.h"
MeleeEnemy* CreateMeleeEnemy(Point p)
{
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	meleeEnemy->base.entity.type = EnemyType;
	meleeEnemy->base.entity.pos.x = p.x;
	meleeEnemy->base.entity.pos.y = p.y;
	meleeEnemy->base.enemy.attackDelay = 1.0;
	meleeEnemy->base.enemy.baseDamage = 15;
	meleeEnemy->base.enemy.hp = 100;
	meleeEnemy->base.enemy.moveSpeed = 1.0;
	meleeEnemy->base.enemy.detectionRadius = 10;
	return meleeEnemy;
}

//#include "MeleeEnemyAttack.h"
//#include "Player.h"
//double meleeAttackCooldown;
//void CalculateMeleeAttackCooldown(MeleeEnemy* meleeEnemy)
//{
//	meleeAttackCooldown -= Time.deltaTime;
//
//	if (meleeAttackCooldown > 0)
//	{
//		meleeEnemy->base.entity.enemyState = Attack;
//	}
//}
//void MeleeEnemyAttack(MeleeEnemy* meleeEnemy)
//{
//	meleeAttackCooldown = meleeEnemy->base.mortal.attackCooldown;
//	if (RectContainsPoint(meleeEnemy->base.mortal.attackRange, player->base.entity.pos))
//	{
//		if (meleeAttackCooldown < 0)
//		{
//			PlayerOnHit(meleeEnemy->base.mortal.baseDamage);
//			meleeEnemy->base.entity.enemyState = Idle;
//		}
//	}
//}
//
//#include "SetMeleeAttackRange.h"
//void SetMeleeAttackRange(MeleeEnemy* meleeEnemy)
//{
//	Point playerPos = player->base.entity.pos;
//	Point meleeEnemyPos = meleeEnemy->base.entity.pos;
//	if (RectContainsPoint(meleeEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
//	{
//		if (playerPos.x >= meleeEnemyPos.x)
//		{
//			meleeEnemy->base.entity.direction = east;
//			meleeEnemy->base.mortal.attackRange =
//				CreateRect(meleeEnemyPos.x - 1, meleeEnemyPos.y - 1, 3, 2);
//		}
//		else if (player->base.entity.pos.x < meleeEnemy->base.entity.pos.x)
//		{
//			meleeEnemy->base.entity.direction = west;
//			meleeEnemy->base.mortal.attackRange =
//				CreateRect(meleeEnemy->base.entity.pos.x - 2, meleeEnemy->base.entity.pos.y - 1, 3, 2);
//		}
//	}
//}
