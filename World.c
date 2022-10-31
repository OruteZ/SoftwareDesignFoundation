#include "World.h"

typedef struct _World {
	TILE* grid;

	int width;
	int height;
} WORLD;





WORLD* current_world = NULL;
void SetCurrentWorld(WORLD* world) {
	current_world = world;
}





BOOLEAN IsPointValidInCurrentWorld(Point p) {
	if (0 <= p.x && p.x < current_world->width &&
		0 <= p.y && p.y < current_world->height) return TRUE;
	else return FALSE;
}
TILE* GetTilePointer(const Point p) {
	return current_world->grid + p.y * current_world->height + p.x;
}





TILE GetTile(const Point p) {
	if (IsPointValidInCurrentWorld(p)) {
		return *GetTilePointer(p);
	}
	else {
		return UNDEFINED_TILE;
	}
}
TILE GetTileUnchecked(const Point p) {
	return *GetTilePointer(p);
}
BOOLEAN SetTile(const Point p, const TILE tile) {
	if (IsPointValidInCurrentWorld(p)) {
		*GetTilePointer(p) = tile;
		return TRUE;
	}
	else return FALSE;
}
void SetTileUnchecked(const Point p, const TILE tile) {
	*GetTilePointer(p) = tile;
}