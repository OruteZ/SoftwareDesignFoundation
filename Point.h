#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct _Point {
	int x;
	int y;
} Point;

Point* Point_new(int _x, int _y);
void Point_delete(Point* point);
Point* Point_duplicate(Point* point);

void Point_add(Point* point, Point* _point);
void Point_sub(Point* point, Point* _point);
void Point_mul(Point* point, double factor);
double Point_distance(Point* point_a, Point* point_b);
double Point_magnitude(Point* point);
