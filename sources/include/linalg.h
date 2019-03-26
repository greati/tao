#ifndef __LINALG__
#define __LINALG__

#include "linalg/Col.h"
#include "linalg/Row.h"

/**
 * tao mathematical library
 * */
namespace tao {
/**
 * A column vector of doubles.
 * */
using Vec = Col<double>;

/**
 * A column vector of doubles.
 * */
using CVec = Col<double>;

/**
 * A column vector of floats.
 * */
using VecF = Col<float>;

/**
 * A column vector of floats.
 * */
using CVecF = Col<float>;

/**
 * A column vector of ints.
 * */
using VecI = Col<int>;

/**
 * A column vector of ints.
 * */
using CVecI = Col<int>;

/**
 * A row vector of doubles.
 * */
using RVec = Row<double>;

/**
 * A row vector of floats.
 * */
using RVecF = Row<float>;

/**
 * A row vector of ints.
 * */
using RVecI = Row<int>;
}
#endif
