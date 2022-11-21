#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"

enum _GameState GameState = Menu;

Player* player;
Vector* enemies;
Vector* expOrbs;

QuadTree* enemiesTree;
QuadTree* expOrbsTree;

#ifdef DEBUG
Vector* debugVector;
QuadTree* debugTree;
#endif

