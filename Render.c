#include "Screen.h"
#include "Time.h"
#include "Camera.h"

#include <stdio.h> // only used for debug

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void Render() {
	ScreenClear();

	RenderCamera();

	ScreenFlipping();
}

