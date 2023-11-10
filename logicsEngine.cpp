#include "logicsEngine.h"

#include <ctime>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace PvZ;

void LogicsEngine::SpawnEnemy(const Position position, Type type) {
    const auto enemy = Enemy(position, type);
    enemies.push_back(enemy);
}

void LogicsEngine::Update(const float deltaTime) {
    for (std::vector<float>::size_type i = 0; i != spawnTimers.size(); i++) {
        if (spawnTimers[i] <= 0) {
            switch(i) {
            case 0: SpawnEnemy({SPAWN_X, FIRST_LINE}, static_cast<Type>(rand() % 4)); break;
            case 1: SpawnEnemy({SPAWN_X, SECOND_LINE}, static_cast<Type>(rand() % 4)); break;
            case 2: SpawnEnemy({SPAWN_X, THIRD_LINE}, static_cast<Type>(rand() % 4)); break;
            default: ;
            }
            spawnTimers[i] = rand() % 10 + 3;
        } else {
            spawnTimers[i] -= 1 * deltaTime;
        }
    }
    
    for (auto &enemy : enemies) {
        Position position = enemy.GetPosition();
    
        if (position.x < END_ZONE_LIMIT) {
            if (enemy.GetScale() > 0) {
                enemy.SetScale(enemy.GetScale() - SCALE_CHANGE_VAL * deltaTime);
            }
        } else {
            position.x -= ENEMY_MOVE_VAL * deltaTime;
            enemy.SetPosition(position);
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy enemy) { return enemy.GetScale() <= 0; }),
                  enemies.end());
    
}

void LogicsEngine::InitLogicsEngine() {
    // set seed
    srand(time(NULL));

    // set the enemy spawn timer on each lane
    spawnTimers.push_back(rand() % 5 + 1);
    spawnTimers.push_back(rand() % 5 + 1);
    spawnTimers.push_back(rand() % 5 + 1);

    // init grid positions
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            grid[i][j].position.x = PADDING * 2 + END_ZONE_WIDTH + (PADDING + SQUARE_SIDE) * i + SQUARE_SIDE / 2;
            grid[i][j].position.y = PADDING + (PADDING + SQUARE_SIDE) * j + SQUARE_SIDE / 2;
        }
}
