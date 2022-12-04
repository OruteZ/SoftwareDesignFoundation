#include "Time.h"
#include "Game.h"

#include "World.h"
#include "HeartBeat.h"

#include "Entity.h"
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "ExpOrb.h"
#include "Boss.h"

#include "Menu.h"

#include "Vector.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
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
void UpdateExpOrbs() {
	for (int i = 0; i < expOrbs->length; i++) {
		ExpOrb* e = (ExpOrb*)expOrbs->entities[i];

		if (e == NULL) {
			VectorDeleteUnstable(expOrbs, i);
			i--;
		}

		else if (e->isDead) {
			free(e);
			VectorDeleteUnstable(expOrbs, i);
			i--;
		}
	}
}

void Update() {
	UpdateTime();
	UpdateKeyboard();

	if (GameState == Dungeon) {
		TrySpawnSequence();

		UpdateHeartBeat();
		UpdatePlayer();
		UpdateEnemies();
		UpdateParticles();
		UpdateExpOrbs();
		UpdateBoss();

		DeleteDeadEnemies();

		TryWorldMaster();

		if (IsPlayerDead()) {
			free(player);
			Point pointless = { .x = 0, .y = 0 };
			player = CreatePlayer(pointless);

			GameState = Menu;
			StartVoidWorld();
			StartGameOverMenu();
			PlaySound(NULL, NULL, SND_ASYNC);
		}

		if (IsBossCleared()) {
			free(player);
			Point pointless = { .x = 0, .y = 0 };
			player = CreatePlayer(pointless);

			GameState = Menu;
			StartVoidWorld();
			StartGameClearMenu();
			PlaySound(NULL, NULL, SND_ASYNC);
		}
	}
	
	if (GameState == Menu) {
		UpdateMenu();
	}

	if (GameState == UpgradeMenu) {
		UpdateUpgradeUI();
	}
}
