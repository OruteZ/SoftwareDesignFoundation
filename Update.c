#include "Time.h"
#include "Game.h"

#include "World.h"
#include "HeartBeat.h"

#include "Entity.h"
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "ExpOrb.h"

#include "Menu.h"

#include "Vector.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void UpdateEnemies() {
	for (int i = 0; i < enemies->length; i++) {
		Enemy* enemy = (Enemy*)enemies->entities[i];

		if (isEnemyDead(enemy)) {
			DeleteEnemy(enemy);
			VectorDeleteUnstable(enemies, i);
			i--;
		}

		else {
			UpdateEnemy(enemy);
		}
	}
}
void UpdateParticles() {
	for (int i = 0; i < particles->length; i++) {
		Particle* particle = (Particle*)particles->entities[i];
			if (particle == NULL) {
				VectorDeleteUnstable(particles, i);
				i--;
			}

			else if (particle->isDead) {
				DeleteParticle(particle);
				VectorDeleteUnstable(particles, i);
				i--;
			}

			else {
				UpdateParticle(particle);
			}
	}
}

void Update() {
	UpdateTime();
	UpdateKeyboard();

	if (GameState == Dungeon) {
		TrySpawnSequence();

		UpdateHeartBeat();
		UpdateEnemies();
		UpdateParticles();
		UpdatePlayer();

		if (GetTile(player->base.entity.pos) & FLAG_GOAL) {
			StartNextWorld();
		}

		if (IsPlayerDead()) {
			DeepDeleteVector(enemies);
			DeepDeleteVector(expOrbs);
			DeepDeleteVector(particles);
			free(player);
			GameState = Menu;
			StartGameOverMenu();
		}
	}
	
	if (GameState == Menu) {
		UpdateMenu();
	}
}
