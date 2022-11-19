#include "SetMeleeAttackRange.h"
void SetMeleeAttackRange(MeleeEnemy* meleeEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point meleeEnemyPos = meleeEnemy->base.entity.pos;
	if (RectContainsPoint(meleeEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		if (playerPos.x >= meleeEnemyPos.x)
		{
			meleeEnemy->base.entity.direction = east;
			meleeEnemy->base.mortal.attackRange =
				CreateRect(meleeEnemyPos.x - 1, meleeEnemyPos.y - 1, 3, 2);
		}
		else if (player->base.entity.pos.x < meleeEnemy->base.entity.pos.x)
		{
			meleeEnemy->base.entity.direction = west;
			meleeEnemy->base.mortal.attackRange =
				CreateRect(meleeEnemy->base.entity.pos.x - 2, meleeEnemy->base.entity.pos.y - 1, 3, 2);
		}
	}
}