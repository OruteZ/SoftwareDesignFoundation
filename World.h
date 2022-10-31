#pragma once

#include <Windows.h>
#include "Point.h"


// 2���� �迭�� �� ��Ҹ� "Ÿ��" �̶�� �θ���� �Ѵ�.
// Ÿ���� 1����Ʈ ������.
typedef unsigned char TILE;





// �� ���� �پ��� Ư¡���� �������� �ϰ�, �� ���� �˻��ϴ� ���� �ƴ� Ư¡���� �˻��ϱ� ���ؼ� �� ��Ʈ�� Flag ó�� ���� �ִ�.
// 
// ��Ʈ ������ AND �� ����Ѵٸ� if-elseif-else Ȥ�� switch�� ������� �ʰ� ���� Ÿ���� Ư¡���� �ſ� ������ �˻��� �� �ִ�.
// ��� ����) ������ Ÿ���� �÷��̾ ����� �� ���ٸ� �Լ� ����: if(   GetTile({Point.x + 1, Point.y})   &   COLLIDE_WITH_BODY   ) return;


// �⺻
#define DEFAULT (0b00000000)
// ��(�÷��̾�, ����)�� �浹�ϴ� Ÿ���ΰ�?
#define COLLIDE_WITH_BODY (0b00000001)
// ���� ����(���� ����, ȭ�� ���� ��ô�� ���Ÿ� ����)�� �浹�ϴ� Ÿ���ΰ�?
#define COLLIDE_WITH_PHYSICAL_ATTACK (0b00000010)
// �� Ÿ���� �þ߸� �����ϴ°�?
#define OPAQUE (0b00001000)
// ����(Ÿ�� A)�� �ִ� Ÿ���ΰ�? ������ ������ �� Flag�� ���ȴ�.
#define HAZARD_TYPE_A (0b00010000)
// ������ Ÿ���ΰ�?
#define GOAL (0b01000000)



// Ȥ�� ���߿� ���� ������ �ƴ� �ٸ� ���� Ÿ���� ����ٸ� ����� Ÿ�� Flag.
// #define COLLIDE_WITH_MAGICAL_ATTACK (0b00000100)

// �Ⱦ��� �־ ���߿� �߰��� �� ����� �� �ִ� Ÿ�� Flags.
// Also future proofing
// #define UNUSED_1 (0b00100000)
// #define UNUSED_2 (0b10000000)

// ���� ��� �� �� ���µ� ����(Ÿ�� A)�� �ִ� Ÿ���� ���� �ȵǴ� Ÿ���̱� ������ ���� ���Ͽ� ���ǵ��� ���� Ÿ�Ϸ� �Ѵ�.
// ��� ����) GetTile(Point) & UNDEFINED_TILE == UNDEFINED_TILE �� TRUE ��� ������ ��ȯ�� ���̴�.
#define UNDEFINED_TILE		(DEFAULT | COLLIDE_WITH_BODY | HAZARD_TYPE_A)

// �� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� Ȯ����.
#define GROUND				(DEFAULT)
// �� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� ����.
#define WALL				(DEFAULT | COLLIDE_WITH_BODY | COLLIDE_WITH_PHYSICAL_ATTACK | OPAQUE)
// ������ Ÿ��.			�� ��� ����. ���� ��� ����. �þ� Ȯ����.
#define PIT					(DEFAULT | COLLIDE_WITH_BODY)
// ���� Ÿ��.				�� ��� ����. ���� ��� ����. �þ� Ȯ����.			����(Ÿ�� A).
#define TRAP				(DEFAULT | HAZARD_TYPE_A)
// �������� ��� Ÿ��.		�� ��� ����. ���� ��� ����. �þ� Ȯ����.			������ Ÿ��.
#define DOWNSTAIRS			(DEFAULT | GOAL)