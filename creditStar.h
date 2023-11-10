#pragma once
#include "constants.h"
#include "utils.h"

namespace PvZ {
    class CreditStar {
    private:
        Position position;
        float timer;
        float blink_timer;
        bool visible;

    public:
        CreditStar(Position position) : position(position) {
            timer = DEFAULT_STAR_TIMER;
            blink_timer = DEFAULT_BLINK_TIMER;
            visible = true;
        }

        float GetTimer() const { return timer; }
        void SetTimer(const float timer) { this->timer = timer; }
        bool IsVisible() const { return visible; }
        void SetVisible(const bool visible) { this->visible = visible; }
        Position GetPosition() const { return position; }
        float GetBlinkTimer() const { return blink_timer; }
        void SetBlinkTimer(const float blinkTimer) { blink_timer = blinkTimer; }
    };

}


