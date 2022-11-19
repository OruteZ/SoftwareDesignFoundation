#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _ArcherEmemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;

	double arrowSpeed;
} ArcherEnemy;

void CalculateRangeAttackCooldown(ArcherEnemy* archerEnemy);
void ArcherEnemyAttack(ArcherEnemy* archerEnemy);
void SetArcherAttackRange(ArcherEnemy* archerEnemy);

