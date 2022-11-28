#pragma once

#include "Entity.h"
#include "Rect.h"

typedef enum _ParticleType {
	MeleeAttackParticleType,
	RangeAttackParticleType,
	EnemyRangeAttackParticleType,
	ExplosionParticleType1, ExplosionParticleType2,

} ParticleType;

typedef struct _Paritcle {
	union {
		Entity entity;
	} base;
	//�浹 �� �������� ������ ��ƼŬ�� ���
	int damage;

	//������ �����Ǵ� ����
	enum ParticleType particleType;
	Rect particleRect;
	Point facing;

	//���� ���� ���� �� �ִ� ����
	bool** particleGrid;
	double nowTime;
	bool isDead;
} Particle;

//��ƼŬ�� �����մϴ�. �����Ͽ��� �ٷ� Vector particles�� �� Game.c���� �����մϴ�.
//Point�� particle�� �߽���ǥ�� �ǹ��մϴ�. ���̰� ¦���� ���, �߰��������� ���� �� ��ǥ�� ����� �ǹ��մϴ�.
void CreateParticle(Point direction, Point point, ParticleType type, int dmg);

//��ƼŬ�� �� �����Ӹ��� �����մϴ�. particleChangeTime�� Ȯ���ϰ� Ư�� �ð��� �Ѿ�� particleImage�� ���մϴ�.
void UpdateParticle(Particle* particle);

//��ƼŬ�� �����մϴ�. ���� �����Ҵ��� ��� ���� �մϴ�.
void DeleteParticle(Particle* particle);
