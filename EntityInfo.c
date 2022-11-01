#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Point.h"

//�ٰŸ� ���� ����ü
typedef struct meleeEnemy
{
	Point memory;//���Ͱ� ����� �÷��̾��� ��ġ
	Point pos; //������ ��ġ
	int hp; //ü��
	int attackDamage;//���� �� ���ط�
	int moveSpeed; //�̵� �ӵ�(sleep�̶� ������ ������, ������ ������)
	double attackDelay; //���� ��Ÿ��
}meleeEnemy;

//���Ÿ� ���� ����ü
typedef struct arrowEnemy
{
	Point arrowPos; // ���Ÿ� ���� ����ü�� ��ġ
	Point memory;//���Ͱ� ����� �÷��̾��� ��ġ
	Point pos; //������ ��ġ
	int hp; //ü��
	int attackDamage;//���� �� ���ط�
	int moveSpeed; //�̵� �ӵ�(sleep�̶� ������ ������, ������ ������)
	int arrowSpeed; //����ü �ӵ�
	double attackDelay; //���� ��Ÿ��
}arrowEnemy;

//���� ���� ����ü
typedef struct bombEnemy
{
	Point memory;// ���Ͱ� ����� �÷��̾��� ��ġ
	Point pos; //������ ��ġ
	int hp; //ü��
	int attackDamage;//���� ���ط�
	int moveSpeed; //�̵� �ӵ�(sleep�̶� ������ ������, ������ ������)

}bombEnemy;

//�÷��̾� ����ü
typedef struct Player
{
	Point pos; //�÷��̾��� ��ġ
	int hp; //ü��
	int meleeDamage;//���� �⺻ ���� �� ���ط�
	int moveSpeed; //�̵� �ӵ�(sleep�̶� ������ ������, ������ ������)
	double attackDelay; //���� ���� ��Ÿ��
	//������ �߰� �� ������ ���� Ȯ���� bool �Ǵ� enum ���� ����
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
	//������ �ʱ� ��ġ 0���� ����
	MeleeEnemy.pos.x = 0; 
	MeleeEnemy.pos.y = 0;
	//�÷��̾� ��ġ �ʱⰪ NULL
	MeleeEnemy.memory.x = NULL;
	MeleeEnemy.memory.y = NULL;
}

void InitArrowEnemy()
{	
	ArrowEnemy.hp = 30;
	ArrowEnemy.attackDelay = 2.0f;
	ArrowEnemy.attackDamage = 10;
	ArrowEnemy.moveSpeed = 3000;

	//������ �ʱ� ��ġ 0���� ����
	ArrowEnemy.pos.x = 0;
	ArrowEnemy.pos.y = 0;

	//����ü �ʱ� ��ġ NULL
	ArrowEnemy.arrowPos.x = NULL;
	ArrowEnemy.arrowPos.y = NULL;

	//�÷��̾� ��ġ �ʱⰪ NULL
	ArrowEnemy.memory.x = NULL;
	ArrowEnemy.memory.y = NULL;
}

void InitBombEnemy()
{
	BombEnemy.hp = 40;
	BombEnemy.attackDamage = 80;


	//���� ���ʹ� ó������ �÷��̾��� ��ǥ�� �˰� �ֱ� ������ ó�� ���� �� player�� ��ǥ�� ����
	BombEnemy.memory = player.pos;
	//������ �ʱ� ��ġ 0���� ����
	BombEnemy.pos.x = 0;
	BombEnemy.pos.y = 0;
	//�÷��̾� ��ġ �ʱⰪ NULL
	BombEnemy.memory.x = NULL;
	BombEnemy.memory.y = NULL;
}

void InitPlayer()
{
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//�ʱ���ġ 50���� �⺻����
	player.pos.x = 50;
	player.pos.y = 50;
}


//�ʿ� ���� �÷��̾�, ���� ���� ��ġ�� �ٲ� �� �ִ�.
