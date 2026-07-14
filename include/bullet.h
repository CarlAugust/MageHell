#pragma once

#include <raylib.h>
#include <common.h>

struct Bullet {
    bool active = false;
    Vector2 lastPosition = { 0.0f, 0.0f };
    Vector2 position = { 0.0f, 0.0f };
    float speed = 0.0f;
    float timeAlive = 0.0f;
    float timeCap = 0.0f;
    u64 bulletId = 0;
};

struct BulletMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    void(*update)(Bullet&) = nullptr;
};

const BulletMetaData& GetBulletMetaData(u64 bulletId);
void SpawnBullet(Vector2 position, u64 bulletId);
u64 RegisterBullet(BulletMetaData RegisteredBulletData);
void UpdatePositionsAndDrawBullets();