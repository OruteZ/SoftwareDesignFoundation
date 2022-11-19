#pragma once

#include "Entity.h"
#include "Rect.h"
typedef struct _Mortal
{
	union {
		Entity entity;
	} base;

	int hp;
	int baseDamage;
	double attackCooldown;
	double moveSpeed;
	Rect *attackRange;
	Rect* playerSearchRange;
} Mortal;

void MortalMove(Mortal* mortal, Point direction);
void EnemyMortalOnHit(Mortal* mortal, int playerDamage);