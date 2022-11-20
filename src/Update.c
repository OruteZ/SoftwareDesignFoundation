#include "Time.h"
#include "Keyboard.h"

#ifdef DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif
void Update() {
	UpdateTime();
	UpdateKeyboard();

#ifdef DEBUG
	if (GetKeyDown('D')) DebugPrint("D Pressed!, %d", rand());
#endif
}
