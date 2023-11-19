#pragma once

#include <unordered_map>
#include <vector>

#include "constants.h"
#include "creditStar.h"
#include "defender.h"
#include "enemy.h"
#include "lawnMower.h"
#include "utils.h"

namespace PvZ {
    class LogicsEngine {
    private:
        struct GridSquare {
            bool occupied = false;
            Position position;
        };
        
        GridSquare grid[GRID_SIDE][GRID_SIDE];
        std::vector<Enemy> enemies;
        std::vector<Defender> defenders;
        std::vector<float> enemySpawnTimers;
        std::vector<CreditStar> creditStars;
        float creditStarSpawnTimer;
        int playerCredit;
        int playerLives;
        
        Type selectedDefender;
        std::unordered_map<Type, int> prices;
        Position dragDefenderPos;

        std::vector<LawnMower> lawnMowers;

    public:
        LogicsEngine();
        
        void SpawnEnemy(Position position, Type type);
        void SpawnDefender(Position position, Type type);
        void SpawnCreditStar(Position position);
        void Update(float deltaTime);
        
        std::vector<Enemy> GetEnemies() const { return enemies; }
        std::vector<Defender> & GetDefenders() { return defenders; }
        std::vector<CreditStar> & GetCreditStars() { return creditStars; }
        int GetPlayerCredit() const { return playerCredit; }
        void SetPlayerCredit(const int playerCredit) { this->playerCredit = playerCredit; }
        int  GetPlayerLives() const { return playerLives; }
        void SetPlayerLives(const int playerLives) { this->playerLives = playerLives; }
        Type GetSelectedDefender() const { return selectedDefender; }
        void SetSelectedDefender(const Type selectedDefender) { this->selectedDefender = selectedDefender; }
        std::unordered_map<Type, int> GetPrices() const { return prices; }
        Position GetDragDefenderPos() const { return dragDefenderPos; }
        void SetDragDefenderPos(const Position &dragDefenderPos) { this->dragDefenderPos = dragDefenderPos; }
        std::vector<LawnMower> GetLawnMowers() const { return lawnMowers; }
        void SetLawnMowers(const std::vector<LawnMower> &lawnMowers) { this->lawnMowers = lawnMowers; }

        // safely get grid square
        GridSquare & GetGridSquare(const int i, const int j) {
            if (i < GRID_SIDE && i >= 0 && j < GRID_SIDE && j >= 0)
                return grid[i][j];
            return grid[0][0];
        }
    };
}
