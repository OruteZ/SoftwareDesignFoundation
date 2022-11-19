#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "Point.h"

typedef struct _Rect {
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Rect;

Rect* CreateRect(int _x, int _y, int _width, int _height);
void DeleteRect(Rect* rect);
Rect* DuplicateRect(Rect* rect);

bool RectIsIntersectingRect(Rect* rect_a, Rect* rect_b);
bool RectIsContainingRect(Rect* rect_a, Rect* rect_b);
bool RectContainsPoint(Rect *rect, Point _point);