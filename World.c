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

//void swapTile(Tile* a, Tile* b) {
//	Tile tempTile = *a;
//	*a = *b;
//	*b = tempTile;
//}
//Tile* GetTilePointerOfWorld(World* world, const Point p) {
//	return world->grid + p.y * world->height + p.x;
//}
//void FlipWorld(World* world) {
//	for (int i = 0; i < world->height / 2; i++) {
//		for (int j = 0; j < world->width; j++) {
//			Point origin = {.y = i, .x = j};
//			Point mirrored = {.y = world->height - 1 - i, .x = j};
//			swapTile(GetTilePointerOfWorld(world, origin), GetTilePointerOfWorld(world, mirrored));
//		}
//	}
//}

World* current_world = NULL;
void SetCurrentWorld(World* world) {
	current_world = world;
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
//Tile GetTileUnchecked(const Point p) {
//	return *GetTilePointer(p);
//}
BOOLEAN SetTile(const Point p, const Tile tile) {
	if (IsPointValidInCurrentWorld(p)) {
		*GetTilePointer(p) = tile;
		return TRUE;
	}
	else return FALSE;
}
//void SetTileUnchecked(const Point p, const Tile tile) {
//	*GetTilePointer(p) = tile;
//}
