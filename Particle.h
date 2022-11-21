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

	//������ �����Ǵ� ����
	enum ParticleType particleType;
	Rect particleRect;
	double particleUpdateTime;

	//���� ���� ���� �� �ִ� ����
	char** particleImage;
	double nowTime;
} Particle;

//��ƼŬ�� �����մϴ�. �����Ͽ��� �ٷ� Vector particles�� �� Game.c���� �����մϴ�.
void CreateParticle(Point direction, Point point, ParticleType type);

//��ƼŬ�� �� �����Ӹ��� �����մϴ�. particleChangeTime�� Ȯ���ϰ� Ư�� �ð��� �Ѿ��
//particleImage�� ���մϴ�.
void UpdateParticle(Particle* particle);
