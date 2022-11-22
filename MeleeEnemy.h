#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _MeleeEnemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;
} MeleeEnemy;

MeleeEnemy* CreateMeleeEnemy(Point p);
void CalculateMeleeAttackCooldown(MeleeEnemy* meleeEnemy);
void MeleeEnemyAttack(MeleeEnemy* meleeEnemy);
void SetMeleeAttackRange(MeleeEnemy* meleeEnemy);

