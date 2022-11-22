#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _BomberEmemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;
} BomberEnemy;

void CalculateBomberAttackCooldown(BomberEnemy* bomberEnemy);
void BomberEnemyAttack(BomberEnemy* bomberEnemy);
void SetBomberAttackRange(BomberEnemy* BomberEnemy);

