#pragma once
#include <glm/fwd.hpp>

namespace PvZ {
    namespace animations {
        glm::mat3 MoveEnemy(float xTranslate, float yTranslate);

        glm::mat3 MoveProjectile(float xTranslate, float yTranslate, float rotation);

        glm::mat3 DestroyObject(float scale);
        
    }
}