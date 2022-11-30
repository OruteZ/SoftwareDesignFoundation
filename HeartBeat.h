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

int IsNoteBeaten();


void SetBPM(int BPM);
int GetBPM();

short* GetNoteInfo();
int GetNoteSize();

bool BPMCall();

