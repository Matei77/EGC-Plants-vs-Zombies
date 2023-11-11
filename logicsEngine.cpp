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

void LogicsEngine::SpawnCreditStar(const Position position) {
    const auto star = CreditStar(position);
    creditStars.push_back(star);
}

void LogicsEngine::Update(const float deltaTime) {
    if (!playerLives) {
        return;
    }
    // spawn enemies randomly
    for (std::vector<float>::size_type i = 0; i != enemySpawnTimers.size(); i++) {
        if (enemySpawnTimers[i] <= 0) {
            switch(i) {
            case 0: SpawnEnemy({SPAWN_X, FIRST_LINE}, static_cast<Type>(rand() % 4)); break;
            case 1: SpawnEnemy({SPAWN_X, SECOND_LINE}, static_cast<Type>(rand() % 4)); break;
            case 2: SpawnEnemy({SPAWN_X, THIRD_LINE}, static_cast<Type>(rand() % 4)); break;
            default: ;
            }
            enemySpawnTimers[i] = (rand() % 100) / 10.0f + 3;
        } else {
            enemySpawnTimers[i] -= 1 * deltaTime;
        }
    }

    if (creditStarSpawnTimer <= 0) {
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        creditStarSpawnTimer = rand() % 7 + 3;
    } else {
        creditStarSpawnTimer -= 1 * deltaTime;
    }

    // update enemy position and scale if necessary
    for (auto &enemy : enemies) {
        Position position = enemy.GetPosition();
    
        if (position.x < END_ZONE_LIMIT) {
            if (enemy.GetScale() > 0) {
                enemy.SetScale(enemy.GetScale() - SCALE_CHANGE_VAL * deltaTime);
            }
            if (!enemy.ReachedEnd()) {
                enemy.SetReachedEnd(true);
                playerLives--;
            }
        } else {
            position.x -= ENEMY_MOVE_VAL * deltaTime;
            enemy.SetPosition(position);
        }
    }

    // update creditStar timer
    for (auto &star : creditStars) {
        star.SetTimer(star.GetTimer() - 1 * deltaTime);
        if (star.GetTimer() <= 2) {
            star.SetBlinkTimer(star.GetBlinkTimer() - 1 * deltaTime);
            if (star.IsVisible() == true && star.GetBlinkTimer() <= 0) {
                star.SetVisible(false);
                star.SetBlinkTimer(DEFAULT_BLINK_TIMER);
            } else if (star.IsVisible() == false && star.GetBlinkTimer() <= 0) {
                star.SetVisible(true);
                star.SetBlinkTimer(DEFAULT_BLINK_TIMER);
            }
        }
    }

    // delete dead enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy enemy) { return enemy.GetScale() <= 0; }),
                  enemies.end());

    // delete expired stars
    creditStars.erase(std::remove_if(creditStars.begin(), creditStars.end(), [](CreditStar star) {return star.GetTimer() <= 0; }),
                      creditStars.end());
    
}

void LogicsEngine::InitLogicsEngine() {
    // set seed
    srand(time(NULL));

    // set initial player credit
    playerCredit = 0;
    playerLives = 3;

    // set the enemy spawn timer on each lane
    enemySpawnTimers.push_back(rand() % 50 / 10.0f + 1);
    enemySpawnTimers.push_back(rand() % 50 / 10.0f + 1);
    enemySpawnTimers.push_back(rand() % 50 / 10.0f + 1);
    creditStarSpawnTimer = rand() % 2 + 1;

    // init grid positions
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            grid[i][j].position.x = PADDING * 2 + END_ZONE_WIDTH + (PADDING + SQUARE_SIDE) * i + SQUARE_SIDE / 2;
            grid[i][j].position.y = PADDING + (PADDING + SQUARE_SIDE) * j + SQUARE_SIDE / 2;
        }
}
