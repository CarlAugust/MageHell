#include <raylib_extra.h>

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