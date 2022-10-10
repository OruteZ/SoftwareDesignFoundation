#include "Rect.h"

Rect* Rect_new(int _x, int _y, int _width, int _height) {
	Rect* rect = (Rect*)malloc(sizeof(Rect));
	if (rect == NULL) return NULL;
	rect->x = _x;
	rect->y = _y;
	rect->width = _width;
	rect->height = _height;

	return rect;
}
void Rect_delete(Rect* rect) {
	free(rect);
	return;
}
Rect* Rect_duplicate(Rect* rect)
{
	return Rect_new(rect->x, rect->y, rect->width, rect->height);
}

bool Rect_is_intersecting_Rect(Rect* rect_a, Rect* rect_b) {
	if (rect_a->x + rect_a->width <= rect_b->x ||
		rect_b->x + rect_b->width <= rect_a->x ||
		rect_a->y + rect_a->height <= rect_b->y ||
		rect_b->y + rect_b->height <= rect_a->y) return false;
	else return true;
}
bool Rect_is_containing_Rect(Rect* rect_a, Rect* rect_b) {
	if (rect_a->x <= rect_b->x &&
		rect_b->x + rect_b->width <= rect_a->x + rect_a->width &&
		rect_a->y <= rect_b->y &&
		rect_b->y + rect_b->height <= rect_a->y + rect_a->height) return true;
	else return false;
}