#pragma once

#include "Mortal.h"

typedef enum _MoveDirection {
	Left,
	Right,
	Up,
	Down
} direction;

struct {
	Point north;
	Point south;
	Point east;
	Point west;
} Direction = {
	.north = {.x = 0 , .y = 1},
	.south = {.x = 0 , .y = -1},
	.east = {.x = 1 , .y = 0},
	.west = {.x = -1 , .y = 0}
};

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