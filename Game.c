#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"

enum _GameState GameState = Menu;

Player* player;
Vector* mortals;
Vector* expOrbs;

QuadTree* mortalsTree;
QuadTree* expOrbsTree;

