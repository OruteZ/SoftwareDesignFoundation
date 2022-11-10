#include <stdlib.h>

#include <stdbool.h>

#include "Point.h"
#include "Rect.h"

#include "Entity.h"

typedef int VECTOR_PLACEHOLDER;
typedef struct _QuadTree {
	Rect boundary;
	Entity* contained_entity;

	struct _QuadTree* nw;
	struct _QuadTree* ne;
	struct _QuadTree* sw;
	struct _QuadTree* se;
} QuadTree;

QuadTree* CreateQuadTree(Rect boundary) {
	QuadTree* tree = (QuadTree*)malloc(sizeof(QuadTree));

	tree->boundary = boundary;
	tree->contained_entity = NULL;

	tree->nw = NULL;
	tree->ne = NULL;
	tree->sw = NULL;
	tree->se = NULL;
}

void QuadTreeSubdivide(QuadTree* tree) {
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

	tree->nw = CreateQuadTree(nwRect);
	tree->ne = CreateQuadTree(neRect);
	tree->sw = CreateQuadTree(swRect);
	tree->se = CreateQuadTree(seRect);

	QuadTreeInsert(tree->nw, tree->contained_entity);
	QuadTreeInsert(tree->ne, tree->contained_entity);
	QuadTreeInsert(tree->sw, tree->contained_entity);
	QuadTreeInsert(tree->se, tree->contained_entity);

	tree->contained_entity = NULL;
}

bool RectContainsPoint(Rect rect, Point point) {
	if (rect.x <= point.x && point.x < rect.x + rect.width &&
		rect.y <= point.y && point.y < rect.y + rect.height) {
		return true;
	}
	else return false;
}
void QuadTreeInsert(QuadTree* tree, Entity* entity) {
	if (!RectContainsPoint(tree->boundary, entity->pos)) return; // does not contain!

	if (tree->contained_entity == NULL && tree->nw == NULL) return tree->contained_entity = entity;

	if (tree->nw == NULL) { // not divided
		if (tree->contained_entity == NULL) return tree->contained_entity = entity;
		QuadTreeSubdivide(tree);
	}

	QuadTreeInsert(tree->nw, entity);
	QuadTreeInsert(tree->ne, entity);
	QuadTreeInsert(tree->sw, entity);
	QuadTreeInsert(tree->se, entity);
}

VECTOR_PLACEHOLDER* QuadTreeDump(QuadTree* tree) {
	if (tree == NULL) return;
	if (tree->contained_entity == NULL) {
		VECTOR_PLACEHOLDER vector;
		vector_add(vector ,QuadTreeDump(tree->nw));
		vector_add(vector ,QuadTreeDump(tree->ne));
		vector_add(vector ,QuadTreeDump(tree->sw));
		vector_add(vector ,QuadTreeDump(tree->se));
	}
}
VECTOR_PLACEHOLDER* QuadTreeQuery(QuadTree* tree, Rect area) {
	if (!RectIsIntersectingRect(&area, &tree->boundary)) return NULL; // does not intersect!

	if (RectIsContainingRect(&area, &tree->boundary)) return QuadTreeDump(tree); // fully contains!
	
	// intersects!
	VECTOR_PLACEHOLDER vector;
	if (tree->nw == NULL) {
		vector_add(vector, QuadTreeQuery(tree->nw, area));
		vector_add(vector, QuadTreeQuery(tree->ne, area));
		vector_add(vector, QuadTreeQuery(tree->sw, area));
		vector_add(vector, QuadTreeQuery(tree->se, area));
	}
	if (RectContainsPoint(area, tree->contained_entity->pos)) {
		vector_add(vector, tree->contained_entity);
	}
	return vector;
}
