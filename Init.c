#include "Screen.h"
#include "Time.h"
#include "Keyboard.h"

#include "World001.h"

#include "Game.h"

#ifdef DEBUG
#include "Debug.h"
#endif 
void Init()
{
#ifdef DEBUG
    DebugInit();
#endif
    ScreenInit();
    InitTime();
    InitializeKeyboard();

    // Initialize worlds
    InitializeWorld001();

    // Vectors
    // todo: player = CreatePlayer();
    enemies = CreateVector();
    expOrbs = CreateVector();


#ifdef DEBUG
    debugVector = CreateVector();
#endif
}
