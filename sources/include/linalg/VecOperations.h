#ifndef __VECOPERATIONS__
#define __VECOPERATIONS__

#include "linalg.h"

namespace tao {

/**
 * Computes the cross product between 
 * two 3D vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the cross product
 * */
Vec cross(const Vec& v1, const Vec& v2);

};

#endif
