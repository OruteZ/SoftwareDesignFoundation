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

//오브 내부에 저장 된 경험치를 반환합니다.
//함수가 끝나면 orb는 삭제처리 됩니다.
int GetExp(ExpOrb* orb);