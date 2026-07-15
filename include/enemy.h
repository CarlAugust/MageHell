#pragma once

#include <raylib.h>

struct Enemy {
    Vector2 position;
    bool alive;
};

struct EnemyMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    void(*update)(Enemy&) = nullptr;
};
