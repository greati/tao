#ifndef _CORE_
#define _CORE_

#include "linalg/Mat.h"

/**
 * tao mathematical library
 * */
namespace tao {

/**
 * A 3-dimensional column matrix of floats.
 * */
using Vec3f = Mat<float, 3, 1>;

/**
 * A 3-dimensional column matrix of doubles.
 * */
using Vec3d = Mat<double, 3, 1>;

/**
 * A 3-dimensional column matrix of doubles.
 * */
using Vec2d = Mat<double, 2, 1>;

/**
 * A 3-dimensional column matrix of doubles.
 * */
using Vec2f = Mat<double, 2, 1>;

}
#endif
