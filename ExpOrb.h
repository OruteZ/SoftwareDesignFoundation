#pragma once

#include "Entity.h"

typedef struct ExpOrb {
	union {
		Entity entity;
	}base;

	int experience;

	bool isDead;
} ExpOrb;


//exp 만큼 경험치를 부여하는 경험치 오브를 생성 합니다.
//동일 좌표에 이미 오브가 있을 경우 해당 오브에 경험치 값을 더합니다.
//생성 즉시 벡터에 삽입합니다.
void CreateEXPOrb(Point p, int exp);

//오브 내부에 저장 된 경험치만큼 플레이어에게 경험치를 부여합니다.
void GetEXP(ExpOrb* orb);