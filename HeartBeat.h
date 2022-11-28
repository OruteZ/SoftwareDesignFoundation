#pragma once

#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"
#include"KeyBoard.h"
#include <stdio.h> 

//for test
#include <process.h>

BOOLEAN isHit;
//----


typedef struct _HeartBeatObject {
	short* note;
	int BPM;
	int noteSize;
	double time_to_check_tempo;
	int combo;
} HeartBeat;

extern HeartBeat* heartBeat;

void InitHeartBeat();
void UpdateHeartBeat();
void RealeseHeartBeat();
void StartBeat();

int IsNoteBeaten();


void SetBPM(int BPM);
int GetBPM();

short* GetNoteInfo();

int GetCombo();

bool BPMCall();

