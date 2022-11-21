#include "Player.h"
#include "Keyboard.h"
#include "Point.h"
#include "World.h"
#include "QuadTree.h"
#include "Rect.h"
#include "Game.h"
#include "Time.h"
#include "Enemy.h"
#include "Debug.h"
#include "Particle.h"

Player* player;

Player* CreatePlayer(Point spawnPoint)
{
	Player* _player = (Player*)malloc(sizeof(Player));

	_player->base.entity.type = _Player;
	_player->base.entity.pos.x = spawnPoint.x;
	_player->base.entity.pos.y = spawnPoint.y;

	_player->attackSpeed = 10.0f;
	_player->baseDamage = 20;
	_player->hp = 100;
	_player->moveSpeed = 12.0f;

	_player->exp = 0;
	_player->level = 0;
	_player->facing = Direction.north;

	_player->attackHeight = 0;
	_player->attackWidth = 2;
	return _player;
}

BOOL _canPlayerAttack = TRUE;
double _playerAttackCooldown;

BOOL _canPlayerMove = TRUE;
double _playerMoveCooldown;

void CalculatePlayerCooldown()
{
	_playerAttackCooldown -= Time.deltaTime;
	_playerMoveCooldown -= Time.deltaTime;

	if (_playerAttackCooldown < 0) _canPlayerAttack = TRUE;
	if (_playerMoveCooldown < 0) _canPlayerMove = TRUE;
}

void PlayerMove(Point dir)
{
	if (!_canPlayerMove) return;

	Point destPos = player->base.entity.pos;
	PointAdd(&destPos, &dir);

	if (GetTile(destPos) & FLAG_COLLIDE_WITH_BODY) return;

	player->base.entity.pos = destPos;
	player->facing = dir;

	_canPlayerMove = FALSE;
	_playerMoveCooldown = 1 / (player->moveSpeed);
}

Rect CreatePlayerAttackRect(Point middle, Point direction) {
	Rect result;
	if (direction.x == 0) { //���� ���� -> ���ζ���
		result.x = middle.x - (player->attackWidth / 2);
		result.y = middle.y - (player->attackHeight / 2);

		result.height = player->attackHeight;
		result.width = player->attackWidth;
	}

	else { //�¿���� -> ���ζ���
		result.x = middle.x - (player->attackHeight / 2);
		result.y = middle.y - (player->attackWidth / 2);

		result.height = player->attackWidth;
		result.width = player->attackHeight;
	}

	return result;
}

void PlayerAttack()
{
	if (!_canPlayerAttack) return;

	Point attackPoint = player->base.entity.pos;
	PointAdd(&attackPoint, &player->facing);
#ifdef DEBUG
	DebugPrint("Player Attack, %d %d", attackPoint.x, attackPoint.y);
#endif 


	Rect attackRect = CreatePlayerAttackRect(attackPoint, player->facing);
	CreateParticle(player->facing, attackPoint, AttackParticleType);


	/* ���� ����Ʈ�� ���� ����
	Vector* hitted_enemys = QuadTreeQuery(enemiesTree, attackRect);

	int len = hitted_enemys->length;
	for (int i = 0; i < len; i++) 
	{
		Enemy* e = (Enemy*)(hitted_enemys->entities)[i];

		if (e->base.entity.type != _Player)
		{
			// m -> getDamage(); -> �ӽ�
		}
	}

	DeleteVector(hitted_enemys);
	*/

	int len = enemies->length;
	for (int i = 0; i < len; i++) {
		Enemy* e = enemies->entities[i];
		if (RectContainsPoint(&attackRect, &e->base.entity.pos)) {
			//EnemyOnHit();
		}
	}

	_canPlayerAttack = FALSE;
	_playerAttackCooldown = 1 - (player->attackSpeed);

#ifdef DEBUG
	DebugPrint("Player Attacked");
#endif
}

void UpdatePlayer() {
	if (player == NULL) return;

	if (GetKey('W')) PlayerMove(Direction.south);
	if (GetKey('A')) PlayerMove(Direction.west);
	if (GetKey('S')) PlayerMove(Direction.north);
	if (GetKey('D')) PlayerMove(Direction.east);

	if (GetKeyDown(VK_SPACE)) PlayerAttack();

	CalculatePlayerCooldown();
}

Point GetPlayerPos() { return player->base.entity.pos; }

void PlayerOnHit(int damage)
{
	player->hp -= damage;
	if (player->hp <= 0) {
		// gameover;
	}
}


