#pragma once
#include <string>

#include "constants.h"
#include "utils.h"

namespace PvZ {
    class Enemy {
    private:
        Position position;
        float scale;
        int health;
        std::string meshType;

    public:
        Enemy(const Position &position, Type color) : position(position) {
            scale = DEFAULT_ENEMY_SCALE;
            health = DEFAULT_ENEMY_HEALTH;
            switch (color) {
            case orangeType: meshType = ORANGE_ENEMY_MESH;
                break;
            case blueType: meshType = BLUE_ENEMY_MESH;
                break;
            case yellowType: meshType = YELLOW_ENEMY_MESH;
                break;
            case purpleType: meshType = PURPLE_ENEMY_MESH;
                break;
            defalut: ;
            }
        }

        Position GetPosition() const { return position; }
        int GetHealth() const { return health; }
        std::string GetMeshType() const { return meshType; }
        float GetScale() const { return scale; }
        void SetPosition(const Position &position) { this->position = position; }
        void SetScale(const float scale) { this->scale = scale; }
        void SetHealth(const int health) { this->health = health; }
    };
}
