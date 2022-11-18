#pragma once

#include "Mortal.h"

typedef enum _MoveDirection {
	Left,
	Right,
	Up,
	Down
} direction;

typedef struct _Player {
	union {
		Entity entity;
		Mortal mortal;
	} base;

	// data about unique abilities!
	int exp;
	int level;

	direction headed_direction;

	int attack_width;
	int attack_height;
} Player;

void PlayerMove(direction dir);

void UpdatePlayer();

void PlayerAttack();

Point GetPlayerPos();

void PlayerOnHit(int damage);