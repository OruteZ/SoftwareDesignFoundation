#include "Enemy.h"
#include "MeleeEnemy.h"

#include "Point.h"
#include "Raycast.h"

MeleeEnemy* CreateMeleeEnemy(Point p) {
	MeleeEnemy* meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	if (meleeEnemy == NULL) exit(-1);
	
	Enemy* enemy = (Enemy*)meleeEnemy;
	enemy->base.entity.pos = p;
	enemy->base.entity.type = MeleeEnemyType;
	
	enemy->state = Tracking;

	enemy->hp = 100;

	enemy->detectionRadius = 10;
	enemy->memory = CreateRayCastResult(enemy->detectionRadius << 1);
	enemy->memory_current_index = 0;
	enemy->player_is_visible = false;

	enemy->move_per_second = 2;
	enemy->cant_move_until = 0;

	enemy->attackDamage = 5;
	enemy->attack_delay_small_beats = 3;
	enemy->attack_cooldown_small_beats = 2;

	enemy->small_beats_after_attack_start = 0;
	enemy->small_beats_after_attack_end = 0;

	enemy->is_frozen_until = 0;


	meleeEnemy->attack_radius = 1;

	return meleeEnemy;
}

#include "Time.h"
#include "Game.h"
#include "HeartBeat.h"
#include "Player.h"
void MeleeEnemyAttack(MeleeEnemy* mEnemy);
void MeleeEnemyUpdate(MeleeEnemy* mEnemy) {
	Enemy* enemy = (Enemy*)mEnemy;
	// Moving
	if (enemy->state == Tracking) {
		if (SmallBeatCall()) { // after attack cooldown counting!
			enemy->small_beats_after_attack_end++;
		}
		if (enemy->attack_cooldown_small_beats <= enemy->small_beats_after_attack_end) { // cooled down! ready to move!
			EnemyMoveAsMemory(mEnemy);

			Rect attack_detection_rect = {
				.x = mEnemy->base.entity.pos.x - mEnemy->attack_radius,
				.y = mEnemy->base.entity.pos.y - mEnemy->attack_radius,
				.width = mEnemy->attack_radius * 2 + 1,
				.height = mEnemy->attack_radius * 2 + 1
			};
			if (RectContainsPoint(&attack_detection_rect, &player->base.entity.pos)) {	// player in range!
				enemy->facing = EnemyDirectionToFacePlayer(mEnemy); // attack direction is decided!
				enemy->small_beats_after_attack_start = 0; // attack delay counting is started!
				enemy->state = ReadyToAttack;
			}
		}
	}

	// Attacking
	else if (enemy->state == ReadyToAttack) {
		if (SmallBeatCall()) { // delay counting!
			enemy->small_beats_after_attack_start++;
		}
		if (enemy->attack_delay_small_beats <= enemy->small_beats_after_attack_start) {	// ATTACK!
			MeleeEnemyAttack(mEnemy);
			enemy->small_beats_after_attack_end = 0;
			enemy->state = Tracking;
		}
	}
}

#include "Particle.h"
void MeleeEnemyAttack(MeleeEnemy* mEnemy) {
	Enemy* enemy = (Enemy*)mEnemy;
	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect;
	if (PointEquals(&mEnemy->base.enemy.facing, &Direction.north)) {
		attackRect.x = enemy->base.entity.pos.x - mEnemy->attack_radius;
		attackRect.y = enemy->base.entity.pos.y + mEnemy->attack_radius;
		attackRect.width = mEnemy->attack_radius * 2 + 1;
		attackRect.height = mEnemy->attack_radius;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.south)) {
		attackRect.x = enemy->base.entity.pos.x - mEnemy->attack_radius;
		attackRect.y = enemy->base.entity.pos.y - mEnemy->attack_radius;
		attackRect.width = mEnemy->attack_radius * 2 + 1;
		attackRect.height = mEnemy->attack_radius;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.west)) {
		attackRect.x = enemy->base.entity.pos.x - mEnemy->attack_radius;
		attackRect.y = enemy->base.entity.pos.y + mEnemy->attack_radius;
		attackRect.width = mEnemy->attack_radius;
		attackRect.height = mEnemy->attack_radius * 2 + 1;
	}
	else {
		attackRect.x = enemy->base.entity.pos.x + mEnemy->attack_radius;
		attackRect.y = enemy->base.entity.pos.y + mEnemy->attack_radius;
		attackRect.width = mEnemy->attack_radius;
		attackRect.height = mEnemy->attack_radius * 2 + 1;
	}

	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(enemy->attackDamage);
	}
}

