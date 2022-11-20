#include <Windows.h>
#include "Keyboard.h"

#define KEY_DOWN_STATE (0x8000)
#define KEY_UP_STATE (0x0000)

enum KeyState {
	DownStroke,
	UpStroke,
	Down,
	Up
};
typedef struct _Key {
	SHORT previous_state;
	SHORT current_state;
	enum KeyState parsed_state;
} Key;
typedef struct _Keyboard {
	Key key[256];
} Keyboard;



// global variable to store keyboard state
Keyboard keyboard;



void InitializeKeyboard() {
	for (int i = 0; i < 256; i++) {
		keyboard.key[i].previous_state = keyboard.key[i].current_state = KEY_UP_STATE;
		keyboard.key[i].parsed_state = Up;
	}
}
void UpdateKeyboard() {
	SHORT keyboard_state[256];

	for (int i = 0; i < 256; i++) {
		// update prev, curr state
		keyboard.key[i].previous_state = keyboard.key[i].current_state;
		keyboard.key[i].current_state = GetAsyncKeyState(i) & KEY_DOWN_STATE;

		SHORT prev = keyboard.key[i].previous_state;
		SHORT curr = keyboard.key[i].current_state;

		//
		// parse from prev, curr
		//
		if (~(prev ^ curr) & KEY_DOWN_STATE) { // if key NOT changed from prev to curr

			if (curr & KEY_DOWN_STATE) keyboard.key[i].parsed_state = Down; // held down
			else keyboard.key[i].parsed_state = Up; // kept up

		}
		else { // key is changed

			if (curr & KEY_DOWN_STATE) keyboard.key[i].parsed_state = DownStroke; // pushed down
			else keyboard.key[i].parsed_state = UpStroke; // released up

		}
	}
}

BOOLEAN GetKeyDown(const unsigned char key) {
	if (keyboard.key[key].parsed_state == DownStroke) return TRUE;
	else return FALSE;
}
BOOLEAN GetKey(const unsigned char key) {
	if (keyboard.key[key].parsed_state == DownStroke || keyboard.key[key].parsed_state == Down) return TRUE;
	else return FALSE;
}
BOOLEAN GetKeyUp(const unsigned char key) {
	if (keyboard.key[key].parsed_state == UpStroke) return TRUE;
	else return FALSE;
}