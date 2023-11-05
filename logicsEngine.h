#pragma once

#include "constants.h"
#include "utils.h"

namespace PvZ {
    class LogicsEngine {
    private:
        const float endZoneLimit = PADDING + END_ZONE_WIDTH;
        
        struct GridSquare {
            bool occupied = false;
            Position position;
        };
        
    public:
        GridSquare grid[GRID_SIDE][GRID_SIDE];
        
        void InitGrid();
    };
}
