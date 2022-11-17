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

	player->base.mortal.attackCooldown = 1.0f;
	player->base.mortal.baseDamage = 20;
	player->base.mortal.hp = 100;
	player->base.mortal.moveSpeed = 2.0f;

	player->exp = 0;
	player->level = 0;
	player->headed_direction = Up;

	player->attack_height = 0;
	player->attack_width = 2;
	return player;
}

BOOL _canPlayerAttack = TRUE;
double _playerAttackCooldown;

BOOL _canPlayerMove = TRUE;
double _playerMoveCooldown;

void UpdatePlayer() {
	if (_player == NULL) return;

	if (GetKeyDown("W")) PlayerMove(Up);
	if (GetKeyDown("S")) PlayerMove(Down);
	if (GetKeyDown("D")) PlayerMove(Right);
	if (GetKeyDown("A")) PlayerMove(Left);

	if (GetKeyDown("VK_SPACE")) PlayerAttack();

	CalculatePlayerCooldown();
}

void PlayerMove(direction dir)
{
	if (!_canPlayerMove) return;

	int dy[4] = {0, 0, -1, 1};
	int dx[4] = {-1, 1, 0, 0};

	Point destination_position = _player->base.entity.pos;

	if (GetTile(destination_position) & FLAG_COLLIDE_WITH_BODY) return;

	_player->base.entity.pos = destination_position;
	_player->headed_direction = dir;

	_canPlayerMove = FALSE;
	_playerMoveCooldown = 1 / (_player->base.mortal.moveSpeed);
}

void PlayerAttack()
{
	if (!_canPlayerAttack) return;

	Rect* attack_rect = NULL;
	Point player_pos = _player->base.entity.pos;

	if (_player->headed_direction == Up) attack_rect = CreateRect(player_pos.x-1, player_pos.y-1, 2, 0);
	if (_player->headed_direction == Down) attack_rect = CreateRect(player_pos.x-1, player_pos.y+1, 2, 0);
	if (_player->headed_direction == Left) attack_rect = CreateRect(player_pos.x-1, player_pos.y-1, 0, 2);
	if (_player->headed_direction == Right) attack_rect = CreateRect(player_pos.x+1, player_pos.y-1, 0, 2);

	Vector* hitted_enemys = QuadTreeQuery(mortalsTree, *attack_rect);

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
	DeleteRect(attack_rect);

	_canPlayerAttack = FALSE;
	_playerAttackCooldown = _player->base.mortal.attackCooldown;
}

Point GetPlayerPos() { return _player->base.entity.pos; }

void CalculatePlayerCooldown()
{
	_playerAttackCooldown -= Time.deltaTime;
	_playerMoveCooldown -= Time.deltaTime;

	if (_playerAttackCooldown < 0) _canPlayerAttack = TRUE;
	if (_playerMoveCooldown < 0) _canPlayerMove = TRUE;
}

void PlayerOnHit(int damage)
{
	_player->base.mortal.hp -= damage;
	if (_player->base.mortal.hp <= 0) {
		// gameover;
	}
}


