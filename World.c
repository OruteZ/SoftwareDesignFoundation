#include "World.h"

#include <Windows.h>
#include "Point.h"
#include "Entity.h"

World* current_world = NULL;





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
#ifdef DEBUG
		DebugPrint("Trying Spawn!");
#endif
		Vector* list = sequence->list;
		for (int i = 0; i < list->length; i++) {
			Entity* enemy;
			switch (list->entities[i]->type) {
			case _MeleeEnemy:
				enemy = CreateMeleeEnemy(list->entities[i]->pos);
				VectorInsert(enemies, enemy);
				break;
			case _ArcherEnemy:
				// todo add ArcherEnemy
				break;
			case _BomberEnemy:
				// todo add BomberEnemy
				break;
			default:
				break;
			}
		}
		current_world->currentSpawnSequence = sequence->next; // prime next spawn sequence
	}
}





World* CreateWorld(const int width, const int height, const Point playerSpawnPoint) {
	World* world = (World*)malloc(sizeof(World));
	if (world == NULL) exit(-1);
	world->width = width;
	world->height = height;
	world->grid = NULL;

	world->playerSpawnPoint = playerSpawnPoint;
	world->enemySpawnSequence = NULL;
	world->currentSpawnSequence = NULL;
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
