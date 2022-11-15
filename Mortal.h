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
} Mortal;