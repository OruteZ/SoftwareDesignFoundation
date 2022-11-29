#pragma once

#include "Entity.h"
#include "Point.h"
#include "Rect.h"

typedef enum EnemyState{
	Tracking,
	ReadyToAttack,
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

	bool ReadyToAttack;

	double stiffDuration;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Entity* entity);
bool isEnemyStiff(Enemy* enemy);

//Enemy���� damage��ŭ�� ���ظ� ���մϴ�. Enemy����� true�� ��ȯ�մϴ�.
bool EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);