#pragma once

#include "Entity.h"

typedef struct _Resource {
	union {
		Entity entity;
	} base;

	int value;
} Resource;