#pragma once
#include "Config.h"
#include <memory>
#include <raylib.h>
#include <vector>

struct Particle {
    Vector2 position;
    int cellX;
    int cellY;
    bool processed;
    Color color;
};

class ParticleManager {
public:
    ParticleManager(const int gridWidth, const int gridHeight);

    void spawnParticle(int cellX, int cellY);

    void update(float dt);
    void draw();

private:
    int getCellY(Vector2 position);
    Color getRandomColor();

    std::vector<Particle> m_particles;
    std::vector<std::vector<bool>> m_occupied;

    int m_gridWidth;
    int m_gridHeight;
};
