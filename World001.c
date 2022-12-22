#include "World.h"
#include "HeartBeat.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,
  //1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 
  //0                10                  20                  30                  40                  50                  60                  70                  80                  90
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

#include "Game.h"
void World001Master() {
	if (GetTile(player->base.entity.pos) & FLAG_GOAL) {
		StartNextWorld();
	}
}

#include "world002.h"
#include "Time.h"
void InitializeWorld001() {
	ResetCumulativeGameTime();
	world001 = CreateWorld(90, 89);
	world001->grid = grid_001;
	
	Point playerSpawnPoint = { .x = 4, .y = 13 };
	world001->playerSpawnPoint = playerSpawnPoint;

	world001->startNextWorld = &StartWorld002;
	world001->worldMaster = &World001Master;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	SpawnSequenceInsert(seq_1, 14, 5, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 36, 26, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 56, 43, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 67, 43, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 30, 55, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 21, 79, MeleeEnemyType);

	SpawnSequenceInsert(seq_1, 76, 26, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 46, 5, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 67, 69, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 73, 5, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 20, 83, ArcherEnemyType);

	SpawnSequenceInsert(seq_1, 65, 56, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 55, 19, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 70, 83, BomberEnemyType);
	WorldInsertSpawnSequence(world001, seq_1);
}
#include "Game.h"
void StartWorld001() {
	SetCurrentWorld(world001);
	StartBeat();
}