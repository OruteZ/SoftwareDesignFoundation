#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct _Point {
	int x;
	int y;
} Point;

Point* CreatePoint(int _x, int _y);
void DeletePoint(Point* point);
Point* DuplicatePoint(Point* point);

// ù��°�� �ѱ� Point �� �ι�°�� �ѱ� Point�� ���� ���Ѵ�.
void PointAdd(Point* point, Point* _point);

// ù��°�� �ѱ� Point �� �ι�°�� �ѱ� Point�� ���� ����.
void PointSub(Point* point, Point* _point);

// Point�� ���鿡 ����� ���Ѵ�.
void PointMul(Point* point, double factor);

// �� Point ���� �Ÿ��� ����Ѵ�.
double PointDistance(Point* point_a, Point* point_b);

// Point �� 0, 0 ���� �Ÿ��� ����Ѵ�.
double PointMagnitude(Point* point);
