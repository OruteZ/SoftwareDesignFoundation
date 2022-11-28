#include "Screen.h"
#include "Time.h"
#include "Keyboard.h"

#include "World001.h"
#include "World002.h"
#include "World003.h"

#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "MeleeEnemy.h"

#ifdef DEBUG
#include "Debug.h"
#endif 
void Init()
{
#ifdef DEBUG
    DebugInit();
    //debugVector = CreateVector();
#endif
    ScreenInit();
    InitTime();
    InitializeKeyboard();
    InitCamera();


    GameState = Menu;
    // Initialize worlds
    InitializeWorld();
    InitializeWorld001();
    InitializeWorld002();
    InitializeWorld003();

    // StartWorld001();

    // Vectors
    player = CreatePlayer();
    enemies = CreateVector();
    expOrbs = CreateVector();
    particles = CreateVector();
}
