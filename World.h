#pragma once

#include "Point.h"

typedef unsigned char BOOLEAN;
// 2차원 배열의 각 요소를 "타일" 이라고 부르기로 한다.
// 타일은 1바이트 정수다.
typedef unsigned char Tile;

typedef struct _World {
	Tile* grid;

	int width;
	int height;
} World;







// 각 블럭이 다양한 특징들을 가지도록 하고, 블럭 별로 검사하는 것이 아닌 특징별로 검사하기 위해서 각 비트를 Flag 처럼 쓰고 있다.
// 
// 비트 연산자 AND 를 사용한다면 if-elseif-else 혹은 switch를 사용하지 않고도 여러 타일을 특징별로 매우 빠르게 검사할 수 있다.
// 사용 예시) 오른쪽 타일이 플레이어가 통과할 수 없다면 함수 종료: if(   GetTile({Point.x + 1, Point.y})   &   COLLIDE_WITH_BODY   ) return;


// 기본
#define FLAG_DEFAULT (0b00000000)
// 몸(플레이어, 몬스터)과 충돌하는 타일인가?
#define FLAG_COLLIDE_WITH_BODY (0b00000001)
// 물리 공격(근접 공격, 화살 등의 투척형 원거리 공격)과 충돌하는 타일인가?
#define FLAG_COLLIDE_WITH_PHYSICAL_ATTACK (0b00000010)
// 이 타일이 시야를 방해하는가?
#define FLAG_OPAQUE (0b00001000)
// 피해(타입 A)를 주는 타일인가? 지금은 함정에 이 Flag가 사용된다.
#define FLAG_HAZARD_TYPE_A (0b00010000)
// 목적지 타일인가?
#define FLAG_GOAL (0b01000000)



// 혹시 나중에 물리 공격이 아닌 다른 공격 타입이 생긴다면 사용할 타일 Flag.
// #define FLAG_COLLIDE_WITH_MAGICAL_ATTACK (0b00000100)

// 안쓰고 있어서 나중에 추가할 때 사용할 수 있는 타일 Flags.
// Also future proofing
// #define UNUSED_1 (0b00100000)
// #define UNUSED_2 (0b10000000)

// 몸이 통과 할 수 없는데 피해(타입 A)를 주는 타일은 말도 안되는 타일이기 때문에 오류 리턴용 정의되지 않은 타일로 한다.
// 사용 예시) GetTile(Point) == UNDEFINED_TILE 가 TRUE 라면 오류가 반환된 것이다.
//#define UNDEFINED_TILE		(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY | FLAG_HAZARD_TYPE_A)
#define UNDEFINED_TILE	0b00010001

// 땅 타일.				몸 통과 가능. 공격 통과 가능. 시야 확보됨.
//#define GROUND			(FLAG_DEFAULT)
#define GROUND			0b00000000
// 벽 타일.				몸 통과 못함. 공격 통과 못함. 시야 막힘.
//#define WALL			(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY | FLAG_COLLIDE_WITH_PHYSICAL_ATTACK | FLAG_OPAQUE)
#define WALL			0b00001011
// 구덩이 타일.			몸 통과 못함. 공격 통과 가능. 시야 확보됨.
//#define PIT				(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY)
#define PIT				0b00000001
// 함정 타일.				몸 통과 가능. 공격 통과 가능. 시야 확보됨.			피해(타입 A).
//#define TRAP			(FLAG_DEFAULT | FLAG_HAZARD_TYPE_A)
#define TRAP			0b00010000
// 내려가는 계단 타일.		몸 통과 가능. 공격 통과 가능. 시야 확보됨.			목적지 타일.
//#define DOWNSTAIRS		(FLAG_DEFAULT | FLAG_GOAL)
#define DOWNSTAIRS		0b01000000



// 새로운 World를 생성한다.
World* CreateWorld(const int width, const int height);
// World를 제거한다.
void DeleteWorld(World* world);

// 현재의 World를 바꾼다.
void SetCurrentWorld(World* world);
World* GetCurrentWorld();

// 지금 World의 width height에 Point가 포함되는지 확인
BOOLEAN IsPointValidInCurrentWorld(Point p);

// Point에 위치한 타일을 가져오기.
Tile GetTile(const Point p);

// Point에 타일을 바꾸기.
// 성공 여부를 BOOLEAN 리턴 한다.
BOOLEAN SetTile(const Point p, const Tile tile);
