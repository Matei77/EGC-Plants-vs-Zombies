#include "animations.h"

#include "glm/glm.hpp"
#include "lab_m1/lab3/transform2D.h"

using namespace PvZ;

glm::mat3 animations::MoveEnemy(const float xTranslate, const float yTranslate) {
    auto animationMatrix = glm::mat3(1);
    animationMatrix *= transform2D::Translate(xTranslate, yTranslate);

    return animationMatrix;
}

glm::mat3 animations::MoveProjectile(const float xTranslate, const float yTranslate, const float rotation) {
    auto animationMatrix = glm::mat3(1);
    animationMatrix *= transform2D::Translate(xTranslate, yTranslate);
    animationMatrix *= transform2D::Rotate(rotation);

    return animationMatrix;
}

glm::mat3 animations::DestroyObject(const float scale) {
    auto animationMatrix = glm::mat3(1);
    animationMatrix *= transform2D::Scale(scale, scale);

    return animationMatrix;
}
