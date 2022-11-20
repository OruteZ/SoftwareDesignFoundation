#include "Game.h"
#include "Rect.h"
#include <stdio.h>
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "QuadTree.h"
#include "Screen.h"

int _cameraWidthInGame = 11;
int _cameraHeightInGame = 9;

Rect CameraRectInGame;
Rect CameraRectInCanvas;

const char enemyChar[] = "ee";
const char playerChar[] = "pp";

void InitCamera()
{
	CameraRectInGame.height = _cameraHeightInGame;
	CameraRectInGame.width = _cameraWidthInGame;

	CameraRectInCanvas.height = _cameraHeightInGame;
	CameraRectInCanvas.width = 2 * _cameraWidthInGame;
}

Point IngamePosition_to_CanvasPosition(Point pos)
{
	Point result;
	result.x = CameraRectInCanvas.x + pos.x * 2;
	result.y = CameraRectInCanvas.y + (CameraRectInCanvas.height - pos.y);

	return result;
}

void PrintWorld()
{
	//2중 for문으로 돌면서 싹 출력
}

void PrintMortal()
{
	Vector* mortalsToPrint = QuadTreeQuery(enemiesTree, CameraRectInGame);
	Point printPos;

	int len = mortalsToPrint->length;
	for (int i = 0; i < len; i++) {
		Mortal* m = mortalsToPrint->entities[i];

		printPos = IngamePosition_to_CanvasPosition(m->base.entity.pos);

		if (m->base.entity.type == _Player) ScreenPrint(printPos.x, printPos.y, playerChar);
		else ScreenPrint(printPos.x, printPos.y, enemyChar);
	}

	DeleteVector(mortalsToPrint);
}

void PrintExpOrb()
{
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
