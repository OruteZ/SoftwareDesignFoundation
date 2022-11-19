#include "MeleeEnemyAttack.h"
#include "Player.h"
double meleeAttackCooldown;
void CalculateMeleeAttackCooldown(MeleeEnemy* meleeEnemy)
{
	meleeAttackCooldown -= Time.deltaTime;

	if (meleeAttackCooldown > 0)
	{
		meleeEnemy->base.entity.enemyState = Attack;
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