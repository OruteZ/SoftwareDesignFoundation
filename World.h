#pragma once

#include <Windows.h>
#include "Point.h"


// 2차원 배열의 각 요소를 "타일" 이라고 부르기로 한다.
// 타일은 1바이트 정수다.
typedef unsigned char TILE;





// 각 블럭이 다양한 특징들을 가지도록 하고, 블럭 별로 검사하는 것이 아닌 특징별로 검사하기 위해서 각 비트를 Flag 처럼 쓰고 있다.
// 
// 비트 연산자 AND 를 사용한다면 if-elseif-else 혹은 switch를 사용하지 않고도 여러 타일을 특징별로 매우 빠르게 검사할 수 있다.
// 사용 예시) 오른쪽 타일이 플레이어가 통과할 수 없다면 함수 종료: if(   GetTile({Point.x + 1, Point.y})   &   COLLIDE_WITH_BODY   ) return;


// 기본
#define DEFAULT (0b00000000)
// 몸(플레이어, 몬스터)과 충돌하는 타일인가?
#define COLLIDE_WITH_BODY (0b00000001)
// 물리 공격(근접 공격, 화살 등의 투척형 원거리 공격)과 충돌하는 타일인가?
#define COLLIDE_WITH_PHYSICAL_ATTACK (0b00000010)
// 이 타일이 시야를 방해하는가?
#define OPAQUE (0b00001000)
// 피해(타입 A)를 주는 타일인가? 지금은 함정에 이 Flag가 사용된다.
#define HAZARD_TYPE_A (0b00010000)
// 목적지 타일인가?
#define GOAL (0b01000000)



// 혹시 나중에 물리 공격이 아닌 다른 공격 타입이 생긴다면 사용할 타일 Flag.
// #define COLLIDE_WITH_MAGICAL_ATTACK (0b00000100)

// 안쓰고 있어서 나중에 추가할 때 사용할 수 있는 타일 Flags.
// Also future proofing
// #define UNUSED_1 (0b00100000)
// #define UNUSED_2 (0b10000000)

// 몸이 통과 할 수 없는데 피해(타입 A)를 주는 타일은 말도 안되는 타일이기 때문에 오류 리턴용 정의되지 않은 타일로 한다.
// 사용 예시) GetTile(Point) & UNDEFINED_TILE == UNDEFINED_TILE 가 TRUE 라면 오류가 반환된 것이다.
#define UNDEFINED_TILE		(DEFAULT | COLLIDE_WITH_BODY | HAZARD_TYPE_A)

// 땅 타일.				몸 통과 가능. 공격 통과 가능. 시야 확보됨.
#define GROUND				(DEFAULT)
// 벽 타일.				몸 통과 못함. 공격 통과 못함. 시야 막힘.
#define WALL				(DEFAULT | COLLIDE_WITH_BODY | COLLIDE_WITH_PHYSICAL_ATTACK | OPAQUE)
// 구덩이 타일.			몸 통과 못함. 공격 통과 가능. 시야 확보됨.
#define PIT					(DEFAULT | COLLIDE_WITH_BODY)
// 함정 타일.				몸 통과 가능. 공격 통과 가능. 시야 확보됨.			피해(타입 A).
#define TRAP				(DEFAULT | HAZARD_TYPE_A)
// 내려가는 계단 타일.		몸 통과 가능. 공격 통과 가능. 시야 확보됨.			목적지 타일.
#define DOWNSTAIRS			(DEFAULT | GOAL)