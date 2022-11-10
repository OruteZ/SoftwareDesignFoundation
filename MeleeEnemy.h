#pragma once

#include "Mortal.h"

typedef struct _MeleeEnemy {
	union {
		Entity entity;
		Mortal mortal;
	} base;
} MeleeEnemy;