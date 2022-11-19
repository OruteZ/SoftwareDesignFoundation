#include "Screen.h"

#include "World.h"
#include "World001.h"


void Release() {
	ScreenRelease();

	DeleteWorld(world001);
}

