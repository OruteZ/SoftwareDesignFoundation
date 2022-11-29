#include "Time.h"
#include "Keyboard.h"

#include "Game.h"


#include "Game.h"
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector.h"
#include "Entity.h"
#include "Menu.h"
#include "World.h"
#include "HeartBeat.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#include "RayCast.h"
#endif
void UpdateEnemies() {
	int len = enemies->length;
	for (int i = 0; i < len; i++) {
		Enemy* enemy = (Enemy*)enemies->entities[i];

		if (isEnemyDead(enemy)) {
			//DeleteEnemy(enemy)
			VectorDeleteUnstable(enemies, i);
		}

		else {
			UpdateEnemy(enemy);
		}
	}
}
void UpdateParticles() {
	int len = particles->length;
	for (int i = 0; i < len; i++) {
		Particle* particle = (Particle*)particles->entities[i];

		if (particle->isDead) {
			VectorDeleteUnstable(particles, i);
			DeleteParticle(particle);
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

#ifdef DEBUG
	if (GetKeyDown('R')) {
		RayCastResult* result = CreateRayCastResult(10);
		Point origin = { .x = 17, .y = 8 };
		Point destination = { .x = 21, .y = 7 };
		bool success = RayCastInCurrentWorld(result, origin, destination);
		DebugPrint("RayCast Successful?: %d, length: %d", success, result->length);
		for (int i = 0; i < result->length; i++) {
			DebugPrint("RayCast Block: (%d, %d)", result->arr[i].x, result->arr[i].y);
		}
		DeleteRayCastResult(result);
	}
#endif
}
