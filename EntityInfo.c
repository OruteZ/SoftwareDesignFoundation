#include "Point.h"
#include "EntityInfo.h"

//부모 몬스터 구조체
typedef struct Enemy
{
	int hp; //체력
	int attackDamage; //공격력
	int moveSpeed;//이동 속도
	double attackDelay;//공격 쿨타임
	Point memory;//몬스터가 기억할 플레이어의 위치
	Point pos; //몬스터의 위치
}Enemy;


//근거리 몬스터 구조체
typedef struct MeleeEnemy
{
	Enemy enemy;
}MeleeEnemy;

//원거리 몬스터 구조체
typedef struct RangeEnemy
{
	Enemy enemy;
	Point rangePos; // 원거리 공격 투사체의 위치
	int rangeSpeed; //투사체 속도
}RangeEnemy;

//자폭 몬스터 구조체
typedef struct BombEnemy
{
	Enemy enemy;

}BombEnemy;

//플레이어 구조체
typedef struct Player
{
	Point pos; 
	int hp;
	int meleeDamage;
	int moveSpeed; 
	double attackDelay;
	//아이템 추가 시 아이템 유무 확인할 bool 또는 enum 번수 선언
}Player;


//근접 몬스터 생성
MeleeEnemy *CreateMeleeEnemy(Point p)
{
	MeleeEnemy *meleeEnemy;
	meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	meleeEnemy->enemy.hp = 50;
	meleeEnemy->enemy.attackDelay = 3.0f;
	meleeEnemy->enemy.attackDamage = 15;
	meleeEnemy->enemy.moveSpeed = 1500;

	//몬스터의 초기 위치 Point 인자로 설정해서 맵에 위치시키기
	meleeEnemy->enemy.pos.x = p.x; 
	meleeEnemy->enemy.pos.y = p.y;

	//플레이어 위치 초기값 NULL
	meleeEnemy->enemy.memory.x = NULL;
	meleeEnemy->enemy.memory.y = NULL;
	return meleeEnemy;
}

//원거리 몬스터 생성
 RangeEnemy *CreateRangeEnemy(Point p)
{	
	RangeEnemy *rangeEnemy;
	rangeEnemy = (RangeEnemy*)malloc(sizeof(RangeEnemy));
	rangeEnemy->enemy.hp = 30;
	rangeEnemy->enemy.attackDelay = 2.0f;
	rangeEnemy->enemy.attackDamage = 10;
	rangeEnemy->enemy.moveSpeed = 3000;

	rangeEnemy->enemy.pos.x = p.x;
	rangeEnemy->enemy.pos.y = p.y;

	rangeEnemy->enemy.memory.x = NULL;
	rangeEnemy->enemy.memory.y = NULL;

	//투사체 초기 위치 NULL
	rangeEnemy->rangePos.x = NULL;
	rangeEnemy->rangePos.y = NULL;
	return rangeEnemy;
}

//자폭 몬스터 생성
BombEnemy *CreateBombEnemy(Point p)
{
	BombEnemy *bombEnemy;
	bombEnemy = (BombEnemy*)malloc(sizeof(BombEnemy));
	bombEnemy->enemy.hp = 40;
	bombEnemy->enemy.attackDamage = 80;
	bombEnemy->enemy.moveSpeed = 2000;

	bombEnemy->enemy.pos.x = p.x;
	bombEnemy->enemy.pos.y = p.y;

	bombEnemy->enemy.memory.x = NULL;
	bombEnemy->enemy.memory.y = NULL;
	return bombEnemy;
}

//게임 시작 시 처음 플레이어 생성하기
Player* CreatePlayer(Point p)
{
	Player* player;
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//초기위치 인자로 받아서 캐릭터 생성

	player.pos.x = p.x;
	player.pos.y = p.y;
}
