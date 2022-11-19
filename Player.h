#pragma once

#include "Mortal.h"

typedef struct _Player {
	union {
		Entity entity;
		Mortal mortal;
	} base;

	// data about unique abilities!
	int exp;
	int level;

	Point headed_direction;

	int attack_width;
	int attack_height;
} Player;

void PlayerMove(Point dir);

void UpdatePlayer();

void PlayerAttack();

Point GetPlayerPos();

void PlayerOnHit(int damage);