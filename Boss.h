#pragma once
#include <stdbool.h>
#include "Rect.h"

/*
* 보스 행동 방식
* 
* 보스는 3 * 3짜리
* 
* 패턴 0 : 이동
* 패턴 공격이 쿨타임일 때 플레이어를 향해 이동합니다.
* 
* 패턴 1 : 돌진 공격
* 플레이어를 바라보고는 1 비트동안 보스 몸체의 색상이 변한 후,
* 4 비트째에 플레이어를 향해 매우 빠른 속도로 돌진합니다.
* 이동 경로는 직선이 아니라 플레이어를 RayCast한 바닥입니다.
* 돌진하는 동안 플레이어와 접촉하면 플레이어에게 데미지를 입힙니다.
*
* 패턴 2 : 원거리 공격
* 플레이어를 향해 즉시 보스의 넓이 만큼의 총알을 일렬로 발사합니다.
* 플레이어가 원거리 사거리 안에 들어와 있어야 발동합니다.
* 
* 패턴 3 : 발밑 폭파 공격
* 제자리에서 번쩍거리면서 플레이어의 발밑에 3x3의 경고 타일을 만든 이후
* 2비트 후 해당 바닥을 폭파시킵니다. 2비트마다 경고 타일을 만들고 10회 반복합니다.
* 
* 패턴 4 : 보스 근접 공격
* 상하좌우 4 * 4 안에 플레이어가 들어왔을 경우 1비트 경고 후 근접공격을 시전합니다.
*/


//boss에게 데미지를 가합니다. 사망여부를 return 합니다.
bool BossOnHit(int damage);

//현재 보스가 존재하는지 반환합니다.
bool IsBossExist();

//현재 보스 체력을 반환합니다.
int GetBossHP();

//현재 보스 체력을 100% 기준으로 몇 %남았는지 반환합니다.
double GetBossHPPercentage();

//현재 보스 위치를 표현하는 Rect를 반환합니다. 충돌 여부 확인에 사용합니다.
Rect GetBossRect();
//현재 보스의 중심 위치
Point GetBossPoint();
//보스 facing
Point GetBossFacing();

//피격 효과를 표현할지 bool로 반환합니다. 참일 경우 보스를 붉게 프린트합니다.
bool BossHitEffect();

//보스 사망여부를 반환합니다. 만약 사망했을경우 관련 상호작용을 모두 차단합니다.
bool isBossDead();

//보스 클리어 여부를 반환합니다.
bool IsBossCleared();

void SpawnBoss(Point p);
void UpdateBoss();

void ResetBossInfo();
