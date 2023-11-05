#include "logicsEngine.h"
#include <vector>

using namespace PvZ;

void LogicsEngine::SpawnEnemy(const Position position, const float scale, const int health, std::string meshType) {
    const auto enemy = Enemy(position, scale, health, meshType);
    enemies.push_back(enemy);
}

void LogicsEngine::Update(const float deltaTime) {
    for (auto &enemy : enemies) {
        Position position = enemy.GetPosition();
        position.x -= ENEMY_MOVE_VAL * deltaTime;
        enemy.SetPosition(position);
    
        if (position.x < endZoneLimit) {
            if (enemy.GetScale() > 0) {
                enemy.SetScale(enemy.GetScale() - SCALE_CHANGE_VAL * deltaTime);
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy enemy) { return enemy.GetScale() <= 0; }),
                  enemies.end());

    
}

void LogicsEngine::InitGrid() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            grid[i][j].position.x = PADDING * 2 + END_ZONE_WIDTH + (PADDING + SQUARE_SIDE) * i + SQUARE_SIDE / 2;
            grid[i][j].position.y = PADDING + (PADDING + SQUARE_SIDE) * j + SQUARE_SIDE / 2;
        }
}
