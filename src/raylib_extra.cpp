#include <raylib_extra.h>
#include <raylib.h>
#include <raymath.h>

#include <iostream>

Texture2D getErrorTexture() {
    Image img = GenImageChecked(16, 16, 4, 4, PURPLE, BLACK);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);

    return tex;
}

Texture2D LoadTextureSafe(const char* filePath) {
    Texture2D tex = LoadTexture(filePath);
    if (tex.height == 0 || tex.width == 0) {
        return getErrorTexture();
    }
    return tex;
}

void DrawTextureCenterEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint) {
    position.x -= texture.width / 2;
    position.y -= texture.height / 2;
    DrawTextureEx(texture, position, rotation, scale, tint);
}

DoubleVector2 GetCameraBounds(Camera2D camera) {
    DoubleVector2 vec;
    vec.x1 = camera.target.x - camera.offset.x / camera.zoom;
    vec.x2 = camera.target.x + camera.offset.x / camera.zoom;
    vec.y1 = camera.target.y - camera.offset.y / camera.zoom;
    vec.y2 = camera.target.y + camera.offset.y / camera.zoom;

    return vec;
}