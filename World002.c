#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

<<<<<<< HEAD
Tile grid[] = {
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
=======
Tile grid_002[] = {
	G W G

>>>>>>> 51168a74c01d1aa2873c77c65972a74c2ae50ae8
};

World* world002;

void InitializeWorld002() {
<<<<<<< HEAD
	world002 = CreateWorld(50, 50);
	world002->grid = grid;
=======
	world002 = CreateWorld(90, 89);
	world002->grid = grid_002;
>>>>>>> 51168a74c01d1aa2873c77c65972a74c2ae50ae8

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