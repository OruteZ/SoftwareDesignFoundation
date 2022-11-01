#pragma once

#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"
#include"KeyBoard.h"


//for test
#include <process.h>

BOOLEAN isHit;
//----

typedef struct _HeartBeatObject {
	short* note;
	int BPM;
	int note_size;
	double time_to_check_tempo;
	int combo;

	Point* print_point;
	char* print_buffer;
} HeartBeat;

HeartBeat* heart_beat;

void HeartBeat_init();
void HeartBeat_update(double delta_time);
void HeartBeat_render();
void HeartBeat_release();

void HeartBeat_reset();

void HeartBeat_move_note();
void HeartBeat_reload_buffer();

int HeartBeat_is_note_beaten();


void HeartBeat_set_BPM(int BPM);
int HeartBeat_get_BPM();

short* HeartBeat_get_note_information();

int HeartBeat_get_combo();

unsigned _stdcall Thread_PlaySound(void* arg);

