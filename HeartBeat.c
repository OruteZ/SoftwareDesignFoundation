
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


//for test
#include <process.h>

BOOLEAN isHit;
//----

HeartBeat* heartBeat;

void ResetNote();
void MoveNote();
int IsNoteBeaten();

bool isBeatNow = false;

void InitHeartBeat()
{
	heartBeat = (HeartBeat*)malloc(sizeof(HeartBeat));
	if (heartBeat == NULL) exit(-1);

	heartBeat->noteSize = 20;
	heartBeat->BPM = 140;
	heartBeat->time_to_check_tempo = 0;
	heartBeat->combo = 0;

	heartBeat->note = (short*)malloc(sizeof(short) * heartBeat->noteSize);
	if (heartBeat->note == NULL) exit(-1);

	for (int i = 0; i < heartBeat->noteSize; i++) {
		heartBeat->note[i] = false;
	}
}

void StartBeat() {
	ResetNote();
	PlaySound(TEXT(".\\GameSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void UpdateHeartBeat() {
	heartBeat->time_to_check_tempo += Time.deltaTime;

	if (heartBeat->time_to_check_tempo >= ((double)60) / (double)heartBeat->BPM) {
		MoveNote();
		isBeatNow = true;
		heartBeat->time_to_check_tempo -= ((double)60) / (double)heartBeat->BPM;
	} else isBeatNow = false;

	if (GetKeyDown('K')) {
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

void RealeseHeartBeat() {
	free(heartBeat->note);
	free(heartBeat);
}

void MoveNote()
{
	//test
	if (isHit) isHit = FALSE;

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
}
void ResetNote() {
	for (int i = 0; i < heartBeat->noteSize; i++) {
		heartBeat->note[i] = false;
	}
}

int IsNoteBeaten()
{
	double time_per_beat = (((double)60) / (double)heartBeat->BPM);

	int notePosition = -1;
	for (int i = 0; i < heartBeat->noteSize; i++) {
		if (heartBeat->note[i]) {
			notePosition = i;
			break;
		}
	}
	if (notePosition > 1) return 0;

	heartBeat->note[notePosition] = false;

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
	return heartBeat->note;
}

int GetCombo() {
	return heartBeat->combo;
}

bool BPMCall() {
	return isBeatNow;
}

bool NotBeatCall() {

}