#include "Screen.h"
#include "Time.h"
#include "Camera.h"
#include "Game.h"
#include "Menu.h"
#include <stdio.h> // only used for debug
#include "Render.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void Render() {
	ScreenClear();

	if (GameState == Dungeon) {
		RenderCamera();
	}

	if (GameState == Menu) {
		RenderMenu();
	}

	ScreenFlipping();
}

