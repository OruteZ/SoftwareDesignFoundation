#pragma once

#include "Mortal.h"

typedef struct _ArcherEmemy {
	union {
		Entity entity;
		Mortal mortal;
	} base;

	double arrowSpeed;
} ArcherEnemy;