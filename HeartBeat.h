#pragma once

#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"

typedef struct _HeartBeatObject {
	short* note;
	int BPM;
	int note_size;
	double time_to_check_tempo;

	Point* print_point;
	char* print_buffer;
} HeartBeat;

HeartBeat* heart_beat;

void HeartBeat_init();
void HeartBeat_update(double delta_time);
void HeartBeat_render();
void HeartBeat_release();

void HeartBeat_move_note();

int HeartBeat_is_note_beaten();


void HeartBeat_set_BPM(int BPM);
int HeartBeat_get_BPM();

short* HeartBeat_get_note_information();

