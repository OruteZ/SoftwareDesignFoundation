#ifdef DEBUG
#include "Debug.h"
#endif // DEBUG

#include <stdlib.h>
#include <stdbool.h>

#include "Game.h"
#include "Time.h"
#include "World.h"
#include "Raycast.h"
#include "HeartBeat.h"

#include "Point.h"
#include "Vector.h"
#include "QuadTree.h"

#include "Entity.h"
#include "Enemy.h"
#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "ExpOrb.h"

void CreateEnemy(enum EntityType type, Point spawnPoint) {
	Enemy* newEnemy = NULL;

	switch (type) {
	case MeleeEnemyType:
		newEnemy = (Enemy*)CreateMeleeEnemy(spawnPoint);
		break;

	case ArcherEnemyType:
		newEnemy = (Enemy*)CreateArcherEnemy(spawnPoint);
		break;

	case BomberEnemyType:
		newEnemy = (Enemy*)CreateBomberEnemy(spawnPoint);
		break;
	default:
		return;
	}

	VectorInsert(enemies, newEnemy);
}
void DeleteEnemy(Enemy* enemy) {
	free(enemy);
}

bool IsEnemyDead(Enemy* enemy) {
	return enemy->hp <= 0;
}
bool IsEnemyFrozen(Enemy* enemy) {
	return GameTime.time <= enemy->is_frozen_until;
}
void EnemyFreezeUntil(Enemy* enemy, double GameTime) {
	enemy->is_frozen_until = enemy->is_frozen_until > GameTime ? enemy->is_frozen_until : GameTime;
}
void EnemyRayCastPlayer(Enemy* enemy) {
	RayCastResult* result = CreateRayCastResult(enemy->detectionRadius * 2);
	Point start = enemy->base.entity.pos;
	Point dest = GetPlayerPos();
	bool success = RayCastInCurrentWorld(result, start, dest);

	if (success) { // raycast 에 성공하면 memory를 새로운 raycast 결과로 바꿔줘야 한다.
		DeleteRayCastResult(enemy->memory);
		enemy->memory = result;
		enemy->memory_current_index = 0;
		enemy->player_is_visible = true;
	}
	else {
		DeleteRayCastResult(result);
		enemy->player_is_visible = false;
	}
}
Point EnemyDirectionToFacePlayer(Enemy* enemy) {
	Point diff = { .x = player->base.entity.pos.x - enemy->base.entity.pos.x, .y = player->base.entity.pos.y - enemy->base.entity.pos.y };
	if (diff.x == 0) {
		if (0 <= diff.y) return Direction.north;
		else return Direction.south;
	}
	else if (diff.x > 0) {
		if (0 < diff.y) return Direction.north;
		else return Direction.east;
	}
	else {
		if (0 <= diff.y)return Direction.west;
		else return Direction.south;
	}
}

void EnemyUpdate(Enemy* enemy) {
	if (IsEnemyDead(enemy)) return;
	Rect detectionRect = {
		.x = enemy->base.entity.pos.x - enemy->detectionRadius,
		.y = enemy->base.entity.pos.y - enemy->detectionRadius,
		.width = enemy->detectionRadius * 2 + 1,
		.height = enemy->detectionRadius * 2 + 1
	};
	if (RectContainsPoint(&detectionRect, &player->base.entity.pos)) { // if within detection range..
		EnemyRayCastPlayer(enemy); // try raycast
		
		// raycast는 enemy가 움직이거나 공격할 수 있는지 여부와 상관없이 시행해야 한다.
	}

	if (IsEnemyFrozen(enemy)) return;
	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		MeleeEnemyUpdate(enemy);
		break;
	case ArcherEnemyType:
		ArcherEnemyUpdate(enemy);
		break;
	case BomberEnemyType:
		BomberEnemyUpdate(enemy);
		break;
	}
}
bool EnemyMove(Enemy* enemy, Point direction) {
	if (GameTime.time <= enemy->cant_move_until) return false;
	Point nextPosition = enemy->base.entity.pos;
	PointAdd(&nextPosition, &direction);
	Point playerPos = GetPlayerPos();

	//Rect nextPositionRect = {
	//	.x = nextPosition->x,
	//	.y = nextPosition->y,
	//	.width = 1,
	//	.height = 1
	//};

	if (GetTile(nextPosition) & FLAG_COLLIDE_WITH_BODY) return false;
	if (PointEquals(&nextPosition, &playerPos)) return false;

	for (int i = 0; i < enemies->length; i++) {
		if (PointEquals(&enemies->entities[i]->pos, &nextPosition)) return false;
	}
	enemy->base.entity.pos = nextPosition;

	enemy->cant_move_until = GameTime.time + 1 / enemy->move_per_second;
	return true;
}
void EnemyMoveAsMemory(Enemy* enemy) {
	const int next_move_index = enemy->memory_current_index + 1;
	if (next_move_index < enemy->memory->length) {
		Point dir = enemy->memory->arr[next_move_index];
		PointSub(&dir, &enemy->base.entity.pos);

		if (EnemyMove(enemy, dir)) { // increment memory only if move is successful
			enemy->memory_current_index++;
		}
	}
}

void EnemyOnDeath(Enemy* enemy)
{
	// special behavor on death
	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		break;
	case ArcherEnemyType:
		break;
	case BomberEnemyType:
		break;
	}

	CreateExpOrb(enemy->base.entity.pos, 10);
}
bool EnemyOnHit(Enemy* enemy, int damage)
{
	if (enemy == NULL) return false;
	enemy->hp -= damage;
	enemy->is_frozen_until = GameTime.time + 0.1;
	
	// special behavior on damage
	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		break;
	case ArcherEnemyType:
		break;
	case BomberEnemyType:
		break;
	}

	if (enemy->hp <= 0)	{
		EnemyOnDeath(enemy);
		return true;
	}
	return false;
}

