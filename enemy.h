#pragma once
#include <string>

#include "constants.h"
#include "utils.h"

namespace PvZ {
    class Enemy {
    private:
        Position position;
        Type color;
        float scale;
        int health;
        std::string meshType;
        bool reachedEnd;

    public:
        Enemy(const Position &position, Type color) : position(position), color(color), scale(DEFAULT_ENEMY_SCALE),
                                                      health(DEFAULT_ENEMY_HEALTH), reachedEnd(false) {
            switch (color) {
            case orangeType: meshType = ORANGE_ENEMY_MESH;
                break;
            case blueType: meshType = BLUE_ENEMY_MESH;
                break;
            case yellowType: meshType = YELLOW_ENEMY_MESH;
                break;
            case purpleType: meshType = PURPLE_ENEMY_MESH;
                break;
            case noType: meshType = GUI_SQUARE_MESH;
                break;
            }
        }

        Position GetPosition() const { return position; }
        int GetHealth() const { return health; }
        std::string GetMeshType() const { return meshType; }
        float GetScale() const { return scale; }
        void SetPosition(const Position &position) { this->position = position; }
        void SetScale(const float scale) { this->scale = scale; }
        void SetHealth(const int health) { this->health = health; }
        bool ReachedEnd() const { return reachedEnd; }
        void SetReachedEnd(const bool reachedEnd) { this->reachedEnd = reachedEnd; }
        Type GetColor() const { return color; }
        
    };
}
