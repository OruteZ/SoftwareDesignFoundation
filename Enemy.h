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

	Rect AttackRange;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Entity* entity);
void EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);