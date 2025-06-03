#include "Config.h"
#include "ParticleManager.h"
#include "raylib.h"
#include <iostream>

void handleInput(ParticleManager& particleManager)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();

        int cellX = mousePosition.x / config::cellSize;
        int cellY = mousePosition.y / config::cellSize;

        particleManager.spawnParticle(cellX, cellY);

        // std::cout << cellX << " " << cellY << std::endl;
    }
}

void update(float dt, ParticleManager& particleManager)
{
    handleInput(particleManager);
}

void drawGrid(const int gridWidth, const int gridHeight)
{
    for (int i = 1; i < gridWidth; i++) {
        DrawLine(i * config::cellSize, 0, i * config::cellSize, config::screenHeight, DARKGREEN);
    }

    for (int j = 1; j < gridHeight; j++) {
        DrawLine(0, j * config::cellSize, config::screenWidth, j * config::cellSize, DARKGREEN);
    }
}

void draw(RenderTexture2D& renderTexture, ParticleManager& particleManager)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(renderTexture.texture, 0, 0, WHITE);
    particleManager.draw();

    DrawFPS(0, 0);

    EndDrawing();
}

int main()
{
    if (!config::load("config.json"))
        return -1;

    const int gridWidth = config::screenWidth / config::cellSize;
    const int gridHeight = config::screenHeight / config::cellSize;

    ParticleManager particleManager(gridWidth, gridHeight);

    SetTraceLogLevel(LOG_ERROR);

    InitWindow(config::screenWidth, config::screenHeight, "Particle Simulation");
    SetTargetFPS(config::maxFps);

    RenderTexture2D renderTexture = LoadRenderTexture(config::screenWidth, config::screenHeight);
    BeginTextureMode(renderTexture);
    drawGrid(gridWidth, gridHeight);
    EndTextureMode();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        update(dt, particleManager);
        draw(renderTexture, particleManager);
    }

    CloseWindow();

    return 0;
}
