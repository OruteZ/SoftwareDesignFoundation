#include "World.h"
#include "World003.h"
#include "World004.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,
  //1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 10
  //0                10                  20                  30                  40                  50                  60                  70                  80                  90                   100
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
	G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G W W W W G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G G W W W G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
	G G G G G G G G W W W G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
	G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W G G G G G G G G G G
	G G G G G G G G W W W W G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G
	G G G G G G G G G W W W G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W G G G G G G G G W W W W G G G G G G G G G G
	G G G G G G G G G W W W W G G G G W W W W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
	G G G G G G G G G W W W W G G G G W W W W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
	G G G G G G G G G G W W W W G G G W W W W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
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
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W G G G W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G W W W G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G W W W G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G W W W G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
	G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
};

World* world003;

void InitializeWorld003() {
	world003 = CreateWorld(100, 100);
	world003->grid = grid_003;

	Point playerSpawnPoint = { .x = 18, .y = 20 };
	world003->playerSpawnPoint = playerSpawnPoint;

	world003->startNextWorld = &StartWorld004;

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