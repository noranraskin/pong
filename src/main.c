// main.c

#include "main.h"
#include "game.h"
#include "menu.h"
#include "raylib.h"

double scale_factor = 1.0;
int main() {
    SetTraceLogLevel(LOG_NONE);
    menu();
    return 0;
}

