#include "Raycast.h"

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

//typedef struct _RayCastResult {
//	Point* arr;
//	int length;
//	int size;
//} RayCastResult;

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
void DeleteRayCastResult(RayCastResult* result) {
	free(result->arr);
	free(result);
}

// return value is true when ray reaches destination
bool RayCastInCurrentWorld(RayCastResult* result, const Point _origin, const Point _destination) {
	const DPoint origin = { .x = _origin.x + 0.5, .y = _origin.y + 0.5 };
	const DPoint destination = { .x = _destination.x + 0.5, .y = _destination.y + 0.5 };
	const DPoint delta = { .x = destination.x - origin.x, .y = destination.y - origin.y };

	const DPoint marchingStep = {
		.x = delta.x >= 0 ? 1 : -1,
		.y = delta.y >= 0 ? 1 : -1
	};
	const DPoint marchedStepToDistanceFactor = {
		.x = delta.x == 0 ? DBL_MAX : sqrt(1 + (delta.y / delta.x) * (delta.y / delta.x)),
		.y = delta.y == 0 ? DBL_MAX : sqrt((delta.x / delta.y) * (delta.x / delta.y) + 1)
	};

	DPoint stepsMarched = {	// first step is marching to the walls of each cell
		.x = marchingStep.x < 0 ? origin.x - floor(origin.x) : floor(origin.x) + 1 - origin.x,
		.y = marchingStep.y < 0 ? origin.y - floor(origin.y) : floor(origin.y) + 1 - origin.y
	};

	Point head = _origin;
	if (!(GetTile(head) & FLAG_COLLIDE_WITH_BODY)) { // first tile check!
		result->arr[0] = head;
		result->length = 1;
	}
	else return false;

	for (int i = 1; stepsMarched.x + stepsMarched.y < result->size; i++) {
		const DPoint marchedDistances = { .x = stepsMarched.x * marchedStepToDistanceFactor.x, .y = stepsMarched.y * marchedStepToDistanceFactor.y };
		if (marchedDistances.y < marchedDistances.x) { // move with marchingStep.y!
			stepsMarched.y += 1;
			head.y += marchingStep.y;
		}
		else { // move with marchingStep.x!
			stepsMarched.x += 1;
			head.x += marchingStep.x;
		}

		if (GetTile(head) & FLAG_COLLIDE_WITH_BODY) {
			return false;
		}

		result->arr[i] = head; // adding to result
		result->length++;
		if (head.x == _destination.x && head.y == _destination.y) return true; // if destination reached, end with true;
	}
	return false;
}