#include "Point.h"
#include "EntityInfo.h"

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
	Point memory;
	Point pos;
	int hp; 
	int attackDamage;
	int moveSpeed; 
	int arrowSpeed; //투사체 속도
	double attackDelay;
}arrowEnemy;

//자폭 몬스터 구조체
typedef struct bombEnemy
{
	Point memory;
	Point pos; 
	int hp;
	int attackDamage;
	int moveSpeed;

}bombEnemy;

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


Player player;

//근접 몬스터 생성
meleeEnemy CreateMeleeEnemy(Point p)
{
	meleeEnemy MeleeEnemy;
	MeleeEnemy.hp = 50;
	MeleeEnemy.attackDelay = 3.0f;
	MeleeEnemy.attackDamage = 15;
	MeleeEnemy.moveSpeed = 1500;

	//몬스터의 초기 위치 Point 인자로 설정해서 맵에 위치시키기
	MeleeEnemy.pos.x = p.x; 
	MeleeEnemy.pos.y = p.y;

	//플레이어 위치 초기값 NULL
	MeleeEnemy.memory.x = NULL;
	MeleeEnemy.memory.y = NULL;
	return MeleeEnemy;
}

//원거리 몬스터 생성
 arrowEnemy CreateArrowEnemy(Point p)
{	
	arrowEnemy ArrowEnemy;
	ArrowEnemy.hp = 30;
	ArrowEnemy.attackDelay = 2.0f;
	ArrowEnemy.attackDamage = 10;
	ArrowEnemy.moveSpeed = 3000;

	ArrowEnemy.pos.x = p.x;
	ArrowEnemy.pos.y = p.y;

	//투사체 초기 위치 NULL
	ArrowEnemy.arrowPos.x = NULL;
	ArrowEnemy.arrowPos.y = NULL;

	ArrowEnemy.memory.x = NULL;
	ArrowEnemy.memory.y = NULL;
	return ArrowEnemy;
}

//자폭 몬스터 생성
bombEnemy CreateBombEnemy(Point p)
{
	bombEnemy BombEnemy;
	BombEnemy.hp = 40;
	BombEnemy.attackDamage = 80;
	BombEnemy.moveSpeed = 2000;

	//자폭 몬스터는 처음부터 플레이어의 좌표를 알고 있기 때문에 처음 생성 시 memory를 player의 좌표로 설정
	BombEnemy.memory = player.pos;


	BombEnemy.pos.x = p.x;
	BombEnemy.pos.y = p.y;
	return BombEnemy;
}

//게임 시작 시 처음 플레이어 생성하기
void CreatePlayer(Point p)
{
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//초기위치 인자로 받아서 캐릭터 생성

	player.pos.x = p.x;
	player.pos.y = p.y;
}
