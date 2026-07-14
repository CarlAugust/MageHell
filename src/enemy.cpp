#include <common.h>
#include <assert.h>
#include <enemy.h>

#include <vector>
#include <array>

namespace {
    struct EnemyMetaDataRegistry {
        std::vector<EnemyMetaData> registry;
    };

    EnemyMetaDataRegistry G_EnemyMetaDataRegistry{};
}

u64 RegisterEnemy(EnemyMetaData RegisteredEnemyData) {
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
    constexpr u64 ENEMY_CAP = 2048;
    struct EnemyBuffer {
        u64 curr = 0;
        u64 cap = ENEMY_CAP;
        std::array<Enemy, ENEMY_CAP> buffer;
    };

    EnemyBuffer G_EnemyBuffer = {};
}