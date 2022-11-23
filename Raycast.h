#pragma once

#include "Point.h"

typedef struct _RayCastResult {
	Point* arr;
	int length;
	int size;
} RayCastResult;

// RayCastResult*를 생성한다.
// 사각형 반지름(width = r + r + 1) 으로 사용할 경우 max_length 는 radius + radius 가 되어야 한다(검색: taxicab distance)
RayCastResult* CreateRayCastResult(const int max_length);
// RayCastResult*를 지운다.
void DeleteRayCastResult(RayCastResult* result);

// RayCastResult* result 에 RayCast 성공 여부와 상관 없이 과정의 블럭들을 반환한다
// 반환값은 RayCast가 destination 에 도착하면 true, 그렇지 않다면 false를 반환한다
bool RayCastInCurrentWorld(RayCastResult* result, const Point _origin, const Point _destination);

