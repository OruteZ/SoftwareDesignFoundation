#include "Point.h"
#include "Time.h"
#include "ArcherEnemy.h"
#include "Player.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = (ArcherEnemy*)malloc(sizeof(ArcherEnemy));
	archerEnemy->base.entity.type = EnemyType;
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

//#include "ArcherEnemyAttack.h"
//
//double archerAttackCooldown;
//
//void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //원거리 몬스터만 설정, 투사체는 추후에.
//{
//	archerAttackCooldown -= Time.deltaTime;
//
//	if (archerAttackCooldown > 0)
//	{
//		archerEnemy->base.entity.enemyState = Attack;
//	}
//}
//void ArcherEnemyAttack(ArcherEnemy* archerEnemy)
//{
//	archerAttackCooldown = archerEnemy->base.mortal.attackCooldown;
//	if (RectContainsPoint(archerEnemy->base.mortal.attackRange, player->base.entity.pos))
//	{
//		//공격 시작
//		//투사체 움직이기
//		//투사체 히트 시 플레이어 체력 감소
//	}
//}
//
//#include "ArcherEnemy.h"
//
//void SetArcherAttackRange(ArcherEnemy* archerEnemy)
//{
//	Point playerPos = player->base.entity.pos;
//	Point archerEnemyPos = archerEnemy->base.entity.pos;
//	if (RectContainsPoint(archerEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
//	{
//		//make ArcherAttackRange - 14x1
//
//		if (archerEnemy->base.mortal.attackRange != NULL)
//		{
//			DeleteRect(archerEnemy->base.mortal.attackRange);//굳이 안 지워도 되나?
//		}
//		if (playerPos.y == archerEnemyPos.y)
//		{
//			if (playerPos.x > archerEnemyPos.x)
//			{
//				archerEnemy->base.entity.direction = east;
//				archerEnemy->base.mortal.attackRange =
//					CreateRect(archerEnemy->base.entity.pos.x - 1, archerEnemy->base.entity.pos.y, 15, 1);
//			}
//			else if (playerPos.x < archerEnemyPos.x)
//			{
//				archerEnemy->base.entity.direction = west;
//				archerEnemy->base.mortal.attackRange =
//					CreateRect(archerEnemy->base.entity.pos.x - 14, archerEnemy->base.entity.pos.y, 15, 1);
//			}
//		}
//		else if (playerPos.x == archerEnemyPos.x)
//		{
//			if (playerPos.y > archerEnemyPos.y)
//			{
//				archerEnemy->base.entity.direction = south;
//				archerEnemy->base.mortal.attackRange =
//					CreateRect(archerEnemy->base.entity.pos.x, archerEnemy->base.entity.pos.y - 1, 1, 15);
//			}
//			else if (playerPos.y < archerEnemyPos.y)
//			{
//				archerEnemy->base.entity.direction = west;
//				archerEnemy->base.mortal.attackRange =
//					CreateRect(archerEnemy->base.entity.pos.x, archerEnemy->base.entity.pos.y - 14, 15, 1);
//			}
//		}
//	}
//}