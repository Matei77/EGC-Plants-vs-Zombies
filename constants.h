#pragma once
#include <string>
#include <glm/vec3.hpp>

namespace PvZ {
    constexpr float END_ZONE_HEIGHT = 5.0f;
    constexpr float END_ZONE_WIDTH = 0.5f;
    constexpr float SQUARE_SIDE = 1.5f;
    constexpr float PADDING = 0.25f;
    constexpr float DEFENDER_HEIGHT = 1.25f;
    constexpr float DEFENDER_WIDTH = 0.7f;
    constexpr float ENEMY_OUTER_RADIUS = 0.5f;
    constexpr float ENEMY_INNER_RADIUS = 0.35f;
    constexpr float STAR_RADIUS = 0.5f;

    constexpr float ENEMY_MOVE_VAL = 2.0f;
    constexpr float SCALE_CHANGE_VAL = 4.0f;
    
    const std::string DEFENDER_MESH = "defender";
    const std::string ENEMY_MESH = "enemy";
    const std::string SQUARE_MESH = "square";
    const std::string END_ZONE_MESH = "endZone";
    const std::string STAR_MESH = "star";
    
    const glm::vec3 RED = glm::vec3(1, 0, 0);
    const glm::vec3 GREEN = glm::vec3(0.3f, 1, 0.1f);
    const glm::vec3 BLUE = glm::vec3(0.1f, 0.3f, 1.0f);
    
    constexpr int GRID_SIDE = 3;
}
