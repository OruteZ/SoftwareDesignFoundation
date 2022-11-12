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

// 쿼드 트리를 만든다.
QuadTree* CreateQuadTree(Rect boundary);
// 쿼드 트리를 삭제한다.
void DeleteQuadTree(QuadTree* tree);
// 쿼드 트리에 엔티티를 삽입한다.
void QuadTreeInsert(QuadTree* tree, Entity* entity);
// 쿼드 트리에 범위(Rect) 안에 있는 모든 엔티티를 반환하도록 명령한다.
Vector* QuadTreeQuery(QuadTree* tree, Rect area);

