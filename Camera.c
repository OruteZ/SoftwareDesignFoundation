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

int _cameraWidthInGame = 25;
int _cameraHeightInGame = 19;

Rect CameraRectInGame;
Rect CameraRectInCanvas;

const char enemyChar[] = "��";
const char playerChar[] = "��";
const char wallChar[] = "��";

Point IngamePosition_to_CanvasPosition(Point pos);

void InitCamera() {
	CameraRectInGame.height = _cameraHeightInGame;
	CameraRectInGame.width = _cameraWidthInGame;

	CameraRectInCanvas.height = _cameraHeightInGame;
	CameraRectInCanvas.width = 2 * _cameraWidthInGame;

	CameraRectInCanvas.x = 7;
	CameraRectInCanvas.y = 3;
}

Point IngamePosition_to_CanvasPosition(Point pos) {
	Point result;
	result.x = CameraRectInCanvas.x + (pos.x - CameraRectInGame.x) * 2;
	result.y = CameraRectInCanvas.y + (pos.y - CameraRectInGame.y);

	if (result.x % 2 == 0) {
#ifdef DEBUG
		DebugPrint("%d %d", result.x, result.y);
#endif
	}

	return result;
}

void DrawBox() {
	const char BoxChar[] = "��";
	int BoxLeft = CameraRectInCanvas.x - 2;
	int BoxRight = CameraRectInCanvas.x + CameraRectInCanvas.width;
	int BoxTop = CameraRectInCanvas.y - 1;
	int BoxBottom = CameraRectInCanvas.y + CameraRectInCanvas.height;

	for (int i = 0; i < CameraRectInCanvas.height + 2; i++) {
		ScreenPrint(BoxLeft, CameraRectInCanvas.y + i - 1, BoxChar);
		ScreenPrint(BoxRight, CameraRectInCanvas.y + i - 1, BoxChar);
	}

	for (int i = 0; i < CameraRectInCanvas.width + 4; i += 2) {
		ScreenPrint(CameraRectInCanvas.x + i - 2, BoxTop, BoxChar);
		ScreenPrint(CameraRectInCanvas.x + i - 2, BoxBottom, BoxChar);
	}
}

void PrintWorld() {
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
	Point printPos;

	int len = enemies->length;
	for (int i = 0; i < len; i++) {
		Enemy* e = (Enemy*)enemies->entities[i];
		if (!RectContainsPoint(&CameraRectInGame, &e->base.entity.pos)) continue;

		printPos = IngamePosition_to_CanvasPosition(e->base.entity.pos);
		ScreenPrint(printPos.x, printPos.y, enemyChar);
	}
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
	Point printPos;

	int len = particles->length;
	for (int i = 0; i < len; i++) {
		Particle* p = (Particle*)particles->entities[i];
		if (!RectIsIntersectingRect(&CameraRectInGame, &p->particleRect)) continue;

		for (int y = 0; y < p->particleRect.height; y++) {
			for (int x = 0; x < p->particleRect.width; x++) {
				Point inGamePos = { p->particleRect.x + x, p->particleRect.y + y };
				if (!RectContainsPoint(&CameraRectInGame, &inGamePos)) continue;

				printPos = IngamePosition_to_CanvasPosition(inGamePos);
				if (p->particleImage[y][x] != ' ') ScreenPrint(printPos.x, printPos.y, "��");
			}
		}
	}
}

//ī�޶��� ��ġ�� �÷��̾ �߽����� �����Ѵ�. ���� ���� ����Ǿ��� ��� true�� ��ȯ�Ѵ�.
bool SetCameraPoint()
{
	Point playerPos = GetPlayerPos();

	int newX = playerPos.x - (_cameraWidthInGame / 2);
	int newY = playerPos.y - (_cameraHeightInGame / 2);

	if (newX == CameraRectInGame.x && newY == CameraRectInGame.y) {
		return false;
	}
	else {
		CameraRectInGame.x = newX;
		CameraRectInGame.y = newY;
	}

	if (CameraRectInGame.x < 0) CameraRectInGame.x = 0;
	if (CameraRectInGame.y < 0) CameraRectInGame.y = 0;

	World* worldInfo = GetCurrentWorld();
	int worldWidth = worldInfo->width;
	int worldHeight = worldInfo->height;

	if (CameraRectInGame.x + CameraRectInGame.width >= worldWidth) CameraRectInGame.x = worldWidth - _cameraWidthInGame;
	if (CameraRectInGame.y + CameraRectInGame.height >= worldHeight) CameraRectInGame.y = worldHeight - _cameraHeightInGame;

	return true;
}

void RenderCamera()
{
	SetCameraPoint();
	PrintWorld();
	DrawBox();
	
	PrintEnemies();
	PrintPlayer();
	PrintParticles();
}