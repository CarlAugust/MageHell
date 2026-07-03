#include <iostream>
#include <stdint.h>
#include <raylib.h>

typedef int32_t i32;
struct Player {
    Vector2 position = { 0.0f, 0.0f };
    Vector2 size = { 20.0f, 20.0f };
    Vector2 hitbox = { 10.0f, 10.0f }; // Just example
    i32 hp = 0;
    float speed = 250;
};

int main(void) {
    const i32 screenWidth = 800;
    const i32 screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    Player player;
    Camera2D camera = {};
    camera.offset = {(screenWidth - player.size.x) / 2, (screenHeight - player.size.y) / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        if (IsKeyDown(KEY_LEFT)) {
            player.position.x -= player.speed * dt;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.position.x += player.speed * dt;
        }
        if (IsKeyDown(KEY_UP)) {
            player.position.y -= player.speed * dt;
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.position.y += player.speed * dt;
        }

        camera.target = player.position;
        BeginDrawing();

        ClearBackground(WHITE);

        i32 fontSize = 20;
        const char* text = "Welcome fool";
        i32 textLength = MeasureText(text, fontSize);
        
        BeginMode2D(camera);

        DrawRectangle(0.0f, 0.0f, 20, 20, BLUE);
        DrawRectangleV(player.position, player.size, GREEN);

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}