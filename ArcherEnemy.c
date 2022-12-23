#include "ArcherEnemy.h"

#include <math.h>

#include "Game.h"
#include "Time.h"

#include "Point.h"

#include "Enemy.h"
#include "Particle.h"

#include "RayCast.h"
ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy = malloc(sizeof(ArcherEnemy));
	if (archerEnemy == NULL) exit(-1);
	
	Enemy* enemy = (Enemy*)archerEnemy;
	enemy->base.entity.pos = p;
	enemy->base.entity.type = ArcherEnemyType;
	
	enemy->state = Tracking;

	enemy->hp = 30;

	enemy->detectionRadius = 12;
	enemy->memory = CreateRayCastResult(enemy->detectionRadius << 1);
	enemy->memory_current_index = 0;
	enemy->player_is_visible = false;

	enemy->move_per_second = 2;
	enemy->cant_move_until = 0;

	enemy->attackDamage = 1;
	enemy->attack_delay_small_beats = 4;
	enemy->attack_cooldown_small_beats = 8;

	enemy->small_beats_after_attack_start = 0;
	enemy->small_beats_after_attack_end = 0;

	enemy->is_frozen_until = 0;


	archerEnemy->bow_attack_radius = 6;

	return archerEnemy;
}

#include "HeartBeat.h"
#include "Debug.h"
void ArcherEnemyAlignWithPlayer(ArcherEnemy* aEnemy);
void ArcherEnemyAttack(ArcherEnemy* aEnemy);
void ArcherEnemyUpdate(ArcherEnemy* aEnemy) {
	Enemy* enemy = (Enemy*)aEnemy;
	// Moving
	if (enemy->state == Tracking) {
		if (SmallBeatCall()) { // after attack cooldown counting!
			enemy->small_beats_after_attack_end++;
		}
		if (enemy->attack_cooldown_small_beats <= enemy->small_beats_after_attack_end) { // cooled down! ready to move!

			Rect attack_detection_rect = {
				.x = aEnemy->base.entity.pos.x - aEnemy->bow_attack_radius,
				.y = aEnemy->base.entity.pos.y - aEnemy->bow_attack_radius,
				.width = aEnemy->bow_attack_radius * 2 + 1,
				.height = aEnemy->bow_attack_radius * 2 + 1
			};
			if (RectContainsPoint(&attack_detection_rect, &player->base.entity.pos) && enemy->player_is_visible) {	// player in arrow range!
				ArcherEnemyAlignWithPlayer(aEnemy);
			}
			else {
				EnemyMoveAsMemory(aEnemy);
			}
		}
	}

	// Attacking
	else if (enemy->state == ReadyToAttack) {
		if (SmallBeatCall()) { // delay counting!
			enemy->small_beats_after_attack_start++;
		}
		if (enemy->attack_delay_small_beats <= enemy->small_beats_after_attack_start) {	// ATTACK!
			ArcherEnemyAttack(aEnemy);
			enemy->small_beats_after_attack_end = 0;
			enemy->state = Tracking;
		}
	}
}

void ArcherEnemyAttack(ArcherEnemy* aEnemy) {
	// TODO: spawn arrow 
	Point arrawSpawnPoint = aEnemy->base.entity.pos;
	PointAdd(&arrawSpawnPoint, &aEnemy->base.enemy.facing);

	CreateParticle(aEnemy->base.enemy.facing, arrawSpawnPoint, 
		EnemyRangeAttackParticleType, aEnemy->base.enemy.attackDamage);
}
void ArcherEnemyAlignWithPlayer(ArcherEnemy* aEnemy) {
	Enemy* enemy = (Enemy*)aEnemy;

	Point delta = { .x = player->base.entity.pos.x - aEnemy->base.entity.pos.x, .y = player->base.entity.pos.y - aEnemy->base.entity.pos.y };

	bool aligned = false;
	Point next_direction;
	if (delta.x == 0 || delta.y == 0) {
		aligned = true;
	}
	else {
		Point abs_delta = { .x = abs(delta.x), .y = abs(delta.y) };

		if (abs_delta.x <= abs_delta.y) { // align x!
			if (delta.x < 0) {
				next_direction = Direction.west;
			}
			else {
				next_direction = Direction.east;
			}
		}
		else { // align y!
			if (delta.y < 0) {
				next_direction = Direction.south;
			}
			else {
				next_direction = Direction.north;
			}
		}
	}
	
	if (aligned) {
		enemy->facing = EnemyDirectionToFacePlayer(aEnemy);
		enemy->small_beats_after_attack_start = 0;
		enemy->state = ReadyToAttack;
	}
	else {
		RayCastResult* check = CreateRayCastResult(enemy->detectionRadius << 1);
		Point next_position = { .x = enemy->base.entity.pos.x + next_direction.x, .y = enemy->base.entity.pos.y + next_direction.y };
		if (RayCastInCurrentWorld(check, next_position, player->base.entity.pos)) { // if player is visible from nextposition
			EnemyMove(aEnemy, next_direction);
		}
		else { // if player is not visible from nextposition
			EnemyMoveAsMemory(aEnemy);
		}
		DeleteRayCastResult(check);
	}
}

