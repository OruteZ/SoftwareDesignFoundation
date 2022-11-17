#include "SetAttackRange.h"


void MeleeEnemyMove(MeleeEnemy* meleeEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point meleeEnemyPos = meleeEnemy->base.entity.pos;
	if (RectContainsPoint(meleeEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//make MeleeAttackRange - 3x4
		if (playerPos.x>= meleeEnemyPos.x)
		{
			meleeEnemy->base.entity.direction = east;
			meleeEnemy->base.mortal.attackRange =
				CreateRect(meleeEnemyPos.x - 1,meleeEnemyPos.y - 2, 3, 4);
		}
		else if (player->base.entity.pos.x < meleeEnemy->base.entity.pos.x)
		{
			meleeEnemy->base.entity.direction = west;
			meleeEnemy->base.mortal.attackRange =
				CreateRect(meleeEnemy->base.entity.pos.x - 2, meleeEnemy->base.entity.pos.y - 2, 3, 4);
		}
	}
}

void ArcherEnemyMove(ArcherEnemy* archerEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point archerEnemyPos = archerEnemy->base.entity.pos;
	if (RectContainsPoint(archerEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//make ArcherAttackRange - 14x1

		if (archerEnemy->base.mortal.attackRange != NULL)
		{
			DeleteRect(archerEnemy->base.mortal.attackRange);//굳이 안 지워도 되나?
		}
		if (playerPos.y == archerEnemyPos.y)
		{
			if (playerPos.x > archerEnemyPos.x)
			{
				archerEnemy->base.entity.direction = east;
				archerEnemy->base.mortal.attackRange =
					CreateRect(archerEnemy->base.entity.pos.x - 1, archerEnemy->base.entity.pos.y, 15, 1);
			}
			else if (playerPos.x < archerEnemyPos.x)
			{
				archerEnemy->base.entity.direction = west;
				archerEnemy->base.mortal.attackRange =
					CreateRect(archerEnemy->base.entity.pos.x - 14, archerEnemy->base.entity.pos.y, 15, 1);
			}
		}
		else if (playerPos.x == archerEnemyPos.x)
		{
			if (playerPos.y > archerEnemyPos.y)
			{
				archerEnemy->base.entity.direction = south;
				archerEnemy->base.mortal.attackRange =
					CreateRect(archerEnemy->base.entity.pos.x, archerEnemy->base.entity.pos.y - 1, 1, 15);
			}
			else if (playerPos.y < archerEnemyPos.y)
			{
				archerEnemy->base.entity.direction = west;
				archerEnemy->base.mortal.attackRange =
					CreateRect(archerEnemy->base.entity.pos.x, archerEnemy->base.entity.pos.y - 14, 15, 1);
			}
		}
	}
}

void BomberEnemyMove(BomberEnemy* bomberEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point bomberEnemyPos = bomberEnemy->base.entity.pos;
	if (RectContainsPoint(bomberEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//make bomberAttackRange
		bomberEnemy->base.mortal.attackRange =
			CreateRect(bomberEnemy->base.entity.pos.x - 3, bomberEnemy->base.entity.pos.y - 3, 6, 6);
	}
}