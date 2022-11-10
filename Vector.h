#pragma once

#include "Entity.h"

typedef struct _Vector {
	Entity** entities;
	int length;
	int size;
} Vector;

// Vector를 생성 한다.
Vector* CreateVector();
// Vector를 제거(shallow) 한다.
void DeleteVector(Vector* vector);
// Vector를 제거(deep) 한다. 
void DeepDeleteVector(Vector* vector);

// Vector에 하나의 엔티티를 추가한다.
void VectorInsert(Vector* vector, const Entity* entity);
// Vector에 index에 위치한 엔티티를 삭제(shallow)한다.
// 빈 공간은 마지막 원소로 채워넣는다.
void VectorDeleteUnstable(Vector* vector, const int index);
// Vector에 index 에 위치한 엔티티를 삭제(deep)한다.
// 빈 공간은 마지막 원소로 채워넣는다.
void VectorDeepDeleteUnstable(Vector* vector, const int index);
// Vector에 index 에 위치한 엔티티를 삭제(shallow)한다.
// 빈 공간은 나머지 원소를 쉬프트 한다.
void VectorDelete(Vector* vector, const int index);
// Vector에 index 에 위치한 엔티티를 삭제(deep)한다.
// 빈 공간은 나머지 원소를 쉬프트 한다.
void VectorDeepDelete(Vector* vector, const int index);
// 두 Vector를 합친다. 합친 Vector는 유효하지 않고 반환된 Vector*만 유효하다.
Vector* VectorMerge(Vector* vectorA, Vector* vectorB);

