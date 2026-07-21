#pragma once

#include <raylib.h>
#include <iostream>
#include <common.h>

struct Player {
    Texture2D texture;
    Vector2 position = { 0.0f, 0.0f };
    Vector2 prevPosition = position;
    Vector2 size = BasePlayerSize;
    Vector2 hitboxPosition = {size.x / 2, size.y / 2};
    i32 hp = 5;
    float hitboxRadius = 2.0f;
    float speed = 75;

    // For handling health
    Timer healthTimer = {};
    bool isDamaged = false;

    void takeDamage() {
        if (isDamaged) return;

        std::cout << "I took damage waiting 3 seconds\n";
        hp--;
        isDamaged = true;
    }

    void updateDamageState() {
        if (!isDamaged) return;

        if (healthTimer.elapses() > 0) {
            isDamaged = false;
            healthTimer.reset();
        } 
    }

    Player() {
        healthTimer.set(3.0f);
    }
};