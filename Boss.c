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
* ���� �ൿ ���
*
* ������ 3 * 3¥��
*
* ���� 0 : �̵�
* ���� ������ ��Ÿ���� �� �÷��̾ ���� �̵��մϴ�.
*
* ���� 1 : ���� ����
* �÷��̾ �ٶ󺸰�� 1 ��Ʈ���� ��� Ÿ���� �� ��,
* 4 ��Ʈ°�� �÷��̾ ���� �ſ� ���� �ӵ��� �����մϴ�.
* �̵� ��δ� ������ �ƴ϶� �÷��̾ RayCast�� �ٴ��Դϴ�.
* �����ϴ� ���� �÷��̾�� �����ϸ� �÷��̾�� �������� �����ϴ�.
*
* ���� 2 : ���Ÿ� ����
* �÷��̾ ���� ��� ������ ���� ��ŭ�� �Ѿ��� �Ϸķ� �߻��մϴ�.
* �÷��̾ ���Ÿ� ��Ÿ� �ȿ� ���� �־�� �ߵ��մϴ�.
*
* ���� 3 : �߹� ���� ����
* ���ڸ����� ��½�Ÿ��鼭 �÷��̾��� �߹ؿ� 3x3�� ��� Ÿ���� ���� ����
* 2��Ʈ �� �ش� �ٴ��� ���Ľ�ŵ�ϴ�. 2��Ʈ���� ��� Ÿ���� ����� 10ȸ �ݺ��մϴ�.
*
* ���� 4 : ���� ���� ����
* �����¿� 3 * 4 �ȿ� �÷��̾ ������ ��� 1��Ʈ ��� �� ���������� �����մϴ�.
*/

//----------���� ����---------------
int bossMaxHP = 1000;
int bossBaseDamage = 10;

double bossOnHitEffectDuration = 0.1f;

int bossWidth = 5;
int bossHeight = 5;

int chargeDmg = 3;
int shotDmg = 1;
int explosionDmg = 4;
int meleeDmg = 2;

//���� ����
const int maxExplodeCount = 10; //3�� ���Ͽ��� ���� �������

int bossMeleeWidth = 5;
int bossMeleeHeight = 3;

double bossMovePerSecond = 1 / 1; //�̵��ӵ� 
double chargeMovePerSecond = 10 / 1; //������ �� �̵��ӵ�

//�ϴ� ������ �÷��̾ �׻� �����ϰ� �ִٴ� �������ε�, RayCast���� �����Ÿ��� �����ؾ� ��.
int bossDetectionRadius = 10;
//���Ÿ� ���� ��Ÿ�
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
//�÷��̾ Raycast�� Ž���մϴ�.
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

	//int�� ��ȯ�ϸ� state���� ������ ��
	StateLength, 
} state;

//���� ����
void ChangeState(enum State next);
//������ �ܼ��̵� �����϶� ȣ��
void StartIdleState();
void UpdateBoss_Idle();
//������ �������� �����϶� ȣ��
void StartRushState();
void UpdateBoss_Rush();
//������ ���Ÿ� �߻� �����϶� ȣ��
void StartShotState();
void UpdateBoss_Shot();
//������ ���� �����϶� ȣ��
void StartExplosionState();
void UpdateBoss_Explosion();
//������ ���� �����϶� ȣ��
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

bool canCollisionAtk = false; // ���ϰ�� ���˽� ������

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

//���� �̵� �Լ�
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
		state != Rush) { // ���� �����̸� RayCast�� �����Ǿ��־�� ������ ��ġ������ ������

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

//�ܼ� �̵��� ������ �̵��ӵ��� �ٸ� �� �����Ƿ� ���ڷ� �޾ƿ�
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
	//�÷��̾� ��ġ raycast
	RayCastResult* result = CreateRayCastResult(bossDetectionRadius);
	Point start = BossPos;
	Point dest = GetPlayerPos();
	bool success = RayCastInCurrentWorld(result, start, dest);

	if (success) { // raycast �� �����ϸ� memory�� ���ο� raycast ����� �ٲ���� �Ѵ�.
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
		break; //�����̶� �ܼ� �̵�, ������ ������ ����

	case Shot:
		//���� ��Ÿ� �ȿ� ���´ٸ� �հ�
		if (IsPlayerInShotRange()) break;
		else nextState = Idle;
		
	case Melee:
		//���� ��Ÿ� �ȿ� ���´ٸ� �հ�
		if (IsPlayerInMeleeRange()) break;
		else nextState = Idle;
	}
	ChangeState(nextState);
}

/*���� 1 : ���� ����
* �÷��̾ �ٶ󺸰�� 1 ��Ʈ���� ��� Ÿ���� �� ��,
* 2 ��Ʈ°�� �÷��̾ ���� �ſ� ���� �ӵ��� �����մϴ�.
* �̵� ��δ� ������ �ƴ϶� �÷��̾ RayCast�� �ٴ��Դϴ�.
* �����ϴ� ���� �÷��̾�� �����ϸ� �÷��̾�� �������� �����ϴ�.*/

void StartRushState() {
	bossBeatCount = 1;

	//Ÿ�ϱ�°� �ٸ��� �� ����� ��������

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
	else { //RayCast ���� �ʾҴµ� �迭 �ʰ��� ���, ������ �����ٴ� �ǹ�
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

//���� 3 : �߹� ���� ����
//���ڸ����� ��½�Ÿ��鼭 �÷��̾��� �߹ؿ� 3x3�� ��� Ÿ���� ���� ����
//2��Ʈ �� �ش� �ٴ��� ���Ľ�ŵ�ϴ�. 2��Ʈ���� ��� Ÿ���� ����� 10ȸ �ݺ��մϴ�.

bool ReadyToExplode = false;
Point explosionPoint;
int explodeCount;
void StartExplosionState() {
	state = Explosion;
	bossBeatCount = 1;

	//���� ���� ���� ���� �ʱ�ȭ
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

		//todo: explodePoint�� ��� Ÿ�� ����

		ReadyToExplode = true;
		bossBeatCount = 2;
	}
}

//���� 4 : ���� ���� ����
//�����¿� Width * Heigth �ȿ� �÷��̾ ������ ��� 1��Ʈ ��� �� ���������� �����մϴ�.

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
