#pragma once

#include "Mortal.h"

typedef struct _BomberEmemy {
	union {
		Entity entity;
		Mortal mortal;
	} base;
} BomberEnemy;
