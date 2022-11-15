#include "Point.h"

Point* CreatePoint(int _x, int _y)
{
	Point* point = (Point*)malloc(sizeof(Point));
	if (point == NULL) return NULL;
	point->x = _x;
	point->y = _y;

	return point;
}
void DeletePoint(Point* point)
{
	free(point);
	return;
}
Point* DuplicatePoint(Point* point)
{
	return CreatePoint(point->x, point->y);
}

void PointAdd(Point* point, Point* _point)
{
	point->x += _point->x;
	point->y += _point->y;
}
void PointSub(Point* point, Point* _point)
{
	point->x -= _point->x;
	point->y -= _point->y;
}
void PointMul(Point* point, double factor)
{
	point->x *= factor;
	point->y *= factor;
}
double PointDistance(Point* point_a, Point* point_b)
{
	double delta_x = point_b->x - point_a->x;
	double delta_y = point_b->y - point_a->y;
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double PointMagnitude(Point* point)
{
	return sqrt(point->x * point->x + point->y * point->y);
}
