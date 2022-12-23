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
#include "ExpOrb.h"
#include "Boss.h"

struct {
	Point pos;
	const Rect cell_rect;
} camera = {
	.pos = {.x = 0, .y = 0},
	.cell_rect = {.x = 8, .y = 1, .width = 23, .height = 23}
};

const double shakingTime = 0.1;
double shakeCooldown;
int CameraOffsetX = 1;
int CameraOffsetY = 0;
void ShakeCamera() {
	if (shakeCooldown > 0) return;

#ifdef DEBUG
	DebugPrint("Shaking Camera");
#endif // DEBUG

	shakeCooldown = shakingTime;
}

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
	const World* current_world = GetCurrentWorld();
	const int height_world = current_world->height;
	const int width_world = current_world->width * 2;
	const int ground_grid_length = height_world * width_world;
	if (ground_grid_length == 0) return;

	const unsigned short ground_grid_color = FOREGROUND_RED | FOREGROUND_GREEN;
	int* ground_grid = malloc(sizeof(int) * ground_grid_length);
	if (ground_grid == NULL) exit(-1);
	srand(6);
	for (int i = 0; i < ground_grid_length; i++) {
		ground_grid[i] = rand() % 10;
	}

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
				for (int i = 0; i < 2; i++) {
					switch (ground_grid[tile_pos.y * height_world + tile_pos.x * 2 + i]) {
					case 0:
					case 7:
					case 8:
					case 9:
					default:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2800, ground_grid_color);
						break;
					case 1:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2801, ground_grid_color);
						break;
					case 2:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2802, ground_grid_color);
						break;
					case 3:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2804, ground_grid_color);
						break;
					case 4:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2808, ground_grid_color);
						break;
					case 5:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2810, ground_grid_color);
						break;
					case 6:
						SetScreenHalfCell(screen_cell_index.x * 2 + i, screen_cell_index.y, 0x2820, ground_grid_color);
						break;
					}
				}
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

	free(ground_grid);
}

void PrintEnemies()
{
	for (int i = 0; i < enemies->length; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		Point screen_cell_index = WorldPosToScreenCellIndex(e->base.entity.pos);
		if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {


			switch (e->base.entity.type) {
			case MeleeEnemyType:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c8, FOREGROUND_GREEN);
				break;

			case ArcherEnemyType:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c8, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;

			case BomberEnemyType:
				SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c8, FOREGROUND_RED);
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
	static const playerColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	if (PointEquals(&player->facing, &Direction.south)) {
		SetScreenCell(pos.x, pos.y, 0x25b2, playerColor);
	}
	else if (PointEquals(&player->facing, &Direction.east)) {
		SetScreenCell(pos.x, pos.y, 0x25b6, playerColor);
	}
	else if (PointEquals(&player->facing, &Direction.north)) {
		SetScreenCell(pos.x, pos.y, 0x25bc, playerColor);
	}
	else if(PointEquals(&player->facing, &Direction.west)){
		SetScreenCell(pos.x, pos.y, 0x25c0, playerColor);
	}
	else {
		SetScreenCell(pos.x, pos.y, 0x25a3, playerColor);
	}
}

void PrintExpOrb() {
	for (int i = 0; i < expOrbs->length; i++) {
		ExpOrb* e = (ExpOrb*)expOrbs->entities[i];

		if (e == NULL) continue;
		if (e->isDead) continue;

		Point world_pos = e->base.entity.pos;
		Point screen_cell_index = WorldPosToScreenCellIndex(world_pos);
		if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {
			SetScreenCell(screen_cell_index.x, screen_cell_index.y, 0x25c9, 15);
		}
	}

}

void PrintParticles() {
	Point printPos;

	int nowUnicode;
	int nowColor;


	for (int i = 0; i < particles->length; i++) {
		Particle* p = (Particle*)particles->entities[i];
		Rect camera_world_rect = CameraCellRectToWorldRect();

		//if (!RectIsIntersectingRect(&camera_world_rect, &p->particleRect)) continue;
		
		switch (p->particleType) {
		case MeleeAttackParticleType:
			if (p->facing.x == 0)
				nowUnicode = 0x2501;
			else
				nowUnicode = 0x2502;
			nowColor = 15;
			break;

		case RangeAttackParticleType:
		case EnemyRangeAttackParticleType:
			nowUnicode = 0x25a1; //¡à 
			nowColor = 15;
			break;

		case ExplosionParticleType1:
			nowUnicode = 0x254b; // ¦¶
			nowColor = FOREGROUND_RED;
			break;

		case ExplosionParticleType2:
			nowUnicode = 0x2169; // ¥¹
			nowColor = FOREGROUND_RED;
			break;
		}

		for (int i = 0; i < p->particleRect.height; i++) {
			for (int j = 0; j < p->particleRect.width; j++) {
				if (p->particleGrid[i][j] == false) continue;

				Point world_pos = { .x = p->particleRect.x + j , .y = p->particleRect.y + i };
				Point screen_cell_index = WorldPosToScreenCellIndex(world_pos);
				if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {

					SetScreenCell(screen_cell_index.x, screen_cell_index.y, nowUnicode, nowColor);
				}
			}
		}
	}
}

void PrintBoss() {
	if (!IsBossExist()) return;

	Rect bossRect = GetBossRect();

	for (int i = 0; i < bossRect.height; i++) {
		for (int j = 0; j < bossRect.width; j++) {

			Point world_pos = { .x = bossRect.x + j, .y = bossRect.y + i };
			Point screen_cell_index = WorldPosToScreenCellIndex(world_pos);
			if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {

				SetScreenCell(screen_cell_index.x, screen_cell_index.y, ' ', BACKGROUND_BLUE | BACKGROUND_RED);
			}
		}
	}

	//draw eye
	Point eyePos = GetBossPoint(), facing = GetBossFacing();
	PointAdd(&eyePos, &facing);
	Point screen_cell_index = WorldPosToScreenCellIndex(eyePos);
	if (RectContainsPoint(&camera.cell_rect, &screen_cell_index)) {
		SetScreenCell(screen_cell_index.x, screen_cell_index.y, ' ', BACKGROUND_RED);
	}
}

void SetCameraPoint()
{
	camera.pos.x = player->base.entity.pos.x - camera.cell_rect.width / 2;
	camera.pos.y = player->base.entity.pos.y - camera.cell_rect.height / 2;

	if (shakeCooldown > 0) {
		camera.pos.x += CameraOffsetX;
		camera.pos.y += CameraOffsetY;
	}

	return true;
}

void RenderCamera()
{
	shakeCooldown -= Time.deltaTime;

	SetCameraPoint();
	PrintWorld();

	PrintExpOrb();
	PrintEnemies();
	PrintPlayer();
	PrintBoss();
	PrintParticles();
}