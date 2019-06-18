#include <cmath>
#include "tao/geometry/geometry.h"

float tao::geometry::radians(float degrees) {
    return M_PI * degrees / 180.0;
}
