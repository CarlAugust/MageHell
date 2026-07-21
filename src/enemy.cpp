#include <common.h>
#include <assert.h>
#include <enemy.h>
#include <raylib_extra.h>

#include <vector>
#include <array>

namespace {
    struct EnemyMetaDataRegistry {
        std::vector<EnemyMetaData> registry;
    };

    EnemyMetaDataRegistry G_EnemyMetaDataRegistry{};
}

u64 RegisterEnemy(EnemyMetaData &RegisteredEnemyData) {
    G_EnemyMetaDataRegistry.registry.push_back(RegisteredEnemyData);
    return G_EnemyMetaDataRegistry.registry.size() - 1;
}

const EnemyMetaData& GetEnemyMetaData(u64 enemyId) {
    assert(enemyId < G_EnemyMetaDataRegistry.registry.size());
    return G_EnemyMetaDataRegistry.registry[enemyId];
}

/*
    ENEMY BUFFER: 
*/
namespace {
    constexpr u64 ENEMY_CAP = 128;
    struct EnemyBuffer {
        u64 curr = 1;
        u64 cap = ENEMY_CAP;
        std::array<Enemy, ENEMY_CAP> buffer;
    };

    EnemyBuffer G_EnemyBuffer = {};
}

void SpawnEnemy(Vector2 position, u64 enemyId) {
    u64 curr = G_EnemyBuffer.curr;
    Enemy &enemy = G_EnemyBuffer.buffer[curr];
    enemy = Enemy{};
    enemy.alive = true;

    G_EnemyBuffer.curr++;
    if (G_EnemyBuffer.curr == G_EnemyBuffer.cap) G_EnemyBuffer.curr = 1;
};



void UpdateStateAndDrawEnemies() {
    
    for (Enemy &enemy : G_EnemyBuffer.buffer) {
        if (enemy.alive == false) continue;

        const EnemyMetaData &enemyMetaData = GetEnemyMetaData(enemy.id);
        assert(enemyMetaData.update != nullptr);
        enemyMetaData.update(enemy);

        DrawTextureCenterEx(enemyMetaData.texture, enemy.position, 0.0f, 1.0f, WHITE);
    }
}