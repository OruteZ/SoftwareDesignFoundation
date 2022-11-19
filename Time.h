#pragma once

#include <time.h>

extern struct {
	clock_t clock_ticks; // don't think about this. ignore this.
	double time; // in seconds
	double deltaTime; // in seconds
} Time;

extern struct {
	double time; // in seconds
	double deltaTime; // in seconds
} GameTime;

void InitTime();
void UpdateTime();
void ResetGameTime();

