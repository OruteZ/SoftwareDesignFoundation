#include "Particle.h"
#include "Time.h"
#include "Game.h"
#include "Vector.h"

#include "World.h"

//MeleeAttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect _baseMeleeAttackParticleRect = { 0,0,3,1 };
const double _meleeAttackParticleUpdateTime = 0.05f;
const double _meleeAttackParticleDuration= 0.15f;
const char _meleeAttackParticleChar = '◈';
void InitMeleeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //위 아래 바라보는 방향 -> 범위 변함 없음
		particle->particleRect.height = _baseMeleeAttackParticleRect.height;
		particle->particleRect.width = _baseMeleeAttackParticleRect.width;
	}
	else { //좌우 바라보는 방향 -> 가로세로 교환
		particle->particleRect.height = _baseMeleeAttackParticleRect.width;
		particle->particleRect.width = _baseMeleeAttackParticleRect.height;
	}
}
void InitMeleeAttackParticleImage(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		for (int j = 0; j < particle->particleRect.width; j++) {
			particle->particleImage[i][j] = ' ';
		}
	}
}
void UpdateMeleeAttackParticle(Particle* particle) {
	particle->nowTime += Time.deltaTime;
	if (particle->nowTime >= _meleeAttackParticleDuration) {
		particle->isDead = true;
		return;
	}

	int index = (int)(particle->nowTime / _meleeAttackParticleUpdateTime);

	//임시
	if (index > 2) return;

	if (particle->facing.x == 0) { //상하
		for (int i = 0; i < particle->particleRect.width; i++) {
			if (i == index) particle->particleImage[0][i] = _meleeAttackParticleChar;
			else particle->particleImage[0][i] = ' ';
		}
	}
	else {
		for (int i = 0; i < particle->particleRect.height; i++) {
			if (i == index) particle->particleImage[i][0] = _meleeAttackParticleChar;
			else particle->particleImage[i][0] = ' ';
		}
	}
}
//-------------------------------------------------------------------------------------------------------

//RangeAttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect _baseRangeAttackParticleRect = { 0, 0, 1, 1 };
const double _rangeAttackParticleMoveSpeed = 0.05f; //Time per block
const char _rangeAttackParticleChar = 'a';

void RangeAttackParticleMove(Particle* particle) {
	Point destination = particle->base.entity.pos;
	PointAdd(&destination, &particle->facing);

	//detection collision
	if (0) { //collision with enemy

	}
	else if (GetTile(destination) & FLAG_COLLIDE_WITH_PHYSICAL_ATTACK) { // collision with else somthing
		particle->isDead = true;
		return;
	}

	particle->base.entity.pos = destination;
	particle->particleRect.x = destination.x;
	particle->particleRect.y = destination.y;
}
void InitRangeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //위 아래 바라보는 방향 -> 범위 변함 없음
		particle->particleRect.height = _baseRangeAttackParticleRect.height;
		particle->particleRect.width = _baseRangeAttackParticleRect.width;
	}
	else { //좌우 바라보는 방향 -> 가로세로 교환
		particle->particleRect.height = _baseRangeAttackParticleRect.width;
		particle->particleRect.width = _baseRangeAttackParticleRect.height;
	}
}
void InitRangeAttackParticleImage(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		for (int j = 0; j < particle->particleRect.width; j++) {
			particle->particleImage[i][j] = '1';
		}
	}
}
void UpdateRangeAttackParticle(Particle* particle) {
	particle->nowTime += Time.deltaTime;

	if (particle->nowTime >= _rangeAttackParticleMoveSpeed) {
		RangeAttackParticleMove(particle);
		particle->nowTime = 0;
	}
}
//---------------------------------------------------------------------------------------------------------

void CreateParticle(Point direction, Point point, ParticleType type)
{
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	switch (type) {
	case MeleeAttackParticleType:
		InitMeleeAttackParticleRect(particle, direction);
		break;
	case RangeAttackParticleType:
		InitRangeAttackParticleRect(particle, direction);
		break;
	}

	Point startPoint = {
		point.x - (particle->particleRect.width / 2),
		point.y - (particle->particleRect.height / 2)
	};

	particle->base.entity.pos = startPoint;
	particle->base.entity.type = ParticleEffectType;

	particle->particleRect.x = startPoint.x;
	particle->particleRect.y = startPoint.y;

	particle->nowTime = 0;
	particle->particleType = type;
	particle->facing = direction;
	particle->isDead = false;

	particle->particleImage = (char**)malloc(sizeof(char*) * particle->particleRect.height);
	for (int i = 0; i < particle->particleRect.height; i++) {
		particle->particleImage[i] = (char*)malloc(sizeof(char*) * particle->particleRect.width);
	}

	switch (type) {
	case MeleeAttackParticleType:
		InitMeleeAttackParticleImage(particle);
		break;
	case RangeAttackParticleType:
		InitRangeAttackParticleImage(particle);
		break;
	}

	VectorInsert(particles, (Entity*)particle);
}

void DeleteParticle(Particle* particle) {
	if (!(particle->isDead)) return;

	for (int i = 0; i < particle->particleRect.height; i++) {
		if(particle->particleImage != NULL) 
			(particle->particleImage[i]);
	}
	free(particle->particleImage);
	free(particle);
}

void UpdateParticle(Particle* particle) {
	if (particle->isDead) return;

	switch (particle->particleType) {
	case MeleeAttackParticleType:
		UpdateMeleeAttackParticle(particle);
		return;
	case RangeAttackParticleType:
		UpdateRangeAttackParticle(particle);
		return;
	}
}
