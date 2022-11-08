#include <stdlib.h>

#include "Rect.h"

typedef struct _QuadTree {
	Rect boundary;
	int capacity;
	// Vector* elements;

	struct _QuadTree* nw;
	struct _QuadTree* ne;
	struct _QuadTree* sw;
	struct _QuadTree* se;
} QuadTree;

// todo: not done! consider after implementation of Vector
QuadTree* CreateQuadTree(Rect boundary, int capacity) {
	QuadTree* tree = (QuadTree*)malloc(sizeof(QuadTree));

	tree->boundary = boundary;
	int capacity = capacity;
	tree->nw = NULL;
	tree->ne = NULL;
	tree->sw = NULL;
	tree->se = NULL;
}

void SubdivideQuadTree(QuadTree* tree) {
	int x = tree->boundary.x;
	int y = tree->boundary.y;
	int width = tree->boundary.width;
	int height = tree->boundary.height;
	int halfWidth = tree->boundary.width / 2;
	int halfHeight = tree->boundary.height / 2;

	Rect nwRect = { .x = x, .y = y, .width = halfWidth, .height = halfHeight }; 
	Rect neRect = { .x = halfWidth, .y = y, .width = width - halfWidth, .height = halfHeight };
	Rect swRect = { .x = x, .y = halfHeight, .width = halfWidth, .height = height - halfHeight };
	Rect seRect = { .x = halfWidth, .y = halfHeight, .width = width - halfWidth, .height = height - halfHeight };

	tree->nw = CreateQuadTree(nwRect, tree->capacity);
	tree->ne = CreateQuadTree(neRect, tree->capacity);
	tree->sw = CreateQuadTree(swRect, tree->capacity);
	tree->se = CreateQuadTree(seRect, tree->capacity);

	// todo: for each element in elements, insert to subtree. and free Vector.
}
