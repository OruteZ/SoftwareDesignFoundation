#include "Player.h"
#include "Keyboard.h"
#include "Point.h"
#include "World.h"
#include "QuadTree.h"
#include "Rect.h"


Player* player;

Player* CreatePlayer(Point p)
{
	Player* player = (Player*)malloc(sizeof(Player));

	player->base.entity.type = _Player;
	player->base.entity.pos.x = p.x;
	player->base.entity.pos.y = p.y;

	player->base.mortal.attackCooldown = 1.0f;
	player->base.mortal.baseDamage = 20;
	player->base.mortal.hp = 100;
	player->base.mortal.moveSpeed = 0.5f;

	player->exp = 0;
	player->level = 0;
	player->headed_direction = Up;

	player->attack_height = 0;
	player->attack_width = 2;
	return player;
}

void UpdatePlayer() {
	if (player == NULL) return;


}

void PlayerMove(direction dir)
{
	int dy[4] = {0, 0, -1, 1};
	int dx[4] = {-1, 1, 0, 0};

	Point destination_position = player->base.entity.pos;

	if (!(GetTile(destination_position) & FLAG_COLLIDE_WITH_BODY)) 
	{
		player->base.entity.pos = destination_position;
		player->headed_direction = dir;
	}
}

void PlayerAttack()
{
	RECT* attack_rect;
	Point player_pos = player->base.entity.pos;

	if (player->headed_direction == Up) attack_rect = CreateRect(player_pos.x-1, player_pos.y+1, 2, 0);
	if (player->headed_direction == Down) attack_rect = CreateRect(player_pos.x-1, player_pos.y-1, 2, 0);
	if (player->headed_direction == Left) attack_rect = CreateRect(player_pos.x-1, player_pos.y-1, 2, 0);
	if (player->headed_direction == Right) attack_rect = CreateRect(player_pos.x+1, player_pos.y-1, 2, 0);

	//Vector* hitted_enemys = QuadTreeQuery()
	// 문의 해야 될 부분 : QuadTreeQuery에서 어떤 tree를 삽입해야 하는가? 모든 엔티티를 포함하는
	Vector* hitted_entities = CreateVector(); // 임시

	int len = hitted_entities->length;
	for (int i = 0; i < len; i++) {
		Entity* e = (hitted_entities->entities)[i];
	}
}
