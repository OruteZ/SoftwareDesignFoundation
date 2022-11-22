#include "Screen.h"
#include "Time.h"
#include "Keyboard.h"

#include "World001.h"

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


    GameState = Dungeon;
    // Initialize worlds
    InitializeWorld001();

    StartWorld001();

    // Vectors
    Point playerSpawnPoint = { 3, 14 };
    player = CreatePlayer(playerSpawnPoint);
    enemies = CreateVector();
    expOrbs = CreateVector();
    particles = CreateVector();

    //test
    Point enemySpawnPoint = { 3, 12 };
    VectorInsert(enemies, CreateMeleeEnemy(enemySpawnPoint));
}
