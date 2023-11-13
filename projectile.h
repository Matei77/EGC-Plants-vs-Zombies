#pragma once
#include "constants.h"
#include "utils.h"

namespace PvZ {
    class Projectile {
    private:
        Position position;
        Type color;
        std::string meshType;
        bool hit;
        float rotation;

    public:
        Projectile(Position position, Type color) : position(position), color(color), hit(false), rotation(0) {
            switch (color) {
            case orangeType: meshType = ORANGE_STAR_MESH;
                break;
            case blueType: meshType = BLUE_STAR_MESH;
                break;
            case yellowType: meshType = YELLOW_STAR_MESH;
                break;
            case purpleType: meshType = PURPLE_STAR_MESH;
                break;
            default: ;
            }
        }

        Position GetPosition() const { return position; }
        void SetPosition(const Position &position) { this->position = position; }
        Type GetColor() const { return color; }
        void SetColor(const Type color) { this->color = color; }
        std::string GetMeshType() const { return meshType; }
        bool IsHit() const { return hit; }
        void SetHit(const bool hit) { this->hit = hit; }
        float GetRotation() const { return rotation; }
        void SetRotation(const float rotation) { this->rotation = rotation; }
    };
}

