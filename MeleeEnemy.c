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
	enemy->attack_delay_small_beats = 2;
	enemy->attack_delay_small_beats = 2;

	enemy->small_beats_after_attack_start = 0;
	enemy->small_beats_after_attack_end = 0;

	enemy->is_frozen_until = 0;


	meleeEnemy->attack_radius = 1;

	return meleeEnemy;
}

#include "Game.h"
#include "HeartBeat.h"
#include "Player.h"
void MeleeEnemyUpdate(MeleeEnemy* mEnemy) {
	Enemy* enemy = (Enemy*)mEnemy;
	// Moving
	if (enemy->state == Tracking) {
		EnemyMoveAsMemory(mEnemy);

		Rect attack_rect = {
			.x = mEnemy->base.entity.pos.x - mEnemy->attack_radius,
			.y = mEnemy->base.entity.pos.y - mEnemy->attack_radius,
			.width = mEnemy->attack_radius * 2 + 1,
			.height = mEnemy->attack_radius * 2 + 1
		};
		if (RectContainsPoint(&attack_rect, &player->base.entity.pos)) {	// player in range!
			mEnemy->base.enemy.facing = EnemyDirectionToFacePlayer(mEnemy); // attack direction is decided!
			mEnemy->base.enemy.small_beats_after_attack_start = 0; // attack delay counting is started!
			mEnemy->base.enemy.state = ReadyToAttack;
		}
	}

	// Attacking
	else if (mEnemy->base.enemy.state == ReadyToAttack) {
		if (SmallBeatCall()) {
			mEnemy->base.enemy.small_beats_after_attack_start++;
		}
		if (mEnemy->base.enemy.attack_delay_small_beats <= mEnemy->base.enemy.small_beats_after_attack_start) {	// ATTACK!
			MeleeEnemyAttack(mEnemy);
		}
	}
}

#include "Particle.h"
void MeleeEnemyAttack(MeleeEnemy* mEnemy) {
	Point attackPoint = mEnemy->base.entity.pos;
	PointAdd(&attackPoint, &mEnemy->base.enemy.facing);

	//바라보는 방향에 따라 공격범위 rect 지정
	Rect attackRect;
	if (PointEquals(&mEnemy->base.enemy.facing, &Direction.north)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackWidth / 2;
		attackRect.y = mEnemy->base.entity.pos.y + 1;
		attackRect.width = mEnemy->base.enemy.attackWidth;
		attackRect.height = mEnemy->base.enemy.attackHeight;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.south)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackWidth / 2;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackHeight;
		attackRect.width = mEnemy->base.enemy.attackWidth;
		attackRect.height = mEnemy->base.enemy.attackHeight;
	}
	else if (PointEquals(&mEnemy->base.enemy.facing, &Direction.west)) {
		attackRect.x = mEnemy->base.entity.pos.x - mEnemy->base.enemy.attackHeight;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackWidth / 2;
		attackRect.width = mEnemy->base.enemy.attackHeight;
		attackRect.height = mEnemy->base.enemy.attackWidth;
	}
	else {
		attackRect.x = mEnemy->base.entity.pos.x + 1;
		attackRect.y = mEnemy->base.entity.pos.y - mEnemy->base.enemy.attackWidth / 2;
		attackRect.width = mEnemy->base.enemy.attackHeight;
		attackRect.height = mEnemy->base.enemy.attackWidth;
	}

	CreateParticle(mEnemy->base.enemy.facing, attackPoint, MeleeAttackParticleType, 0);

	//플레이어 피격 확인
	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attackRect, &playerPos)) {
		PlayerOnHit(mEnemy->base.enemy.baseDamage);
	}
}

