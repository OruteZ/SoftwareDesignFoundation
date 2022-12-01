#include "Point.h"
#include "BomberEnemy.h"

#include "Player.h"
#include "Particle.h"

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy = (BomberEnemy*)malloc(sizeof(BomberEnemy));
	if (bomberEnemy == NULL) exit(-1);

	bomberEnemy->base.entity.type = BomberEnemyType;
	bomberEnemy->base.entity.pos = p;

	bomberEnemy->base.enemy.baseDamage = 50;
	bomberEnemy->base.enemy.hp = 30;
	bomberEnemy->base.enemy.attackSpeed = 1;
	bomberEnemy->base.enemy.moveSpeed = 1;
	bomberEnemy->base.enemy.detectionRadius = 2;

	bomberEnemy->base.enemy.actCooldown = 0;
	bomberEnemy->base.enemy.attackHeight = 1;
	bomberEnemy->base.enemy.attackWidth = 3;

	return bomberEnemy;
}

void BomberEnemyAttack(BomberEnemy* bomberEnemy) {
	Point attackPoint = bomberEnemy->base.entity.pos;

	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect = {
		.x = attackPoint.x - (bomberEnemy->base.enemy.attackWidth / 2),
		.y = attackPoint.y - (bomberEnemy->base.enemy.attackHeight / 2),
		.width = bomberEnemy->base.enemy.attackWidth,
		.height = bomberEnemy->base.enemy.attackHeight * 3
	};

	CreateParticle(bomberEnemy->base.enemy.facing, bomberEnemy->base.entity.pos, ExplosionParticleType1, bomberEnemy->base.enemy.baseDamage);
	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(bomberEnemy->base.enemy.baseDamage);
	}

	bomberEnemy->base.enemy.hp = -1;
	bomberEnemy->base.enemy.actCooldown = 10000;

#ifdef DEBUG
	DebugPrint("Enemy Attacked");
#endif
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
