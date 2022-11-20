#pragma once

#include "Entity.h"

typedef struct _Player {
	union {
		Entity entity;
	} base;
	Point facing;

	int hp;

	int level;
	int exp;

	int base_damage;
	int attack_width;
	int attack_height;
} Player;

void PlayerMove(Point dir);

void UpdatePlayer();

void PlayerAttack();

Point GetPlayerPos();

void PlayerOnHit(int damage);