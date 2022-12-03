#include "ArcherEnemy.h"

#include "Game.h"
#include "Time.h"

#include "Point.h"

#include "Enemy.h"
#include "Particle.h"

#include "RayCast.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = (ArcherEnemy*)malloc(sizeof(ArcherEnemy));
	if (archerEnemy == NULL) exit(-1);

	archerEnemy->base.entity.type = ArcherEnemyType;
	archerEnemy->base.entity.pos = p;

	archerEnemy->base.enemy.baseDamage = 10;
	archerEnemy->base.enemy.attackSpeed = 1;
	archerEnemy->base.enemy.hp = 30;
	archerEnemy->base.enemy.moveSpeed = 1;
	archerEnemy->base.enemy.detectionRadius = 20;
	archerEnemy->base.enemy.memory = CreateRayCastResult(archerEnemy->base.enemy.detectionRadius << 1);
	archerEnemy->base.enemy.memory_current_index = 0;

	archerEnemy->base.enemy.facing = Direction.north;
	archerEnemy->base.enemy.actCooldown = 0;

	archerEnemy->base.enemy.attackHeight = 10;
	archerEnemy->base.enemy.attackWidth = 1;

	return archerEnemy;
}

void ArcherEnemyAttack(ArcherEnemy* archerEnemy) {
	Point attackPoint = archerEnemy->base.entity.pos;
	PointAdd(&attackPoint, &archerEnemy->base.enemy.facing);

	CreateParticle(archerEnemy->base.enemy.facing, attackPoint, EnemyRangeAttackParticleType, archerEnemy->base.enemy.baseDamage);
}

void ArcherAlignWithPlayer(ArcherEnemy* archerEnemy) {
	
}
void ArcherEnemyUpdate(ArcherEnemy* archerEnemy) {
	if (!SmallBeatCall()) return;

	CalEnemyCooldown(archerEnemy);
	if (isEnemyStiff(archerEnemy)) return;
	archerEnemy->base.enemy.ReadyToAttack = IsPlayerInRange(archerEnemy);
}

