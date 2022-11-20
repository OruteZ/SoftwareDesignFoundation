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

// ���� Ʈ���� �����.
QuadTree* CreateQuadTree(Rect boundary);
// ���� Ʈ���� �����Ѵ�.
void DeleteQuadTree(QuadTree* tree);
// ���� Ʈ���� ��ƼƼ�� �����Ѵ�.
void QuadTreeInsert(QuadTree* tree, Entity* entity);
// ���� Ʈ���� ����(Rect) �ȿ� �ִ� ��� ��ƼƼ�� ��ȯ�ϵ��� ����Ѵ�.
Vector* QuadTreeQuery(QuadTree* tree, Rect area);

