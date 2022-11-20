#pragma once

#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

enum _GameState {
	Menu,
	Dialogue,
	Dungeon
};

extern enum _GameState GameState;

extern Player* player;
extern Vector* enemies;
extern Vector* expOrbs;

extern QuadTree* enemiesTree;
extern QuadTree* expOrbsTree;

