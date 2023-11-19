#pragma once
#include <string>
#include <glm/vec3.hpp>

namespace PvZ {
    // logic space
    constexpr float LOGIC_SPACE_X = 0;
    constexpr float LOGIC_SPACE_Y = 0;
    constexpr float LOGIC_SPACE_WIDTH = 16;
    constexpr float LOGIC_SPACE_HEIGHT = 9;

    // objects
    constexpr float END_ZONE_HEIGHT = 5.0f;
    constexpr float END_ZONE_WIDTH = 0.5f;
    constexpr float SQUARE_SIDE = 1.5f;
    constexpr float PADDING = 0.25f;
    constexpr float DEFENDER_HEIGHT = 1.25f;
    constexpr float DEFENDER_WIDTH = 0.7f;
    constexpr float ENEMY_OUTER_RADIUS = 0.5f;
    constexpr float ENEMY_INNER_RADIUS = 0.35f;
    constexpr float STAR_RADIUS = 0.5f;
    constexpr float END_ZONE_LIMIT = PADDING + END_ZONE_WIDTH;
    constexpr float LAWN_MOWER_HEIGHT = 0.5f;
    constexpr float LAWN_MOWER_WIDTH = 0.7f;

    // positions for lines and enemy spawn
    constexpr float FIRST_LINE = PADDING + SQUARE_SIDE / 2;
    constexpr float SECOND_LINE = PADDING * 2 + SQUARE_SIDE * 1.5f;
    constexpr float THIRD_LINE = PADDING * 3 + SQUARE_SIDE * 2.5f;
    constexpr float SPAWN_X = LOGIC_SPACE_WIDTH + 1;
    constexpr int GRID_SIDE = 3;
    constexpr float PROJECTILE_OFFSET = 0.25f;
    constexpr float PROJECTILE_X_LIMIT = 17.0f;
    constexpr float HIT_OFFSET = 0.25f;

    // defaults
    constexpr float PROJECTILE_MOVE_VAL = 5.0f;
    constexpr float LAWN_MOWER_MOVE_VAL = 10.0f;
    constexpr float ENEMY_MOVE_VAL = 1.25f;
    constexpr float SCALE_CHANGE_VAL = 4.0f;
    constexpr float DEFAULT_STAR_TIMER = 7;
    constexpr float DEFAULT_BLINK_TIMER = 0.2f;
    constexpr float DEFAULT_DEFENDER_SCALE = 1; 
    constexpr float DEFAULT_ENEMY_SCALE = 1; 
    constexpr int DEFAULT_ENEMY_HEALTH = 2;
    constexpr float DEFAULT_FIRE_TIMER = 2.0f;
    constexpr float PROJECTILE_ROTATION = -6.0f;

    // gui
    constexpr float GUI_Y = LOGIC_SPACE_HEIGHT - PADDING - SQUARE_SIDE / 2;
    constexpr float LIFE_SIDE = 1.0f;
    constexpr float GRAY_STAR_RADIUS = 0.25f;
    constexpr float CREDIT_STAR_START_X = PADDING * 5 + SQUARE_SIDE * 4;
    constexpr float CREDIT_STAR_START_Y = LOGIC_SPACE_HEIGHT - PADDING - GRAY_STAR_RADIUS;
    constexpr float PRICE_Y = LOGIC_SPACE_HEIGHT - PADDING - SQUARE_SIDE - GRAY_STAR_RADIUS;
    constexpr float DRAG_AND_DROP_SCALE = 0.75f;

    // color types for objects
    enum Type {
        orangeType,
        blueType,
        yellowType,
        purpleType,
        noType
    };

    // meshes
    const std::string ORANGE_DEFENDER_MESH = "orangeDefender";
    const std::string BLUE_DEFENDER_MESH = "blueDefender";
    const std::string YELLOW_DEFENDER_MESH = "yellowDefender";
    const std::string PURPLE_DEFENDER_MESH = "purpleDefender";

    const std::string LAWN_MOWER_MESH = "lawnMower";

    const std::string ORANGE_ENEMY_MESH = "orangeEnemy";
    const std::string BLUE_ENEMY_MESH = "blueEnemy";
    const std::string YELLOW_ENEMY_MESH = "yellowEnemy";
    const std::string PURPLE_ENEMY_MESH = "purpleEnemy";

    const std::string ORANGE_STAR_MESH = "orangeStar";
    const std::string BLUE_STAR_MESH = "blueStar";
    const std::string YELLOW_STAR_MESH = "yellowStar";
    const std::string PURPLE_STAR_MESH = "purpleStar";

    const std::string PINK_STAR_MESH = "pinkStar";
    const std::string GRAY_STAR_MESH = "grayStar";

    const std::string SQUARE_MESH = "square";
    const std::string END_ZONE_MESH = "endZone";

    const std::string GUI_SQUARE_MESH = "guiSquare";
    const std::string GUI_LIVES_MESH = "livesMesh";

    // colors
    constexpr glm::vec3 BACKGROUND = glm::vec3(0.1f, 0.1f, 0.1f);
    constexpr glm::vec3 RED = glm::vec3(1, 0, 0);
    constexpr glm::vec3 GREEN = glm::vec3(0.3f, 1, 0.1f);
    constexpr glm::vec3 PINK = glm::vec3(0.92f, 0.2f, 0.58f);
    constexpr glm::vec3 BLACK = glm::vec3(0, 0, 0);
    constexpr glm::vec3 DARK_GRAY = glm::vec3(0.28f, 0.28f, 0.28f);
    constexpr glm::vec3 GRAY = glm::vec3(0.5f, 0.5f, 0.5f);
    constexpr glm::vec3 ORANGE = glm::vec3(0.98f, 0.53f, 0.01f);
    constexpr glm::vec3 LIGHT_ORANGE = glm::vec3(1.0f, 0.65f, 0.26f);
    constexpr glm::vec3 BLUE = glm::vec3(0.1f, 0.3f, 1.0f);
    constexpr glm::vec3 LIGHT_BLUE = glm::vec3(0.1f, 0.6f, 1.0f);
    constexpr glm::vec3 YELLOW = glm::vec3(0.99f, 0.96f, 0.1f);
    constexpr glm::vec3 LIGHT_YELLOW = glm::vec3(0.89f, 0.81f, 0.35f);
    constexpr glm::vec3 PURPLE = glm::vec3(0.69f, 0.03f, 0.98f);
    constexpr glm::vec3 LIGHT_PURPLE = glm::vec3(0.8f, 0.35f, 1);
    constexpr glm::vec3 CYAN = glm::vec3(0.19f, 0.94f, 0.72f);
    
}
