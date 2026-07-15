#include <stdint.h>
#include <raylib.h>
#include <raymath.h>
#include <raylib_extra.h>
#include <assert.h>
#include <common.h>
#include <bullet.h>

#include <iostream>
#include <array>

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

float GetPlayerHorizontalDirection(Player &player) {
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

PublicGameData& GetPublicGameData() {
    static PublicGameData instance;
    return instance;
}

int main(void) {
    const i32 screenWidth = 1280;
    const i32 screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "MageHell dogde the bullets pew pew");
    SetTargetFPS(165);

    // Initilize game data ==================
    PublicGameData& gameData = GetPublicGameData();
    gameData = {0};

    Player& player = gameData.player;
    player.texture = LoadTexture("assets/redmage_forward.png");
    stone1_floortileTex = LoadTexture("assets/stone1_floortile.png");

    Camera2D& camera = gameData.camera;
    camera.offset = {(screenWidth - player.size.x) / 2, (screenHeight - player.size.y) / 2};
    camera.rotation = 0.0f;
    camera.zoom = 6.0f;

    // End of gamedata initilization ===================================


    BulletMetaData redBulletMetaData = {};
    redBulletMetaData.texture = LoadTextureSafe("assets/bullets/.png");
    redBulletMetaData.update = [](Bullet &bullet) {
        float dt = GetFrameTime();
        Vector2 direction = Vector2Subtract(bullet.position, bullet.lastPosition);
        direction = Vector2Normalize(direction);

        bullet.lastPosition = bullet.position;

        bullet.position.x += direction.x * bullet.speed * dt;
        bullet.position.y += direction.y * bullet.speed * dt;
    };
    redBulletMetaData.hitboxRadius = 1.0f;

    u64 redBulletId = RegisterBullet(redBulletMetaData);

    float timeInterval = 0.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();
        HandlePlayerInput(player);
        camera.target = player.position;

        timeInterval += dt;
        for (float x = -1.0f; x <= 1.0f; x += 1.0f) {
            for (float y = -1.0f; y <= 1.0f; y += 1.0f) {
                if (x == 0.0f && y == 0.0f) continue;
                SpawnBullet({x * 20.0f, y * 20.0f}, redBulletId);
            }
        }
        timeInterval = 0.0f;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(10, 10);
        
        BeginMode2D(camera);

            Rectangle Destination = {player.position.x, player.position.y, player.size.x, player.size.y};

            Rectangle playerTexRectangle = {0.0f, 0.0f, player.texture.width, player.texture.height};
            float playerDirection = GetPlayerHorizontalDirection(player);
            if (playerDirection != 0.0f) {
                playerTexRectangle.width = std::abs(playerTexRectangle.width) * playerDirection;
            }

            DrawTexturePro(player.texture, playerTexRectangle, Destination, { 0.0f, 0.0f }, 0.0f, WHITE);
            DrawCircleV(Vector2Add(player.position, player.hitboxPosition), player.hitboxRadius, {255, 0, 0, 128});

            UpdatePositionsAndDrawBullets();

        EndMode2D();
        EndDrawing();

        // End of frame updates
        player.prevPosition = player.position;
    }

    CloseWindow();
    return 0;
}