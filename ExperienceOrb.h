#pragma once

#include "Entity.h"

typedef struct _ExperienceOrb {
	union {
		Entity entity;
	} base;

	int value;
} ExperienceOrb;