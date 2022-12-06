#include "Boss.h"

#include "Rect.h"
#include "Raycast.h"
#include "Player.h"
#include "Game.h"
#include "Time.h"

#include "HeartBeat.h"
#include "World.h"
#include "Particle.h"
#include "Debug.h"

/*
* 보스 행동 방식
*
* 보스는 3 * 3짜리
*
* 패턴 0 : 이동
* 패턴 공격이 쿨타임일 때 플레이어를 향해 이동합니다.
*
* 패턴 1 : 돌진 공격
* 플레이어를 바라보고는 1 비트동안 경고 타일을 깐 뒤,
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
* 상하좌우 3 * 4 안에 플레이어가 들어왔을 경우 1비트 경고 후 근접공격을 시전합니다.
*/

//----------변경 변수---------------
int bossMaxHP = 1000;
int bossBaseDamage = 10;

double bossOnHitEffectDuration = 0.1f;

int bossWidth = 5;
int bossHeight = 5;

int chargeDmg = 3;
int shotDmg = 1;
int explosionDmg = 4;
int meleeDmg = 2;

//패턴 관련
const int maxExplodeCount = 10; //3번 패턴에서 폭발 몇번할지

int bossMeleeWidth = 5;
int bossMeleeHeight = 3;

double bossMovePerSecond = 1 / 1; //이동속도 
double chargeMovePerSecond = 10 / 1; //돌진할 때 이동속도

//일단 보스는 플레이어를 항상 감지하고 있다는 가정하인데, RayCast에서 감지거리를 설정해야 함.
int bossDetectionRadius = 10;
//원거리 공격 사거리
int bossShotRange = 10;
//------------------------------------

bool isBossExist = false;
bool isBossCleared = false;
int bossNowHP;
Rect BossRect;
Point BossPos;
Point bossFacing;

RayCastResult* memory;
int memoryCurIdx = 0;
bool playerVisible;
//플레이어를 Raycast로 탐색합니다.
void BossRayCast();

double bossOnHitEffectUntil = 0;

double bossNotMoveUntil = 0;

int bossBeatCount = 0;

enum State {
	Idle,
	Rush,
	Shot,
	Explosion,
	Melee,

	//int로 변환하면 state들의 개수가 됨
	StateLength, 
} state;

//상태 변경
void ChangeState(enum State next);
//보스가 단순이동 패턴일때 호출
void StartIdleState();
void UpdateBoss_Idle();
//보스가 돌진공격 패턴일때 호출
void StartRushState();
void UpdateBoss_Rush();
//보스가 원거리 발사 패턴일때 호출
void StartShotState();
void UpdateBoss_Shot();
//보스가 폭발 패턴일때 호출
void StartExplosionState();
void UpdateBoss_Explosion();
//보스가 근접 패턴일때 호출
void StartMeleeState();
void UpdateBoss_Melee();


void LookAt(Point dest) {
	Point diff = { .x = player->base.entity.pos.x - BossPos.x, .y = player->base.entity.pos.y - BossPos.y };
	if (diff.x == 0) {
		if (0 <= diff.y) bossFacing = Direction.north;
		else bossFacing = Direction.south;
	}
	else if (diff.y == 0) {
		if (0 <= diff.x) bossFacing = Direction.east;
		else bossFacing = Direction.west;
	}
	else {
		if (abs(diff.x) > abs(diff.y)) {
			if (0 <= diff.x) bossFacing = Direction.east;
			else bossFacing = Direction.west;
		}
		else {
			if (0 <= diff.y) bossFacing = Direction.north;
			else bossFacing = Direction.south;
		}
	}

	/*
	if (diff.x == 0) {
		if (0 <= diff.y) bossFacing = Direction.north;
		else bossFacing = Direction.south;
	}
	else if (diff.x > 0) {
		if (0 < diff.y) bossFacing = Direction.north;
		else bossFacing = Direction.east;
	}
	else {
		if (0 <= diff.y) bossFacing = Direction.west;
		else bossFacing = Direction.south;
	}
	*/
}
bool IsPlayerInMeleeRange() {
	Rect attackRect;

	Point attackPoint = BossPos;
	attackPoint.x += bossFacing.x * (bossWidth / 2);
	attackPoint.y += bossFacing.y * (bossHeight / 2);

	if (PointEquals(&bossFacing, &Direction.north)) {
		attackRect.x = attackPoint.x - bossMeleeWidth / 2;
		attackRect.y = attackPoint.y + 1;
		attackRect.width = bossMeleeWidth;
		attackRect.height = bossMeleeHeight;
	}
	else if (PointEquals(&bossFacing, &Direction.south)) {
		attackRect.x = attackPoint.x - bossMeleeWidth / 2;
		attackRect.y = attackPoint.y - bossMeleeHeight;
		attackRect.width = bossMeleeWidth;
		attackRect.height = bossMeleeHeight;
	}
	else if (PointEquals(&bossFacing, &Direction.east)) {
		attackRect.x = attackPoint.x + 1;
		attackRect.y = attackPoint.y - bossMeleeWidth / 2;
		attackRect.width = bossMeleeHeight;
		attackRect.height = bossMeleeWidth;
	}
	else {
		attackRect.x = attackPoint.x - bossMeleeHeight;
		attackRect.y = attackPoint.y - bossMeleeWidth / 2;
		attackRect.width = bossMeleeHeight;
		attackRect.height = bossMeleeWidth;
	}
	Point playerPos = GetPlayerPos();
	return RectContainsPoint(&attackRect, &playerPos);
}
bool IsPlayerInShotRange() {
	Point playerPos = GetPlayerPos();

	if (BossPos.x - (bossWidth / 2) <= playerPos.x &&
		BossPos.x + (bossWidth / 2) >= playerPos.x)
		return true;

	if (BossPos.y - (bossWidth / 2) <= playerPos.y &&
		BossPos.y + (bossWidth / 2) >= playerPos.y)
		return true;

	return false;
}
void BossShot() {
	Point shotPoint = BossPos;
	if (bossFacing.x == 0) {
		shotPoint.y += bossFacing.y * (bossHeight / 2);
		for (int i = -(bossWidth / 2); i <= (bossWidth / 2); i++) {
			shotPoint.x += i;
			CreateParticle(bossFacing, shotPoint, EnemyRangeAttackParticleType, shotDmg);
			shotPoint.x -= i;
		}
	}

	else {
		shotPoint.x += bossFacing.x * (bossHeight / 2);
		for (int i = -(bossWidth / 2); i <= (bossWidth / 2); i++) {
			shotPoint.y += i;
			CreateParticle(bossFacing, shotPoint, EnemyRangeAttackParticleType, shotDmg);
			shotPoint.y -= i;
		}
	}
}

bool canCollisionAtk = false; // 참일경우 접촉시 데미지

void ChangeState(enum State next) {
	if (next >= StateLength) return;

	switch (next) {
	case Idle:
		StartIdleState();
		break;
	case Rush:
		StartRushState();
		break;
	case Explosion:
		StartExplosionState();
		break;
	case Shot:
		StartShotState();
		break;
	case Melee:
		StartMeleeState();
		break;
	}
}

//보스 이동 함수
bool BossMove(Point direction, double moveSpeed);
void BossMoveAsMemory();

//public:
int GetBossHP() { return bossNowHP; }
double GetBossHPPercentage() { return (double)bossNowHP / (double)bossMaxHP; }
Rect GetBossRect() { return BossRect; }
Point GetBossPoint() { return BossPos; }
Point GetBossFacing() { return bossFacing; }
void ResetBossInfo() {
	isBossExist = false;
	isBossCleared = false;
}
bool BossOnHit(int damage) {
	bossNowHP -= damage;
	bossOnHitEffectUntil = bossOnHitEffectDuration;
#ifdef DEBUG
	DebugPrint("Boss hitted, hp left : %d", bossNowHP);
#endif
	if (bossNowHP) {
		isBossCleared = true;
	}

	return (bossNowHP <= 0);
}
bool BossHitEffect() {
	return bossOnHitEffectUntil > 0;
}
bool isBossDead() {
	return bossNowHP < 0;
}
void SpawnBoss(Point p) {
	bossNowHP = bossMaxHP;

	BossPos = p;

	BossRect.x = p.x - (bossWidth / 2);
	BossRect.y = p.y - (bossHeight / 2);
	BossRect.height = bossHeight;
	BossRect.width = bossWidth;

	isBossExist = true;

	memoryCurIdx = 0;
	memory = CreateRayCastResult(bossDetectionRadius * bossDetectionRadius);

	bossBeatCount = 0;
	LookAt(GetPlayerPos());
	ChangeState(Idle);
}
void UpdateBoss() {
	if (!isBossExist) return;

#ifdef DEBUG
	if(GetKeyDown('M')) BossOnHit(10000);
#endif // DEBUG

	Rect detectionRect = {
		.x = BossPos.x - bossDetectionRadius,
		.y = BossPos.y - bossDetectionRadius,
		.width = bossDetectionRadius * 2 + 1,
		.height = bossDetectionRadius * 2 + 1
	};
	if (RectContainsPoint(&detectionRect, &player->base.entity.pos) && // if within detection range..
		state != Rush) { // 돌진 패턴이면 RayCast가 고정되어있어야 정해진 위치까지만 돌진함

		BossRayCast(); // try raycast
	}
	switch (state) {
	case Idle:
		UpdateBoss_Idle();
		break;

	case Rush:
		UpdateBoss_Rush();
		break;

	case Shot:
		UpdateBoss_Shot();
		break;

	case Explosion:
		UpdateBoss_Explosion();
		break;

	case Melee:
		UpdateBoss_Melee();
		break;

	default : break;
	}
}
bool IsBossExist() { return isBossExist; }
bool IsBossCleared() { return isBossCleared; }

//private:

//단순 이동과 돌진시 이동속도가 다를 수 있으므로 인자로 받아옴
bool BossMove(Point direction, double moveSpeed) { 
	if (bossNotMoveUntil > GameTime.time) return false;

	Point dest = BossPos;
	PointAdd(&dest, &direction);
	LookAt(dest);
	
	Rect destRect = {
		.x = dest.x - (bossWidth / 2),
		.y = dest.y - (bossHeight / 2),
		.width = bossWidth,
		.height = bossHeight
	};

	Point playerPos = GetPlayerPos();

	if (GetTile(dest) & FLAG_COLLIDE_WITH_BODY) return false;
	if (RectContainsPoint(&destRect, &playerPos)) {
		if (canCollisionAtk) PlayerOnHit(chargeDmg);
		return false;
	}
	for (int i = 0; i < enemies->length; i++) {
		if (RectContainsPoint(&destRect, &enemies->entities[i]->pos)) return false;
	}
	//Success
	BossPos = dest;
	BossRect.x = dest.x - bossWidth / 2;
	BossRect.y = dest.y - bossHeight / 2;

	bossNotMoveUntil = GameTime.time + (1 / moveSpeed);
}
void BossMoveAsMemory() {
	const int nextIndex = memoryCurIdx + 1;
	if (nextIndex < memory->length) {
		Point dir = memory->arr[nextIndex];
		PointSub(&dir, &BossPos);

		if (BossMove(dir, bossMovePerSecond)) { // increment memory only if move is successful
			memoryCurIdx++;
		}
	}
}
void BossRayCast() {
	//플레이어 위치 raycast
	RayCastResult* result = CreateRayCastResult(bossDetectionRadius);
	Point start = BossPos;
	Point dest = GetPlayerPos();
	bool success = RayCastInCurrentWorld(result, start, dest);

	if (success) { // raycast 에 성공하면 memory를 새로운 raycast 결과로 바꿔줘야 한다.
		DeleteRayCastResult(memory);
		memory = result;
		memoryCurIdx = 0;
		playerVisible = true;
	}
	else {
		DeleteRayCastResult(result);
		playerVisible = false;
	}
}

enum State nextState;
void StartIdleState() {
	state = Idle;
}
void UpdateBoss_Idle() {
	BossMoveAsMemory();
	if (!BeatCall()) return;

	//nextState = (enum State)(rand() % (int)StateLength);
	nextState = Shot;
	switch (nextState) {
	case Idle:
	case Rush:
	case Explosion:
		break; //돌진이랑 단순 이동, 폭발은 언제든 가능

	case Shot:
		//만약 사거리 안에 들어온다면 합격
		if (IsPlayerInShotRange()) break;
		else nextState = Idle;
		
	case Melee:
		//만약 사거리 안에 들어온다면 합격
		if (IsPlayerInMeleeRange()) break;
		else nextState = Idle;
	}
	ChangeState(nextState);
}

/*패턴 1 : 돌진 공격
* 플레이어를 바라보고는 1 비트동안 경고 타일을 깐 뒤,
* 2 비트째에 플레이어를 향해 매우 빠른 속도로 돌진합니다.
* 이동 경로는 직선이 아니라 플레이어를 RayCast한 바닥입니다.
* 돌진하는 동안 플레이어와 접촉하면 플레이어에게 데미지를 입힙니다.*/

void StartRushState() {
	bossBeatCount = 1;

	//타일까는건 다른거 다 만들고 마지막에

	state = Rush;
	BossRayCast();
	LookAt(GetPlayerPos());
#ifdef DEBUG
	DebugPrint("Ready To Rush");
#endif
}
void UpdateBoss_Rush() {
	if (BeatCall()) bossBeatCount--;
	if (bossBeatCount > 0) return;
#ifdef DEBUG
	DebugPrint("RUsh");
#endif

	canCollisionAtk = true;

	int nextIndex = memoryCurIdx + 1;
	if (nextIndex < memory->length) {
		Point dir = memory->arr[nextIndex];
		PointSub(&dir, &BossPos);

		if (BossMove(dir, chargeMovePerSecond)) { // increment memory only if move is successful
			memoryCurIdx++;
		}
	}
	else { //RayCast 하지 않았는데 배열 초과일 경우, 돌진이 끝났다는 의미
		canCollisionAtk = false;
		ChangeState(Idle);
	}
}

void StartShotState() {
	LookAt(GetPlayerPos());

	state = Shot;
	bossBeatCount = 5;
}
void UpdateBoss_Shot() {

	if (!BeatCall()) return;

	if (--bossBeatCount > 0) {
		BossShot();
		LookAt(GetPlayerPos());
	}
	else {
		ChangeState(Idle);
	}
}

//패턴 3 : 발밑 폭파 공격
//제자리에서 번쩍거리면서 플레이어의 발밑에 3x3의 경고 타일을 만든 이후
//2비트 후 해당 바닥을 폭파시킵니다. 2비트마다 경고 타일을 만들고 10회 반복합니다.

bool ReadyToExplode = false;
Point explosionPoint;
int explodeCount;
void StartExplosionState() {
	state = Explosion;
	bossBeatCount = 1;

	//폭발 패턴 관련 변수 초기화
	ReadyToExplode = false;
	explosionPoint.x = explosionPoint.y = 0;
	explodeCount = 0;
}
void UpdateBoss_Explosion() {
	if (BeatCall()) bossBeatCount--;
	if (bossBeatCount > 0) return;

	if (ReadyToExplode) {
		Rect explosionRect = {
			.x = explosionPoint.x - 1,
			.y = explosionPoint.y - 1,
			.width = 3,
			.height = 3
		};
		if (RectContainsPoint(&explosionRect, &player->base.entity.pos))
			PlayerOnHit(explosionDmg);

		CreateParticle(Direction.north, explosionPoint, ExplosionParticleType1, 0);

		if (++explodeCount >= maxExplodeCount) {
			ChangeState(Idle);
			return;
		}
		else {
			bossBeatCount = 0;
			ReadyToExplode = false;
		}
	}
	
	else {
		explosionPoint = GetPlayerPos();

		//todo: explodePoint에 경고 타일 생성

		ReadyToExplode = true;
		bossBeatCount = 2;
	}
}

//패턴 4 : 보스 근접 공격
//상하좌우 Width * Heigth 안에 플레이어가 들어왔을 경우 1비트 경고 후 근접공격을 시전합니다.

void StartMeleeState() {
	state = Melee;
	bossBeatCount = 1;

	LookAt(GetPlayerPos());
}
void UpdateBoss_Melee() {
	if (BeatCall()) bossBeatCount--;
	if (bossBeatCount > 0) return;

	if (IsPlayerInMeleeRange()) {
		PlayerOnHit(meleeDmg);
#ifdef DEBUG
		DebugPrint("Player hit");
#endif // DEBUG

	}

	Point attackPoint = BossPos;
	attackPoint.x += bossFacing.x * (bossWidth / 2);
	attackPoint.y += bossFacing.y * (bossHeight / 2);

	for (int i = 0; i < bossMeleeHeight; i++) {
		PointAdd(&attackPoint, &bossFacing);
		CreateParticle(bossFacing, attackPoint, MeleeAttackParticleType, 0);
	}
	ChangeState(Idle);
}
