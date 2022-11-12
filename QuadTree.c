#include <stdlib.h>

#include <stdbool.h>

#include "Point.h"
#include "Rect.h"

#include "Entity.h"
#include "Vector.h"

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
void DeleteQuadTree(QuadTree* tree) {
	if (tree->nw != NULL) {
		DeleteQuadTree(tree->nw);
		DeleteQuadTree(tree->ne);
		DeleteQuadTree(tree->sw);
		DeleteQuadTree(tree->se);
	}

	free(tree);
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

Vector* QuadTreeDump(QuadTree* tree) {
	if (tree == NULL) return NULL;

	Vector* vector;
	if (tree->nw != NULL) {
		vector = QuadTreeDump(tree->nw);
		vector = VectorMerge(vector, QuadTreeDump(tree->ne));
		vector = VectorMerge(vector, QuadTreeDump(tree->sw));
		vector = VectorMerge(vector, QuadTreeDump(tree->se));
	}
	
	vector = CreateVector();
	if (tree->contained_entity != NULL) {
		VectorInsert(vector, tree->contained_entity);
	}
	return vector;
}
Vector* QuadTreeQuery(QuadTree* tree, Rect area) {
	if (tree == NULL) return NULL;
	if (!RectIsIntersectingRect(&area, &tree->boundary)) return CreateVector(); // does not intersect!

	if (RectIsContainingRect(&area, &tree->boundary)) return QuadTreeDump(tree); // fully contains!
	
	// intersects!
	Vector* vector;
	if (tree->nw != NULL) {
		vector = QuadTreeQuery(tree->nw, area);
		vector = VectorMerge(vector, QuadTreeQuery(tree->ne, area));
		vector = VectorMerge(vector, QuadTreeQuery(tree->sw, area));
		vector = VectorMerge(vector, QuadTreeQuery(tree->se, area));
	}
	vector = CreateVector();
	if (RectContainsPoint(area, tree->contained_entity->pos)) {
		VectorInsert(vector, tree->contained_entity);
	}
	return vector;
}

