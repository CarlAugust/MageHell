#pragma once

#include <raylib.h>

struct Enemy {
    Vector2 position;
    u64 id;
    bool alive;
};

struct EnemyMetaData {
    float hitboxRadius = 0.0f;
    Texture2D texture = {};
    void(*update)(Enemy&) = nullptr;
};

u64 RegisterEnemy(EnemyMetaData RegisteredEnemyData);
void SpawnEnemy(Vector2 position, u64 enemyId);
void UpdateStateAndDrawEnemies();