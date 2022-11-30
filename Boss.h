#pragma once
#include <stdbool.h>

//보스를 굳이 구조체로 해야할까?
//단일 개체일텐데
//Player공격 관련 Rect들에 보스 충돌 함수 추가로 넣기만 하면 될거같다

//boss에게 데미지를 가합니다. 사망여부를 return 합니다.
bool BossOnHit(int damage);

//현재 보스 체력을 반환합니다.
int GetBossHP();

//현재 보스 위치를 표현하는 Rect를 반환합니다. 충돌 여부 확인에 사용합니다.
Rect GetBossRect();

//피격 효과를 표현할지 bool로 반환합니다. 참일 경우 보스를 붉게 프린트합니다.
bool BossHitEffect();

//보스 사망여부를 반환합니다. 만약 사망했을경우 관련 상호작용을 모두 차단합니다.
bool isBossDead();

void BossSpawn(Point p);
void BossUpdate();
