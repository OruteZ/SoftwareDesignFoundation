#pragma once

#include "Entity.h"

typedef struct ExpOrb {
	union {
		Entity entity;
	}base;

	int experience;

	bool isDead;
} ExpOrb;


//exp ��ŭ ����ġ�� �ο��ϴ� ����ġ ���긦 ���� �մϴ�.
//���� ��ǥ�� �̹� ���갡 ���� ��� �ش� ���꿡 ����ġ ���� ���մϴ�.
//���� ��� ���Ϳ� �����մϴ�.
void CreateExpOrb(Point p, int exp);

//���� ���ο� ���� �� ����ġ�� ��ȯ�մϴ�.
//�Լ��� ������ orb�� ����ó�� �˴ϴ�.
int GetExp(ExpOrb* orb);

//�ش� ����Ʈ�� ����ġ ���갡 �ִ��� Ȯ���մϴ�.
//������� �ش� ������ �����͸�, �ƴϸ� NULL�� ��ȯ�մϴ�.
ExpOrb* FindOrb(Point p);