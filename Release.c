#include "Screen.h"

#include "World.h"
#include "World001.h"
#include "World002.h"
#include "World003.h"


void Release() {
	ScreenRelease();

	DeleteWorld(world001);
	DeleteWorld(world002);
	DeleteWorld(world003);
}

