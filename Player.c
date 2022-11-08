#include "Point.h"
#include "Player.h"

Player* CreatePlayer(Point p)
{
	Player* player;
	player->base.entity.type = _Player;
	player->base.entity.pos.x = p.x;
	player->base.entity.pos.y = p.y;
	player->base.mortal.attackCooldown = 1.0f;
	player->base.mortal.baseDamage = 20;
	player->base.mortal.hp = 100;
	player->base.mortal.moveSpeed = 0.5f;
	return player;
}