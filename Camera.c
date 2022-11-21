#include "Game.h"
#include "Rect.h"
#include<stdio.h>
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "QuadTree.h"
#include "Screen.h"
#include "Enemy.h"

int _cameraWidthInGame = 25;
int _cameraHeightInGame = 19;

Rect CameraRectInGame;
Rect CameraRectInCanvas;

const char enemyChar[] = "ee";
const char playerChar[] = "pp";
const char wallChar[] = "WW";

Point IngamePosition_to_CanvasPosition(Point pos);

void InitCamera()
{
	CameraRectInGame.height = _cameraHeightInGame;
	CameraRectInGame.width = _cameraWidthInGame;

	CameraRectInCanvas.height = _cameraHeightInGame;
	CameraRectInCanvas.width = 2 * _cameraWidthInGame;

	CameraRectInCanvas.x = 7;
	CameraRectInCanvas.y = 7;
}

Point IngamePosition_to_CanvasPosition(Point pos)
{
	Point result;
	result.x = CameraRectInCanvas.x + (pos.x - CameraRectInGame.x) * 2;
	//result.y = CameraRectInCanvas.y + (CameraRectInCanvas.height - (pos.y - CameraRectInGame.y));
	result.y = CameraRectInCanvas.x + (pos.y - CameraRectInGame.y);

	return result;
}

void PrintWorld()
{
	for (int dx = 0; dx < CameraRectInGame.width; dx++) {
		for (int dy = 0; dy < CameraRectInGame.height; dy++) {
			int x = CameraRectInGame.x + dx;
			int y = CameraRectInGame.y + dy;
			Point p = { x, y };
			Point q = IngamePosition_to_CanvasPosition(p);

			if (GetTile(p) == WALL) ScreenPrint(q.x, q.y, wallChar);
			else ScreenPrint(q.x, q.y, "  ");
		}
	}
}

void PrintEnemies()
{
	Vector* enemiesToPrint = QuadTreeQuery(enemiesTree, CameraRectInGame);
	Point printPos;

	int len = enemiesToPrint->length;
	for (int i = 0; i < len; i++) {
		Enemy* e = enemiesToPrint->entities[i];

		printPos = IngamePosition_to_CanvasPosition(e->base.entity.pos);
		ScreenPrint(printPos.x, printPos.y, enemyChar);
	}

	DeleteVector(enemiesToPrint);
}

void PrintPlayer()
{
	Point playerPos = player->base.entity.pos;
	if (RectContainsPoint(&CameraRectInGame, &playerPos)) {
		Point printPos = IngamePosition_to_CanvasPosition(playerPos);
		ScreenPrint(printPos.x, printPos.y, playerChar);
	}
}

void PrintExpOrb()
{
}

void PrintParticles() {
	
}

void SetCameraPoint()
{
	Point playerPos = GetPlayerPos();

	CameraRectInGame.x = playerPos.x - (_cameraWidthInGame / 2);
	CameraRectInGame.y = playerPos.y - (_cameraHeightInGame / 2);

	if (CameraRectInGame.x < 0) CameraRectInGame.x = 0;
	if (CameraRectInGame.y < 0) CameraRectInGame.y = 0;

	World* worldInfo = GetCurrentWorld();
	int worldWidth = worldInfo->width;
	int worldHeight = worldInfo->height;

	if (CameraRectInGame.x + CameraRectInGame.width >= worldWidth) CameraRectInGame.x = worldWidth - _cameraWidthInGame;
	if (CameraRectInGame.y + CameraRectInGame.height >= worldHeight) CameraRectInGame.y = worldHeight - _cameraHeightInGame;
}

void RenderCamera()
{
	SetCameraPoint();
	PrintWorld();
	PrintEnemies();
	PrintPlayer();
}