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
extern Vector* mortals;
extern Vector* expOrbs;

extern QuadTree* mortalsTree;
extern QuadTree* expOrbsTree;

