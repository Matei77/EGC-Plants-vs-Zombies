#include "utils.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "constants.h"
#include "components/simple_scene.h"

using namespace std;
using namespace PvZ;
int PvZ::logicToGridIndexX(float logicX) {
    return (logicX - SQUARE_SIDE / 2 - PADDING * 2 - END_ZONE_WIDTH) / (PADDING + SQUARE_SIDE);
}
int PvZ::logicToGridIndexY(float logicY) {
    return (logicY - PADDING - SQUARE_SIDE / 2) / (PADDING + SQUARE_SIDE); 
}
