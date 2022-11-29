#define MAX_VOLUME (100)

#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int nowVolume = 10;

bool SoundPlay(char* soundName) {
	return false;
}

void SetVolume(int value) {
	if (value > MAX_VOLUME) value = MAX_VOLUME;
	if (value < 0) value = 0;
	nowVolume = value;
}

void UpVolume(int value) {
	SetVolume(GetVolume() + value);
}

void DownVolume(int value) {
	SetVolume(GetVolume() - value);
}

int GetVolume() {
	return nowVolume;
}