#include "World.h"
#include "World003.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

Tile grid_003[] = {
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W W W W W G G W W W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W G G G W W W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W G G G W W W W W W W W G G G G G G G G W W W W W W W W W G G G G G G G G G W W W W W W W W W G G G G G G G W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W G G G W W W W G G G G G G G G G G G G G G G W W W W W W W G G G G G G W W W W W W W G G G G G G G G G G G G G G G W W W W W W W G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W G G G W W G G G G G G G G G G G G G G G G G G G W W W W W W G G G G W W W W W W G G G G G G G G G G G G G G G G G G G W W W W W W W G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G W W G G G W W W W W W W W W W W G G G W W W W W W W W W W W W W W G G W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G W W W G G G W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G W W W W W G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G W W W W G G G W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W W W G G G G G G G G G G G G G G
	G G G G G G G G G G G G W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W G G G G G G G G G G G G G G
	G G G G G G G G G G G W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W W G G G G G G G G G G G G G
	G G G G G G G G G G G W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W W W G G G G G G G G G G G G
	G G G G G G G G G G W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W G G G G G G G G G G G G
	G G G G G G G G G G W W W G W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W W G G G G G G G G G G G
	G G G G G G G G G W W W W G W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W W G G G G G G G G G G G
	G G G G G G G G G W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G W W W G W W W W G G G G G G G G G G
	G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G W W W G W W W W G G G G G G G G G G
	G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G W W W G G W W W G G G G G G G G G G
	G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G G G G G G G W W W G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G G W W W G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G G W W W G G G W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W G G G W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W W G G W W W W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W G G G G G G G G G G
	G G G G G G G G W W W W G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G
	G G G G G G G G G W W W G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W G G G G G G G G W W W W G G G G G G G G G G
	G G G G G G G G G W W W W G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
	G G G G G G G G G W W W W G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
	G G G G G G G G G G W W W W G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
	G G G G G G G G G G W W W W W G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W G G G G W W W W W W G G G G G G G G G G G G
	G G G G G G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W G G G G G G G G G G G G G
	G G G G G G G G G G G G W W W W G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W G G G G G G G G G G G G G
	G G G G G G G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G	G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G W W W W W G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G W W W W W G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G W W W W W G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G G G G W W W W W G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G W W W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G W W W G G G W W W W W W W W G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G W W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G W W W G G G W W W W W W W G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G W W W G G G W W W W W W G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G W W W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W W W G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G W W W W W G G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W W G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G W W W W W G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G W W W W W W W W G G G W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G D G W W G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G W W W W W W W G G G W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G G G W G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G W W W W W W G G G W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G G W G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G W W W G W G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W G G G W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G W W W G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G W W W G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
};

World* world003;

#include "Game.h"
void World003Master() {
	if (GetTile(player->base.entity.pos) & FLAG_GOAL) {
		StartNextWorld();
	}
}

#include "World004.h"
void InitializeWorld003() {
	world003 = CreateWorld(100, 100);
	world003->grid = grid_003;

	Point playerSpawnPoint = { .x = 19, .y = 20 };
	world003->playerSpawnPoint = playerSpawnPoint;

	world003->startNextWorld = &StartWorld004;
	world003->worldMaster = &World003Master;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	WorldInsertSpawnSequence(world003, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	WorldInsertSpawnSequence(world003, seq_2);
}
void StartWorld003() {
	SetCurrentWorld(world003);
}