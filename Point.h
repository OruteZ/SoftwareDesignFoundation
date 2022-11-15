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

void PointAdd(Point* point, Point* _point);
void PointSub(Point* point, Point* _point);
void PointMul(Point* point, double factor);
double PointDistance(Point* point_a, Point* point_b);
double PointMagnitude(Point* point);
