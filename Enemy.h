#pragma once

#include "Entity.h"
#include "Point.h"
#include "Rect.h"

#include "RayCast.h"
typedef enum EnemyState {
	Tracking,
	ReadyToAttack,
} EnemyState;

typedef struct _Enemy {
	union {
		Entity entity;
	} base;

	EnemyState state;
	Point facing;

	int hp;
	int baseDamage;

	int detectionRadius;
	RayCastResult* memory;
	int memory_current_index;
	int moveSpeed; // small beat per time

	int attackSpeed; // small beat per time
	int attackWidth;
	int attackHeight;
	bool ReadyToAttack;

	int actCooldown; //���� : beat
	double stiffDuration;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Entity* entity);
bool isEnemyStiff(Enemy* enemy);

//Enemy���� damage��ŭ�� ���ظ� ���մϴ�. Enemy����� true�� ��ȯ�մϴ�.
bool EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);
void DeleteEnemy(Enemy* enemy);