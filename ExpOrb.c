#include "ExpOrb.h"
#include "Game.h"
#include "Player.h"

ExpOrb* FindOrb(Point p) {
	for (int i = 0; i < expOrbs->length; i++) {
		ExpOrb* orb = (ExpOrb*)expOrbs->entities[i];

		if (PointEquals(&p, &orb->base.entity.pos)) return orb;
	}

	return NULL;
}

void CreateExpOrb(Point p, int exp) {
#ifdef DEBUG
	DebugPrint("Create Exp Orb %d %d", p.x, p.y);
#endif

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

	//º¤ÅÍ »ðÀÔ
	VectorInsert(expOrbs, origin);
}

int GetExp(ExpOrb* orb) {
	orb->isDead = true;
	return orb->experience;
}
