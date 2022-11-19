#include "ArcherEnemyAttack.h"

double archerAttackCooldown;

void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //원거리 몬스터만 설정, 투사체는 추후에.
{
	archerAttackCooldown -= Time.deltaTime;

	if (archerAttackCooldown > 0)
	{
		archerEnemy->base.entity.enemyState = Attack;
	}
}
void ArcherEnemyAttack(ArcherEnemy* archerEnemy)
{
	archerAttackCooldown = archerEnemy->base.mortal.attackCooldown;
	if (RectContainsPoint(archerEnemy->base.mortal.attackRange, player->base.entity.pos))
	{
		//공격 시작
		//투사체 움직이기
		//투사체 히트 시 플레이어 체력 감소
	}
}