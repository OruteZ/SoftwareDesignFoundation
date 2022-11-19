#pragma once

#include <time.h>

extern struct {
	clock_t clock_ticks; // don't think about this. ignore this.
	double time; // in seconds
	double deltaTime; // in seconds
} Time;

void InitTime();
void UpdateTime();

