#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

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
	W G G G G G G G G G G G G G G G G G W P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W P P P P P P P W G G G G G G G G G G G W G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G W P P P P P P P W G G G G G G G G G G G W G G G G G G G G G G W
	W G G G G G G G G G W W G G G G G G W P P P P P P P W G G G G G G G G W W W W G G G G G G G G G G W
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

void InitializeWorld002() {
	world002 = CreateWorld(90, 89);
	world002->grid = grid_002;

	Point playerSpawnPoint = { .x = 25, .y = 25 };
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