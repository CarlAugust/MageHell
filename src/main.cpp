#include <iostream>
#include <stdint.h>
#include <raylib.h>

typedef int32_t i32;

const Vector2 BasePlayerSize = { 16.0f, 32.0f };

struct Player {
    Vector2 position = { 0.0f, 0.0f };
    Vector2 size = BasePlayerSize;
    i32 hp = 0;
    float hitboxRadius = 8.0f;
    float speed = 250;
};

void DrawCircleVInsideRectangle(Vector2 position, Vector2 rectangleSize, float circleRadius, Color color) {
    Vector2 circlePosition = position;
    circlePosition.x += rectangleSize.x / 2;
    circlePosition.y += rectangleSize.y / 2;
    DrawCircleV(circlePosition, circleRadius, color);
}


int main(void) {
    const i32 screenWidth = 1280;
    const i32 screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    Player player;
    Texture2D playerTex = LoadTexture("assets/redmage_forward.png");

    Camera2D camera = {};
    camera.offset = {(screenWidth - player.size.x) / 2, (screenHeight - player.size.y) / 2};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player.position.x -= player.speed * dt;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player.position.x += player.speed * dt;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            player.position.y -= player.speed * dt;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            player.position.y += player.speed * dt;
        }

        camera.target = player.position;
        BeginDrawing();
            ClearBackground(BLACK);
        
        BeginMode2D(camera);

            DrawRectangle(0.0f, 0.0f, 20, 20, BLUE);
            DrawTextureEx(playerTex, player.position, 0.0f, 2.0f, WHITE);
            DrawCircleVInsideRectangle(player.position, player.size, player.hitboxRadius / 2, {122, 122, 0, 255});
            

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}