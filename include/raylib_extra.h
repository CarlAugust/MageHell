#pragma once

/*
    This header files contains extra wrapper functions around Raylib functions to make my
    own life easier.
*/

#include <raylib.h>

Texture2D LoadTextureSafe(const char* filePath);
void DrawCircleVInsideRectangle(Vector2 position, Vector2 rectangleSize, float circleRadius, Color color);