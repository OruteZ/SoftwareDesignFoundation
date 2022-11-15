#include "StartMeleeAttack.h"
void startMeleeAttack(MeleeEnemy meleeEnemy)
{
	enum Direction direction;
	double attackTime;
	if (RectContainsPoint(meleeEnemy.base.mortal.attackRange, player->base.entity.pos))
	{
		attackTime = Time.deltaTime + meleeEnemy.base.mortal.attackCooldown;
		if (player->base.entity.pos.x > meleeEnemy.base.entity.pos.x)
		{
			direction = east;
		}
		else if (player->base.entity.pos.x < meleeEnemy.base.entity.pos.x)
		{
			direction = west;
		}
		else if (player->base.entity.pos.y > meleeEnemy.base.entity.pos.y)
		{
			direction = south;
		}
		else if (player->base.entity.pos.y < meleeEnemy.base.entity.pos.y)
		{
			direction = north;
		}
	}

	//decide facing, store planned attack time
}