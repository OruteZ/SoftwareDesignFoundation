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
//Point�� particle�� �߽���ǥ�� �ǹ��մϴ�. ���̰� ¦���� ���, �߰��������� ���� �� ��ǥ�� ����� �ǹ��մϴ�.
void CreateParticle(Point direction, Point point, ParticleType type);

//��ƼŬ�� �� �����Ӹ��� �����մϴ�. particleChangeTime�� Ȯ���ϰ� Ư�� �ð��� �Ѿ�� particleImage�� ���մϴ�.
void UpdateParticle(Particle* particle);

//��ƼŬ�� �����մϴ�. ���� �����Ҵ��� ��� ���� �մϴ�.
void DeleteParticle(Particle* particle);

//�ش� ��ƼŬ�� ������ ���ߴ��� Ȯ���մϴ�.
bool IsParticleFinished(Particle* particle);
