#include "Player.h"

#include "Vector.h"
#include "QuadTree.h"

#include "Game.h"

enum _GameState GameState = Menu;

Player* player;
Vector* enemies;
Vector* expOrbs;
Vector* particles;

QuadTree* enemiesTree;
QuadTree* expOrbsTree;
QuadTree* particleTree;

#ifdef DEBUG
Vector* debugVector;
QuadTree* debugTree;
#endif

//------------���� �ý��� (���� ��� ���� ����)--------------------------------------------------

/*
API
bool SoundPlay(SoundName) : �ش� �̸��� ���� ���带 ����մϴ�. �� �̸��� define���� ����Ǿ� �ֽ��ϴ�
							���� ��� ���� ���θ� �� �������� ��ȯ�մϴ�.

void SetVolume(int value) : 0���� 100���� ������ ���� �� �� �ֽ��ϴ�.
void UpVolume(int value) : ���� ������ value��ŭ ������ŵ�ϴ�.
void DownVolume(int value) : ���� ������ value��ŭ ���ҽ�ŵ�ϴ�.

int GetVolume() : ���� �����Դϴ�.
*/
#define MAX_VOLUME (100)

int nowVolume = 10;

bool SoundPlay(char* soundName) {
	return false;
}

void SetVolume(int value) {
	if (value > MAX_VOLUME) value = MAX_VOLUME;
	if (value < 0) value = 0;
	nowVolume = value;
}

void UpVolume(int value) {
	SetVolume(GetVolume() + value);
}

void DownVolume(int value) {
	SetVolume(GetVolume() - value);
}

int GetVolume() {
	return nowVolume;
}