#include "EnemyAttack.h"
#include "Player.h"
double meleeAttackCooldown;
double archerAttackCooldown;
double bomberAttackCooldown;

void CalculateMeleeAttackCooldown(MeleeEnemy *meleeEnemy)
{
	meleeAttackCooldown -= Time.deltaTime;

	if (meleeAttackCooldown > 0)
	{
		meleeEnemy->base.entity.enemyState = Attack;
	}
}

void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //원거리 몬스터만 설정, 투사체는 추후에.
{
	archerAttackCooldown -= Time.deltaTime;

	if (archerAttackCooldown > 0)
	{
		archerEnemy->base.entity.enemyState = Attack;
	}
}

void CalculateBomberAttackCooldown(BomberEnemy* bomberEnemy) 
{
	bomberAttackCooldown -= Time.deltaTime;

	if (bomberAttackCooldown > 0)
	{
		bomberEnemy->base.entity.enemyState = Attack;
	}
}


void MeleeEnemyAttack(MeleeEnemy* meleeEnemy)
{
	meleeAttackCooldown = meleeEnemy->base.mortal.attackCooldown;
	if (RectContainsPoint(meleeEnemy->base.mortal.attackRange, player->base.entity.pos))
	{
		if (meleeAttackCooldown < 0)
		{
			PlayerOnHit(meleeEnemy->base.mortal.baseDamage);
			meleeEnemy->base.entity.enemyState = Idle;
		}
	}
}
void ArcherEnemyAttack(ArcherEnemy* archerEnemy)
{
	archerAttackCooldown = archerEnemy->base.mortal.attackCooldown;
	if (RectContainsPoint(archerEnemy->base.mortal.attackRange, player->base.entity.pos))
	{
		//공격 시작
		//투사체 움직이기
		//투사체 히트 시 플레이어 체력 감소
	}
}

void BomberEnemyAttack(BomberEnemy* bomberEnemy)
{
	bomberAttackCooldown = bomberEnemy->base.mortal.attackCooldown;
	if (RectContainsPoint(bomberEnemy->base.mortal.attackRange, player->base.entity.pos))
	{
		if (bomberAttackCooldown < 0)
		{
			PlayerOnHit(bomberEnemy->base.mortal.baseDamage);
			bomberEnemy->base.entity.enemyState = Idle;
		}
	}
}
void EnemyOnHit(Mortal *mortal, int playerDamage)
{
	mortal->hp -= playerDamage;
	if (mortal->hp <= 0)
	{
		//Delete Enemy, free Enemy
	}
}


