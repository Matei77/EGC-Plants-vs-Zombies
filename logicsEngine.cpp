#include "logicsEngine.h"

using namespace PvZ;

void LogicsEngine::InitGrid() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
                grid[i][j].position.x = PADDING * 2 + END_ZONE_WIDTH + (PADDING + SQUARE_SIDE) * i + SQUARE_SIDE / 2;
                grid[i][j].position.y = PADDING + (PADDING + SQUARE_SIDE) * j + SQUARE_SIDE / 2;
        }
}
