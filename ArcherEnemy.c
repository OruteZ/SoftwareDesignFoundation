#include "Point.h"
#include "Time.h"
#include "ArcherEnemy.h"
#include "Player.h"
#include "Particle.h"

ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = (ArcherEnemy*)malloc(sizeof(ArcherEnemy));
	if (archerEnemy == NULL) exit(-1);

	archerEnemy->base.entity.type = ArcherEnemyType;
	archerEnemy->base.entity.pos = p;

	archerEnemy->base.enemy.baseDamage = 10;
	archerEnemy->base.enemy.attackSpeed = 1;
	archerEnemy->base.enemy.hp = 30;
	archerEnemy->base.enemy.moveSpeed = 1;
	archerEnemy->base.enemy.detectionRadius = 20;

	archerEnemy->base.enemy.facing = Direction.north;
	archerEnemy->base.enemy.actCooldown = 0;

	archerEnemy->base.enemy.attackHeight = 10;
	archerEnemy->base.enemy.attackWidth = 1;

	return archerEnemy;
}

void ArcherEnemyAttack(ArcherEnemy* archerEnemy) {
	Point attackPoint = archerEnemy->base.entity.pos;
	PointAdd(&attackPoint, &archerEnemy->base.enemy.facing);

	CreateParticle(archerEnemy->base.enemy.facing, attackPoint, EnemyRangeAttackParticleType, archerEnemy->base.enemy.baseDamage);
}
/*
void BomberEnemyAttack(BomberEnemy* bomberEnemy) {
	Point attackPoint = bomberEnemy->base.entity.pos;

	//�ٶ󺸴� ���⿡ ���� ���ݹ��� rect ����
	Rect attackRect = {
		.x = attackPoint.x - (bomberEnemy->base.enemy.attackWidth / 2),
		.y = attackPoint.y - (bomberEnemy->base.enemy.attackHeight / 2),
		.width = bomberEnemy->base.enemy.attackWidth,
		.height = bomberEnemy->base.enemy.attackHeight * 3
	};

	CreateParticle(bomberEnemy->base.enemy.facing, bomberEnemy->base.entity.pos, ExplosionParticleType1, bomberEnemy->base.enemy.baseDamage);
	//�÷��̾� �ǰ� Ȯ��
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(bomberEnemy->base.enemy.baseDamage);
	}

	bomberEnemy->base.enemy.hp = -1;
	bomberEnemy->base.enemy.attackDelay = 10000;

#ifdef DEBUG
	DebugPrint("Enemy Attacked");
#endif
}*/

//#include "ArcherEnemyAttack.h"
//
//double archerAttackCooldown;
//
//void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //���Ÿ� ���͸� ����, ����ü�� ���Ŀ�.
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
//		//���� ����
//		//����ü �����̱�
//		//����ü ��Ʈ �� �÷��̾� ü�� ����
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
//			DeleteRect(archerEnemy->base.mortal.attackRange);//���� �� ������ �ǳ�?
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