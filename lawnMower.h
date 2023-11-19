#pragma once
#include <string>

#include "constants.h"
#include "utils.h"

namespace PvZ {
    class LawnMower {
    private:
        Position position;
        bool activated;
        bool reachedEnd;

    public:
        LawnMower(const Position &position) : position(position), activated(false), reachedEnd(false) {}

        Position GetPosition() const { return position; }
        void SetPosition(const Position &position) { this->position = position; }
        bool ReachedEnd() const { return reachedEnd; }
        void SetReachedEnd(const bool reachedEnd) { this->reachedEnd = reachedEnd; }
        bool IsActivated() const { return activated; }
        void SetActivated(const bool activated) { this->activated = activated; }
    };
}
