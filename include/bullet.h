#pragma once

#include <raylib.h>
#include <common.h>

struct Bullet {
    bool active = false;
    Vector2 position = { 0.0f, 0.0f };
    float speed = 0.0f;
    float timeAlive = 0.0f;
    float timeCap = 0.0f;
};

struct BulletMetaData {
    Texture2D texture = {};
    void(*update)(Bullet&) = nullptr;
};