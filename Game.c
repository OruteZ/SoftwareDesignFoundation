#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"

enum _GameState GameState = Menu;

Player* player;
Vector* enemies;
Vector* expOrbs;
Vector* particles;

QuadTree* enemiesTree;
QuadTree* expOrbsTree;
QuadTree* particleTree;

#ifdef DEBUG
Vector* debugVector;
QuadTree* debugTree;
#endif

#include "Enemy.h"
void UpdateEnemies() {
	for (int i = 0; i < enemies->length; i++) {
		EnemyUpdate(enemies->entities[i]);
	}
}
void DeleteDeadEnemies() {
	for (int i = 0; i < enemies->length; i++) {
		Enemy* enemy = enemies->entities[i];

		if (IsEnemyDead(enemy)) {
			VectorDeepDeleteUnstable(enemies, i);
			i--;
		}
	}
}

