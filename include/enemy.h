#pragma once

#include <functional>

#include <raylib.h>
#include <common.h>
#include <bullet.h>

struct Enemy {
    Timer timer = {};
    Vector2 position = {0, 0};
    u64 id = 0;
    u64 hp = 0;
    float timeAlive = 0.0f;
    bool alive;
};

struct EnemyMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    std::function<void(Enemy&)> update = nullptr;
};

u64 RegisterEnemy(EnemyMetaData &RegisteredEnemyData);
void SpawnEnemy(const Enemy& enemyTemplate);
void UpdateStateAndDrawEnemies();
void EventBulletEnemyCollisions(Bullet& bullet, const BulletMetaData& bulletMetaData);