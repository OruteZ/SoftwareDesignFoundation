#include "Screen.h"
#include "Time.h"
#include "Keyboard.h"

#include "World001.h"

#include "Game.h"
#include "Player.h"
#include "Camera.h"

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
    InitCamera();

    // Initialize worlds
    InitializeWorld001();

    SetCurrentWorld(world001);

    // Vectors
    Point playerSpawnPoint = { 3, 14 };
    player = CreatePlayer(playerSpawnPoint);
    enemies = CreateVector();
    expOrbs = CreateVector();
    particles = CreateVector();
}
