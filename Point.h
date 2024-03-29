#pragma once

#include <stdbool.h>

typedef struct _Point {
	int x;
	int y;
} Point;

extern const struct __Directions {
	Point north;
	Point south;
	Point east;
	Point west;
} Direction;

Point* CreatePoint(int _x, int _y);
void DeletePoint(Point* point);
Point* DuplicatePoint(Point* point);

// 두 Point가 동일(x, y)한지 확인한다.
bool PointEquals(Point* point_a, Point* point_b);

// 첫번째로 넘긴 Point 에 두번째로 넘긴 Point의 값을 더한다.
void PointAdd(Point* point, Point* _point);

// 첫번째로 넘긴 Point 에 두번째로 넘긴 Point의 값을 뺀다.
void PointSub(Point* point, Point* _point);

// Point의 값들에 상수를 더한다.
void PointMul(Point* point, double factor);

// 두 Point 간의 거리를 계산한다.
double PointDistance(Point* point_a, Point* point_b);

// Point 와 0, 0 간의 거리를 계산한다.
double PointMagnitude(Point* point);
