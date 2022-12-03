#include "ArcherEnemy.h"

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
	enemy->base.entity.type = MeleeEnemyType;
	
	enemy->state = Tracking;

	enemy->hp = 100;

	enemy->detectionRadius = 12;
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


	// archer specifics

	return archerEnemy;
}

void ArcherEnemyAttack(ArcherEnemy* archerEnemy) {
	Point attackPoint = archerEnemy->base.entity.pos;
	PointAdd(&attackPoint, &archerEnemy->base.enemy.facing);

	//CreateParticle(archerEnemy->base.enemy.facing, attackPoint, EnemyRangeAttackParticleType, archerEnemy->base.enemy.baseDamage);
}

void ArcherAlignWithPlayer(ArcherEnemy* archerEnemy) {
	
}
void ArcherEnemyUpdate(ArcherEnemy* archerEnemy) {
	//if (!SmallBeatCall()) return;

	//CalEnemyCooldown(archerEnemy);
	//if (isEnemyStiff(archerEnemy)) return;
	//archerEnemy->base.enemy.ReadyToAttack = IsPlayerInRange(archerEnemy);
}

