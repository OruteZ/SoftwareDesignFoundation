#pragma once

#include "Mortal.h"

typedef struct _Player {
	union {
		Entity entity;
		Mortal mortal;
	} base;

	// data about unique abilities!
} Player;