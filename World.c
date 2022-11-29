#include "World.h"

#include <Windows.h>
#include "Point.h"
#include "Entity.h"

World* current_world;
World* void_world;
Tile void_grid[] = { GROUND };

#include "World001.h"
void InitializeWorld() {
	void_world = CreateWorld(1, 1);
	void_world->grid = void_grid;
	void_world->startNextWorld = &StartWorld001;
	SetCurrentWorld(void_world);
}





#ifdef DEBUG
#include "Debug.h"
#endif
#include "Time.h"
#include "Game.h"
#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
SpawnSequence* CreateSpawnSequence(double gameTime) {
	SpawnSequence* seq = (SpawnSequence*)malloc(sizeof(SpawnSequence));
	if (seq == NULL) exit(-1);
	seq->gameTime = gameTime;
	seq->list = CreateVector();
	seq->next = NULL;
}
void SpawnSequenceInsert(SpawnSequence* seq, const int spawn_x, const int spawn_y, const enum EntityType entityType) {
	Entity* entity = (Entity*)malloc(sizeof(Entity));
	if (entity == NULL) exit(-1);
	entity->pos.x = spawn_x;
	entity->pos.y = spawn_y;
	entity->type = entityType;
	VectorInsert(seq->list, entity);
}
void WorldInsertSpawnSequence(World* world, SpawnSequence* seq) {
	if (world->enemySpawnSequence == NULL) world->enemySpawnSequence = seq;
	else {
		SpawnSequence* head = world->enemySpawnSequence;
		SpawnSequence* head_prev = NULL;
		while (head != NULL) { // travel to end of linked list
			head_prev = head;
			head = head->next;
		}
		head_prev->next = seq; // insert
	}
}
void TrySpawnSequence() {
	SpawnSequence* sequence = current_world->currentSpawnSequence;
	if (sequence == NULL) return; // end of linked list! stop spawning!

	if (sequence->gameTime <= GameTime.time) { // time to spawn!
		Vector* list = sequence->list;
		for (int i = 0; i < list->length; i++) {
			CreateEnemy(list->entities[i]->type, list->entities[i]->pos);
			/*
			Entity* enemy;
			switch (list->entities[i]->type) {
			case MeleeEnemyType:
				enemy = CreateMeleeEnemy(list->entities[i]->pos);
				VectorInsert(enemies, enemy);
				break;
			case ArcherEnemyType:
				// todo add ArcherEnemy
				break;
			case BomberEnemyType:
				// todo add BomberEnemy
				break;
			default:
				break;
			}
			*/
		}
		current_world->currentSpawnSequence = sequence->next; // prime next spawn sequence
	}
}




void voidFunc() {
}
World* CreateWorld(const int width, const int height) {
	World* world = (World*)malloc(sizeof(World));
	if (world == NULL) exit(-1);
	world->width = width;
	world->height = height;
	world->grid = NULL;

	world->playerSpawnPoint.x = 0;
	world->playerSpawnPoint.y = 0;

	world->enemySpawnSequence = NULL;
	world->currentSpawnSequence = NULL;

	world->startNextWorld = &voidFunc;
}
void DeleteWorld(World* world) {
	free(world);
}

void SetCurrentWorld(World* world) {
	current_world = world;
}
World* GetCurrentWorld() {
	return current_world;
}

void StartVoidWorld() {
	current_world = void_world;
}
void StartNextWorld() {
	(*current_world->startNextWorld)();

	DeepDeleteVector(enemies);
	DeepDeleteVector(expOrbs);
	DeepDeleteVector(particles);
	enemies = CreateVector();
	expOrbs = CreateVector();
	particles = CreateVector();

	player->base.entity.pos.x = current_world->playerSpawnPoint.x;
	player->base.entity.pos.y = current_world->playerSpawnPoint.y;

	current_world->currentSpawnSequence = current_world->enemySpawnSequence;

	ResetGameTime();
}





BOOLEAN IsPointValidInCurrentWorld(Point p) {
	if (0 <= p.x && p.x < current_world->width &&
		0 <= p.y && p.y < current_world->height) return TRUE;
	else return FALSE;
}
Tile* GetTilePointer(const Point p) {
	return current_world->grid + p.y * current_world->width + p.x;
}





Tile GetTile(const Point p) {
	if (IsPointValidInCurrentWorld(p)) {
		return *GetTilePointer(p);
	}
	else {
		return UNDEFINED_TILE;
	}
}
BOOLEAN SetTile(const Point p, const Tile tile) {
	if (IsPointValidInCurrentWorld(p)) {
		*GetTilePointer(p) = tile;
		return TRUE;
	}
	else return FALSE;
}
