#pragma once

#include "Entity.h"
#include "Point.h"
#include "Rect.h"

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

	int attackSpeed; // small beat per time
	int moveSpeed; // small beat per time

	int detectionRadius;

	int attackWidth;
	int attackHeight;

	bool ReadyToAttack;
	int actCooldown; //단위 : beat
	double stiffDuration;
} Enemy;

bool isEnemyDead(Enemy* enemy);
bool isEnemy(Entity* entity);
bool isEnemyStiff(Enemy* enemy);

//Enemy에게 damage만큼의 피해를 가합니다. Enemy사망시 true를 반환합니다.
bool EnemyOnHit(Enemy* enemy, int damage);
void CreateEnemy(enum EntityType type, Point spawnPoint);
void UpdateEnemy(Enemy* enemy);
void DeleteEnemy(Enemy* enemy);