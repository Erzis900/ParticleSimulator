#pragma once
#include "Config.h"
#include <memory>
#include <raylib.h>
#include <vector>

enum class ParticleType {
    SAND,
    WATER,
    SOLID
};

struct Particle {
    int cellX;
    int cellY;
    bool processed;
    ParticleType type;
    Color color;
};

class ParticleManager {
public:
    ParticleManager(const int gridWidth, const int gridHeight);

    void spawnParticle(ParticleType type, int cellX, int cellY);

    void update(float dt);
    void draw();

private:
    std::vector<Particle> m_particles;
    std::vector<std::vector<bool>> m_occupied;

    int m_gridWidth;
    int m_gridHeight;
};
