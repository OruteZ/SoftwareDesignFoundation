#include <stdlib.h>
#include <stdbool.h>
#include "Time.h"
#include "Keyboard.h"

#include "Init.h"
#include "Update.h"
#include "Render.h"
#include "Release.h"

#include "Game.h"

int main() {
    //Init();
    //while (true) {
    //    Update();
    //    Render();
    //    if (GameState == Exiting) break;
    //}
    //Release();

#ifdef DEBUG
#include "Canvas.h"
    InitCanvas();
    //FillCanvasWithRandomCells();
    FillCanvasWithTestString();
    PrintCanvas();
    getch();
#endif // DEBUG


    return 0;
}

