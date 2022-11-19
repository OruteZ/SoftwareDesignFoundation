#include "Mortal.h"
#include "Game.h"
#include "QuadTree.h"
#include "World.h"
void MortalMove(Mortal *mortal, Point direction)
{
	Rect next_position_rect = { .x = mortal->base.entity.pos.x + direction.x,
		.y = mortal->base.entity.pos.y + direction.y, 1,1 };
	
	Point next_pos = { .x = mortal->base.entity.pos.x + direction.x, .y = mortal->base.entity.pos.y + direction.y};
	Vector* vector = QuadTreeQuery(mortalsTree, next_position_rect);
	if (vector->length == 0 && !(GetTile(next_pos) & FLAG_COLLIDE_WITH_BODY)) 
	{
		mortal->base.entity.pos = next_pos;
	}
	DeleteVector(vector);
}
void EnemyMortalOnHit(Mortal* mortal, int playerDamage)
{
	mortal->hp -= playerDamage;
	if (mortal->hp <= 0)
	{
		//Delete Enemy, free Enemy
	}
}