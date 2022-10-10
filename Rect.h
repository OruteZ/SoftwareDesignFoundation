#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct _Rect {
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Rect;

Rect* Rect_new(int _x, int _y, int _width, int _height);
void Rect_delete(Rect* rect);
Rect* Rect_duplicate(Rect* rect);

bool Rect_is_intersecting_Rect(Rect* rect_a, Rect* rect_b);
bool Rect_is_containing_Rect(Rect* rect_a, Rect* rect_b);
