#include "Point.h"
#include "BomberEnemy.h"

#include "Player.h"

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy = (BomberEnemy*)malloc(sizeof(BomberEnemy));
	bomberEnemy->base.entity.type = BomberEnemyType;
	bomberEnemy->base.entity.pos.x = p.x;
	bomberEnemy->base.entity.pos.y = p.y;
	bomberEnemy->base.enemy.attackDelay = 1;
	bomberEnemy->base.enemy.baseDamage = 50;
	bomberEnemy->base.enemy.hp = 30;
	bomberEnemy->base.enemy.moveSpeed = 0.5f;
	bomberEnemy->base.enemy.detectionRadius = 15;
	return bomberEnemy;
}

void BomberEnemyAttack(BomberEnemy* bomberEnemy) {
	Point attackPoint = bomberEnemy->base.entity.pos;

	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect = {
		.x = attackPoint.x - (bomberEnemy->base.enemy.attackHeight - 1),
		.y = attackPoint.y - (bomberEnemy->base.enemy.attackHeight - 1),
		.width = bomberEnemy->base.enemy.attackWidth,
		.height = bomberEnemy->base.enemy.attackHeight
	};

	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(bomberEnemy->base.enemy.baseDamage);
	}


	bomberEnemy->base.enemy.attackDelay = 1 / (bomberEnemy->base.enemy.attackSpeed);
	if (bomberEnemy->base.enemy.moveCoolDown < bomberEnemy->base.enemy.attackDelay) {
		bomberEnemy->base.enemy.moveCoolDown = bomberEnemy->base.enemy.attackDelay;
	}

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
