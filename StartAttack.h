#pragma once
#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "Time.h"
#include "Game.h"
#include "Rect.h"
double StartMeleeAttack(MeleeEnemy* meleeEnemy);
double StartRangeAttack(ArcherEnemy* archerEnemy);
double StartBomberAttack(BomberEnemy* bomberEnemy);