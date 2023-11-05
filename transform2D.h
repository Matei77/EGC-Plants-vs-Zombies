#pragma once

#include "utils.h"

namespace PvZ {
    namespace transform2D {
        // Translate matrix
        inline glm::mat3 Translate(const float translateX, const float translateY) {
            // TODO(student): Implement the translation matrix
            return glm::transpose(
                glm::mat3(1, 0, translateX,
                          0, 1, translateY,
                          0, 0, 1)
            );
        }

        // Scale matrix
        inline glm::mat3 Scale(const float scaleX, const float scaleY) {
            // TODO(student): Implement the scaling matrix
            return glm::mat3(scaleX, 0, 0,
                             0, scaleY, 0,
                             0, 0, 1);
        }

        // Rotate matrix
        inline glm::mat3 Rotate(const float radians) {
            // TODO(student): Implement the rotation matrix
            return glm::transpose(
                glm::mat3(cos(radians), -sin(radians), 0,
                          sin(radians), cos(radians), 0,
                          0, 0, 1)
            );
        }

        // Uniform 2D visualization matrix (same scale factor on x and y axes)
        inline glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace) {
            float sx, sy, tx, ty, smin;
            sx = static_cast<float>(viewSpace.width) / logicSpace.width;
            sy = static_cast<float>(viewSpace.height) / logicSpace.height;
            if (sx < sy)
                smin = sx;
            else
                smin = sy;
            tx = static_cast<float>(viewSpace.x) - smin * logicSpace.x + (static_cast<float>(viewSpace.width) - smin *
                logicSpace.width) / 2;
            ty = static_cast<float>(viewSpace.y) - smin * logicSpace.y + (static_cast<float>(viewSpace.height) - smin *
                logicSpace.height) / 2;

            return glm::transpose(glm::mat3(
                smin, 0.0f, tx,
                0.0f, smin, ty,
                0.0f, 0.0f, 1.0f));
        }
    } // namespace transform2D
}
