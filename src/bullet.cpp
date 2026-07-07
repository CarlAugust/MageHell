#include <raylib.h>
#include <common.h>
#include <bullet.h>

#include <array>
#include <vector>

namespace {
    struct BulletMetaDataRegistry {
        std::vector<BulletMetaData> registry;
    };

    BulletMetaDataRegistry G_BulletMetaDataRegistry{};
}

u64 RegisterBullet(BulletMetaData RegisteredBulletData) {
    G_BulletMetaDataRegistry.registry.push_back(RegisteredBulletData);
    return G_BulletMetaDataRegistry.registry.size() - 1;
}

const BulletMetaData& GetBulletMetaData(u64 id) {
    return G_BulletMetaDataRegistry.registry[id];
}

/*
    BULLET BUFFER: 
*/
namespace {
    constexpr u64 BULLET_CAP = 2048;
    struct BulletBuffer {
        u64 curr = 0;
        u64 cap = BULLET_CAP;
        std::array<Bullet, BULLET_CAP> buffer;
    };

    BulletBuffer G_BulletBuffer = {};
}

void SpawnBullet(Vector2 position) {
    u64 curr = G_BulletBuffer.curr;
    Bullet &bullet = G_BulletBuffer.buffer[curr];

    bullet.active = true;
    bullet.position = position;

};