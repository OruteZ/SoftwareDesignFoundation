#include "World.h"
#include "World004.h"
#include "Boss.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,
  //1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
  //0                10                  20                  30                  40
Tile grid_004[] = {
	W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W 
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W
	W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W
};

World* world004;

#include "Game.h"
void World004Master() {
	
}

void emptyFunc() {
}

void InitializeWorld004() {
	world004 = CreateWorld(30, 30);
	world004->grid = grid_004;

	Point playerSpawnPoint = { .x = 15, .y = 20 };
	world004->playerSpawnPoint = playerSpawnPoint;

	world004->startNextWorld = &emptyFunc;
	world004->worldMaster = &World004Master;
}
void StartWorld004() {
	SetCurrentWorld(world004);

	Point bossPoint = { 15, 15 };
	SpawnBoss(bossPoint);
}