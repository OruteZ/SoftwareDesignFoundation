#include "Screen.h"
#include "Time.h"
#include "Keyboard.h"

#include "World001.h"

#include "Game.h"

void Init()
{
    ScreenInit();
    InitTime();
    InitializeKeyboard();

    // Initialize worlds
    InitializeWorld001();

    // Vectors
    // todo: player = CreatePlayer();
    mortals = CreateVector();
    expOrbs = CreateVector();
}
