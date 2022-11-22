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

#define ENEMY_SPAWN_SEQUENCES 1

void InitializeWorld001() {
	world001 = CreateWorld(90, 89);
	world001->grid = grid;
	
	Point playerSpawnPoint = { .x = 4, .y = 13 };
	world001->playerSpawnPoint = playerSpawnPoint;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	SpawnSequenceInsert(seq_1, 13, 5, _MeleeEnemy);
	SpawnSequenceInsert(seq_1, 15, 5, _MeleeEnemy);
	WorldInsertSpawnSequence(world001, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	SpawnSequenceInsert(seq_2, 20, 5, _MeleeEnemy);
	SpawnSequenceInsert(seq_2, 23, 5, _MeleeEnemy);
	SpawnSequenceInsert(seq_2, 26, 5, _MeleeEnemy);
	WorldInsertSpawnSequence(world001, seq_2);
}
void StartWorld001() {
	SetCurrentWorld(world001);
	world001->currentSpawnSequence = world001->enemySpawnSequence;
}