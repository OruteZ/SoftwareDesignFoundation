#pragma once

#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

enum _GameState {
	Menu,
	Dialogue,
	Dungeon,
	Exiting,
	UpgradeMenu,
};

extern enum _GameState GameState;

extern Player* player;
extern Vector* enemies;
extern Vector* expOrbs;
extern Vector* particles;

extern QuadTree* enemiesTree;
extern QuadTree* expOrbsTree;
extern QuadTree* particleTree;

#ifdef DEBUG
extern Vector* debugVector;
extern QuadTree* debugTree;
#endif

