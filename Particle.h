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
	Point facing;

	//���� ���� ���� �� �ִ� ����
	char** particleImage;
	double nowTime;
} Particle;

//��ƼŬ�� �����մϴ�. �����Ͽ��� �ٷ� Vector particles�� �� Game.c���� �����մϴ�.
//Point�� particle�� �߽���ǥ�� �ƴ� ���������� �ǹ��մϴ�.
void CreateParticle(Point direction, Point point, ParticleType type);

//��ƼŬ�� �� �����Ӹ��� �����մϴ�. particleChangeTime�� Ȯ���ϰ� Ư�� �ð��� �Ѿ��
//particleImage�� ���մϴ�. Particle�� �ð��� �ٵǾ� �����Ǿ��� ��� True��, �ƴϸ� False�� Return�մϴ�.
bool UpdateParticle(Particle* particle);

//��ƼŬ�� �����մϴ�. ���� �����Ҵ��� ��� ���� �մϴ�.
void DeleteParticle(Particle* particle);
