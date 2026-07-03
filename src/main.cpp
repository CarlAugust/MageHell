#include <iostream>
#include <stdint.h>
#include <raylib.h>

typedef int32_t i32;

int main(void) {
    const i32 screenWidth = 800;
    const i32 screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Welcome fool", screenWidth / 2, screenHeight / 2, 20, RED);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}