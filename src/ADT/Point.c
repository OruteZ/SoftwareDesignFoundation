#include "Point.h"

const struct {
	Point north;
	Point south;
	Point east;
	Point west;
} Direction = {
	.north = {.x = 0 , .y = 1},
	.south = {.x = 0 , .y = -1},
	.east = {.x = 1 , .y = 0},
	.west = {.x = -1 , .y = 0}
};

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

bool PointEquals(Point* point_a, Point* point_b) {
	if (point_a->x == point_b->x &&
		point_a->y == point_b->y) return true;
	else return false;
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
