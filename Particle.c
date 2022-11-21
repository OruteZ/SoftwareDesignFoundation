#include "Particle.h"
#include "Time.h"

//AttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect _baseAttackParticleRect = { 0,0,3,1 };
const double _AttackParticleUpdateTime = 0.1f;
const double _AttackParticleDuration = 0.3f;
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
bool UpdateAttackParticle(Particle* particle) {
	particle->nowTime += GameTime.deltaTime;
	if (particle->nowTime >= _AttackParticleDuration) {
		DeleteParticle(particle);
		return true;
	}

	int index = (int)(particle->nowTime / _AttackParticleUpdateTime);

	//임시
	if (index > 2) {
		DeleteParticle(particle);
		return true;
	}

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

	return false;
}

void CreateParticle(Point direction, Point point, ParticleType type)
{
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	particle->base.entity.pos = point;
	particle->base.entity.type = _ParticleEffect;

	particle->particleRect.x = point.x;
	particle->particleRect.y = point.y;

	particle->nowTime = 0;
	particle->particleType = type;
	particle->facing = direction;

	switch (type) {
	case AttackParticleType:
		InitAttackParticleRect(particle, direction);
		break;
	}

	particle->particleImage = (char**)malloc(sizeof(char*) * particle->particleRect.height);
	for (int i = 0; i < particle->particleRect.height; i++) {
		particle->particleImage[i] = (char*)malloc(sizeof(char*) * particle->particleRect.width);
	}
}

void DeleteParticle(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		free(particle->particleImage[i]);
	}
	free(particle->particleImage);
	free(particle);
}

bool UpdateParticle(Particle* particle) {
	switch (particle->particleType){
	case AttackParticleType:
		return UpdateAttackParticle(particle);
	}
}
