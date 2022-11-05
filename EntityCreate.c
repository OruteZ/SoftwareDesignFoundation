#include "ArcherEnemy.h"
#include "BomberEnemy.h"
#include "Entity.h"
#include "MeleeEnemy.h"
#include "Mortal.h"
#include "Point.h"
#include "Player.h"

MeleeEnemy* CreateMeleeEnemy(Point p)
{
	MeleeEnemy* meleeEnemy;
	meleeEnemy->base.entity.type = _MeleeEnemy;
	meleeEnemy->base.entity.pos.x = p.x;
	meleeEnemy->base.entity.pos.y = p.y;
	meleeEnemy->base.mortal.attackCooldown = 2.0f;
	meleeEnemy->base.mortal.baseDamage = 15;
	meleeEnemy->base.mortal.hp = 40;
	meleeEnemy->base.mortal.moveSpeed = 1.0f;
	return meleeEnemy;
}

ArcherEnemy* CreateArcherEnemy(Point p)
{
	ArcherEnemy* archerEnemy;
	archerEnemy->base.entity.type = _ArcherEnemy;
	archerEnemy->base.entity.pos.x = p.x;
	archerEnemy->base.entity.pos.y = p.y;
	archerEnemy->base.mortal.attackCooldown = 3.0f;
	archerEnemy->base.mortal.baseDamage = 10;
	archerEnemy->base.mortal.hp = 30;
	archerEnemy->base.mortal.moveSpeed = 2.0f;
	archerEnemy->arrowSpeed = 0.5f;
	return archerEnemy;
}

BomberEnemy* CreateBomberEnemy(Point p)
{
	BomberEnemy* bomberEnemy;
	bomberEnemy->base.entity.type = _BomberEnemy;
	bomberEnemy->base.entity.pos.x = p.x;
	bomberEnemy->base.entity.pos.y = p.y;
	bomberEnemy->base.mortal.attackCooldown = 0; //ÀÚÆøÀÌ¶ó ÄðÅ¸ÀÓ ¾øÀ½
	bomberEnemy->base.mortal.baseDamage = 50;
	bomberEnemy->base.mortal.hp = 30;
	bomberEnemy->base.mortal.moveSpeed = 0.5f;
	bomberEnemy->blastRadius = 3.0f; //Æø¹ß ¹üÀ§ ¹ÌÁ¤
	return bomberEnemy;
}

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

