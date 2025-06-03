#pragma once
#include "Config.h"
#include <memory>
#include <raylib.h>
#include <vector>

struct Particle {
    Vector2 position;
};

class ParticleManager {
public:
    ParticleManager(const int gridWidth, const int gridHeight);

    void spawnParticle(int cellX, int cellY);

    void update(float dt);
    void draw();

private:
    std::vector<Particle>
        m_particles;
};
