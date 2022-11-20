#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _MeleeEnemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;
} MeleeEnemy;

void CalculateMeleeAttackCooldown(MeleeEnemy* meleeEnemy);
void MeleeEnemyAttack(MeleeEnemy* meleeEnemy);
void SetMeleeAttackRange(MeleeEnemy* meleeEnemy);

