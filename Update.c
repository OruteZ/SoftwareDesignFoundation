#include "Time.h"
#include "Keyboard.h"

#include "Game.h"


#include "Game.h"
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector.h"
#include "Entity.h"
#include "World.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
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
			//UpdateEnemy(enemy);
		}
	}
}
void UpdateParticles() {
	int len = particles->length;
	for (int i = 0; i < len; i++) {
		Particle* particle = (Particle*)particles->entities[i];

		if (particle->isDead) {
			DeleteParticle(particle);
			VectorDeleteUnstable(particles, i);
		}

		else {
			UpdateParticle(particle);
		}
	}
}

void Update() {
	UpdateTime();
	UpdateKeyboard();

	UpdateEnemies();
	UpdateParticles();
	UpdatePlayer();

	TrySpawnSequence();

#ifdef DEBUG
	if (GetKeyDown('P')) {
		DebugPrint("GameTime.time = %.3f", GameTime.time);
	}
#endif
}
