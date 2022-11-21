#pragma once

#include "Entity.h"
#include "Rect.h"

typedef enum _ParticleType {
	AttackParticleType,
} ParticleType;

typedef struct _Paritcle {
	union {
		Entity entity;
	} base;

	//생성시 고정되는 변수
	enum ParticleType particleType;
	Rect particleRect;
	Point facing;

	//생성 이후 변할 수 있는 변수
	char** particleImage;
	double nowTime;
} Particle;

//파티클을 생성합니다. 생성하여서 바로 Vector particles로 들어가 Game.c에서 관리합니다.
//Point는 particle의 중심좌표가 아닌 시작지점을 의미합니다.
void CreateParticle(Point direction, Point point, ParticleType type);

//파티클을 매 프레임마다 갱신합니다. particleChangeTime을 확인하고 특정 시간을 넘어가면
//particleImage가 변합니다. Particle이 시간이 다되어 삭제되었을 경우 True를, 아니면 False를 Return합니다.
bool UpdateParticle(Particle* particle);

//파티클을 삭제합니다. 내부 동적할당을 모두 해제 합니다.
void DeleteParticle(Particle* particle);
