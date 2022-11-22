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

	_player->attackHeight = 1;
	_player->attackWidth = 3;
	return _player;
}

BOOL _canPlayerMeleeAttack = TRUE;
bool _canPlayerRangeAttack = true;

BOOL _canPlayerMove = TRUE;
double _playerMoveCooldown;

double _playerAttackDelay = 0.15f;

void CalculatePlayerCooldown() {
	_playerAttackDelay -= Time.deltaTime;
	_playerMoveCooldown -= Time.deltaTime;

	if (_playerAttackDelay < 0) {
		_canPlayerMeleeAttack = TRUE;
		_canPlayerRangeAttack = true;
	}
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

void PlayerMeleeAttack() {
	if (!_canPlayerMeleeAttack) return;

	Point attackPoint = player->base.entity.pos;
	PointAdd(&attackPoint, &player->facing);


	Rect attackRect = CreatePlayerAttackRect(attackPoint, player->facing);
	CreateParticle(player->facing, attackPoint, MeleeAttackParticleType);


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
			EnemyOnHit(e, player->baseDamage);
		}
	}

	_canPlayerMeleeAttack = FALSE;
	_playerAttackDelay = 1 - (player->attackSpeed);

	if (_playerMoveCooldown < _playerAttackDelay) {
		_canPlayerMove = FALSE;
		_playerMoveCooldown = _playerAttackDelay;
	}

#ifdef DEBUG
	DebugPrint("Player Attacked");
#endif
}

void PlayerRangeAttack() {
	if (!_canPlayerRangeAttack) return;

	CreateParticle(player->facing, player->base.entity.pos, RangeAttackParticleType);

#ifdef DEBUG
	DebugPrint("Created Range Particle");
#endif

	_canPlayerRangeAttack = false;
	_playerAttackDelay = 1 - (player->attackSpeed);
	if (_playerMoveCooldown < _playerAttackDelay) {
		_canPlayerMove = FALSE;
		_playerMoveCooldown = _playerAttackDelay;
	}
}

void UpdatePlayer() {
	if (player == NULL) return;

	if (GetKeyDown('W')) PlayerMove(Direction.south);
	if (GetKeyDown('A')) PlayerMove(Direction.west);
	if (GetKeyDown('S')) PlayerMove(Direction.north);
	if (GetKeyDown('D')) PlayerMove(Direction.east);

	if (GetKeyDown(VK_SPACE)) PlayerMeleeAttack();
	if (GetKeyDown('J')) PlayerRangeAttack();

	CalculatePlayerCooldown();
}

Point GetPlayerPos() { return player->base.entity.pos; }

void PlayerOnHit(int damage) {
	player->hp -= damage;
	if (player->hp <= 0) {
		// gameover;
	}
}


