#include "Point.h"
#include "EntityInfo.h"

//�θ� ���� ����ü
typedef struct Enemy
{
	int hp; //ü��
	int attackDamage; //���ݷ�
	int moveSpeed;//�̵� �ӵ�
	double attackDelay;//���� ��Ÿ��
	Point memory;//���Ͱ� ����� �÷��̾��� ��ġ
	Point pos; //������ ��ġ
}Enemy;


//�ٰŸ� ���� ����ü
typedef struct MeleeEnemy
{
	Enemy enemy;
}MeleeEnemy;

//���Ÿ� ���� ����ü
typedef struct RangeEnemy
{
	Enemy enemy;
	Point rangePos; // ���Ÿ� ���� ����ü�� ��ġ
	int rangeSpeed; //����ü �ӵ�
}RangeEnemy;

//���� ���� ����ü
typedef struct BombEnemy
{
	Enemy enemy;

}BombEnemy;

//�÷��̾� ����ü
typedef struct Player
{
	Point pos; 
	int hp;
	int meleeDamage;
	int moveSpeed; 
	double attackDelay;
	//������ �߰� �� ������ ���� Ȯ���� bool �Ǵ� enum ���� ����
}Player;


//���� ���� ����
MeleeEnemy *CreateMeleeEnemy(Point p)
{
	MeleeEnemy *meleeEnemy;
	meleeEnemy = (MeleeEnemy*)malloc(sizeof(MeleeEnemy));
	meleeEnemy->enemy.hp = 50;
	meleeEnemy->enemy.attackDelay = 3.0f;
	meleeEnemy->enemy.attackDamage = 15;
	meleeEnemy->enemy.moveSpeed = 1500;

	//������ �ʱ� ��ġ Point ���ڷ� �����ؼ� �ʿ� ��ġ��Ű��
	meleeEnemy->enemy.pos.x = p.x; 
	meleeEnemy->enemy.pos.y = p.y;

	//�÷��̾� ��ġ �ʱⰪ NULL
	meleeEnemy->enemy.memory.x = NULL;
	meleeEnemy->enemy.memory.y = NULL;
	return meleeEnemy;
}

//���Ÿ� ���� ����
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

	//����ü �ʱ� ��ġ NULL
	rangeEnemy->rangePos.x = NULL;
	rangeEnemy->rangePos.y = NULL;
	return rangeEnemy;
}

//���� ���� ����
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

//���� ���� �� ó�� �÷��̾� �����ϱ�
Player* CreatePlayer(Point p)
{
	Player* player;
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//�ʱ���ġ ���ڷ� �޾Ƽ� ĳ���� ����

	player.pos.x = p.x;
	player.pos.y = p.y;
}
