#include "Particle.h"
#include "Time.h"
#include "Game.h"
#include "Vector.h"

//AttackParticle�� ���� �Լ� �� ���� ���, ��� Rect�� �⺻ direction�� north, �⺻��ǥ�� 0���� �����Ѵ�.
const Rect _baseMeleeAttackParticleRect = { 0,0,3,1 };
const double _MeleeAttackParticleUpdateTime = 0.05f;
const double _MeleeAttackParticleDuration = 0.15f;
const char _MeleeAttackParticleChar = '��';
void InitMeleeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //�� �Ʒ� �ٶ󺸴� ���� -> ���� ���� ����
		particle->particleRect.height = _baseMeleeAttackParticleRect.height;
		particle->particleRect.width = _baseMeleeAttackParticleRect.width;
	}
	else { //�¿� �ٶ󺸴� ���� -> ���μ��� ��ȯ
		particle->particleRect.height = _baseMeleeAttackParticleRect.width;
		particle->particleRect.width = _baseMeleeAttackParticleRect.height;
	}
}
void UpdateMeleeAttackParticle(Particle* particle) {
	particle->nowTime += Time.deltaTime;
	if (particle->nowTime >= _MeleeAttackParticleDuration) return;

	int index = (int)(particle->nowTime / _MeleeAttackParticleUpdateTime);

	//�ӽ�
	if (index > 2) return;

	if (particle->facing.x == 0) { //����
		for (int i = 0; i < particle->particleRect.width; i++) {
			if (i == index) particle->particleImage[0][i] = _MeleeAttackParticleChar;
			else particle->particleImage[0][i] = ' ';
		}
	}
	else {
		for (int i = 0; i < particle->particleRect.height; i++) {
			if (i == index) particle->particleImage[i][0] = _MeleeAttackParticleChar;
			else particle->particleImage[i][0] = ' ';
		}
	}
}
bool IsMeleeAttackParticleFinished(Particle* particle) {
	return (bool)(particle->nowTime >= _MeleeAttackParticleDuration);
}
//-------------------------------------------------------------------------------------------------------

void CreateParticle(Point direction, Point point, ParticleType type)
{
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	switch (type) {
	case AttackParticleType:
		InitMeleeAttackParticleRect(particle, direction);
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
	case AttackParticleType: return IsMeleeAttackParticleFinished(particle);
	}
}

void UpdateParticle(Particle* particle) {
	switch (particle->particleType) {
	case AttackParticleType:
		UpdateMeleeAttackParticle(particle);
		return;
	}
}
