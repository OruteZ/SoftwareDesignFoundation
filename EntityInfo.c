#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Point.h"

typedef struct meleeEnemy
{
	Point memory;
	Point pos;
	int hp;
	int attackDamage;
	int moveSpeed;
	//공격력 쿨타임 - 
};