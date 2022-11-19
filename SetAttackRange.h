#pragma once
#include "MeleeEnemy.h"
#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "Time.h"
#include "Game.h"
#include "Rect.h"
void SetMeleeAttackRange(MeleeEnemy* meleeEnemy);
void SetRangeAttackRange(ArcherEnemy* archerEnemy);
void SetBomberAttackRange(BomberEnemy* bomberEnemy);