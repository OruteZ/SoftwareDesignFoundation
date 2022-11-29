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

int _cameraWidthInGame = 51;
int _cameraHeightInGame = 21;
int _cameraStartX = 17;
int _cameraStartY = 3;

Rect CameraRectInGame;
Rect CameraRectInCanvas;

const char enemyChar[] = "◎";
const char playerChar[] = "▣";
const char wallChar[] = "▒";

const char MeleeAttackChar[] = "◈";
const char RangeAttackChar[] = "RR";

const char ExplosionChar1[] = "qq";
const char ExplosionChar2[] = "pp";

char** BufferToPrintWorld;

void InitCamera() {
	CameraRectInGame.height = _cameraHeightInGame;
	CameraRectInGame.width = _cameraWidthInGame;

	CameraRectInCanvas.height = _cameraHeightInGame;
	CameraRectInCanvas.width = 2 * _cameraWidthInGame;

	CameraRectInCanvas.x = _cameraStartX;
	CameraRectInCanvas.y = _cameraStartY;

	BufferToPrintWorld = (char**)malloc(sizeof(char*) * (CameraRectInCanvas.height));
	if (BufferToPrintWorld == NULL) exit(-1);
	for (int i = 0; i < CameraRectInCanvas.height; i++) {
		BufferToPrintWorld[i] = (char*)malloc(sizeof(char) * CameraRectInCanvas.width);
		if (BufferToPrintWorld[i] == NULL) exit(-1);
	}
}

Point IngamePosition_to_CanvasPosition(Point pos) {
	Point result;
	result.x = CameraRectInCanvas.x + (pos.x - CameraRectInGame.x) * 2;
	result.y = CameraRectInCanvas.y + (pos.y - CameraRectInGame.y);

#ifdef DEBUG
	if (result.x % 2 == 1) {
		//DebugPrint("%d %d", result.x, result.y);

	}
#endif

	return result;
}

void DrawBox() {
	const char BoxChar[] = "■";
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
			//else ScreenPrint(q.x, q.y, "  ");

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

		if (isEnemyStiff(e)) SetColor(3);
		ScreenPrint(printPos.x, printPos.y, enemyChar);
		SetColor(15);
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

		if (!RectIsIntersectingRect(&CameraRectInGame, &p->particleRect)) {

			continue;
		}


		char nowChar[3];
		switch (p->particleType) {
		case MeleeAttackParticleType:
			strcpy(nowChar, MeleeAttackChar);
			break;

		case RangeAttackParticleType:
		case EnemyRangeAttackParticleType:
			strcpy(nowChar, RangeAttackChar);
			break;

		case ExplosionParticleType1:
			strcpy(nowChar, ExplosionChar1);
			break;

		case ExplosionParticleType2:
			strcpy(nowChar, ExplosionChar2);
			break;
		}

		for (int y = 0; y < p->particleRect.height; y++) {
			for (int x = 0; x < p->particleRect.width; x++) {
				Point inGamePos = { p->particleRect.x + x, p->particleRect.y + y };
				if (!RectContainsPoint(&CameraRectInGame, &inGamePos)) continue;

				printPos = IngamePosition_to_CanvasPosition(inGamePos);
				if (p->particleGrid[y][x]) {
					ScreenPrint(printPos.x, printPos.y, nowChar);
				}
			}
		}
	}
}

//카메라의 위치를 플레이어를 중심으로 설정한다. 만약 값이 변경되었을 경우 true를 반환한다.
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

bool isShaking = false;
double ShakingTime = 0;
double BaseShakingTime = 0.1f;

void CameraShake() {
	if (isShaking) return;

	CameraRectInCanvas.x++;
	isShaking = true;

	ShakingTime = BaseShakingTime;
}

void UpdateShakingTime() {
	ShakingTime -= Time.deltaTime;

	if (ShakingTime <= 0) {
		isShaking = false;

		CameraRectInCanvas.x--;
		//CameraRectInGame.y--;
	}
}

void RenderCamera()
{
	SetCameraPoint();
	PrintWorld();
	DrawBox();
	
	PrintEnemies();
	PrintPlayer();
	PrintParticles();

	if (isShaking) UpdateShakingTime();
}