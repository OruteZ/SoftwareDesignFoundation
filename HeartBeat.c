
#include "HeartBeat.h"
#include<stdlib.h>
#include<string.h>
#include"Point.h"
#include"Screen.h"
#include"KeyBoard.h"


//for test
#include <process.h>

BOOLEAN isHit;
//----

HeartBeat* heartBeat;

void ResetNote();
void MoveNote();
int IsNoteBeaten();

bool isBeatNow = false;

unsigned _stdcall Thread_PlaySound(void* arg);

void InitHeartBeat()
{
	heartBeat = (HeartBeat*)malloc(sizeof(HeartBeat));
	if (heartBeat == NULL) exit(-1);

	heartBeat->note_size = 40;
	heartBeat->BPM = 240;
	heartBeat->time_to_check_tempo = 0;
	heartBeat->combo = 0;

	heartBeat->note = (short*)malloc(sizeof(short) * heartBeat->note_size);
	if (heartBeat->note == NULL) exit(-1);

	for (int i = 0; i < heartBeat->note_size; i++) {
		heartBeat->note[i] = 0;
	}

	heartBeat->print_point = CreatePoint(0, 20);
}

void UpdateHeartBeat(double delta_time)
{
	heartBeat->time_to_check_tempo += delta_time;

	if (heartBeat->time_to_check_tempo >= ((double)60 * 1000) / (double)heartBeat->BPM) {
		MoveNote();
		isBeatNow = true;
		heartBeat->time_to_check_tempo -= ((double)60 * 1000) / (double)heartBeat->BPM;
	}
	else {
		isBeatNow = false;
	}

	if (GetKeyDown(BeatKey)) {
		if (IsNoteBeaten()) {
			isHit = TRUE;
			if (++(heartBeat->combo) >= 10) {
				ResetNote();
				heartBeat->combo = 0;
				heartBeat->BPM += 120;
			}
		}
		else {
			heartBeat->combo = 0;
		}
	}
}

void RealeseHeartBeat()
{
	free(heartBeat->note);
	free(heartBeat->print_buffer);
	DeletePoint(heartBeat->print_point);
	free(heartBeat);
}

void MoveNote()
{
	//test
	if (isHit) isHit = FALSE;

	int i, size = heartBeat->note_size;
	int last_node_point = -1;
	for (i = 1; i < size; i++) {
		heartBeat->note[i - 1] = heartBeat->note[i];
		if (heartBeat->note[i - 1] == 1) last_node_point = i;
	}

	if (last_node_point <= size - 4) {
		heartBeat->note[size - 1] = 1;
		//_beginthreadex(NULL, 0, Thread_PlaySound, 0, 0, NULL);
	}

	else heartBeat->note[size - 1] = 0;
}

void ResetNote()
{
	for (int i = 0; i < heartBeat->note_size; i++) {
		heartBeat->note[i] = 0;
	}
}

int IsNoteBeaten()
{
	double time_per_beat = (((double)60 * 1000) / (double)heartBeat->BPM);

	int notePosition;
	for (int i = 0; i < heartBeat->note_size; i++) {
		if (heartBeat->note[i] == 1) {
			notePosition = i;
			break;
		}
	}
	if (notePosition > 1) return 0;

	heartBeat->note[notePosition] = 0;

	double correct_time = time_per_beat * notePosition;
	double time_differece = abs(correct_time - heartBeat->time_to_check_tempo);

	if (time_differece < time_per_beat / 2) return 1;
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
	short* result = (short*)malloc(sizeof(short) * heartBeat->note_size);
	if (result == NULL) exit(-1);

	memcpy(result, heartBeat->note, heartBeat->note_size);
	return result;
}

int GetCombo() {
	return heartBeat->combo;
}

bool nowBeat() {
	return isBeatNow;
}