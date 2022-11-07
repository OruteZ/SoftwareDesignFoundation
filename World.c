#include "World.h"

#include <Windows.h>
#include "Point.h"






World* CreateWorld(const int width, const int height) {
	World* world = (World*)malloc(sizeof(World));
	if (world == NULL) exit(-1);
	world->width = width;
	world->height = height;
	world->grid = NULL;
	return world;
}

World* current_world = NULL;
void SetCurrentWorld(World* world) {
	current_world = world;
}
World* GetCurrentWorld() {
	return current_world;
}





BOOLEAN IsPointValidInCurrentWorld(Point p) {
	if (0 <= p.x && p.x < current_world->width &&
		0 <= p.y && p.y < current_world->height) return TRUE;
	else return FALSE;
}
Tile* GetTilePointer(const Point p) {
	return current_world->grid + p.y * current_world->height + p.x;
}





Tile GetTile(const Point p) {
	if (IsPointValidInCurrentWorld(p)) {
		return *GetTilePointer(p);
	}
	else {
		return UNDEFINED_TILE;
	}
}
BOOLEAN SetTile(const Point p, const Tile tile) {
	if (IsPointValidInCurrentWorld(p)) {
		*GetTilePointer(p) = tile;
		return TRUE;
	}
	else return FALSE;
}
