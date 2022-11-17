#pragma once

#include "Point.h"

#define ENTITY_DEFAULT_POS_X = (0)
#define ENTITY_DEFAULT_POS_Y = (0)

enum EntityType {
	_Player,
	_MeleeEnemy,
	_ArcherEnemy,
	_BomberEnemy,
	_ExperienceOrb,
	_ParticleEffect
};
enum Direction
{
	east,
	west,
	south,
	north
};
enum EnemyStatus{
	Idle,
	Move,
	Attack,
};

typedef struct _Entity {
	enum EntityType type;
	enum Direction direction;
	enum EnemyState enemyState;
	Point pos;
} Entity;
