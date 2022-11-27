#include "World.h"

#define G GROUND,
#define W WALL,
#define P PIT,
#define D DOWNSTAIRS,

<<<<<<< HEAD
Tile grid[] = {


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
G G G G G G G G G G G G G G G W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G W W W W W G G G G G G G G G G G G G G G
G G G G G G G G G G G G G W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W G G G G G G G G G G G G G G
G G G G G G G G G G G G W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W G G G G G G G G G G G G G G
G G G G G G G G G G G W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W W G G G G G G G G G G G G G
G G G G G G G G G G G W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G W W W W W W G G G G G G G G G G G G
G G G G G G G G G G W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W G G G G G G G G G G G G
G G G G G G G G G G W W W G W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W W G G G G G G G G G G G
G G G G G G G G G W W W W G W W W G G G W W W G G G W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G G W W W W W W W G G G G G G G G G G G
G G G G G G G G G W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G W W W G G G G W W W G W W W W G G G G G G G G G G
G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G W W W G G G G W W W G W W W W G G G G G G G G G G
G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G G G G G G G G G G W W W G G G W W W G G G G W W W G G W W W G G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G G G G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G W W W W W W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W G G W W W W W W W W W W G G G W W W G G G G G G G G G W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G W W W G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W W G G G G G G G G G
G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G W W W G G G G G G G G G G
G G G G G G G G W W W W G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G G G G G G W W W G G G G G G G G G G
G G G G G G G G G W W W G G W W W G G G G G G G G G W W W G G G W W W G G G G W W W W W W W W W W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W G G G G G G G G W W W W G G G G G G G G G G
G G G G G G G G G W W W W G W W W W W W W W W W W W W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W G G G G G G G G G W W W G G G W W W W W W W W W W G W W W G G G G G G G G G G G
G G G G G G G G G W W W W G W W W W W W W W W W W W W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
G G G G G G G G G G W W W W W W W W W W W W W W W W W W W G G G W W W G G G G G G G G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G
G G G G G G G G G G W W W W W G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W W W W W W W G G G W W W G G G W W W G G G G W W W W W W G G G G G G G G G G G G
G G G G G G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W G G G G G G G G G G G G G
G G G G G G G G G G G G W W W W G G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G W W W W G G G G G W W W G G G W W W G G G W W W G G G W W W G G G G W W W W W G G G G G G G G G G G G G
G G G G G G G G G G G G G W W W W G G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G W W G G G G G G W W W G G G W W W G G G W W W G G G W W W G G G W W W W W G G G G G G G G G G G G G G
G G G G G G G G G G G G G G W W W W G G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G G W W W W W G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G W W W W W G W W W G G G W W W G G G W W W G G G G W W W G G G G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G W W W G W W W W W G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G W W W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G W W W W W W W W G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G W W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G W W W W W W W G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G W W W W W G G G W W W G G G W W W G G G G W W W W W W W W W W W W W W W W W W W W W G G G W W W G G G W W W G G G W W W W W W G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G W W W W G G G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W W W G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G W W W W W G G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W W G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G W W W W W G W W W G G G W W W G G G G G G G G G G G G G W W W G G G G G G G G G G G G W W W G G G W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G W W W W W W W W G G G W W W W G W G W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G G G W W G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G W W W W W W G G G W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G W W W W W W G G G W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W W W W W G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G W G W G G W G G G G G G G G G G W G G G G G W W W W W W G G G G G G G G W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W W W W W W W W W W W W W W G G G W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G G G G G G G G G G G G G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W G G G W W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W W G G G W W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W W W W W W G G G W W W W W W W W W W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G G W W W G G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G G W W W G G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G G W W W G G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G W W W W G G G W W W G G W W W W W G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G
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




=======
Tile grid_003[] = {
	G W G
>>>>>>> 51168a74c01d1aa2873c77c65972a74c2ae50ae8
};

World* world003;

void InitializeWorld003() {
<<<<<<< HEAD
	world003 = CreateWorld(100, 100);
	world003->grid = grid;
=======
	world003 = CreateWorld(90, 89);
	world003->grid = grid_003;
>>>>>>> 51168a74c01d1aa2873c77c65972a74c2ae50ae8

	Point playerSpawnPoint = { .x = 19, .y = 20 };
	world003->playerSpawnPoint = playerSpawnPoint;

	// spawn at Gametime.time >= 0
	SpawnSequence* seq_1 = CreateSpawnSequence(0);
	WorldInsertSpawnSequence(world003, seq_1);

	// spawn at GameTime.time >= 60.0
	SpawnSequence* seq_2 = CreateSpawnSequence(60);
	WorldInsertSpawnSequence(world003, seq_2);
}
void StartWorld003() {
	SetCurrentWorld(world003);
	world003->currentSpawnSequence = world003->enemySpawnSequence;
}