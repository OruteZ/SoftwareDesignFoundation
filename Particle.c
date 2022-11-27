#include "Particle.h"
#include "Time.h"
#include "Game.h"
#include "Vector.h"
#include "Enemy.h"

#include "World.h"

#include <string.h>

//MeleeAttackParticle�� ���� �Լ� �� ���� ���, ��� Rect�� �⺻ direction�� north, �⺻��ǥ�� 0���� �����Ѵ�.
const Rect _baseMeleeAttackParticleRect = { 0,0,3,1 };
const double _meleeAttackParticleUpdateTime = 0.05f;
const double _meleeAttackParticleDuration= 0.15f;
const char _meleeAttackParticleChar[3] = "��";
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
	if (particle->nowTime >= _meleeAttackParticleDuration) {
		particle->isDead = true;
		return;
	}

	int index = (int)(particle->nowTime / _meleeAttackParticleUpdateTime);

	//�ӽ�
	if (index > 2) return;

	if (particle->facing.x == 0) { //����
		for (int i = 0; i < particle->particleRect.width; i++) {
			if (i == index) particle->particleGrid[0][i] = true;
			else particle->particleGrid[0][i] = false;
		}
	}
	else { //�¿�
		for (int i = 0; i < particle->particleRect.height; i++) {
			if (i == index) particle->particleGrid[i][0]  = true;
			else particle->particleGrid[i][0] = false;
		}
	}
}
//-------------------------------------------------------------------------------------------------------

//RangeAttackParticle�� ���� �Լ� �� ���� ���, ��� Rect�� �⺻ direction�� north, �⺻��ǥ�� 0���� �����Ѵ�.
const Rect _baseRangeAttackParticleRect = { 0, 0, 1, 1 };
const double _rangeAttackParticleMoveSpeed = 0.05f; //Time per block
const char _rangeAttackParticleChar[3] = "as";

//RangeAttack�� ��� Enemy�� ������ Player�� ������ ���еǸ�, Ÿ�Կ� ���� �浹ó���ϴ� ����� �ٸ���
void RangeAttackDetectPlayer(Particle* particle) {
	Point playerPos = GetPlayerPos();

	if (PointEquals(&particle, &playerPos)) {
		PlayerOnHit(particle->damage);
		particle->isDead = true;
	}
}
void RangeAttackDetectEnemy(Particle* particle) {
	/*
	Vector* enemiesCollided = QuadTreeQuery(enemies, particle->particleRect);
	if (enemiesCollided->length > 0) {
		for (int i = 0; i < enemiesCollided->length; i++) {
			Enemy* e = (Enemy*)enemiesCollided->entities[i];
			EnemyOnHit(e, particle->damage);
		}

		particle->isDead = true;
	}
	DeleteVector(enemiesCollided);
	*/

	int len = enemies->length;
	for (int i = 0; i < len; i++) {
		Enemy* e = enemies->entities[i];
		if (RectContainsPoint(&particle->particleRect, &e->base.entity.pos)) {
			EnemyOnHit(e, player->baseDamage);

			particle->isDead = true;
			return;
		}
	}
}

void RangeAttackParticleMove(Particle* particle) {
	Point destination = particle->base.entity.pos;
	PointAdd(&destination, &particle->facing);

	//detection Tile collision
	if (GetTile(destination) & FLAG_COLLIDE_WITH_PHYSICAL_ATTACK) { // collision with else somthing
		particle->isDead = true;
		return;
	}

	particle->base.entity.pos = destination;
	particle->particleRect.x = destination.x;
	particle->particleRect.y = destination.y;

	if (particle->particleType == EnemyRangeAttackParticleType) RangeAttackDetectPlayer(particle);
	if (particle->particleType == RangeAttackParticleType) RangeAttackDetectEnemy(particle);
}
void InitRangeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //�� �Ʒ� �ٶ󺸴� ���� -> ���� ���� ����
		particle->particleRect.height = _baseRangeAttackParticleRect.height;
		particle->particleRect.width = _baseRangeAttackParticleRect.width;
	}
	else { //�¿� �ٶ󺸴� ���� -> ���μ��� ��ȯ
		particle->particleRect.height = _baseRangeAttackParticleRect.width;
		particle->particleRect.width = _baseRangeAttackParticleRect.height;
	}
}
void UpdateRangeAttackParticle(Particle* particle) {
	particle->nowTime += Time.deltaTime;

	if (particle->nowTime >= _rangeAttackParticleMoveSpeed) {
		particle->particleGrid[0][0] = true;
		RangeAttackParticleMove(particle);
		particle->nowTime = 0;
	}
}
//---------------------------------------------------------------------------------------------------------

void CreateParticle(Point direction, Point point, ParticleType type, int dmg) {
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	switch (type) {
	case MeleeAttackParticleType:
		InitMeleeAttackParticleRect(particle, direction);
		particle->damage = dmg;
		break;
	case EnemyRangeAttackParticleType:
	case RangeAttackParticleType:
		InitRangeAttackParticleRect(particle, direction);
		particle->damage = dmg;
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

	particle->particleGrid = (bool**)malloc(sizeof(bool*) * particle->particleRect.height);
	for (int i = 0; i < particle->particleRect.height; i++) {
		particle->particleGrid[i] = (bool*)malloc(sizeof(bool) * particle->particleRect.width);

		for (int j = 0; j < particle->particleRect.width;j++) {
			particle->particleGrid[i][j] = false;
		}
	}

	VectorInsert(particles, (Entity*)particle);
}

void DeleteParticle(Particle* particle) {
	if (!(particle->isDead)) return;

	for (int i = 0; i < particle->particleRect.height; i++) {
		free(particle->particleGrid[i]);
	}
	free(particle->particleGrid);
	free(particle);
}

void UpdateParticle(Particle* particle) {
	if (particle->isDead) return;

	switch (particle->particleType) {
	case MeleeAttackParticleType:
		UpdateMeleeAttackParticle(particle);
		return;
		
	case RangeAttackParticleType:
	case EnemyRangeAttackParticleType:
		UpdateRangeAttackParticle(particle);
		return;
	}
}
