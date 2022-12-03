#pragma once

#include "Entity.h"
#include "Enemy.h"

typedef struct _BomberEmemy {
	union {
		Entity entity;
		Enemy enemy;
	} base;

	int attack_radius;
} BomberEnemy;

BomberEnemy* CreateBomberEnemy(Point p);

void BomberEnemyUpdate(BomberEnemy* bEnemy);

