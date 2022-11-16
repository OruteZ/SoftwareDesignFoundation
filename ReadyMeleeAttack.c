#include "MoveAndAttack.h"
double ReadyMeleeAttack(MeleeEnemy *meleeEnemy)
{
	double attackTime = 0;
	if (RectContainsPoint(meleeEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		attackTime = Time.deltaTime + meleeEnemy->base.mortal.attackCooldown;
		return attackTime;
	}
}