#include "ArcherEnemyAttack.h"

double archerAttackCooldown;

void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //���Ÿ� ���͸� ����, ����ü�� ���Ŀ�.
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
		//���� ����
		//����ü �����̱�
		//����ü ��Ʈ �� �÷��̾� ü�� ����
	}
}