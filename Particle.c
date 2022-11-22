#include "Particle.h"
#include "Time.h"
#include "Game.h"
#include "Vector.h"

//AttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect _baseAttackParticleRect = { 0,0,3,1 };
const double _AttackParticleUpdateTime = 0.05f;
const double _AttackParticleDuration = 0.15f;
const char _AttackParticleChar = '◈';
void InitAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //위 아래 바라보는 방향 -> 범위 변함 없음
		particle->particleRect.height = _baseAttackParticleRect.height;
		particle->particleRect.width = _baseAttackParticleRect.width;
	}
	else { //좌우 바라보는 방향 -> 가로세로 교환
		particle->particleRect.height = _baseAttackParticleRect.width;
		particle->particleRect.width = _baseAttackParticleRect.height;
	}
}
void UpdateAttackParticle(Particle* particle) {
	particle->nowTime += Time.deltaTime;
	if (particle->nowTime >= _AttackParticleDuration) return;
	
	int index = (int)(particle->nowTime / _AttackParticleUpdateTime);

	//임시
	if (index > 2) return;

	if (particle->facing.x == 0) { //상하
		for (int i = 0; i < particle->particleRect.width; i++) {
			if (i == index) particle->particleImage[0][i] = _AttackParticleChar;
			else particle->particleImage[0][i] = ' ';
		}
	}
	else {
		for (int i = 0; i < particle->particleRect.height; i++) {
			if (i == index) particle->particleImage[i][0] = _AttackParticleChar;
			else particle->particleImage[i][0] = ' ';
		}
	}
}
bool IsAttackParticleFinished(Particle* particle) {
	return (bool)(particle->nowTime >= _AttackParticleDuration);
}

void CreateParticle(Point direction, Point point, ParticleType type)
{
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	switch (type) {
	case AttackParticleType:
		InitAttackParticleRect(particle, direction);
		break;
	}

	Point startPoint = {
		point.x - (particle->particleRect.width / 2),
		point.y - (particle->particleRect.height / 2)
	};

	particle->base.entity.pos = startPoint;
	particle->base.entity.type = _ParticleEffect;

	particle->particleRect.x = startPoint.x;
	particle->particleRect.y = startPoint.y;

	particle->nowTime = 0;
	particle->particleType = type;
	particle->facing = direction;

	particle->particleImage = (char**)malloc(sizeof(char*) * particle->particleRect.height);
	for (int i = 0; i < particle->particleRect.height; i++) {
		particle->particleImage[i] = (char*)malloc(sizeof(char*) * particle->particleRect.width);
	}
	for (int i = 0; i < particle->particleRect.height; i++) {
		for (int j = 0; j < particle->particleRect.width; j++) {
			particle->particleImage[i][j] = ' ';
		}
	}

	VectorInsert(particles, (Entity*)particle);
}

void DeleteParticle(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		free(particle->particleImage[i]);
	}
	free(particle->particleImage);
	free(particle);
}

bool IsParticleFinished(Particle* particle)
{
	switch (particle->particleType) {
	case AttackParticleType: return IsAttackParticleFinished(particle);
	}
}

void UpdateParticle(Particle* particle) {
	switch (particle->particleType){
	case AttackParticleType:
		UpdateAttackParticle(particle);
		return;
	}
}
