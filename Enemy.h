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

	int hp;

	int detectionRadius;
	RayCastResult* memory;
	int memory_current_index;
	bool player_is_visible;

	double move_per_second;
	double cant_move_until;

	Point facing;
	int attackDamage;
	int attack_delay_small_beats; // 공격 시작 후 끝나기까지 걸리는 small_beat
	int small_beats_after_attack_start; // (공격 시작) 후 얼마나 small_beat가 지났는지
	int attack_cooldown_small_beats; // 공격 끝 후 다음 공격을 시작하기 전 쿨타임
	int small_beats_after_attack_end; // 공격 끝 후 얼마나 small_beat가 지났는지

	double is_frozen_until; // until gametime
} Enemy;
void CreateEnemy(enum EntityType type, Point spawnPoint);
void DeleteEnemy(Enemy* enemy);

bool IsEnemyDead(Enemy* enemy);
bool IsEnemyFrozen(Enemy* enemy);
void EnemyFreezeUntil(Enemy* enemy, double GameTime);

Point EnemyDirectionToFacePlayer(Enemy* enemy);
bool EnemyMove(Enemy* enemy, Point direction);
void EnemyMoveAsMemory(Enemy* enemy);

bool EnemyOnHit(Enemy* enemy, int damage);
void EnemyUpdate(Enemy* enemy);