#include <time.h>
#include "Game.h"

// if tps is less than 20, time slows down.
#define DELTA_TIME_MAX (0.05)

clock_t clock_ticks;

struct {
	double time;
	double deltaTime;
} Time;

struct {
	double time;
	double deltaTime;
} GameTime;

void InitTime() {
	clock_ticks = clock();
	Time.time = 0;
	Time.deltaTime = 0;

	GameTime.time = 0;
	GameTime.deltaTime = 0;
}
void UpdateTime() {
	clock_t clock_ticks_now = clock();
	clock_t delta = clock_ticks_now - clock_ticks;
	clock_ticks = clock_ticks_now;
	double parsedDelta = (double)delta / CLOCKS_PER_SEC;
	parsedDelta = parsedDelta < DELTA_TIME_MAX ? parsedDelta : DELTA_TIME_MAX;

	Time.time += parsedDelta;
	Time.deltaTime = parsedDelta;

	if (GameState == Dungeon) {
		GameTime.time += parsedDelta;
		GameTime.deltaTime = parsedDelta;
	}
}
void ResetGameTime() {
	GameTime.time = 0;
	GameTime.deltaTime = 0;
}