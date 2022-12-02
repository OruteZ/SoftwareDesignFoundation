#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"
#include "World.h"
#include "Point.h"
#include "Time.h"

#include "Entity.h"
#include "Enemy.h"

#include "Player.h"
#include "Debug.h"

#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"

#include "HeartBeat.h"
#include "Raycast.h"

double baseStiffDuration = 0.3;

bool isEnemyDead(Enemy* enemy);
bool canEnemyAct(Enemy* enemy);
bool isEnemy(Entity* entity);

void LookAt(Enemy* enemy, Point target);
bool IsPlayerInRange(Enemy* enemy);
bool EnemyMove(Enemy* enemy, Point direction);
void EnemyAttack(Enemy* enemy);
void CalEnemyCooldown(Enemy* enemy);
void EnemyRayCastPlayer(Enemy* enemy);

void EnemyRayCastPlayer(Enemy* enemy) {
	RayCastResult* result = CreateRayCastResult(enemy->detectionRadius * 2);
	Point start = enemy->base.entity.pos;
	Point dest = GetPlayerPos();
	bool success = RayCastInCurrentWorld(result, start, dest);

	if (success) { // raycast �� �����ϸ� memory�� ���ο� raycast ����� �ٲ���� �Ѵ�.
		DeleteRayCastResult(enemy->memory);
		enemy->memory = result;
		enemy->memory_current_index = 0;
	}
	else {
		DeleteRayCastResult(result);
	}
}

void LookAt(Enemy* enemy, Point target) {
	int deltaX = target.x - enemy->base.entity.pos.x;
	int deltaY = target.y - enemy->base.entity.pos.y;

	if (abs(deltaX) > abs(deltaY)) {
		if (deltaX < 0) enemy->facing = Direction.west;
		else enemy->facing = Direction.east;
	}

	else {
		if (deltaY < 0) enemy->facing = Direction.south;
		else enemy->facing = Direction.north;
	}
}

bool IsPlayerInRange(Enemy* enemy) {
	Point playerPos = player->base.entity.pos;

	//���ι���
	Rect verticalDetectRect = {
		.x = enemy->base.entity.pos.x - (enemy->attackWidth / 2),
		.y = enemy->base.entity.pos.y - enemy->attackHeight,
		.width = enemy->attackWidth,
		.height = enemy->attackHeight * 2 + 1
	};

	//���ι���
	Rect horizontalDetectRect = {
		.x = enemy->base.entity.pos.x - enemy->attackHeight,
		.y = enemy->base.entity.pos.y - (enemy->attackWidth / 2),
		.width = enemy->attackHeight * 2 + 1,
		.height = enemy->attackWidth
	};

	return (bool)(
		RectContainsPoint(&verticalDetectRect, &playerPos)||
		RectContainsPoint(&horizontalDetectRect, &playerPos)
		);
}

bool EnemyMove(Enemy* enemy, Point direction) {
	Point* nextPosition = DuplicatePoint(&enemy->base.entity.pos);
	Point playerPos = GetPlayerPos();
	PointAdd(nextPosition, &direction);
	Rect nextPositionRect = {
		.x = nextPosition->x,
		.y = nextPosition->y,
		.width = 1,
		.height = 1
	};
	
	//Vector* vector = QuadTreeQuery(enemiesTree, nextPositionRect);

	bool moveSuccess = true;

	if(GetTile(*nextPosition) & FLAG_COLLIDE_WITH_BODY) moveSuccess = false;
	if(PointEquals(nextPosition, &playerPos)) moveSuccess = false;
	for (int i = 0; i < enemies->length; i++) {
		if (PointEquals(&enemies->entities[i]->pos, nextPosition)) {
			moveSuccess = false;
		}

		if (!moveSuccess) break;
	}

	if(moveSuccess) enemy->base.entity.pos = *nextPosition;

	DeletePoint(nextPosition);
	//DeleteVector(vector);

	enemy->actCooldown = enemy->moveSpeed;
	return moveSuccess;
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

bool canEnemyAct(Enemy* enemy) {
	return enemy->actCooldown <= 0;
}

void EnemyAttack(Enemy* enemy) {
	switch (enemy->base.entity.type) {
	case MeleeEnemyType:
		MeleeEnemyAttack((MeleeEnemy*)enemy);
		break;

	case ArcherEnemyType:
		ArcherEnemyAttack((ArcherEnemy*)enemy);
		break;

	case BomberEnemyType:
		BomberEnemyAttack((BomberEnemy*)enemy);
		break;
	}

	enemy->actCooldown = enemy->attackSpeed;
}

void CalEnemyCooldown(Enemy* enemy) {
	enemy->actCooldown--;
	enemy->stiffDuration -= GameTime.deltaTime;
}

void EnemyOnDeath(Enemy* enemy)
{
#ifdef DEBUG
	DebugPrint("Enemy Dead!");
#endif
}

bool EnemyOnHit(Enemy* enemy, int damage)
{
	if (enemy == NULL) return false;
	enemy->hp -= damage;

	if (!isEnemyStiff(enemy)) enemy->stiffDuration = baseStiffDuration;
	

	if (enemy->hp <= 0)	{
		EnemyOnDeath(enemy);
		return true;
	}
	return false;
}

void CreateEnemy(enum EntityType type, Point spawnPoint) {
	Enemy* newEnemy = NULL;

	switch (type) {
	case MeleeEnemyType:
	default:
		newEnemy = (Enemy*)CreateMeleeEnemy(spawnPoint);
		break;

	case ArcherEnemyType:
		newEnemy = (Enemy*)CreateArcherEnemy(spawnPoint);
		break;

	case BomberEnemyType:
		newEnemy = (Enemy*)CreateBomberEnemy(spawnPoint);
		break;
	}

	newEnemy->state = Tracking;
	newEnemy->ReadyToAttack = false;

#ifdef DEBUG
	DebugPrint("%d %d", newEnemy->base.entity.type, type);
#endif
	VectorInsert(enemies, newEnemy);
	//QuadTreeInsert(enemiesTree, newEnemy);
}
void DeleteEnemy(Enemy* enemy) {
	free(enemy);
	*(&enemy) = NULL;
}

void UpdateEnemy(Enemy* enemy) {
	//��Ÿ� ���� ������ �켱 �����ϱ�
	/*
	if (!isEnemyStiff(enemy)) {
		if (IsPlayerInRange(enemy)) {
			LookAt(enemy, GetPlayerPos());
			EnemyAttack(enemy);
		}

		if (canEnemyMove(enemy)) {
			EnemyRayCastPlayer(enemy);
		}
	}
	*/
	Rect detectionRect = {
		.x = enemy->base.entity.pos.x - enemy->detectionRadius,
		.y = enemy->base.entity.pos.y - enemy->detectionRadius,
		.width = enemy->detectionRadius * 2 + 1,
		.height = enemy->detectionRadius * 2 + 1
	};
	if (RectContainsPoint(&detectionRect, &player->base.entity.pos)) { // if within detection range..
		EnemyRayCastPlayer(enemy); // try raycast
		
		// raycast�� enemy�� �����̰ų� ������ �� �ִ��� ���ο� ������� �����ؾ� �Ѵ�.
	}

	if (!SmallBeatCall()) return;

	CalEnemyCooldown(enemy);
	if (isEnemyStiff(enemy)) return;

	if (canEnemyAct(enemy)) {
		if (IsPlayerInRange(enemy)) { // player in attack range!
			LookAt(enemy, GetPlayerPos());
			EnemyAttack(enemy);
		}
		else { // player is NOT in attack range!
			EnemyMoveAsMemory(enemy);
		}
	}

	enemy->ReadyToAttack = IsPlayerInRange(enemy);
}

bool isEnemyDead(Enemy* enemy) {
	return (bool)(enemy->hp <= 0);
}

bool isEnemyStiff(Enemy* enemy) {
	return (bool)(enemy->stiffDuration > 0);
}

bool isEnemy(Entity* entity) {
	enum EntityType type = entity->type;
	return (bool)(MeleeEnemyType <= type && type <= BomberEnemyType);
}

