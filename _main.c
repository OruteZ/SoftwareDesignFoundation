#include <stdlib.h>
#include <stdbool.h>
#include "Time.h"
#include "Keyboard.h"

#include "Init.h"
#include "Update.h"
#include "Render.h"
#include "Release.h"

int main() {
    Init();
    while (true) {
        Update();
        Render();
    }
    Release();

    return 0;
}

