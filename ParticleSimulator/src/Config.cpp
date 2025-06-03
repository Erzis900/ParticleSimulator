#include "Config.h"
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

bool config::load(const std::string& configPath)
{
    std::ifstream f(configPath);
    if (!f.is_open())
        return false;

    json data;

    try {
        data = json::parse(f);
    } catch (const json::parse_error& e) {
        return false;
    }

    screenWidth = data["screen_width"];
    screenHeight = data["screen_height"];
    maxFps = data["max_fps"];
    cellSize = data["cell_size"];
    deltaY = data["delta_y"];

    return true;
}
