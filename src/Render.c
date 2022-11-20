#include "Screen.h"
#include "Time.h"

#include <stdio.h> // only used for debug

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void Render() {
	ScreenClear();

	// debug start
	char buffer[50];
	sprintf_s(buffer, 50, "%06.4f", Time.time);
	ScreenPrint(0, 1, buffer);
	sprintf_s(buffer, 50, "%06.4f", Time.deltaTime);
	ScreenPrint(0, 2, buffer);
	ScreenPrint(0, 3, "¹¹¾ß Test");
	// debug end


	ScreenFlipping();
}

