#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"

enum _GameState GameState = Menu;

Player* player;
Vector* enemies;
Vector* expOrbs;
Vector* particles;

QuadTree* enemiesTree;
QuadTree* expOrbsTree;
QuadTree* particleTree;

#ifdef DEBUG
Vector* debugVector;
QuadTree* debugTree;
#endif

