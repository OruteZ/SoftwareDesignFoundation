#pragma once

#include "Point.h"

typedef struct _RayCastResult {
	Point* arr;
	int length;
	int size;
} RayCastResult;

// RayCastResult*�� �����Ѵ�.
// �簢�� ������(width = r + r + 1) ���� ����� ��� max_length �� radius + radius �� �Ǿ�� �Ѵ�(�˻�: taxicab distance)
RayCastResult* CreateRayCastResult(const int max_length);
// RayCastResult*�� �����.
void DeleteRayCastResult(RayCastResult* result);

// RayCastResult* result �� RayCast ���� ���ο� ��� ���� ������ ������ �����Ѵ�
// �Լ��� ��ȯ���� RayCast�� destination �� �����ϸ� true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�
bool RayCastInCurrentWorld(RayCastResult* result, const Point _origin, const Point _destination);

// todo:
// ����� �ؾ� �ϴ� �͵�.
// x ��ȭ 0�϶�, y ��ȭ 0�϶�(Ray�� ���Ⱑ 0�϶�, �����϶�)
// destination ���� �ķ� �� RayCast�� �õ��ϴ°�?
// ������ �����ϴ� ��� �������� RayCast�� �������ΰ�? (�ϵ�, �ϼ�, ����, ���� ��� �׽�Ʈ �ؾ���)

