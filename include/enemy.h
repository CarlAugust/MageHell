#pragma once

#include <functional>

#include <raylib.h>

struct Enemy {
    Vector2 position;
    u64 id;
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