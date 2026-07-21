#pragma once

#include <raylib.h>
#include <common.h>
#include <functional>

struct Bullet {
    Vector2 lastPosition = { 0.0f, 0.0f };
    Vector2 position = { 0.0f, 0.0f };
    u64 id = 0;
    float speed = 0.0f;
    float timeAlive = 0.0f;
    float timeCap = 0.0f;
    bool isFriendly = false;
    bool active = false;
};

struct BulletMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    std::function<void(Bullet&)> update = nullptr;
};

const BulletMetaData& GetBulletMetaData(u64 bulletId);
void SpawnBullet(const Bullet bulletTemplate);
u64 RegisterBullet(BulletMetaData &RegisteredBulletData);
void UpdateStateAndDrawBullets();