#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Point.h"

//근거리 몬스터 구조체
typedef struct meleeEnemy
{
	Point memory;//몬스터가 기억할 플레이어의 위치
	Point pos; //몬스터의 위치
	int hp; //체력
	int attackDamage;//공격 당 피해량
	int moveSpeed; //이동 속도(sleep이라 높으면 느리고, 낮으면 빠르다)
	double attackDelay; //공격 쿨타임
}meleeEnemy;

//원거리 몬스터 구조체
typedef struct arrowEnemy
{
	Point arrowPos; // 원거리 공격 투사체의 위치
	Point memory;//몬스터가 기억할 플레이어의 위치
	Point pos; //몬스터의 위치
	int hp; //체력
	int attackDamage;//공격 당 피해량
	int moveSpeed; //이동 속도(sleep이라 높으면 느리고, 낮으면 빠르다)
	int arrowSpeed; //투사체 속도
	double attackDelay; //공격 쿨타임
}arrowEnemy;

//자폭 몬스터 구조체
typedef struct bombEnemy
{
	Point memory;// 몬스터가 기억할 플레이어의 위치
	Point pos; //몬스터의 위치
	int hp; //체력
	int attackDamage;//자폭 피해량
	int moveSpeed; //이동 속도(sleep이라 높으면 느리고, 낮으면 빠르다)

}bombEnemy;

//플레이어 구조체
typedef struct Player
{
	Point pos; //플레이어의 위치
	int hp; //체력
	int meleeDamage;//근접 기본 공격 당 피해량
	int moveSpeed; //이동 속도(sleep이라 높으면 느리고, 낮으면 빠르다)
	double attackDelay; //근접 공격 쿨타임
	//아이템 추가 시 아이템 유무 확인할 bool 또는 enum 번수 선언
}Player;

meleeEnemy MeleeEnemy;
arrowEnemy ArrowEnemy;
bombEnemy BombEnemy;
Player player;

void InitMeleeEnemy()
{
	MeleeEnemy.hp = 50;
	MeleeEnemy.attackDelay = 3.0f;
	MeleeEnemy.attackDamage = 15;
	MeleeEnemy.moveSpeed = 1500;
	//몬스터의 초기 위치 0으로 설정
	MeleeEnemy.pos.x = 0; 
	MeleeEnemy.pos.y = 0;
	//플레이어 위치 초기값 NULL
	MeleeEnemy.memory.x = NULL;
	MeleeEnemy.memory.y = NULL;
}

void InitArrowEnemy()
{	
	ArrowEnemy.hp = 30;
	ArrowEnemy.attackDelay = 2.0f;
	ArrowEnemy.attackDamage = 10;
	ArrowEnemy.moveSpeed = 3000;

	//몬스터의 초기 위치 0으로 설정
	ArrowEnemy.pos.x = 0;
	ArrowEnemy.pos.y = 0;

	//투사체 초기 위치 NULL
	ArrowEnemy.arrowPos.x = NULL;
	ArrowEnemy.arrowPos.y = NULL;

	//플레이어 위치 초기값 NULL
	ArrowEnemy.memory.x = NULL;
	ArrowEnemy.memory.y = NULL;
}

void InitBombEnemy()
{
	BombEnemy.hp = 40;
	BombEnemy.attackDamage = 80;


	//자폭 몬스터는 처음부터 플레이어의 좌표를 알고 있기 때문에 처음 생성 시 player의 좌표로 설정
	BombEnemy.memory = player.pos;
	//몬스터의 초기 위치 0으로 설정
	BombEnemy.pos.x = 0;
	BombEnemy.pos.y = 0;
	//플레이어 위치 초기값 NULL
	BombEnemy.memory.x = NULL;
	BombEnemy.memory.y = NULL;
}

void InitPlayer()
{
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//초기위치 50으로 기본설정
	player.pos.x = 50;
	player.pos.y = 50;
}


//맵에 따라 플레이어, 몬스터 스폰 위치는 바뀔 수 있다.
