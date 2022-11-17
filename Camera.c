#include "Game.h"
#include "Rect.h"
#include<stdio.h>
#include "Camera.h"
#include "Player.h"

Point CameraPoint;

int _cameraWidth = 11;
int _cameraHeight = 9;

Rect CameraRect;

void PrintWorld()
{
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

	CameraPoint.x = playerPos.x - (_cameraWidth / 2);
	CameraPoint.y = playerPos.y - (_cameraHeight / 2);

	if(CameraPoint.x < 0)
}
