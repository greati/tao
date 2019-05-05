#ifndef _CORE_
#define _CORE_

#include "linalg/Mat.h"
#include "linalg/Operations.h"

/**
 * tao mathematical library
 * */
namespace tao {

/**
 * A 2-dimensional vector.
 * */
template<typename T>
using Vec2 = Mat<T, 2, 1>;

/**
 * A 3-dimensional vector.
 * */
template<typename T>
using Vec3 = Mat<T, 3, 1>;

/**
 * A 3-dimensional column matrix of floats.
 * */
using Vec3f = Vec3<float>;

/**
 * A 3-dimensional column matrix of doubles.
 * */
using Vec3d = Vec3<double>;

/**
 * A 3-dimensional column matrix of doubles.
 * */
using Vec2d = Vec2<double>;

/**
 * A 3-dimensional column matrix of floats.
 * */
using Vec2f = Vec2<float>;


}
#endif
