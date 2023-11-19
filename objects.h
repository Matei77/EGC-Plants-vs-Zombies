#pragma once

#include "core/gpu/mesh.h"

namespace PvZ {
    namespace objects {
        Mesh *CreateRectangle(const std::string &name,
                              float width,
                              float height,
                              glm::vec3 color,
                              bool fill);

        Mesh *CreateDefender(const std::string &name,
                             float width,
                             float height,
                             glm::vec3 color);

        Mesh *CreateEnemy(const std::string &name,
                          float outer_radius,
                          float inner_radius,
                          glm::vec3 outer_color,
                          glm::vec3 inner_color);

        Mesh *CreateStar(const std::string &name,
                         float outer_radius,
                         glm::vec3 color);

        Mesh *CreateHearth(const std::string &name,
                            float width,
                            float height,
                            glm::vec3 color);
    }
}
