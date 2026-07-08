#include <raylib.h>
#include <common.h>
#include <bullet.h>
#include <assert.h>

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

const BulletMetaData& GetBulletMetaData(u64 bulletId) {
    assert(bulletId < G_BulletMetaDataRegistry.registry.size());
    return G_BulletMetaDataRegistry.registry[bulletId];
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

void SpawnBullet(Vector2 position, u64 bulletId) {
    u64 curr = G_BulletBuffer.curr;
    Bullet &bullet = G_BulletBuffer.buffer[curr];

    bullet.active = true;
    bullet.position = position;
    bullet.bulletId = bulletId;

    // TODO: How should these be defined?
    bullet.speed = 20.0f;
    bullet.timeCap = 5.0f;
};

void UpdatePositionsAndDrawBullets() {
    float dt = GetFrameTime();
    for (Bullet &b : G_BulletBuffer.buffer) {
        if (!b.active) continue;

        b.timeAlive += dt;
        if (b.timeAlive >= b.timeCap) {
            b.active = false;
            continue;
        }

        BulletMetaData BulletMetaData = GetBulletMetaData(b.bulletId);
        BulletMetaData.update(b);
        DrawTextureV(BulletMetaData.texture, b.position, WHITE);

    }
}