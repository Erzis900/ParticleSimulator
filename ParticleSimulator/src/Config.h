#pragma once
#include <string>

namespace config {
inline int screenWidth;
inline int screenHeight;
inline int maxFps;

inline int cellSize;
inline float deltaY;

bool load(const std::string& configPath);
};
