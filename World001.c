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

void InitializeWorld001() {
	world001 = CreateWorld(90, 89);
	world001->grid = grid;
}