#pragma once

#include "Point.h"

#define ENTITY_DEFAULT_POS_X = (0)
#define ENTITY_DEFAULT_POS_Y = (0)

enum EntityType {
	_Player,
	_MeleeEnemy,
	_ArcherEnemy,
	_BomberEnemy,
	_Experience,
	_ParticleEffect
};

enum EnemyStatus{
	_Idle,
	_IsMove,
	_IsAttack,
	_DelayAttack
};

typedef struct _Entity {
	enum EntityType type;
	Point pos;
} Entity;
