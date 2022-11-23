#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#include "Point.h"
#include "World.h"

typedef struct _DPoint {
	double x;
	double y;
} DPoint;

typedef struct _RayCastResult {
	Point* arr;
	int length;
	int size;
} RayCastResult;

// when used with rect radius, max_length is radius + radius (taxicab distance)
RayCastResult* CreateRayCastResult(const int max_length) {
	RayCastResult* result = (RayCastResult*)malloc(sizeof(RayCastResult));
	if (result == 0) exit(-1);
	result->arr = (Point*)malloc(sizeof(Point) * (max_length + 1));
	if (result->arr == NULL) exit(-1);
	result->length = 0;
	result->size = max_length + 1;
	return result;
}

// when used with rect radius, max_length is radius + radius (taxicab distance)
bool RayCastInCurrentWorld(RayCastResult* result, const Point _origin, const Point _destination, const int max_length) {
	const DPoint delta = { .x = _destination.x - _origin.x, .y = _destination.y - _origin.y };
	const DPoint origin = { .x = _origin.x + 0.5, .y = _origin.y + 0.5 };
	const DPoint destination = { .x = _destination.x + 0.5, .y = _destination.y + 0.5 };

	const double dx2length = delta.x == 0 ? DBL_MAX : sqrt(1 + (delta.y / delta.x) * (delta.y / delta.x));
	const double dy2length = delta.y == 0 ? DBL_MAX : sqrt((delta.x / delta.y) * (delta.x / delta.y) + 1);

	if (!(GetTile(_origin) & FLAG_COLLIDE_WITH_BODY)) result->arr[0] = _origin;

	double xMarched = 0;
	double yMarched = 0;
	for (int i = 0; i < max_length; i++) {
		
	}
}