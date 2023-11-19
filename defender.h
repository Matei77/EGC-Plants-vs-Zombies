#pragma once
#include <vector>

#include "constants.h"
#include "projectile.h"
#include "utils.h"

namespace PvZ {
    class Defender {
    private:
        Position position;
        Type color;
        float scale;
        std::string meshType;
        bool alive;
        std::vector<Projectile> projectiles;
        float fireTimer;

    public:
        Defender(const Position &position, Type color) : position(position), color(color),
                                                         scale(DEFAULT_DEFENDER_SCALE), alive(true),
                                                         fireTimer(0) {
            switch (color) {
            case orangeType: meshType = ORANGE_DEFENDER_MESH;
                break;
            case blueType: meshType = BLUE_DEFENDER_MESH;
                break;
            case yellowType: meshType = YELLOW_DEFENDER_MESH;
                break;
            case purpleType: meshType = PURPLE_DEFENDER_MESH;
                break;
            case noType: meshType = GUI_SQUARE_MESH;
                break;
            }
        }

        void SpawnProjectile();
        
        Position GetPosition() const { return position; }
        void SetPosition(const Position &position) { this->position = position; }
        float GetScale() const { return scale; }
        void SetScale(const float scale) { this->scale = scale; }
        bool IsAlive() const { return alive; }
        void SetAlive(const bool alive) { this->alive = alive; }
        std::string GetMeshType() const { return meshType; }
        Type GetColor() const { return color; }
        float GetFireTimer() const { return fireTimer; }
        void SetFireTimer(const float fireTimer) { this->fireTimer = fireTimer; }
        std::vector<Projectile> & GetProjectiles() { return projectiles; }
    };
}
