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

	double moveSpeed;	//block per second
	double attackSpeed; //attack per second

	int hp;

	int baseDamage;

	double moveCoolDown;
	double attackDelay;

	int detectionRadius;

	int attackWidth;
	int attackHeight;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Entity* entity);
void EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);