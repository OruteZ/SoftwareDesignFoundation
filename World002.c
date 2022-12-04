#include "World.h"
#include "World002.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,
  //1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
  //0                10                  20                  30                  40                  50
Tile grid_002[] = {
	W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G W W W W W W G G G G G G G G G W W W W G G G G G G G G G G W W W W W G G G G G G G W
	W G G G G G G G W P P P P W G G G G G G G G G W P P W G G G G G G G G G G W P P P W G G G G G G G W
	W G G G G G G G W P P P P W G G G G G G G G G W P P W G G G G G G G G G G W P P P W G G G G G G G W
	W G G G G G G G W P P P P W G G G G G G G G G W P P W G G G G G G G G G G W P P P W G G G G G G G W
	W G G G G G G G W W W W W W G G G G G G G G G W W W W G G G G G G G G G G W W W W W G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G W W W W G G G G G G G G G G W W W W G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G W P P W G G G G G G G G G G W P P W G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G W P P W G G G G G G G G G G W P P W G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G W P P W G G G G G G G G G G W P P W G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G W W W W G G G G G G G G G G W W W W G G G G G G G G G G G G G G G W
	W G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G W
	W G G G G W P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G G G W
	W G G G G W P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G G G W
	W G G G G W P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G G G W
	W W W W W W W W W W G G G W W W W W W W W W W G G G G W W W W W W W W W W G G G W W W W W W W W W W
	W W W W W W W W W W G G G W W W W W W W W W W G G G G W W W W W W W W W W G G G W W W W W W W W W W
	W W W W W W W W W W G G G W W W W W W W W W W G G G G W W W W W W W W W W G G G W W W W W W W W W W
	W W W W W W W W W W G G G W W W W W W W W W W G G G G W W W W W W W W W W G G G W W W W W W W W W W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W G G G G G G G W G G G G G G G G G G G W G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W G D G G G G G W G G G G G G G G G G G W G G G G G G G G G G W
	W G G G G G G G G G W W G G G G G G W G G G G G G G W G G G G G G G G W W W W G G G G G G G G G G W
	W G G G G G G G W W W W W W G G G G W W W W W W W W W G G G G G G W W W W W G G G G G G G G G G G W
	W G G G G G G W W P P P P W W G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G W
	W G G G G G G W P P P P P P W G G G G G G G G G G G G G G G G G G G W W G G G G G G G G G G G G G W
	W G G G G G G W P P P P P P W G G G G G G G G G G G G G G G G G G G W W G G G G G G G G G G G G G W
	W G G G G G G W P P P P P P W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G W
	W G G G G G G W W P P P P W W G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G W
	W G G G G G G W W W P P W W W G G G G G G W W W W W W W G G G G G G G W W W G G G G G G G G G G G W
	W G G G G G G G W W W W W W G G G G G G W W W W W W W W W G G G G G G G W W W G G G G G G G G G G W
	W G G G G G G G G G W W G G G G G G G G G G G G G G G W W G G G G G G G G W W G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G W W G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G W G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G W W G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W
};

World* world002;

const Point door = { .x = 25, .y = 29 };
bool door_open = false;

#include "Game.h"
void World002Master() {
	if (!door_open) {
		if (enemies->length <= 0) {
			door_open = true;
			SetTile(door, GROUND);
		}
	}

	if (door_open) {
		if (GetTile(player->base.entity.pos) & FLAG_GOAL) {
			StartNextWorld();
		}
	}
}

#include "World003.h"
void InitializeWorld002() {
	world002 = CreateWorld(50, 50);
	world002->grid = grid_002;

	Point playerSpawnPoint = { .x = 25, .y = 25 };
	world002->playerSpawnPoint = playerSpawnPoint;

	world002->startNextWorld = &StartWorld003;
	world002->worldMaster = &World002Master;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	SpawnSequenceInsert(seq_1, 25, 20, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 25, 29, MeleeEnemyType);
	WorldInsertSpawnSequence(world002, seq_1);

	// spawn at GameTime.time >= 30.0
	SpawnSequence* seq_2 = CreateSpawnSequence(30);	

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_3 = CreateSpawnSequence(60);
	WorldInsertSpawnSequence(world002, seq_3);
}
void StartWorld002() {
	door_open = false;
	SetTile(door, WALL);
	SetCurrentWorld(world002);
}