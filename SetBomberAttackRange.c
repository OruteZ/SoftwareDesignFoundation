#include "SetBomberAttackRange.h"
void SetBomberAttackRange(BomberEnemy* bomberEnemy)
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