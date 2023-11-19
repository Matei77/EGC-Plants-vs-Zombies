#include "logicsEngine.h"

#include <ctime>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <glm/geometric.hpp>

using namespace PvZ;

void LogicsEngine::SpawnEnemy(const Position position, Type type) {
    const auto enemy = Enemy(position, type);
    enemies.push_back(enemy);
}

void LogicsEngine::SpawnDefender(const Position position, Type type) {
    const auto defender = Defender(position, type);
    defenders.push_back(defender);
}

void LogicsEngine::SpawnCreditStar(const Position position) {
    const auto star = CreditStar(position);
    creditStars.push_back(star);
}

void LogicsEngine::Update(const float deltaTime) {
    if (!playerLives) {
        enemies.clear();
        defenders.clear();
        creditStars.clear();
        playerCredit = 0;
        return;
    }

    // spawn enemies randomly
    for (std::vector<float>::size_type i = 0; i != enemySpawnTimers.size(); i++) {
        if (enemySpawnTimers[i] <= 0) {
            switch (i) {
            case 0: SpawnEnemy({SPAWN_X, FIRST_LINE}, static_cast<Type>(rand() % 4));
                break;
            case 1: SpawnEnemy({SPAWN_X, SECOND_LINE}, static_cast<Type>(rand() % 4));
                break;
            case 2: SpawnEnemy({SPAWN_X, THIRD_LINE}, static_cast<Type>(rand() % 4));
                break;
            default: ;
            }
            enemySpawnTimers[i] = (rand() % 100) / 10.0f + 7;
        }
        else {
            enemySpawnTimers[i] -= 1 * deltaTime;
        }
    }

    // spawn stars randomly
    if (creditStarSpawnTimer <= 0) {
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        SpawnCreditStar({static_cast<float>(rand() % 10 + 6.5), static_cast<float>(rand() % 6 + 1)});
        creditStarSpawnTimer = rand() % 7 + 3;
    }
    else {
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
        }
        else if (enemy.GetScale() > 0 && enemy.GetHealth() <= 0) {
            enemy.SetScale(enemy.GetScale() - SCALE_CHANGE_VAL * deltaTime);
        }
        else {
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
            }
            else if (star.IsVisible() == false && star.GetBlinkTimer() <= 0) {
                star.SetVisible(true);
                star.SetBlinkTimer(DEFAULT_BLINK_TIMER);
            }
        }
    }

    // spawn projectiles
    for (auto &defender : defenders) {
        for (auto enemy : enemies) {
            if (defender.GetPosition().y == enemy.GetPosition().y && defender.GetColor() == enemy.GetColor() &&
                defender.GetPosition().x < enemy.GetPosition().x) {
                if (defender.GetFireTimer() <= 0) {
                    defender.SpawnProjectile();
                    defender.SetFireTimer(DEFAULT_FIRE_TIMER);
                }
                else {
                    defender.SetFireTimer(defender.GetFireTimer() - 1 * deltaTime);
                }
            }
        }
    }

    // move projectile
    for (auto &defender : defenders)
        for (auto &projectile : defender.GetProjectiles()) {
            Position position = projectile.GetPosition();

            if (position.x >= PROJECTILE_X_LIMIT) {
                projectile.SetHit(true);
            }
            else {
                position.x += PROJECTILE_MOVE_VAL * deltaTime;
                projectile.SetPosition(position);
                projectile.SetRotation(projectile.GetRotation() + PROJECTILE_ROTATION * deltaTime);

                // check for enemy hit
                for (auto &enemy : enemies) {
                    if (enemy.GetColor() == projectile.GetColor() &&
                        projectile.IsHit() == false &&
                        glm::distance(glm::vec3(enemy.GetPosition().x, enemy.GetPosition().y, 0),
                                      glm::vec3(projectile.GetPosition().x, projectile.GetPosition().y, 0)) <
                        ENEMY_OUTER_RADIUS + STAR_RADIUS - HIT_OFFSET) {
                        enemy.SetHealth(enemy.GetHealth() - 1);
                        projectile.SetHit(true);
                    }
                }
            }
        }

    // defender scale down animation
    for (auto &defender : defenders) {
        if (defender.IsAlive() == false && defender.GetScale() > 0) {
            defender.SetScale(defender.GetScale() - SCALE_CHANGE_VAL * deltaTime);
        }

        // check defender-enemy collision
        for (auto &enemy : enemies) {
            if (enemy.GetPosition().y == defender.GetPosition().y &&
                abs(enemy.GetPosition().x - defender.GetPosition().x) < ENEMY_OUTER_RADIUS + DEFENDER_WIDTH -
                HIT_OFFSET && defender.IsAlive() == true) {
                grid[logicToGridIndexX(defender.GetPosition().x)][logicToGridIndexY(defender.GetPosition().y)].occupied
                        = false;
                defender.SetAlive(false);
            }
        }
    }

    // delete dead enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](Enemy enemy) { return enemy.GetScale() <= 0; }),
                  enemies.end());

    // delete dead defenders
    defenders.erase(std::remove_if(defenders.begin(), defenders.end(),
                                   [](Defender defender) { return defender.GetScale() <= 0; }),
                    defenders.end());

    // delete expired stars
    creditStars.erase(std::remove_if(creditStars.begin(), creditStars.end(),
                                     [](CreditStar star) { return star.GetTimer() <= 0; }),
                      creditStars.end());

    // delete projectiles
    for (auto &defender : defenders) {
        defender.GetProjectiles().erase(std::remove_if(defender.GetProjectiles().begin(),
                                                       defender.GetProjectiles().end(),
                                                       [](Projectile projectile) {
                                                           return projectile.IsHit() == true;
                                                       }),
                                        defender.GetProjectiles().end());
    }
}

LogicsEngine::LogicsEngine() {
    // set seed
    srand(time(NULL));

    // set initial player credit and lives
    playerCredit = 0;
    playerLives = 3;
    selectedDefender = noType;

    // set prices
    prices.insert({orangeType, 1});
    prices.insert({blueType, 2});
    prices.insert({yellowType, 2});
    prices.insert({purpleType, 3});

    // set the enemy spawn timer on each lane
    enemySpawnTimers.push_back(rand() % 100 / 10.0f + 5);
    enemySpawnTimers.push_back(rand() % 100 / 10.0f + 5);
    enemySpawnTimers.push_back(rand() % 100 / 10.0f + 5);
    creditStarSpawnTimer = rand() % 2 + 1;

    // init grid positions
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            grid[i][j].position.x = PADDING * 2 + END_ZONE_WIDTH + (PADDING + SQUARE_SIDE) * i + SQUARE_SIDE / 2;
            grid[i][j].position.y = PADDING + (PADDING + SQUARE_SIDE) * j + SQUARE_SIDE / 2;
            grid[i][j].occupied = false;
        }
}
