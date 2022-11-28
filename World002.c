#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

Tile grid_002[] = {
	G W G

};

World* world002;

void InitializeWorld002() {
	world002 = CreateWorld(90, 89);
	world002->grid = grid_002;

	Point playerSpawnPoint = { .x = 4, .y = 13 };
	world002->playerSpawnPoint = playerSpawnPoint;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	WorldInsertSpawnSequence(world002, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	WorldInsertSpawnSequence(world002, seq_2);
}
void StartWorld002() {
	SetCurrentWorld(world002);
	world002->currentSpawnSequence = world002->enemySpawnSequence;
}