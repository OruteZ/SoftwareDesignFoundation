#include "BomberEnemyAttack.h"
double bomberAttackCooldown;
void CalculateBomberAttackCooldown(BomberEnemy* bomberEnemy)
{
	bomberAttackCooldown -= Time.deltaTime;

	if (bomberAttackCooldown > 0)
	{
		bomberEnemy->base.entity.enemyState = Attack;
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