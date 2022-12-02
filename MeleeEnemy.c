#include "Point.h"
#include "MeleeEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "Particle.h"
#include<string.h>


#include "RayCast.h"
MeleeEnemy* CreateMeleeEnemy(Point p) {
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	if (meleeEnemy == NULL) exit(-1);

	meleeEnemy->base.entity.pos = p;
	meleeEnemy->base.entity.type = MeleeEnemyType;

	meleeEnemy->base.enemy.baseDamage = 15;
	meleeEnemy->base.enemy.hp = 100;
	meleeEnemy->base.enemy.moveSpeed = 2;
	meleeEnemy->base.enemy.attackSpeed = 4; //beat per attack
	meleeEnemy->base.enemy.detectionRadius = 10;
	meleeEnemy->base.enemy.memory = CreateRayCastResult(meleeEnemy->base.enemy.detectionRadius << 1);
	meleeEnemy->base.enemy.memory_current_index = 0;
	meleeEnemy->base.enemy.facing = Direction.north;

	meleeEnemy->base.enemy.actCooldown = 0;
	meleeEnemy->base.enemy.attackHeight = 1;
	meleeEnemy->base.enemy.attackWidth = 3;

	return meleeEnemy;
}

void MeleeEnemyAttack(MeleeEnemy* mEnemy) {
#ifdef DEBUG
	DebugPrint("Enemy Attacked");
#endif
	Point attackPoint = mEnemy->base.entity.pos;
	PointAdd(&attackPoint, &mEnemy->base.enemy.facing);

	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect;
	if (PointEquals(&mEnemy->base.enemy.facing, &Direction.north)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackWidth / 2;
		attackRect.y = mEnemy->base.entity.pos.y + 1;
		attackRect.width = mEnemy->base.enemy.attackWidth;
		attackRect.height = mEnemy->base.enemy.attackHeight;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.south)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackWidth / 2;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackHeight;
		attackRect.width = mEnemy->base.enemy.attackWidth;
		attackRect.height = mEnemy->base.enemy.attackHeight;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.west)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackHeight;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackWidth / 2;
		attackRect.width = mEnemy->base.enemy.attackHeight;
		attackRect.height = mEnemy->base.enemy.attackWidth;
	}
	else {
		attackRect.x = mEnemy->base.entity.pos.x + 1;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackWidth / 2;
		attackRect.width = mEnemy->base.enemy.attackHeight;
		attackRect.height = mEnemy->base.enemy.attackWidth;
	}

	CreateParticle(mEnemy->base.enemy.facing, attackPoint, MeleeAttackParticleType, 0);

	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(mEnemy->base.enemy.baseDamage);
	}
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
