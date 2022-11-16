#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "Time.h"
#include "Game.h"
#include "Rect.h"


void MeleeEnemyMove(MeleeEnemy* meleeEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point meleeEnemyPos = meleeEnemy->base.entity.pos;
	if (RectContainsPoint(meleeEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//move MeleeEnemy




		//make MeleeAttackRange - 3x4
		if (playerPos.x>= meleeEnemyPos.x)
		{
			meleeEnemy->base.entity.direction = east;
			meleeEnemy->base.mortal.attackRange =
				Rect_new(meleeEnemyPos.x - 1,meleeEnemyPos.y - 2, 3, 4);
		}
		else if (player->base.entity.pos.x < meleeEnemy->base.entity.pos.x)
		{
			meleeEnemy->base.entity.direction = west;
			meleeEnemy->base.mortal.attackRange =
				Rect_new(meleeEnemy->base.entity.pos.x - 2, meleeEnemy->base.entity.pos.y - 2, 3, 4);
		}
	}
}

void ArcherEnemyMove(ArcherEnemy* archerEnemy)
{
	Point playerPos = player->base.entity.pos;
	Point archerEnemyPos = archerEnemy->base.entity.pos;
	if (RectContainsPoint(archerEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//move ArcherEnemy
		

		//make ArcherAttackRange
		if (playerPos.x >= archerEnemyPos.x && playerPos.y == archerEnemyPos.y)
		{
			archerEnemy->base.entity.direction = east;
			archerEnemy->base.mortal.attackRange =
				Rect_new(archerEnemy->base.entity.pos.x - 1, archerEnemy->base.entity.pos.y , 3, 4);
		}
		else if (player->base.entity.pos.x < meleeEnemy->base.entity.pos.x)
		{
			meleeEnemy->base.entity.direction = west;
			meleeEnemy->base.mortal.attackRange =
				Rect_new(meleeEnemy->base.entity.pos.x - 2, meleeEnemy->base.entity.pos.y - 2, 3, 4);
		}
	}
}

void BomberEnemyMove(BomberEnemy* bomberEnemy)
{
	if (RectContainsPoint(bomberEnemy->base.mortal.playerSearchRange, player->base.entity.pos))
	{
		//move actions
	}
}