#include "Point.h"
#include "BomberEnemy.h"

#include "Player.h"
#include "Particle.h"

#include "RayCast.h"
BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy = (BomberEnemy*)malloc(sizeof(BomberEnemy));
	if (bomberEnemy == NULL) exit(-1);
	
	Enemy* enemy = (Enemy*)bomberEnemy;
	enemy->base.entity.pos = p;
	enemy->base.entity.type = BomberEnemyType;
	
	enemy->state = Tracking;

	enemy->hp = 100;

	enemy->detectionRadius = 10;
	enemy->memory = CreateRayCastResult(enemy->detectionRadius << 1);
	enemy->memory_current_index = 0;
	enemy->player_is_visible = false;

	enemy->move_per_second = 3;
	enemy->cant_move_until = 0;

	enemy->attackDamage = 10;
	enemy->attack_delay_small_beats = 2;
	enemy->attack_cooldown_small_beats = 2;

	enemy->small_beats_after_attack_start = 0;
	enemy->small_beats_after_attack_end = 0;

	enemy->is_frozen_until = 0;


	bomberEnemy->attack_radius = 1;

	return bomberEnemy;
}

#include "Game.h"
void BomberEnemyAttack(BomberEnemy* bEnemy);
void BomberEnemyUpdate(BomberEnemy* bEnemy) {
	Enemy* enemy = (Enemy*)bEnemy;
	// Moving
	if (enemy->state == Tracking) {
		if (SmallBeatCall()) { // after attack cooldown counting!
			enemy->small_beats_after_attack_end++;
		}
		if (enemy->attack_cooldown_small_beats <= enemy->small_beats_after_attack_end) { // cooled down! ready to move!
			EnemyMoveAsMemory(bEnemy);

			Rect attack_detection_rect = {
				.x = bEnemy->base.entity.pos.x - bEnemy->attack_radius,
				.y = bEnemy->base.entity.pos.y - bEnemy->attack_radius,
				.width = bEnemy->attack_radius * 2 + 1,
				.height = bEnemy->attack_radius * 2 + 1
			};
			if (RectContainsPoint(&attack_detection_rect, &player->base.entity.pos)) {	// player in range!
				enemy->facing = EnemyDirectionToFacePlayer(bEnemy); // attack direction is decided!
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
			BomberEnemyAttack(bEnemy);
			enemy->small_beats_after_attack_end = 0;
			enemy->state = Tracking;
		}
	}
}

void BomberEnemyAttack(BomberEnemy* bEnemy) {
	Enemy* enemy = (Enemy*)bEnemy;

	Rect attack_rect = {
		.x = enemy->base.entity.pos.x - bEnemy->attack_radius,
		.y = enemy->base.entity.pos.y - bEnemy->attack_radius,
		.width = bEnemy->attack_radius * 2 + 1,
		.height = bEnemy->attack_radius * 2 + 1
	};

	Point playerPos = GetPlayerPos();
	if (RectContainsPoint(&attack_rect, &playerPos)) {
		PlayerOnHit(enemy->attackDamage);
	}
	bEnemy->base.enemy.hp = 0;
}

