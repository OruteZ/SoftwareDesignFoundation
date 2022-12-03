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


	bomberEnemy->attack_radius = 1;

	return bomberEnemy;
}

void BomberEnemyUpdate() {

}

//void BomberEnemyAttack(BomberEnemy* bomberEnemy) {
//	Point attackPoint = bomberEnemy->base.entity.pos;
//
//	//바라보는 방향에 따라 공격범위 rect 지정
//	Rect attackRect = {
//		.x = attackPoint.x - (bomberEnemy->base.enemy.attackWidth / 2),
//		.y = attackPoint.y - (bomberEnemy->base.enemy.attackHeight / 2),
//		.width = bomberEnemy->base.enemy.attackWidth,
//		.height = bomberEnemy->base.enemy.attackHeight * 3
//	};
//
//	CreateParticle(bomberEnemy->base.enemy.facing, bomberEnemy->base.entity.pos, ExplosionParticleType1, bomberEnemy->base.enemy.baseDamage);
//	//플레이어 피격 확인
//	Point playerPos = GetPlayerPos();
//	if (RectContainsPoint(&attackRect, &playerPos)) {
//		PlayerOnHit(bomberEnemy->base.enemy.baseDamage);
//	}
//
//	bomberEnemy->base.enemy.hp = -1;
//	bomberEnemy->base.enemy.actCooldown = 10000;
//
//#ifdef DEBUG
//	DebugPrint("Enemy Attacked");
//#endif
//}

