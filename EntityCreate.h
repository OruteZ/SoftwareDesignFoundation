#pragma once
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "Entity.h"
#include "MeleeEnemy.h"
#include "Mortal.h"
#include "Point.h"
#include "Player.h"

MeleeEnemy* CreateMeleeEnemy(Point p);
ArcherEnemy* CreateArcherEnemy(Point p);
BomberEnemy* CreateBomberEnemy(Point p);
Player* CreatePlayer(Point p);