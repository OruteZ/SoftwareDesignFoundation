#include "Rect.h"
Rect* CreateRect(int _x, int _y, int _width, int _height) {
	Rect* rect = (Rect*)malloc(sizeof(Rect));
	if (rect == NULL) return NULL;
	rect->x = _x;
	rect->y = _y;
	rect->width = _width;
	rect->height = _height;

	return rect;
}
void DeleteRect(Rect* rect) {
	free(rect);
	return;
}
Rect* DuplicateRect(Rect* rect)
{
	return CreateRect(rect->x, rect->y, rect->width, rect->height);
}

bool RectIsIntersectingRect(Rect* rect_a, Rect* rect_b) {
	if (rect_a->x + rect_a->width <= rect_b->x ||
		rect_b->x + rect_b->width <= rect_a->x ||
		rect_a->y + rect_a->height <= rect_b->y ||
		rect_b->y + rect_b->height <= rect_a->y) return false;
	else return true;
}
bool RectIsContainingRect(Rect* rect_a, Rect* rect_b) {
	if (rect_a->x <= rect_b->x &&
		rect_b->x + rect_b->width <= rect_a->x + rect_a->width &&
		rect_a->y <= rect_b->y &&
		rect_b->y + rect_b->height <= rect_a->y + rect_a->height) return true;
	else return false;
}
bool RectContainsPoint(Rect* rect, Point* _point)
{
	if (rect->x <= _point->x && _point->x < rect->x + rect->width &&
		rect->y <= _point->y && _point->y < rect->y + rect->height) {
		return true;
	}
	else return false;
}