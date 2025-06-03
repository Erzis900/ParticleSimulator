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
    p.position = { float(cellX) * config::cellSize, float(cellY) * config::cellSize };
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
        if (p.processed)
            continue;

        int cellY = getCellY(p.position);

        if (p.cellY != cellY) {
            m_occupied[p.cellX][p.cellY] = false;
            m_occupied[p.cellX][cellY] = true;

            p.cellY = cellY;
        }

        if (cellY + 1 == m_gridHeight) {
            p.processed = true;
            continue;
        }

        if (m_occupied[p.cellX][p.cellY + 1]) {
            continue;
        }

        p.position.y += config::deltaY * dt;
    }
}

void ParticleManager::draw()
{
    for (auto& p : m_particles) {
        DrawRectangleV(p.position, { float(config::cellSize), float(config::cellSize) }, p.color);
    }
}

int ParticleManager::getCellY(Vector2 position)
{
    return position.y / config::cellSize;
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
