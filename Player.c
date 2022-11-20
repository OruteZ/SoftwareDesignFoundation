#include "Player.h"
#include "Keyboard.h"
#include "Point.h"
#include "World.h"
#include "QuadTree.h"
#include "Rect.h"
#include "Game.h"
#include "Time.h"
#include "Enemy.h"

Player* player;

Player* CreatePlayer(Point p)
{
	Player* _player = (Player*)malloc(sizeof(Player));

	_player->base.entity.type = _Player;
	_player->base.entity.pos.x = p.x;
	_player->base.entity.pos.y = p.y;

	_player->attackSpeed = 1.0f;
	_player->baseDamage = 20;
	_player->hp = 100;
	_player->moveSpeed = 2.0f;

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

void UpdatePlayer() {
	if (player == NULL) return;

	if (GetKeyDown('W')) PlayerMove(Direction.south);
	if (GetKeyDown('A')) PlayerMove(Direction.west);
	if (GetKeyDown('S')) PlayerMove(Direction.north);
	if (GetKeyDown('D')) PlayerMove(Direction.east);

	if (GetKeyDown("VK_SPACE")) PlayerAttack();

	CalculatePlayerCooldown();
}

void PlayerMove(Point dir)
{
	if (!_canPlayerMove) return;

	Point destPos = player->base.entity.pos;
	PointAdd(&destPos, &dir);

	if (GetTile(destPos) & FLAG_COLLIDE_WITH_BODY) return;

	player->base.entity.pos = destPos;
	player->facing = destPos;

	_canPlayerMove = FALSE;
	_playerMoveCooldown = 1 / (player->moveSpeed);
}

Rect CreatePlayerAttackRect(Point middle, Point direction) {
	Rect result;
	if (direction.x == 0) { //상하 공격 -> 가로라인
		result.x = middle.x - (player->attackWidth / 2);
		result.y = middle.y - (player->attackHeight / 2);

		result.height = player->attackHeight;
		result.width = player->attackWidth;
	}

	else { //좌우공격 -> 세로라인
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

	Rect attackRect = CreatePlayerAttackRect(attackPoint, player->facing);

	/* 차후 쿼드트리 사용시 변경
	Vector* hitted_enemys = QuadTreeQuery(enemiesTree, attackRect);

	int len = hitted_enemys->length;
	for (int i = 0; i < len; i++) 
	{
		Enemy* e = (Enemy*)(hitted_enemys->entities)[i];

		if (e->base.entity.type != _Player)
		{
			// m -> getDamage(); -> 임시
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
}

Point GetPlayerPos() { return player->base.entity.pos; }

void PlayerOnHit(int damage)
{
	player->hp -= damage;
	if (player->hp <= 0) {
		// gameover;
	}
}


