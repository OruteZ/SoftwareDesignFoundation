#include "Point.h"
#include "MeleeEnemy.h"
#include "Player.h"



const double _baseMeleeEnemyAttackDelay = 0.15;
const MeleeEnemy DefaultMeleeEnemy = {
	.base.entity = {
		.pos = {0, 0},
		.type = MeleeEnemyType
	},

	.base.enemy = {
		.baseDamage = 15,
		.hp = 100,
		.moveSpeed = 1, //block per second
		.attackSpeed = 1 / 0.15,
		.detectionRadius = 10,
		.facing = {0, 1},

		.moveCoolDown = 0,
		.attackDelay = 0,
		.attackRange = {
			.x = 0,
			.y = 0,
			.width = 3,
			.height = 1,
		}
	}
};

MeleeEnemy* CreateMeleeEnemy(Point p) {
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));

	(*meleeEnemy) = DefaultMeleeEnemy;
	meleeEnemy->base.entity.pos = p;

	return meleeEnemy;
}

void MeleeEnemyAttack(MeleeEnemy* mEnemy) {
	Point attackPoint = mEnemy->base.entity.pos;
	PointAdd(&attackPoint, &mEnemy->base.enemy.facing);

	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect;

	if (PointEquals(&mEnemy->base.enemy.facing, &Direction.north)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackRange.width / 2;
		attackRect.y = mEnemy->base.entity.pos.y + 1;
		attackRect.width = mEnemy->base.enemy.attackRange.width;
		attackRect.height = mEnemy->base.enemy.attackRange.height;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.south)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackRange.width / 2;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackRange.height;
		attackRect.width = mEnemy->base.enemy.attackRange.width;
		attackRect.height = mEnemy->base.enemy.attackRange.height;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.west)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackRange.height;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackRange.width / 2;
		attackRect.width = mEnemy->base.enemy.attackRange.height;
		attackRect.height = mEnemy->base.enemy.attackRange.width;
	}
	else {
		attackRect.x = mEnemy->base.entity.pos.x + 1;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackRange.width / 2;
		attackRect.width = mEnemy->base.enemy.attackRange.height;
		attackRect.height = mEnemy->base.enemy.attackRange.width;
	}

	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(mEnemy->base.enemy.baseDamage);
	}


	mEnemy->base.enemy.attackDelay = 1 / (mEnemy->base.enemy.attackSpeed);
	if (mEnemy->base.enemy.moveCoolDown < mEnemy->base.enemy.attackDelay) {
		mEnemy->base.enemy.moveCoolDown = mEnemy->base.enemy.attackDelay;
	}

#ifdef DEBUG
	DebugPrint("Enemy Attacked");
#endif
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
