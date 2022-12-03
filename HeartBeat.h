#pragma once

#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"
#include"KeyBoard.h"
#include <stdio.h> 

typedef struct _HeartBeatObject {
	bool* note;
	int BPM;
	int noteSize;
	double time_to_check_tempo;
} HeartBeat;

void InitHeartBeat();
void UpdateHeartBeat();
void RealeseHeartBeat();
void StartBeat();
int GetNowBpmLevel();
//현재 BPM을 반환합니다.
int GetBPM();

//현재 노트들의 위치를 배열로 반환합니다.
bool* GetNoteInfo();

//노트의 길이를 반환합니다.
int GetNoteSize();

//현재 BPM 게이지를 0에서 100사이 수로 표현해서 반환합니다.
int GetBPMGaugePercentage();

//이번 프레임에 박자가 맞을 경우 참을 반환합니다.
bool BeatCall();

//더 잘게 쪼갠 박자를 기준으로 BPMCall을 합니다.
bool SmallBeatCall();
