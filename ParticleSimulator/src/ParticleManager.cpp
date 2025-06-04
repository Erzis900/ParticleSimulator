#include "ParticleManager.h"
#include "Config.h"
#include <iostream>

ParticleManager::ParticleManager(const int gridWidth, const int gridHeight)
    : m_gridWidth(gridWidth)
    , m_gridHeight(gridHeight)
{
    m_occupied.resize(gridWidth, std::vector<bool>(gridHeight, false));
}

void ParticleManager::spawnParticle(ParticleType type, int cellX, int cellY)
{
    if (m_occupied[cellX][cellY])
        return;

    Particle p;
    p.cellX = cellX;
    p.cellY = cellY;
    p.processed = false;
    p.type = type;

    switch (p.type) {
    case ParticleType::SAND:
        p.color = { 199, 199, 99, 255 };
        break;
    case ParticleType::WATER:
        p.color = BLUE;
        break;
    }

    m_particles.push_back(p);
    m_occupied[cellX][cellY] = true;
}

void ParticleManager::update(float dt)
{
    for (auto& p : m_particles) {
        if (!p.processed) {
            if (p.cellY == m_gridHeight - 1) {
                p.processed = true;
                continue;
            }

            if (!m_occupied[p.cellX][p.cellY + 1]) { // if cell below empty
                p.cellY++;
                m_occupied[p.cellX][p.cellY - 1] = false;
            } else if (p.cellX > 0 && !m_occupied[p.cellX - 1][p.cellY + 1]) { // if cell below left empty
                p.cellX--;
                p.cellY++;
                m_occupied[p.cellX + 1][p.cellY - 1] = false;
            } else if (p.cellX < m_gridWidth - 1 && !m_occupied[p.cellX + 1][p.cellY + 1]) { // if cell below right empty
                p.cellX++;
                p.cellY++;
                m_occupied[p.cellX - 1][p.cellY - 1] = false;
            } else {
                if (p.type == ParticleType::SAND) {
                    p.processed = true;
                } else if (p.type == ParticleType::WATER) {
                    if (p.cellX > 0 && !m_occupied[p.cellX - 1][p.cellY]) { // if cell left empty
                        p.cellX--;
                        m_occupied[p.cellX + 1][p.cellY] = false;
                    } else if (p.cellX < m_gridWidth - 1 && !m_occupied[p.cellX + 1][p.cellY]) { // if cell right empty
                        p.cellX++;
                        m_occupied[p.cellX - 1][p.cellY] = false;
                    } else {
                        p.processed = true;
                    }
                }
            }
            m_occupied[p.cellX][p.cellY] = true;
        }
    }
}

void ParticleManager::draw()
{
    for (auto& p : m_particles) {
        DrawRectangle(p.cellX * config::cellSize, p.cellY * config::cellSize, config::cellSize, config::cellSize, p.color);
    }
}
