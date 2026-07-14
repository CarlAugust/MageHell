#pragma once

/*
    This header files contains extra wrapper functions around Raylib functions to make my
    own life easier.
*/

#include <raylib.h>

Texture2D LoadTextureSafe(const char* filePath);

/*
    DrawTextureEx but it draws the texture with the position at the center
*/
void DrawTextureCenterEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);