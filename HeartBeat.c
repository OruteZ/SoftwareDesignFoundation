
#include "HeartBeat.h"
#include<stdlib.h>
#include<string.h>
#include <Windows.h>
#include <process.h>
#include"Point.h"
#include"Screen.h"
#include "Time.h"
#include"KeyBoard.h"
#include "Debug.h"

#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
#include <process.h>

#define BPM_MAX_LEVEL (5)
#define LEVEL_UP_LINE_BY_BPM (0.1)

HeartBeat* heartBeat;

int bpmByLevels[BPM_MAX_LEVEL] = {
	90,
	120,
	160,
	200,
	240,
};
int nowBpmLv;

HeartBeat* heartBeat;
bool isBeatNow = false;

int HeartGauge = 0;
int HeartLevelUpLine;

void ResetNote();
void MoveNote();
int IsNoteBeaten();
void BPMGaugeUp();
void BPMLevelUp();
void BPMLevelDown();
void BPMGaugeDown();

void InitHeartBeat()
{
	heartBeat = (HeartBeat*)malloc(sizeof(HeartBeat));
	if (heartBeat == NULL) exit(-1);

	heartBeat->noteSize = 20;
	heartBeat->time_to_check_tempo = 0;

	heartBeat->note = (short*)malloc(sizeof(short) * heartBeat->noteSize);
	if (heartBeat->note == NULL) exit(-1);

	for (int i = 0; i < heartBeat->noteSize; i++) {
		heartBeat->note[i] = false;
	}

	nowBpmLv = 0;
	HeartLevelUpLine = bpmByLevels[nowBpmLv] * LEVEL_UP_LINE_BY_BPM;
	heartBeat->BPM = bpmByLevels[nowBpmLv];
}

void StartBeat() {
	ResetNote();
	//PlaySound(TEXT(".\\GameSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void UpdateHeartBeat() {
	heartBeat->time_to_check_tempo += Time.deltaTime;

	double BeatCheckTime = (double)60 / (double)heartBeat->BPM;
	if (heartBeat->time_to_check_tempo >= BeatCheckTime) {
		MoveNote();
		isBeatNow = true;
		heartBeat->time_to_check_tempo -= BeatCheckTime;
	} else isBeatNow = false;

	if (GetKeyDown('K')) {
		int value = IsNoteBeaten();

		if		(value == 1) BPMGaugeUp();
		else if (value == 0) BPMGaugeDown();
	}

#ifdef DEBUG
	DebugPrint("%d %d %d", heartBeat->BPM, nowBpmLv, HeartGauge);
#endif
}

void RealeseHeartBeat() {
	free(heartBeat->note);
	free(heartBeat);
}

void MoveNote()
{
	bool isThereNoteInJudgeLine = heartBeat->note[0];

	int i, size = heartBeat->noteSize;
	int last_node_point = -1;
	for (i = 1; i < size; i++) {
		heartBeat->note[i - 1] = heartBeat->note[i];
		if (heartBeat->note[i - 1]) last_node_point = i;
	}

	if (last_node_point <= size - 4) {
		heartBeat->note[size - 1] = 1;
	}
	else {
		heartBeat->note[size - 1] = false;
	}

	if (isThereNoteInJudgeLine) BPMGaugeDown();
}
void ResetNote() {
	for (int i = 0; i < heartBeat->noteSize; i++) {
		heartBeat->note[i] = false;
	}
}

//노트의 판정 여부를 반환합니다. 
//판정할 노트가 근처에 없으면 -1, miss판정일 경우 0, 적합 판정이 났을 경우 1이 반환 됩니다.
int IsNoteBeaten() {
	double time_per_beat = (((double)60) / (double)heartBeat->BPM);

	int notePosition = -1;
	for (int i = 0; i < heartBeat->noteSize; i++) {
		if (heartBeat->note[i]) {
			notePosition = i;
			break;
		}
	}
	if (notePosition > 2) return -1;

	heartBeat->note[notePosition] = false;

	double correct_time = time_per_beat * notePosition;
	double time_differece = abs(correct_time - heartBeat->time_to_check_tempo);

	if (time_differece < time_per_beat / 4) return 1;
	else return 0;
}

void SetBPM(int BPM) {
	heartBeat->BPM = BPM;
}

int GetBPM() {
	return heartBeat->BPM;
}

short* GetNoteInfo()
{
	return heartBeat->note;
}

int GetNoteSize() {
	return heartBeat->noteSize;
}

int GetBPMGaugePercentage() {
	return (100 * HeartGauge) / HeartLevelUpLine;
}

bool BPMCall() {
	return isBeatNow;
}

void BPMLevelUp() {
	if (nowBpmLv >= BPM_MAX_LEVEL - 1) return;

	nowBpmLv++;
	heartBeat->BPM = bpmByLevels[nowBpmLv];
	HeartLevelUpLine = bpmByLevels[nowBpmLv] * LEVEL_UP_LINE_BY_BPM;

	HeartGauge = 0;

	ResetNote();
}
void BPMLevelDown() {
	if (nowBpmLv == 0) return;

	nowBpmLv--;
	heartBeat->BPM = bpmByLevels[nowBpmLv];
	HeartLevelUpLine = bpmByLevels[nowBpmLv] * LEVEL_UP_LINE_BY_BPM;

	HeartGauge = 0;

	ResetNote();
}

void BPMGaugeUp() {
	if (++HeartGauge >= HeartLevelUpLine) BPMLevelUp();
}
void BPMGaugeDown() {
	if (--HeartGauge < 0) BPMLevelDown();
}
