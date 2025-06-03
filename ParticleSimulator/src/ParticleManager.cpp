#include "ParticleManager.h"
#include "Config.h"

ParticleManager::ParticleManager(const int gridWidth, const int gridHeight)
{
    // m_particles.resize(gridWidth * gridHeight);
}

void ParticleManager::spawnParticle(int cellX, int cellY)
{
    Particle p;
    p.position = { float(cellX) * config::cellSize, float(cellY) * config::cellSize };

    m_particles.push_back(p);
}

void ParticleManager::draw()
{
    for (auto& p : m_particles) {
        DrawRectangleV(p.position, { float(config::cellSize), float(config::cellSize) }, WHITE);
    }
}
