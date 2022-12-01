#pragma once
#include <stdbool.h>
#include "Rect.h"

//������ ���� ����ü�� �ؾ��ұ�?
//���� ��ü���ٵ�
//Player���� ���� Rect�鿡 ���� �浹 �Լ� �߰��� �ֱ⸸ �ϸ� �ɰŰ���


//boss���� �������� ���մϴ�. ������θ� return �մϴ�.
bool BossOnHit(int damage);

//���� ���� ü���� ��ȯ�մϴ�.
int GetBossHP();

//���� ���� ��ġ�� ǥ���ϴ� Rect�� ��ȯ�մϴ�. �浹 ���� Ȯ�ο� ����մϴ�.
Rect GetBossRect();

//�ǰ� ȿ���� ǥ������ bool�� ��ȯ�մϴ�. ���� ��� ������ �Ӱ� ����Ʈ�մϴ�.
bool BossHitEffect();

//���� ������θ� ��ȯ�մϴ�. ���� ���������� ���� ��ȣ�ۿ��� ��� �����մϴ�.
bool isBossDead();

void BossSpawn(Point p);
void BossUpdate();
