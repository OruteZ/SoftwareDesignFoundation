#pragma once

#include "Entity.h"
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

	double moveSpeed;
	double moveCooldown;
	double lastMoved;

	int hp;

	int baseDamage;
	double attackDelay;
	double momentOfAttack;

	int detectionRadius;
} Enemy;

