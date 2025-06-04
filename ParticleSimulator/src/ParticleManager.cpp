#include "ParticleManager.h"
#include "Config.h"
#include <iostream>

ParticleManager::ParticleManager(const int gridWidth, const int gridHeight)
    : m_gridWidth(gridWidth)
    , m_gridHeight(gridHeight)
{
    m_occupied.resize(gridWidth, std::vector<bool>(gridHeight, false));
}

void ParticleManager::spawnParticle(int cellX, int cellY)
{
    if (m_occupied[cellX][cellY])
        return;

    Particle p;
    p.cellX = cellX;
    p.cellY = cellY;
    p.processed = false;
    p.color = getRandomColor();

    m_particles.push_back(p);
    m_occupied[cellX][cellY] = true;
}

void ParticleManager::update(float dt)
{
    for (auto& p : m_particles) {
        if (!p.processed) {
            if (p.cellY == m_gridHeight - 1 || m_occupied[p.cellX][p.cellY + 1]) {
                p.processed = true;
                continue;
            }

            if (!m_occupied[p.cellX][p.cellY + 1]) {
                p.cellY++;
                m_occupied[p.cellX][p.cellY] = true;
                m_occupied[p.cellX][p.cellY - 1] = false;
            }
        }
    }
}

void ParticleManager::draw()
{
    for (auto& p : m_particles) {
        DrawRectangle(p.cellX * config::cellSize, p.cellY * config::cellSize, config::cellSize, config::cellSize, p.color);
    }
}

Color ParticleManager::getRandomColor()
{
    return {
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        255
    };
}
