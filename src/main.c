// main.c

#include "main.h"

void loop();
void update();
void draw();

int main() {
    InitWindow(800, 450, "Pong");
    SetTargetFPS(60);
    loop();
    return 0;
}

void loop() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
    CloseWindow();
}

void update() {

}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}