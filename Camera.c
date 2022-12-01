#include "Game.h"
#include "Rect.h"
#include<stdio.h>
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "QuadTree.h"
#include "Screen.h"
#include "Enemy.h"
#include "Particle.h"
#include "Debug.h"
#include "Time.h"

struct {
	Point pos;
	const Rect cell_rect;
} camera = {
	.pos = {.x = 0, .y = 0},
	.cell_rect = {.x = 8, .y = 1, .width = 23, .height = 23}
};

Point WorldPosToScreenCellIndex(Point pos) {
	Point screen_cell = {
		.x = pos.x - camera.pos.x + camera.cell_rect.x,
		.y = pos.y - camera.pos.y + camera.cell_rect.y
	};
	return screen_cell;
}
Rect CameraCellRectToWorldRect() {
	Rect world_rect = {
		.x = camera.pos.x,
		.y = camera.pos.y,
		.width = camera.cell_rect.width,
		.height = camera.cell_rect.height
	};
	return world_rect;
}

void PrintWorld() {
	for (int i = 0; i < camera.cell_rect.height; i++) {
		for (int j = 0; j < camera.cell_rect.width; j++) {
			Point tile_pos = { .x = camera.pos.x + j, .y = camera.pos.y + i };
			Point screen_cell_index = WorldPosToScreenCellIndex(tile_pos);


			switch (GetTile(tile_pos)) {
			case UNDEFINED_TILE:
			case PIT:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, ' ', 0);
				break;
			case GROUND:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, ' ', 0);
				break;
			case WALL:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x254b, BACKGROUND_RED | BACKGROUND_BLUE);
				break;
			case DOWNSTAIRS:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25a5, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
				break;
			}


		}
	}
}

void PrintEnemies()
{
	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		Point screen_cell_index = WorldPosToScreenCellIndex(e->base.entity.pos);
		if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {


			switch (e->base.entity.type) {
			case MeleeEnemyType:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c8, FOREGROUND_RED | FOREGROUND_GREEN);
				break;
			case ArcherEnemyType:
				break;
			case BomberEnemyType:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c8, FOREGROUND_RED | FOREGROUND_GREEN);
				break;
			default:
				break;
			}


		}
	}
}

void PrintPlayer()
{
	Point pos = {
		.x = player->base.entity.pos.x - camera.pos.x + camera.cell_rect.x,
		.y = player->base.entity.pos.y - camera.pos.y + camera.cell_rect.y
	};
	SetScreenCell(pos.x, pos.y, 0x25a3, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void PrintExpOrb() {
}

void PrintParticles() {
	Point printPos;

	for (int i = 0; i < particles->length; i++) {
		Particle* p = (Particle*)particles->entities[i];
		Rect camera_world_rect = CameraCellRectToWorldRect();

		if (!RectIsIntersectingRect(&camera_world_rect, &p->particleRect)) continue;

		for (int i = 0; i < p->particleRect.height; i++) {
			for (int j = 0; j < p->particleRect.width; j++) {
				Point world_pos = { .x = p->particleRect.x + j , .y = p->particleRect.y + i };
				Point screen_cell_index = WorldPosToScreenCellIndex(world_pos);
				if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {


					switch (p->particleType) {
					case MeleeAttackParticleType:
						SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c9, 0); // ¢Â
						break;
					case RangeAttackParticleType:
					case EnemyRangeAttackParticleType:
						SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25a2, 0); // ¡à
						break;
					case ExplosionParticleType1:
						SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x254b, 0); // ¦¶
						break;
					case ExplosionParticleType2:
						SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x2169, 0); // ¥¹
						break;
					}


				}
			}
		}
	}
}

void SetCameraPoint()
{
	camera.pos.x = player->base.entity.pos.x - camera.cell_rect.width / 2;
	camera.pos.y = player->base.entity.pos.y - camera.cell_rect.height / 2;

	return true;
}

void RenderCamera()
{
	SetCameraPoint();
	PrintWorld();
	
	PrintEnemies();
	PrintPlayer();
	PrintParticles();
}