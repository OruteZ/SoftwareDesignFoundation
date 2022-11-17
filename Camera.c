#include "Game.h"
#include "Rect.h"
#include<stdio.h>
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "QuadTree.h"

int _cameraWidth = 11;
int _cameraHeight = 9;

Rect CameraRectInGame;

Rect CameraRectInCanvas;

void InitCamera()
{
	CameraRectInGame.height = _cameraHeight;
	CameraRectInGame.width = _cameraWidth;
}

void PrintWorld()
{
	//2중 for문으로 돌면서 싹 출력
}

void PrintMortal()
{
	Vector* mortalsToPrint = QuadTreeQuery(mortalsTree, CameraRectInGame);
	


	DeleteVector(mortalsToPrint);
}

void PrintExpOrb()
{
}

void SetCameraPoint()
{
	Point playerPos = GetPlayerPos();

	CameraRectInGame.x = playerPos.x - (_cameraWidth / 2);
	CameraRectInGame.y = playerPos.y - (_cameraHeight / 2);

	if (CameraRectInGame.x < 0) CameraRectInGame.x = 0;
	if (CameraRectInGame.y < 0) CameraRectInGame.y = 0;

	World* worldInfo = GetCurrentWorld();
	int worldWidth = worldInfo->width;
	int worldHeight = worldInfo->height;

	if (CameraRectInGame.x + CameraRectInGame.width >= worldWidth) CameraRectInGame.x = worldWidth - _cameraWidth;
	if (CameraRectInGame.y + CameraRectInGame.height >= worldHeight) CameraRectInGame.y = worldHeight - _cameraHeight;
}
