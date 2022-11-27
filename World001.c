#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

Tile grid_001[] = {
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
	P P P P P P P P P P P P P P P P P P P P W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W G G G W G G G G G W W W W W W W W W W W W W W W W W W W W W 
	P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P 
	P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P P 
	P P P P P P P P P P P P P P P P W W W W W W W W W P P P P P P P P P P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P P P P P 
	P P P P P P P P P P P P P P P W W G G G G G G G W W W W P P P P P P P P P P P P P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P P P 
	P P P P P P P P P P W W W W W W G G G G G G G G G G G W W W W W W W W W P P P P P P P W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P P P P 
	P P P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P P P 
	P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P P 
	P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P 
	P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P 
	P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P 
	P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P 
	P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P 
	P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G W P P P P P P P P P 
	P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G W W P P P P P P P P 
	P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G W P P P P P P P P 
	P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P 
	P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P 
	P W G G G G G G G G G G G G G W W W W W W G G G G G G G G G G G G G G G W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P 
	W W G G G G G G G W W W W W W W P P P P W G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P 
	W G G G G G G W W W P P P P P P P P P P W G G G G G G G G G G G G G G G W P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P 
	W G G G G G W W P P P P P P P P P P P P W W G G G G G G G G G G G G G G W P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P 
	W G G G G W W P P P P P P P P P P P P P P W G G G G G G G G G G G G G G W P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P 
	W G G G G W P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G W P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P 
	W G G G W W P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G W P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P 
	W G G G W P P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G W P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P 
	W G G G W P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G W W P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P 
	W W G W W P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G W P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P 
	P W W W P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G W P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P 
	P P P P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G W P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P 
	P P P P P P P P P P P P P P P W W W G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P 
	P P P P P P P P P P P P W W W W G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P 
	P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P W W G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G W P 
	P P P P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G W P 
	P P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G G G W P 
	P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P 
	P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P 
	P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P 
	P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P 
	P P P P P W G G G D G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P 
	P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W P P P P P P P P P P P P P P W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W P P P P 
	P P P P P P W W W G G G G G G G G G G G G G G G G G G G G G G G G G W W W P P P P P P P P P P P P P P P W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W P P P P P 
	P P P P P P P P W W W W W W G G G G G G G G G G G G G G G G G G G W W P P P P P P P P P P P P P P P P P W W W W W W W W W W G G G G G G G G G G G G G G G G G G G W W P P P P P P P 
	P P P P P P P P P P P P P W W W W G G G G G G G G G G G G G G W W W P P P P P P P P P P P P P P P P P P P P P P P P P P P W W W W W W W W W W G G G G G G G W W W W P P P P P P P P 
	P P P P P P P P P P P P P P P P W W W W W W W W W W W W W W W W P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P P W W W W W W W W W P P P P P P P P P P P 
};

World* world001;

#include "world002.h"
void InitializeWorld001() {
	world001 = CreateWorld(90, 89);
	world001->grid = grid_001;
	
	Point playerSpawnPoint = { .x = 4, .y = 13 };
	world001->playerSpawnPoint = playerSpawnPoint;

	world001->startNextWorld = &StartWorld002;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	SpawnSequenceInsert(seq_1, 13, 5, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 15, 5, MeleeEnemyType);
	WorldInsertSpawnSequence(world001, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	SpawnSequenceInsert(seq_2, 20, 5, MeleeEnemyType);
	SpawnSequenceInsert(seq_2, 23, 5, MeleeEnemyType);
	SpawnSequenceInsert(seq_2, 26, 5, MeleeEnemyType);
	WorldInsertSpawnSequence(world001, seq_2);
}
#include "Game.h"
void StartWorld001() {
	SetCurrentWorld(world001);
	
	player->base.entity.pos.x = world001->playerSpawnPoint.x;
	player->base.entity.pos.y = world001->playerSpawnPoint.y;

	world001->currentSpawnSequence = world001->enemySpawnSequence;
}