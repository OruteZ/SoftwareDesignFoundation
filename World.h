#pragma once

#include "Point.h"
#include "Entity.h"
#include "Vector.h"

typedef unsigned char BOOLEAN;
// 2���� �迭�� �� ��Ҹ� "Ÿ��" �̶�� �θ���� �Ѵ�.
// Ÿ���� 1����Ʈ ������.
typedef unsigned char Tile;

typedef struct _SpawnSequence {
	double gameTime;
	Vector* list;

	struct _SpawnSequence* next;
} SpawnSequence;

typedef struct _World {
	Tile* grid;

	int width;
	int height;

	Point playerSpawnPoint;

	SpawnSequence* enemySpawnSequence;
	SpawnSequence* currentSpawnSequence;
} World;







// �� ���� �پ��� Ư¡���� �������� �ϰ�, �� ���� �˻��ϴ� ���� �ƴ� Ư¡���� �˻��ϱ� ���ؼ� �� ��Ʈ�� Flag ó�� ���� �ִ�.
// 
// ��Ʈ ������ AND �� ����Ѵٸ� if-elseif-else Ȥ�� switch�� ������� �ʰ� ���� Ÿ���� Ư¡���� �ſ� ������ �˻��� �� �ִ�.
// ��� ����) ������ Ÿ���� �÷��̾ ����� �� ���ٸ� �Լ� ����: if(   GetTile({Point.x + 1, Point.y})   &   COLLIDE_WITH_BODY   ) return;


// �⺻
#define FLAG_DEFAULT (0b00000000)
// ��(�÷��̾�, ����)�� �浹�ϴ� Ÿ���ΰ�?
#define FLAG_COLLIDE_WITH_BODY (0b00000001)
// ���� ����(���� ����, ȭ�� ���� ��ô�� ���Ÿ� ����)�� �浹�ϴ� Ÿ���ΰ�?
#define FLAG_COLLIDE_WITH_PHYSICAL_ATTACK (0b00000010)
// �� Ÿ���� �þ߸� �����ϴ°�?
#define FLAG_OPAQUE (0b00001000)
// ����(Ÿ�� A)�� �ִ� Ÿ���ΰ�? ������ ������ �� Flag�� ���ȴ�.
#define FLAG_HAZARD_TYPE_A (0b00010000)
// ������ Ÿ���ΰ�?
#define FLAG_GOAL (0b01000000)



// Ȥ�� ���߿� ���� ������ �ƴ� �ٸ� ���� Ÿ���� ����ٸ� ����� Ÿ�� Flag.
// #define FLAG_COLLIDE_WITH_MAGICAL_ATTACK (0b00000100)

// �Ⱦ��� �־ ���߿� �߰��� �� ����� �� �ִ� Ÿ�� Flags.
// Also future proofing
// #define UNUSED_1 (0b00100000)
// #define UNUSED_2 (0b10000000)

// ���� ��� �� �� ���µ� ����(Ÿ�� A)�� �ִ� Ÿ���� ���� �ȵǴ� Ÿ���̱� ������ ���� ���Ͽ� ���ǵ��� ���� Ÿ�Ϸ� �Ѵ�.
// ��� ����) GetTile(Point) == UNDEFINED_TILE �� TRUE ��� ������ ��ȯ�� ���̴�.
//#define UNDEFINED_TILE		(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY | FLAG_HAZARD_TYPE_A)
#define UNDEFINED_TILE	0b00010001

// �� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� Ȯ����.
//#define GROUND			(FLAG_DEFAULT)
#define GROUND			0b00000000
// �� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� ����.
//#define WALL			(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY | FLAG_COLLIDE_WITH_PHYSICAL_ATTACK | FLAG_OPAQUE)
#define WALL			0b00001011
// ������ Ÿ��.			�� ��� ����. ���� ��� ����. �þ� Ȯ����.
//#define PIT				(FLAG_DEFAULT | FLAG_COLLIDE_WITH_BODY)
#define PIT				0b00000001
// ���� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� Ȯ����.			����(Ÿ�� A).
//#define TRAP			(FLAG_DEFAULT | FLAG_HAZARD_TYPE_A)
#define TRAP			0b00010000
// �������� ��� Ÿ��.		�� ��� ����. ���� ��� ����. �þ� Ȯ����.			������ Ÿ��.
//#define DOWNSTAIRS		(FLAG_DEFAULT | FLAG_GOAL)
#define DOWNSTAIRS		0b01000000



// ���ο� World�� �����Ѵ�.
World* CreateWorld(const int width, const int height);
// World�� �����Ѵ�.
void DeleteWorld(World* world);



// �� ���� �ʱ�ȭ�� �ϴ� �Լ� ���� ���뿡 ������ ���� ������ �־�� �Ѵ�.
// 1. "���� �ܰ�"�� �ϳ� �����.
// 2. �� ���� �ܰ迡 ��ƼƼ�� �߰��Ѵ�.
// 3. ���忡 ���� �ܰ踦 �߰��Ѵ�.
// ���� �ܰ���� ���ϴ� �ܰ� �� ��ŭ ����� �Ѵ�. ���ô� World001.c ����.


// ���� "���� �ܰ�"�� �ϳ� �����Ѵ�. ���ڷ� ���޵� gameTime�� �ð��� �°� �����Ѵ�.
// ���Ƿ��� WorldInsertSpawnSequence()�� ����ؾ� �Ѵ�.
SpawnSequence* CreateSpawnSequence(double gameTime);
// "���� �ܰ�"�� ��ƼƼ�� �ϳ� �ִ´�.
void SpawnSequenceInsert(SpawnSequence* seq, const int spawn_x, const int spawn_y, const enum EntityType entityType);
// ���忡 "���� �ܰ�"�� ����ִ´�. ������ �ڿ� �߰��Ǳ� ������ ������� �־�� �Ѵ�.
void WorldInsertSpawnSequence(World* world, SpawnSequence* seq);
// "���� �ܰ�"�� �õ��Ѵ�. ���� �ܰ谡 �� ���������� Ȯ���ϱ� ������ ���� ���� ȣ���ص� �ȴ�.
void TrySpawnSequence();



// ������ World�� �ٲ۴�.
void SetCurrentWorld(World* world);
World* GetCurrentWorld();

// ���� World�� width height�� Point�� ���ԵǴ��� Ȯ��
BOOLEAN IsPointValidInCurrentWorld(Point p);

// Point�� ��ġ�� Ÿ���� ��������.
Tile GetTile(const Point p);

// Point�� Ÿ���� �ٲٱ�.
// ���� ���θ� BOOLEAN ���� �Ѵ�.
BOOLEAN SetTile(const Point p, const Tile tile);
