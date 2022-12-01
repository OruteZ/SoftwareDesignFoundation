#pragma once

#include "Entity.h"
#include "UpgradeUI.h"

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

//�÷��̾ �����մϴ�.
Player* CreatePlayer(Point spawnPoint);

//�÷��̾��� �̹� �����ӿ����� ���¸� ������Ʈ�մϴ�.
void UpdatePlayer();

//�÷��̾��� ���� ��ġ�� Point�� ��ȯ�մϴ�.
Point GetPlayerPos();

//�÷��̾�� �������� ���մϴ�.
void PlayerOnHit(int damage);

//�÷��̾��� ���� ������ ������ �ɴϴ�.
int GetScore();

//�÷��̾��� ������ �ø��ϴ�.
void UpScore(int baseScore);

//�÷��̾��� ü���� Ȯ���ؼ� ��� ���θ� ��ȯ�մϴ�.
bool IsPlayerDead();

//�÷��̾��� �ɷ�ġ�� BPM�� ���� �缳�� �մϴ�.
void ResetPlayerStatusByBPM(int BPM);

//------------���� �� ����-----------------

void Upgrade(UpgradeType);


