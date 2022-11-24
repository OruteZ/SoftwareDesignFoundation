#pragma once

#include "Entity.h"
#include "Point.h"
#include "Rect.h"

typedef enum EnemyState{
	Idle,
	Moving,
	Attacking,
} EnemyState;

typedef struct _Enemy
{
	union {
		Entity entity;
	} base;
	EnemyState state;

	Point facing;

	double moveSpeed;
	double lastMoved;

	int hp;

	int baseDamage;
	double attackDelay;
	double momentOfAttack;

	int detectionRadius;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Enemy* enemy);
void EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);