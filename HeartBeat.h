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

const char BeatKey = 'J';

typedef struct _HeartBeatObject {
	short* note;
	int BPM;
	int note_size;
	double time_to_check_tempo;
	int combo;

	Point* print_point;
	char* print_buffer;
} HeartBeat;

extern HeartBeat* heartBeat;

void InitHeartBeat();
void UpdateHeartBeat(double delta_time);
void RealeseHeartBeat();

int IsNoteBeaten();


void SetBPM(int BPM);
int GetBPM();

short* GetNoteInfo();

int GetCombo();

bool BPMCall();

