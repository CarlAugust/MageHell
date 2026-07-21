#pragma once

/*
    This header files contains extra wrapper functions around Raylib functions to make my
    own life easier.
*/

#include <raylib.h>

struct DoubleVector2 {
    float x1;
    float x2;
    float y1;
    float y2;
};

Texture2D LoadTextureSafe(const char* filePath);

/*
    DrawTextureEx but it draws the texture with the position at the center
*/
void DrawTextureCenterEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
DoubleVector2 GetCameraBounds(Camera2D camera);
Vector2 GetMousePositionOnCamera(Camera2D camera);