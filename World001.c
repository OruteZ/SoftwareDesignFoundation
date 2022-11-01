#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

Tile grid[] = {
	P P P P P P P W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P P P P P P W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P P P P P P W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P P P P P P W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P W W W W W W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P W G G W W W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	P P W G G W P W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	W W W G G W W W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	W G G G G G G W G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P W G G W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P 
	W G G G G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W 
	W G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	W G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	W G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	W G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	W W W W W W W W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G G G G G G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G G G G G G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G G G G G G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G G G G G G G G G G G W P P W G G G G G G G G G G G G W P P W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G W W W W G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W 
	P P P P P P P P P P P P P P P P P P P P W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W 
};

World* world001;

void InitializeWorld001() {
	world001 = CreateWorld(10, 10);

	world001->grid = grid;
}