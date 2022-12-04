#pragma once

#include "Entity.h"
#define KINDS_OF_ITEM (2)
#define BULLET_ID (0)
#define POTION_ID (1)

typedef struct _Player {
	union {
		Entity entity;
	} base;
	Point facing;

	int hp;
	int maxHp;

	int level;
	int exp;

	int baseDamage;
	int attackWidth;
	int attackHeight;
	double attackSpeed; // attack per second;
	double moveSpeed; // block per second;
} Player;

//플레이어를 생성합니다.
Player* CreatePlayer(Point spawnPoint);

//플레이어의 이번 프레임에서의 상태를 업데이트합니다.
void UpdatePlayer();

//플레이어의 현재 위치를 Point로 반환합니다.
Point GetPlayerPos();

//플레이어에게 데미지를 가합니다.
void PlayerOnHit(int damage);

//플레이어의 현재 점수를 가지고 옵니다.
int GetScore();

//플레이어의 점수를 올립니다.
void UpScore(int baseScore);

//플레이어의 체력을 확인해서 사망 여부를 반환합니다.
bool IsPlayerDead();

//플레이어의 능력치를 BPM에 따라 재설정 합니다.
void ResetPlayerStatusByBPM(int BPM);

//플레이어의 아이템 개수를 반환합니다.
int GetPlayerItemCount(int id);

//------------레벨 업 관련-----------------

void Upgrade(int upgrade);


