#pragma once

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

QuadTree* CreateQuadTree(Rect boundary);
void QuadTreeInsert(QuadTree* tree, Entity* entity);
Vector* QuadTreeQuery(QuadTree* tree, Rect area);

