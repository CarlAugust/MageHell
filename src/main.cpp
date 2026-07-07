#include <stdint.h>
#include <raylib.h>
#include <assert.h>
#include <common.h>

#include <iostream>
#include <array>

const Vector2 BasePlayerSize = { 8.0f, 16.0f };
const float TileSize = 8.0f;

std::array<std::array<u8, 256>, 256> map; 

struct Player {
    Vector2 position = { 0.0f, 0.0f };
    Vector2 prevPosition = position;
    Vector2 size = BasePlayerSize;
    i32 hp = 0;
    float hitboxRadius = 4.0f;
    float speed = 75;
};

void DrawCircleVInsideRectangle(Vector2 position, Vector2 rectangleSize, float circleRadius, Color color) {
    Vector2 circlePosition = position;
    circlePosition.x += rectangleSize.x / 2;
    circlePosition.y += rectangleSize.y / 2;
    DrawCircleV(circlePosition, circleRadius, color);
}

float GetPlayerDirection(Player &player) {
    float x = player.position.x - player.prevPosition.x;
    if (x < 0.0f) return 1.0f;
    else if (x > 0.0f) return -1.0f;

    return 0.0f;
}


int main(void) {
    const i32 screenWidth = 1280;
    const i32 screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    Player player;
    Texture2D playerTex = LoadTexture("assets/redmage_forward.png");
    Rectangle playerTexRectangle = {0.0f, 0.0f, playerTex.width, playerTex.height};

    Texture2D stone1_floortileTex = LoadTexture("assets/stone1_floortile.png");
    for (auto &row : map) {
        for (auto &tile : row) {
            tile = 1;
        }
    }

    Camera2D camera = {};
    camera.offset = {(screenWidth - player.size.x) / 2, (screenHeight - player.size.y) / 2};
    camera.rotation = 0.0f;
    camera.zoom = 6.0f;

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

            float y = 0;
            for (auto &row : map) {
                float x = 0;

                for (auto &tile : row) {
                    DrawTextureEx(stone1_floortileTex, {x, y}, 0.0f, 1.0f, WHITE);
                    
                    x += TileSize;
                }
                y += TileSize;
            }

            DrawRectangle(0.0f, 0.0f, 20, 20, BLUE);

            Rectangle Destination = {player.position.x, player.position.y, player.size.x, player.size.y};

            float playerDirection = GetPlayerDirection(player);
            if (playerDirection != 0.0f) {
                playerTexRectangle.width = std::abs(playerTexRectangle.width) * playerDirection;
            }

            DrawTexturePro(playerTex, playerTexRectangle, Destination, { 0.0f, 0.0f }, 0.0f, WHITE);

        EndMode2D();
        EndDrawing();

        // End of frame updates
        player.prevPosition = player.position;
    }

    CloseWindow();
    return 0;
}