#pragma once

#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"
#include"KeyBoard.h"
#include <stdio.h> 

typedef struct _HeartBeatObject {
	short* note;
	int BPM;
	int noteSize;
	double time_to_check_tempo;
} HeartBeat;

void InitHeartBeat();
void UpdateHeartBeat();
void RealeseHeartBeat();
void StartBeat();
int GetNowBpmLevel();
//���� BPM�� ��ȯ�մϴ�.
int GetBPM();

//���� ��Ʈ���� ��ġ�� �迭�� ��ȯ�մϴ�.
short* GetNoteInfo();

//��Ʈ�� ���̸� ��ȯ�մϴ�.
int GetNoteSize();

//���� BPM �������� 0���� 100���� ���� ǥ���ؼ� ��ȯ�մϴ�.
int GetBPMGaugePercentage();

//�̹� �����ӿ� ���ڰ� ���� ��� ���� ��ȯ�մϴ�.
bool BeatCall();

//�� �߰� �ɰ� ���ڸ� �������� BPMCall�� �մϴ�.
bool SmallBeatCall();
