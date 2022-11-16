#include "MoveAndAttack.h"
void StartMeleeAttack(MeleeEnemy* meleeEnemy)
{
	double attackTime = ReadyMeleeAttack(meleeEnemy);
	if (attackTime != 0)
	{
		if ((RectContainsPoint(meleeEnemy->base.mortal.attackRange, player->base.entity.pos)))
		{
			if()
		}
	}
}