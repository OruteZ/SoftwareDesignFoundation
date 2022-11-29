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

	int baseDamage;
	int attackWidth;
	int attackHeight;
	double attackSpeed; // attack per second;
	double moveSpeed; // block per second;
} Player;

Player* CreatePlayer(Point spawnPoint);

void PlayerMove(Point dir);

void UpdatePlayer();

Point GetPlayerPos();

void PlayerOnHit(int damage);

int GetScore();