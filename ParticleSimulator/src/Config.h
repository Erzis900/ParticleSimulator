#pragma once
#include <string>

namespace config {
inline int screenWidth;
inline int screenHeight;
inline int maxFps;

inline int cellSize;

bool load(const std::string& configPath);
};
