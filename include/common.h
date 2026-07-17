#pragma once

/*
    Common variables and types used across the entire program
*/

#include <stdint.h>
#include <raylib.h>
#include <cmath>

typedef int32_t i32;
typedef size_t u64;
typedef uint8_t u8;



const Vector2 BasePlayerSize = { 8.0f, 16.0f };
const float TileSize = 8.0f;

struct Player {
    Texture2D texture;
    Vector2 position = { 0.0f, 0.0f };
    Vector2 prevPosition = position;
    Vector2 size = BasePlayerSize;
    Vector2 hitboxPosition = {size.x / 2, size.y / 2};
    i32 hp = 0;
    float hitboxRadius = 2.0f;
    float speed = 75;
};

struct Timer {
    float time = 0.0f;
    float target = 1.0f;

    void add(float seconds) { 
        time += seconds;
    }

    void set(float seconds) {
        target = seconds;
    }

    u64 elapses() {
        u64 elapse_count = static_cast<u64>(time / target);
        time = std::fmod(time, target);
        return elapse_count;
    }
};

/*
    Game data that gets shared across files.
    Does not contain global variables found in specific files like bullet.c
    but rather game state that all files might want like the player state
*/
struct PublicGameData {
    Player player;
    Camera2D camera;
};
PublicGameData& GetPublicGameData();