#include "Particle.h"
#include "Time.h"
#include "Game.h"
#include "Vector.h"
#include "Enemy.h"

#include "World.h"

#include <string.h>

//MeleeAttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect baseMeleeAttackParticleRect = { 0,0,3,1 };
const double meleeAttackParticleUpdateTime = 0.05f;
const double meleeAttackParticleDuration = 0.15f;
void InitMeleeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //위 아래 바라보는 방향 -> 범위 변함 없음
		particle->particleRect.height = baseMeleeAttackParticleRect.height;
		particle->particleRect.width = baseMeleeAttackParticleRect.width;
	}
	else { //좌우 바라보는 방향 -> 가로세로 교환
		particle->particleRect.height = baseMeleeAttackParticleRect.width;
		particle->particleRect.width = baseMeleeAttackParticleRect.height;
	}
}
void SetMeleeAttackParticleGrid(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		for (int j = 0; j < particle->particleRect.width; j++) {
			particle->particleGrid[i][j] = false;
		}
	}
}
void UpdateMeleeAttackParticle(Particle* particle) {
	particle->nowTime += GameTime.deltaTime;
	if (particle->nowTime >= meleeAttackParticleDuration) {
		particle->isDead = true;
		return;
	}

	int index = (int)(particle->nowTime / meleeAttackParticleUpdateTime);

	//임시
	if (index > 2) return;

	if (particle->facing.x == 0) { //상하
		for (int i = 0; i < particle->particleRect.width; i++) {
			if (i <= index) particle->particleGrid[0][i] = true;
			else particle->particleGrid[0][i] = false;
		}
	}
	else { //좌우
		for (int i = 0; i < particle->particleRect.height; i++) {
			if (i <= index) particle->particleGrid[i][0]  = true;
			else particle->particleGrid[i][0] = false;
		}
	}
}
//-------------------------------------------------------------------------------------------------------

//RangeAttackParticle에 관한 함수 및 고정 상수, 모든 Rect의 기본 direction은 north, 기본좌표는 0으로 고정한다.
const Rect baseRangeAttackParticleRect = { 0, 0, 1, 1 };
const double rangeAttackParticleMoveSpeed = 0.05f; //Time per block

//RangeAttack의 경우 Enemy의 소유와 Player의 소유로 구분되며, 타입에 따라 충돌처리하는 대상이 다르다
void RangeAttackDetectPlayer(Particle* particle) {
	Point playerPos = GetPlayerPos();

	if (PointEquals(&particle->particleRect, &playerPos)) {
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
			if(EnemyOnHit(e, player->baseDamage)) UpScore(1);

			particle->isDead = true;
			return;
		}
	}
}

void RangeAttackParticleMove(Particle* particle) {
	if (particle->particleType == EnemyRangeAttackParticleType) RangeAttackDetectPlayer(particle);
	if (particle->particleType == RangeAttackParticleType) RangeAttackDetectEnemy(particle);

	Point destination = particle->base.entity.pos;
	PointAdd(&destination, &particle->facing);

	//detection Tile collision
	if (GetTile(destination) & FLAG_COLLIDE_WITH_PHYSICAL_ATTACK) { // collision with somthing else
		particle->isDead = true;
		return;
	}

	particle->base.entity.pos = destination;
	particle->particleRect.x = destination.x;
	particle->particleRect.y = destination.y;
}
void SetRangeAttackParticleGrid(Particle* particle) {
	particle->particleGrid[0][0] = true;
}
void InitRangeAttackParticleRect(Particle* particle, Point direction) {
	if (direction.x == 0) { //위 아래 바라보는 방향 -> 범위 변함 없음
		particle->particleRect.height = baseRangeAttackParticleRect.height;
		particle->particleRect.width = baseRangeAttackParticleRect.width;
	}
	else { //좌우 바라보는 방향 -> 가로세로 교환
		particle->particleRect.height = baseRangeAttackParticleRect.width;
		particle->particleRect.width = baseRangeAttackParticleRect.height;
	}
}
void UpdateRangeAttackParticle(Particle* particle) {
	particle->nowTime += GameTime.deltaTime;

	if (particle->nowTime >= rangeAttackParticleMoveSpeed) {
		particle->particleGrid[0][0] = true;
		RangeAttackParticleMove(particle);
		particle->nowTime = 0;
	}
}
//---------------------------------------------------------------------------------------------------------

//BombParticle에 관한 . . .
const Rect baseExplosionParticleRect = { 0, 0, 3, 3 };
const double ExplosionChangeTime = 0.05;
const int ExplosionParticleLifeCount = 5;

void InitExplosionParticleRect(Particle* particle) {
	particle->particleRect.height = baseExplosionParticleRect.height;
	particle->particleRect.width = baseExplosionParticleRect.width;

	particle->particleRect.x = particle->base.entity.pos.x - (baseExplosionParticleRect.width / 2);
	particle->particleRect.y = particle->base.entity.pos.y - (baseExplosionParticleRect.height / 2);
}
void SetExplosionParticleGrid(Particle* particle) {
	for (int i = 0; i < particle->particleRect.height; i++) {
		for (int j = 0; j < particle->particleRect.width; j++) {
			particle->particleGrid[i][j] = true;
		}
	}
}
void UpdateExplosionParticle(Particle* particle) {
	particle->nowTime += GameTime.deltaTime;

	if (particle->nowTime > ExplosionChangeTime * ExplosionParticleLifeCount) {
		particle->isDead = true;
		return;
	}

	int cnt = (int)(particle->nowTime / ExplosionChangeTime);

	particle->particleType = ExplosionParticleType1 + (cnt % 2);
}
//---------------------------------------------------------------------------------------------------------

void CreateParticle(Point direction, Point point, ParticleType type, int dmg) {
	Particle* particle = (Particle*)malloc(sizeof(Particle));
	if (particle == NULL) exit(-1);

	switch (type) {
	case MeleeAttackParticleType:
		InitMeleeAttackParticleRect(particle, direction);
		break;

	case EnemyRangeAttackParticleType:
	case RangeAttackParticleType:
		InitRangeAttackParticleRect(particle, direction);
		break;

	case ExplosionParticleType1:
	case ExplosionParticleType2:
		InitExplosionParticleRect(particle);
		break;

	default: exit(10);
	}
	particle->damage = dmg;

	Point startPoint = {
		point.x - (particle->particleRect.width / 2),
		point.y - (particle->particleRect.height / 2)
	};

	particle->base.entity.pos = point;
	particle->base.entity.type = ParticleEffectType;

	particle->particleRect.x = startPoint.x;
	particle->particleRect.y = startPoint.y;

	particle->nowTime = 0;
	particle->particleType = type;
	particle->facing = direction;
	particle->isDead = false;

	particle->particleGrid = (bool**)malloc(sizeof(bool*) * particle->particleRect.height);
	if (particle->particleGrid == NULL) exit(-1);

	for (int i = 0; i < particle->particleRect.height; i++) {
		particle->particleGrid[i] = (bool*)malloc(sizeof(bool) * particle->particleRect.width);
		if (particle->particleGrid[i] == NULL) exit(-1);
	}

	switch (particle->particleType) {
	case MeleeAttackParticleType:
		SetMeleeAttackParticleGrid(particle);
		break;

	case EnemyRangeAttackParticleType:
	case RangeAttackParticleType:
		SetRangeAttackParticleGrid(particle);
		break;

	case ExplosionParticleType1:
	case ExplosionParticleType2:
		SetExplosionParticleGrid(particle);
		break;

	default: exit(10);
	}

	VectorInsert(particles, (Entity*)particle);
}

void DeleteParticle(Particle* particle) {
	if (!(particle->isDead)) return;
	if (particle == NULL) return;

	for (int i = 0; i < particle->particleRect.height; i++) {
		free(particle->particleGrid[i]);
	}
	free(particle->particleGrid);
	free(particle);

	*(&particle) = NULL;
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

	case ExplosionParticleType1:
	case ExplosionParticleType2:
		UpdateExplosionParticle(particle);
		return;
	}
}
