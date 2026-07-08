#include <stdint.h>
#include <raylib.h>
#include <raymath.h>
#include <raylib_extra.h>
#include <assert.h>
#include <common.h>
#include <bullet.h>

#include <iostream>
#include <array>

const Vector2 BasePlayerSize = { 8.0f, 16.0f };
const float TileSize = 8.0f;

Texture2D stone1_floortileTex;

std::array<std::array<u8, 256>, 256> map; 

void DrawMap() {
    float y = 0;
    for (auto &row : map) {
        float x = 0;

        for (auto &tile : row) {
            DrawTextureEx(stone1_floortileTex, {x, y}, 0.0f, 1.0f, WHITE);
                    
            x += TileSize;
        }
        y += TileSize;
    }
}

void FillMap() {
    for (auto &row : map) {
        for (auto &tile : row) {
            tile = 1;
        }
    }
}

struct Player {
    Texture2D texture;
    Vector2 position = { 0.0f, 0.0f };
    Vector2 prevPosition = position;
    Vector2 size = BasePlayerSize;
    i32 hp = 0;
    float hitboxRadius = 2.0f;
    float speed = 75;
};

float GetPlayerDirection(Player &player) {
    float x = player.position.x - player.prevPosition.x;
    if (x < 0.0f) return 1.0f;
    else if (x > 0.0f) return -1.0f;

    return 0.0f;
}

void HandlePlayerInput(Player &player) {
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
}


int main(void) {
    const i32 screenWidth = 1920;
    const i32 screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    Player player;
    player.texture = LoadTexture("assets/redmage_forward.png");
    stone1_floortileTex = LoadTexture("assets/stone1_floortile.png");

    Camera2D camera = {};
    camera.offset = {(screenWidth - player.size.x) / 2, (screenHeight - player.size.y) / 2};
    camera.rotation = 0.0f;
    camera.zoom = 6.0f;

    BulletMetaData redBulletMetaData = {};
    redBulletMetaData.texture = LoadTextureSafe("assets/red_bullet.png");
    redBulletMetaData.update = [](Bullet &bullet) {
        float dt = GetFrameTime();
        Vector2 direction = Vector2Subtract(bullet.position, bullet.lastPosition);
        direction = Vector2Normalize(direction);

        bullet.lastPosition = bullet.position;

        bullet.position.x += direction.x * bullet.speed * dt;
        bullet.position.y += direction.y * bullet.speed * dt;
    };
    u64 redBulletId = RegisterBullet(redBulletMetaData);

    float timeInterval = 0.0f;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        HandlePlayerInput(player);
        camera.target = player.position;

        timeInterval += dt;
        if (timeInterval > 0.1f) {
            for (float x = -1.0f; x <= 1.0f; x += 1.0f) {
                for (i32 y = -1.0f; y <= 1.0f; y += 1.0f) {
                    if (x == 0.0f && y == 0.0f) continue;
                    SpawnBullet({x * 20.0f, y * 20.0f}, redBulletId);
                }
            }
            timeInterval = 0.0f;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(10, 10);
        
        BeginMode2D(camera);

            Rectangle Destination = {player.position.x, player.position.y, player.size.x, player.size.y};

            Rectangle playerTexRectangle = {0.0f, 0.0f, player.texture.width, player.texture.height};
            float playerDirection = GetPlayerDirection(player);
            if (playerDirection != 0.0f) {
                playerTexRectangle.width = std::abs(playerTexRectangle.width) * playerDirection;
            }

            DrawTexturePro(player.texture, playerTexRectangle, Destination, { 0.0f, 0.0f }, 0.0f, WHITE);
            DrawCircleVInsideRectangle(player.position, player.size, player.hitboxRadius, {255, 0, 0, 128});
            DrawTextureEx(redBulletMetaData.texture, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);

            UpdatePositionsAndDrawBullets();

        EndMode2D();
        EndDrawing();

        // End of frame updates
        player.prevPosition = player.position;
    }

    CloseWindow();
    return 0;
}