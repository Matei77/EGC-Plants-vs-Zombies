#pragma once
#include "constants.h"
#include "utils.h"

namespace PvZ {
    class Defender {
    private:
        Position position;
        float scale;
        std::string meshType;
        bool alive;

    public:
        Defender(const Position &position, Type color) : position(position) {
            scale = DEFAULT_DEFENDER_SCALE;
            alive = true;
            switch (color) {
            case orangeType: meshType = ORANGE_DEFENDER_MESH;
                break;
            case blueType: meshType = BLUE_DEFENDER_MESH;
                break;
            case yellowType: meshType = YELLOW_DEFENDER_MESH;
                break;
            case purpleType: meshType = PURPLE_DEFENDER_MESH;
                break;
            default: ;
            }
        }

        Position GetPosition() const { return position; }
        void SetPosition(const Position &position) { this->position = position; }
        float GetScale() const { return scale; }
        void SetScale(const float scale) { this->scale = scale; }
        bool IsAlive() const { return alive; }
        void SetAlive(const bool alive) { this->alive = alive; }
        std::string GetMeshType() const { return meshType; }
    };
}
