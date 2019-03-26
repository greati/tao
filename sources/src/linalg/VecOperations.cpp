#include "linalg/VecOperations.h"

tao::Vec tao::cross(const Vec& v1, const Vec& v2) {
    if (v1.nrows() != 3 or v2.nrows() != 3)
        throw std::invalid_argument("cross product is defined only for 3d vectors");
    return tao::Vec{
        (v1(1) * v2(2) - v1(2) * v2(1)), 
        (-(v1(0) * v2(2) - v1(2) * v2(0))), 
        (v1(0) * v2(1) - v1(1) * v2(0))
    };
}
