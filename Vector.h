#pragma once

#include "Entity.h"

typedef struct _Vector {
	Entity** entities;
	int length;
	int size;
} Vector;

// Vector�� ���� �Ѵ�.
Vector* CreateVector();
// Vector�� ����(shallow) �Ѵ�.
void DeleteVector(Vector* vector);
// Vector�� ����(deep) �Ѵ�. 
void DeepDeleteVector(Vector* vector);

// Vector�� �ϳ��� ��ƼƼ�� �߰��Ѵ�.
void VectorInsert(Vector* vector, const Entity* entity);
// Vector�� index�� ��ġ�� ��ƼƼ�� ����(shallow)�Ѵ�.
// �� ������ ������ ���ҷ� ä���ִ´�.
void VectorDeleteUnstable(Vector* vector, const int index);
// Vector�� index �� ��ġ�� ��ƼƼ�� ����(deep)�Ѵ�.
// �� ������ ������ ���ҷ� ä���ִ´�.
void VectorDeepDeleteUnstable(Vector* vector, const int index);
// Vector�� index �� ��ġ�� ��ƼƼ�� ����(shallow)�Ѵ�.
// �� ������ ������ ���Ҹ� ����Ʈ �Ѵ�.
void VectorDelete(Vector* vector, const int index);
// Vector�� index �� ��ġ�� ��ƼƼ�� ����(deep)�Ѵ�.
// �� ������ ������ ���Ҹ� ����Ʈ �Ѵ�.
void VectorDeepDelete(Vector* vector, const int index);
// �� Vector�� ��ģ��. ��ģ Vector�� ��ȿ���� �ʰ� ��ȯ�� Vector*�� ��ȿ�ϴ�.
Vector* VectorMerge(Vector* vectorA, Vector* vectorB);

