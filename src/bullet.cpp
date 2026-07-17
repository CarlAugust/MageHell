#include <raylib.h>
#include <raymath.h>
#include <raylib_extra.h>
#include <common.h>
#include <bullet.h>
#include <assert.h>
#include <stdio.h>

#include <array>
#include <vector>
#include <iostream>

namespace {
    struct BulletMetaDataRegistry {
        std::vector<BulletMetaData> registry;
    };

    BulletMetaDataRegistry G_BulletMetaDataRegistry{};
}

u64 RegisterBullet(BulletMetaData &RegisteredBulletData) {
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
        u64 curr = 1;
        u64 cap = BULLET_CAP;
        std::array<Bullet, BULLET_CAP> buffer;
    };

    BulletBuffer G_BulletBuffer = {};
}

void SpawnBullet(Vector2 position, u64 bulletId) {
    u64 curr = G_BulletBuffer.curr;
    Bullet &bullet = G_BulletBuffer.buffer[curr];
    bullet = Bullet{};

    bullet.active = true;
    bullet.position = position;
    bullet.id = bulletId;

    // TODO: How should these be defined?
    bullet.speed = 20.0f;
    bullet.timeCap = 50000.0f;

    G_BulletBuffer.curr++;
    if (G_BulletBuffer.curr == G_BulletBuffer.cap) G_BulletBuffer.curr = 1;
};

void UpdateStateAndDrawBullets() {
    float dt = GetFrameTime();
    PublicGameData& gameData = GetPublicGameData();
    Player& player = gameData.player;

    for (Bullet &bullet : G_BulletBuffer.buffer) {
        if (!bullet.active) continue;        
        
        bullet.timeAlive += dt;
        if (bullet.timeAlive >= bullet.timeCap) {
            bullet.active = false;
            continue;
        }


        const BulletMetaData &bulletMetaData = GetBulletMetaData(bullet.id);
        assert(bulletMetaData.update != nullptr);
        bulletMetaData.update(bullet);

        bool collision = CheckCollisionCircles(
            Vector2Add(player.position, player.hitboxPosition),
            player.hitboxRadius, 
            bullet.position, 
            bulletMetaData.hitboxRadius
        );

        if (collision) {
            player.takeDamage();
        }

        DrawTextureCenterEx(bulletMetaData.texture, bullet.position, 0.0f, 1.0f, WHITE);
    }
}