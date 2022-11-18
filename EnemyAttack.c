#include "EnemyAttack.h"
#include "Player.h"
double meleeAttackCooldown;
double archerAttackCooldown;
double bomberAttackCooldown;

void CalculateMeleeAttackCooldown(MeleeEnemy *meleeEnemy)
{
	meleeAttackCooldown -= Time.deltaTime;

	if (meleeAttackCooldown > 0)
	{
		meleeEnemy->base.entity.enemyState = Attack;
	}
}

void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy) //���Ÿ� ���͸� ����, ����ü�� ���Ŀ�.
{
	archerAttackCooldown -= Time.deltaTime;

	if (archerAttackCooldown > 0)
	{
		archerEnemy->base.entity.enemyState = Attack;
	}
}

void CalculateBomberAttackCooldown(BomberEnemy* bomberEnemy) 
{
	bomberAttackCooldown -= Time.deltaTime;

	if (bomberAttackCooldown > 0)
	{
		bomberEnemy->base.entity.enemyState = Attack;
	}
}


void MeleeEnemyAttack(MeleeEnemy* meleeEnemy)
{
	meleeAttackCooldown = meleeEnemy->base.mortal.attackCooldown;
	if (RectContainsPoint(meleeEnemy->base.mortal.attackRange, player->base.entity.pos))
	{
		if (meleeAttackCooldown < 0)
		{
			PlayerOnHit(meleeEnemy->base.mortal.baseDamage);
			meleeEnemy->base.entity.enemyState = Idle;
		}
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
void EnemyOnHit(Mortal *mortal, int playerDamage)
{
	mortal->hp -= playerDamage;
	if (mortal->hp <= 0)
	{
		//Delete Enemy, free Enemy
	}
}


