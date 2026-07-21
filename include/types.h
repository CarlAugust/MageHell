#pragma once

#include <raylib.h>
#include <iostream>

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64; 

const Vector2 BasePlayerSize = { 8.0f, 16.0f };
const float TileSize = 32.0f;

struct Player {
    Texture2D texture;
    Vector2 position = { 0.0f, 0.0f };
    Vector2 prevPosition = position;
    Vector2 size = BasePlayerSize;
    Vector2 hitboxPosition = {size.x / 2, size.y / 2};
    i32 hp = 5;
    float hitboxRadius = 2.0f;
    float speed = 75;

    // For handling health
    Timer healthTimer = {};
    bool isDamaged = false;

    void takeDamage() {
        if (isDamaged) return;

        std::cout << "I took damage waiting 3 seconds\n";
        hp--;
        isDamaged = true;
    }

    void updateDamageState() {
        if (!isDamaged) return;

        if (healthTimer.elapses() > 0) {
            isDamaged = false;
            healthTimer.reset();
        } 
    }

    Player() {
        healthTimer.set(3.0f);
    }
};

struct Timer {
    float time = 0.0f;
    float target = 1.0f;

    void add(float seconds) { 
        time += seconds;
    }

    void reset() {
        time = 0.0f;
    }

    void set(float seconds) {
        target = seconds;
    }

    /*
        Elapses adds time and calculates how many times the target has been reached
        Elapses function must be called every frame, its the natural way its done at least 
    */
    u64 elapses() {
        float dt = GetFrameTime();
        time += dt;
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