#pragma once

extern struct {
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

