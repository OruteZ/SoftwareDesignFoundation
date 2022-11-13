#pragma once

#include <time.h>

typedef struct _GameTime {
	clock_t clock_ticks;
	double time;
	double deltaTime;
} GameTime;

extern GameTime Time;

void InitTime();
void UpdateTime();

