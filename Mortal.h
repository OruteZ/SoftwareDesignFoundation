#pragma once

#include "Entity.h"

typedef struct _Mortal
{
	union {
		Entity entity;
	} base;

	int hp;
	int baseDamage;
	double attackCooldown;
	double moveSpeed;
} Mortal;