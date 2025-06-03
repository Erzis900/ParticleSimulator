#include "Config.h"
#include "raylib.h"

void update(float dt)
{
}

void drawGrid()
{
    for (int i = 1; i < config::screenWidth / config::cellSize; i++) {
        DrawLine(i * config::cellSize, 0, i * config::cellSize, config::screenHeight, DARKGREEN);
    }

    for (int j = 1; j < config::screenHeight / config::cellSize; j++) {
        DrawLine(0, j * config::cellSize, config::screenWidth, j * config::cellSize, DARKGREEN);
    }
}

void draw(RenderTexture2D& renderTexture)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(renderTexture.texture, 0, 0, WHITE);
    DrawFPS(0, 0);

    EndDrawing();
}

int main()
{
    if (!config::load("config.json"))
        return -1;

    SetTraceLogLevel(LOG_ERROR);

    InitWindow(config::screenWidth, config::screenHeight, "Particle Simulation");
    SetTargetFPS(config::maxFps);

    RenderTexture2D renderTexture = LoadRenderTexture(config::screenWidth, config::screenHeight);
    BeginTextureMode(renderTexture);
    drawGrid();
    EndTextureMode();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        update(dt);
        draw(renderTexture);
    }

    CloseWindow();

    return 0;
}
