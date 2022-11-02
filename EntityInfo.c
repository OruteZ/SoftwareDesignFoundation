#include "Point.h"
#include "EntityInfo.h"

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
	Point memory;
	Point pos;
	int hp; 
	int attackDamage;
	int moveSpeed; 
	int arrowSpeed; //����ü �ӵ�
	double attackDelay;
}arrowEnemy;

//���� ���� ����ü
typedef struct bombEnemy
{
	Point memory;
	Point pos; 
	int hp;
	int attackDamage;
	int moveSpeed;

}bombEnemy;

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


Player player;

//���� ���� ����
meleeEnemy CreateMeleeEnemy(Point p)
{
	meleeEnemy MeleeEnemy;
	MeleeEnemy.hp = 50;
	MeleeEnemy.attackDelay = 3.0f;
	MeleeEnemy.attackDamage = 15;
	MeleeEnemy.moveSpeed = 1500;

	//������ �ʱ� ��ġ Point ���ڷ� �����ؼ� �ʿ� ��ġ��Ű��
	MeleeEnemy.pos.x = p.x; 
	MeleeEnemy.pos.y = p.y;

	//�÷��̾� ��ġ �ʱⰪ NULL
	MeleeEnemy.memory.x = NULL;
	MeleeEnemy.memory.y = NULL;
	return MeleeEnemy;
}

//���Ÿ� ���� ����
 arrowEnemy CreateArrowEnemy(Point p)
{	
	arrowEnemy ArrowEnemy;
	ArrowEnemy.hp = 30;
	ArrowEnemy.attackDelay = 2.0f;
	ArrowEnemy.attackDamage = 10;
	ArrowEnemy.moveSpeed = 3000;

	ArrowEnemy.pos.x = p.x;
	ArrowEnemy.pos.y = p.y;

	//����ü �ʱ� ��ġ NULL
	ArrowEnemy.arrowPos.x = NULL;
	ArrowEnemy.arrowPos.y = NULL;

	ArrowEnemy.memory.x = NULL;
	ArrowEnemy.memory.y = NULL;
	return ArrowEnemy;
}

//���� ���� ����
bombEnemy CreateBombEnemy(Point p)
{
	bombEnemy BombEnemy;
	BombEnemy.hp = 40;
	BombEnemy.attackDamage = 80;
	BombEnemy.moveSpeed = 2000;

	//���� ���ʹ� ó������ �÷��̾��� ��ǥ�� �˰� �ֱ� ������ ó�� ���� �� memory�� player�� ��ǥ�� ����
	BombEnemy.memory = player.pos;


	BombEnemy.pos.x = p.x;
	BombEnemy.pos.y = p.y;
	return BombEnemy;
}

//���� ���� �� ó�� �÷��̾� �����ϱ�
void CreatePlayer(Point p)
{
	player.hp = 100;
	player.meleeDamage = 15;
	player.attackDelay = 1.5f;
	player.moveSpeed = 500;
	//�ʱ���ġ ���ڷ� �޾Ƽ� ĳ���� ����

	player.pos.x = p.x;
	player.pos.y = p.y;
}
