#pragma once

#include "Point.h"

#define ENTITY_DEFAULT_POS_X = 0
#define ENTITY_DEFAULT_POS_Y = 0

enum EntityType {
	PlayerType,
	MeleeEnemyType,
	ArcherEnemyType,
	BomberEnemyType,
	ExpOrbType,
	ParticleEffectType
};

typedef struct _Entity {
	enum EntityType type;
	Point pos;
} Entity;
