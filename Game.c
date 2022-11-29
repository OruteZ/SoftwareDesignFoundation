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

//------------사운드 시스템 (추후 헤더 만들 예정)--------------------------------------------------

/*
API
bool SoundPlay(SoundName) : 해당 이름을 가진 사운드를 출력합니다. 각 이름은 define으로 저장되어 있습니다
							사운드 재생 성공 여부를 참 거짓으로 반환합니다.

void SetVolume(int value) : 0부터 100사이 볼륨을 조절 할 수 있습니다.
void UpVolume(int value) : 현재 볼륨을 value만큼 증가시킵니다.
void DownVolume(int value) : 현재 볼륨을 value만큼 감소시킵니다.

int GetVolume() : 현재 볼륨입니다.
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