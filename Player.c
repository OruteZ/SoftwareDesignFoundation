#include "Player.h"
#include "Keyboard.h"
#include "Point.h"
#include "World.h"
#include "QuadTree.h"
#include "Rect.h"
#include "Game.h"
#include "Time.h"

Player* _player;

Player* CreatePlayer(Point p)
{
	Player* player = (Player*)malloc(sizeof(Player));

	player->base.entity.type = _Player;
	player->base.entity.pos.x = p.x;
	player->base.entity.pos.y = p.y;

	player->attackSpeed = 1.0f;
	player->baseDamage = 20;
	player->hp = 100;
	player->moveSpeed = 2.0f;

	player->exp = 0;
	player->level = 0;
	player->facing = Direction.north;

	player->attackHeight = 0;
	player->attackWidth = 2;
	return player;
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
	if (_player == NULL) return;


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

	Point destPos = _player->base.entity.pos;
	PointAdd(&destPos, &dir);

	if (GetTile(destPos) & FLAG_COLLIDE_WITH_BODY) return;

	_player->base.entity.pos = destPos;
	_player->facing = destPos;

	_canPlayerMove = FALSE;
	_playerMoveCooldown = 1 / (_player->moveSpeed);
}

void PlayerAttack()
{
	if (!_canPlayerAttack) return;

	Rect* attackRect = NULL;
	Point playerPos = _player->base.entity.pos;

	if (_player->facing == Direction.south) attackRect = CreateRect(playerPos.x-1, playerPos.y-1, 3, 1);
	if (_player->facing == Direction.north) attackRect = CreateRect(playerPos.x-1, playerPos.y+1, 3, 1);
	if (_player->facing == Left) attackRect = CreateRect(playerPos.x-1, playerPos.y-1, 1, 3);
	if (_player->headed_direction == Right) attackRect = CreateRect(playerPos.x+1, playerPos.y-1, 1, 3);

	Vector* hitted_enemys = QuadTreeQuery(enemiesTree, *attackRect);

	int len = hitted_enemys->length;
	for (int i = 0; i < len; i++) 
	{
		Mortal* e = (Mortal*)(hitted_enemys->entities)[i];

		if (e->base.entity.type != _Player)
		{
			Mortal* m = (Mortal*)e;

			// m -> getDamage(); -> юс╫ц
		}
	}

	DeleteVector(hitted_enemys);
	DeleteRect(attackRect);

	_canPlayerAttack = FALSE;
	_playerAttackCooldown = _player->base.mortal.attackCooldown;
}

Point GetPlayerPos() { return _player->base.entity.pos; }



void PlayerOnHit(int damage)
{
	_player->base.mortal.hp -= damage;
	if (_player->base.mortal.hp <= 0) {
		// gameover;
	}
}


