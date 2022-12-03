#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _ArcherEmemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;
} ArcherEnemy;

ArcherEnemy* CreateArcherEnemy(Point p);
void ArcherEnemyAttack(ArcherEnemy* archerEnemy);

