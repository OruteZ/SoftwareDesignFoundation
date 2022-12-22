#pragma once

extern struct {
	double time; // in seconds
	double deltaTime; // in seconds
} Time;

extern struct {
	double cumulative_time;
	double time; // in seconds
	double deltaTime; // in seconds
} GameTime;

void InitTime();
void UpdateTime();
void ResetCumulativeGameTime();
void ResetGameTime();

