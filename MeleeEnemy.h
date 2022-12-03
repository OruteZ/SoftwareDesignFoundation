#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _MeleeEnemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;

	int attack_radius;
} MeleeEnemy;

MeleeEnemy* CreateMeleeEnemy(Point p);

void MeleeEnemyUpdate(MeleeEnemy* mEnemy);

