#include "StartAttack.h"
double StartMeleeAttack(MeleeEnemy* meleeEnemy)
{
	double MeleeAttackTime = 0;
	if ((RectContainsPoint(meleeEnemy->base.mortal.attackRange, player->base.entity.pos)))
	{
		MeleeAttackTime = Time.time + meleeEnemy->base.mortal.attackCooldown;
		return MeleeAttackTime;
	}
}

double StartRangeAttack(ArcherEnemy* archerEnemy)
{
	double RangeAttackTime = 0;
	if ((RectContainsPoint(archerEnemy->base.mortal.attackRange, player->base.entity.pos)))
	{
		RangeAttackTime = Time.time + archerEnemy->base.mortal.attackCooldown;
		return RangeAttackTime;
	}
}

double StartBomberAttack(BomberEnemy* bomberEnemy)
{
	double BomberAttackTime = 0;
	if ((RectContainsPoint(bomberEnemy->base.mortal.attackRange, player->base.entity.pos)))
	{
		BomberAttackTime = Time.time + bomberEnemy->base.mortal.attackCooldown;
		return BomberAttackTime;
	}
}