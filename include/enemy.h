#pragma once

#include <functional>

#include <raylib.h>
#include <common.h>

struct Enemy {
    Timer timer = {};
    Vector2 position;
    u64 id = 0;
    float timeAlive = 0.0f;
    bool alive;
};

struct EnemyMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    std::function<void(Enemy&)> update = nullptr;
};

u64 RegisterEnemy(EnemyMetaData &RegisteredEnemyData);
void SpawnEnemy(Vector2 position, u64 enemyId);
void UpdateStateAndDrawEnemies();