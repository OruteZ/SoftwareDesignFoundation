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
	int attack_delay_small_beats; // ���� ���� �� ��������� �ɸ��� small_beat
	int small_beats_after_attack_start; // (���� ����) �� �󸶳� small_beat�� ��������
	int attack_cooldown_small_beats; // ���� �� �� ���� ������ �����ϱ� �� ��Ÿ��
	int small_beats_after_attack_end; // ���� �� �� �󸶳� small_beat�� ��������

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