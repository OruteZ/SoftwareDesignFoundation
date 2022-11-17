#include "Game.h"
#include "Rect.h"
#include<stdio.h>
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "QuadTree.h"

int _cameraWidth = 11;
int _cameraHeight = 9;

Rect CameraRect;

void InitCamera()
{
	CameraRect.height = _cameraHeight;
	CameraRect.width = _cameraWidth;
}

void PrintWorld()
{
	//2중 for문으로 돌면서 싹 출력
}

void PrintMortal()
{

}

void PrintExpOrb()
{
}

void SetCameraPoint()
{
	Point playerPos = GetPlayerPos();

	CameraRect.x = playerPos.x - (_cameraWidth / 2);
	CameraRect.y = playerPos.y - (_cameraHeight / 2);

	if (CameraRect.x < 0) CameraRect.x = 0;
	if (CameraRect.y < 0) CameraRect.y = 0;

	World* worldInfo = GetCurrentWorld();
	int worldWidth = worldInfo->width;
	int worldHeight = worldInfo->height;

	if (CameraRect.x + CameraRect.width >= worldWidth) CameraRect.x = worldWidth - _cameraWidth;
	if (CameraRect.y + CameraRect.height >= worldHeight) CameraRect.y = worldHeight - _cameraHeight;
}
