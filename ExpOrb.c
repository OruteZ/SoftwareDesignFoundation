#include "ExpOrb.h"
#include "Game.h"
#include "Player.h"
//해당 좌표에 오브가 있는지 찾고 없으면 NULL 반환
ExpOrb* FindOrb(Point p) {
	for (int i = 0; i < expOrbs->length; i++) {
		ExpOrb* orb = (ExpOrb*)expOrbs->entities[i];

		if (PointEquals(&p, &orb->base.entity.pos)) return orb;
	}

	return NULL;
}

void CreateEXPOrb(Point p, int exp) {
	ExpOrb* origin = FindOrb(p);

	if (origin != NULL && origin->isDead == false) {
		origin->experience += exp;
		return;
	}

	//Create
	origin = (ExpOrb*)malloc(sizeof(ExpOrb));
	if (origin == NULL) exit(-1);

	origin->experience = exp;
	origin->isDead = false;

	origin->base.entity.pos = p;
	origin->base.entity.type = ExpOrbType;

	//벡터 삽입
	VectorInsert(expOrbs, origin);
}

int GetExp(ExpOrb* orb) {
	orb->isDead = true;
	return orb->experience;
}
