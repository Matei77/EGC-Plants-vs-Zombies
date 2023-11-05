#pragma once
#include <glm/vec3.hpp>

namespace PvZ {
    struct LogicSpace
    {
        LogicSpace() : x(0), y(0), width(1), height(1) {}
        LogicSpace(const float x, const float y, const float width, const float height)
            : x(x), y(y), width(width), height(height) {}
        float x;
        float y;
        float width;
        float height;
    };

    struct ViewportSpace
    {
        ViewportSpace() : x(0), y(0), width(1), height(1) {}
        ViewportSpace(const int x, const int y, const int width, const int height)
            : x(x), y(y), width(width), height(height) {}
        int x;
        int y;
        int width;
        int height;
    };

    struct Position {
        Position() : x(0), y(0) {}
        Position(const float x, const float y) : x(x), y(y) {}
        float x, y;
    };
}
