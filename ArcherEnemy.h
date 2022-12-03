#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _ArcherEmemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;

	int bow_attack_radius;
} ArcherEnemy;

ArcherEnemy* CreateArcherEnemy(Point p);

void ArcherEnemyUpdate(ArcherEnemy* archerEnemy);

