#include "Point.h"

Point* Point_new(int _x, int _y)
{
	Point* point = (Point*)malloc(sizeof(Point));
	if (point == NULL) return NULL;
	point->x = _x;
	point->y = _y;

	return point;
}
void Point_delete(Point* point)
{
	free(point);
	return;
}
Point* Point_duplicate(Point* point)
{
	return Point_new(point->x, point->y);
}

void Point_add(Point* point, Point* _point)
{
	point->x += _point->x;
	point->y += _point->y;
}
void Point_sub(Point* point, Point* _point)
{
	point->x -= _point->x;
	point->y -= _point->y;
}
void Point_mul(Point* point, double factor)
{
	point->x *= factor;
	point->y *= factor;
}
double Point_distance(Point* point_a, Point* point_b)
{
	double delta_x = point_b->x - point_a->x;
	double delta_y = point_b->y - point_a->y;
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double Point_magnitude(Point* point)
{
	return sqrt(point->x * point->x + point->y * point->y);
}
