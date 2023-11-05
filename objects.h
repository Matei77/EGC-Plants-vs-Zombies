#pragma once

#include "core/gpu/mesh.h"

namespace PvZ {
    namespace objects {
        Mesh *CreateRectangle(const std::string &name,
                              const float width,
                              const float height,
                              const glm::vec3 color,
                              const bool fill);

        Mesh *CreateDefender(const std::string &name,
                             const float width,
                             const float height,
                             const glm::vec3 color);

        Mesh *CreateEnemy(const std::string &name,
                          const float outer_radius,
                          const float inner_radius,
                          const glm::vec3 outer_color,
                          const glm::vec3 inner_color);

        Mesh *CreateStar(const std::string &name,
                         const float outer_radius,
                         const glm::vec3 color);
    }
}
