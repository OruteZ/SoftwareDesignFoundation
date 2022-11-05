#include "Archer.h"
#include "BomberEnemy.h"
#include "Entity.h"
#include "MeleeEnemy.h"
#include "Mortal.h"
#include "Point.h"
#include "Player.h"

MeleeEnemy* CreateMeleeEnemy(Point p)
{
	MeleeEnemy* meleeEnemy;
	meleeEnemy->base.entity.type = _MeleeEnemy;
	meleeEnemy->base.entity.pos = p.
}