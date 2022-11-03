#pragma once

#include "Point.h"
#include "Entity.h"

typedef struct _Mortal
{
	Entity base;

	int hp;
	int baseDamage;
	double attackDelay;
	double moveSpeed;
} Mortal;