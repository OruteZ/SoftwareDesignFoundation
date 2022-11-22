#include <stdlib.h>

#include <stdbool.h>

#include "Point.h"
#include "Rect.h"

#include "Entity.h"
#include "Vector.h"

#include "QuadTree.h"
#include "Rect.h"

QuadTree* CreateQuadTree(Rect boundary) {
	QuadTree* tree = (QuadTree*)malloc(sizeof(QuadTree));
	if (tree == NULL) exit(-1);

	tree->boundary = boundary;
	tree->contained_entity = NULL;

	tree->nw = NULL;
	tree->ne = NULL;
	tree->sw = NULL;
	tree->se = NULL;

	return tree;
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

	Rect swRect = { .x = x,				.y = y,					.width = halfWidth,			.height = halfHeight };
	Rect seRect = { .x = x + halfWidth,	.y = y,					.width = width - halfWidth,	.height = halfHeight };
	Rect nwRect = { .x = x,				.y = y + halfHeight,	.width = halfWidth,			.height = height - halfHeight };
	Rect neRect = { .x = x + halfWidth,	.y = y + halfHeight,	.width = width - halfWidth,	.height = height - halfHeight };

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

bool QuadTreeInsert(QuadTree* tree, Entity* entity) {
	if (!RectContainsPoint(&tree->boundary, &entity->pos)) return false; // does not contain!

	if (tree->contained_entity == NULL && tree->nw == NULL) {
		tree->contained_entity = entity;
		return true;
	}

	if (tree->nw == NULL) { // not divided
		QuadTreeSubdivide(tree);
	}

	return QuadTreeInsert(tree->nw, entity) || QuadTreeInsert(tree->ne, entity) || QuadTreeInsert(tree->sw, entity) || QuadTreeInsert(tree->se, entity);
}

Vector* QuadTreeDump(QuadTree* tree) {
	Vector* vector = CreateVector();
	if (tree == NULL) return vector;

	if (tree->nw != NULL) {
		vector = VectorMerge(vector, QuadTreeDump(tree->nw));
		vector = VectorMerge(vector, QuadTreeDump(tree->ne));
		vector = VectorMerge(vector, QuadTreeDump(tree->sw));
		vector = VectorMerge(vector, QuadTreeDump(tree->se));
	}
	else if (tree->contained_entity != NULL) {
		VectorInsert(vector, tree->contained_entity);
	}
	return vector;
}
Vector* QuadTreeQuery(QuadTree* tree, Rect area) {
	Vector* vector;
	if (tree == NULL) return CreateVector();
	if (!RectIsIntersectingRect(&area, &tree->boundary)) return CreateVector(); // does not intersect!

	if (RectIsContainingRect(&area, &tree->boundary)) return QuadTreeDump(tree); // fully contains!
	
	// intersects!
	vector = CreateVector();
	if (tree->nw != NULL) {
		vector = VectorMerge(vector, QuadTreeQuery(tree->nw, area));
		vector = VectorMerge(vector, QuadTreeQuery(tree->ne, area));
		vector = VectorMerge(vector, QuadTreeQuery(tree->sw, area));
		vector = VectorMerge(vector, QuadTreeQuery(tree->se, area));
	}
	else if (tree->contained_entity != NULL && RectContainsPoint(&area, &tree->contained_entity->pos)) {
		VectorInsert(vector, tree->contained_entity);
	}
	return vector;
}

#ifdef DEBUG
#include "Debug.h"
void DebugQuadTreeRecursive(QuadTree* tree, const int depth) {
	DebugPrint("tree depth: %d, (%d, %d, %d, %d)", depth, tree->boundary.x, tree->boundary.y, tree->boundary.width, tree->boundary.height);
	if (tree->contained_entity != NULL) {
		DebugPrint("Entity: (%d, %d)", tree->contained_entity->pos.x, tree->contained_entity->pos.y);
	}
	if (tree->nw != NULL) {
		DebugQuadTreeRecursive(tree->nw, depth + 1);
		DebugQuadTreeRecursive(tree->ne, depth + 1);
		DebugQuadTreeRecursive(tree->sw, depth + 1);
		DebugQuadTreeRecursive(tree->se, depth + 1);
	}
}
void DebugQuadTree(QuadTree* tree) {
	DebugQuadTreeRecursive(tree, 1);
}
#endif

