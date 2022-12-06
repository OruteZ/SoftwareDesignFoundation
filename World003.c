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

	Point playerSpawnPoint = { .x = 18, .y = 20 };
	world003->playerSpawnPoint = playerSpawnPoint;

	world003->startNextWorld = &StartWorld004;
	world003->worldMaster = &World003Master;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	SpawnSequenceInsert(seq_1, 18, 32, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 12, 38, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 30, 35, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 31, 23, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 58, 27, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 30, 52, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 33, 70, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 46, 78, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 36, 53, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 68, 62, MeleeEnemyType);
	SpawnSequenceInsert(seq_1, 73, 55, MeleeEnemyType);

	SpawnSequenceInsert(seq_1, 18, 44, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 25, 56, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 60, 27, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 47, 70, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 45, 57, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 52, 51, ArcherEnemyType);
	SpawnSequenceInsert(seq_1, 73, 57, ArcherEnemyType);

	SpawnSequenceInsert(seq_1, 16, 53, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 79, 37, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 83, 49, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 67, 21, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 49, 89, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 55, 49, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 54, 63, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 62, 70, BomberEnemyType);
	SpawnSequenceInsert(seq_1, 73, 61, BomberEnemyType);
	WorldInsertSpawnSequence(world003, seq_1);
}
void StartWorld003() {
	SetCurrentWorld(world003);
}