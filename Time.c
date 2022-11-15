#include <time.h>

// if tps is less than 20, time slows down.
#define DELTA_TIME_MAX (0.05)

typedef struct _GameTime {
	clock_t clock_ticks;
	double time;
	double deltaTime;
} GameTime;

GameTime Time;

void InitTime() {
	Time.clock_ticks = clock();
	Time.time = 0;
	Time.deltaTime;
}
void UpdateTime() {
	clock_t clock_ticks = clock();
	clock_t delta = clock_ticks - Time.clock_ticks;
	Time.clock_ticks = clock_ticks;
	double parsedDelta = (double)delta / CLOCKS_PER_SEC;
	parsedDelta = parsedDelta < DELTA_TIME_MAX ? parsedDelta : DELTA_TIME_MAX;

	Time.time += parsedDelta;
	Time.deltaTime = parsedDelta;
}