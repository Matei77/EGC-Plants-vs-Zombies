#pragma once
#include <string>

#include "utils.h"

namespace PvZ {
    class Enemy {
    private:
        Position position;
        float scale;
        int health;
        std::string meshType;

    public:
        Enemy(const Position& position, const float scale, const int health, const std::string& meshType)
            : position(position),
              scale(scale),
              health(health),
              meshType(meshType) {}

        Position GetPosition() const { return position; }
        int GetHealth() const { return health; }
        std::string GetMeshType() const { return meshType; }
        float GetScale() const { return scale; }
        void SetPosition(const Position &position) { this->position = position; }
        void SetScale(const float scale) { this->scale = scale; }
        void SetHealth(const int health) { this->health = health; }
    };
    
}

