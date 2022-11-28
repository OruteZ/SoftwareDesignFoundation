#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

Tile grid_003[] = {
	G W G
};

World* world003;

void InitializeWorld003() {
	world003 = CreateWorld(90, 89);
	world003->grid = grid_003;

	Point playerSpawnPoint = { .x = 4, .y = 13 };
	world003->playerSpawnPoint = playerSpawnPoint;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	WorldInsertSpawnSequence(world003, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	WorldInsertSpawnSequence(world003, seq_2);
}
void StartWorld003() {
	SetCurrentWorld(world003);
	world003->currentSpawnSequence = world003->enemySpawnSequence;
}