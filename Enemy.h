#pragma once

#include "Entity.h"
#include "Point.h"
#include "Rect.h"

typedef enum EnemyState{
	Idle,
	Moving,
	Attacking,
} EnemyState;

typedef enum _EnemyType {
	MeleeEnemyType,
	RangeEnemyType,
	BomberEnemyType,
} EnemyBehaviorType;

typedef struct _Enemy
{
	union {
		Entity entity;
	} base;

	EnemyBehaviorType enemyType;
	EnemyState state;

	double moveSpeed;
	double lastMoved;

	int hp;

	int baseDamage;
	double attackDelay;
	double momentOfAttack;

	int detectionRadius;
} Enemy;

bool isEnemyDead(Enemy* enemy);
void EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(EnemyBehaviorType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);
