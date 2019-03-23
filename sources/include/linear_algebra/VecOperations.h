#ifndef __VECOPERATIONS__
#define __VECOPERATIONS__

#include "linalg.h"

namespace tao {

/**
 * Computes the dot product between 
 * two vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the dot product
 * */
double dot(const vec& v1, const vec& v2);

/**
 * Computes the dot product between 
 * two float vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the dot product
 * */
float dot(const vec_f& v1, const vec_f& v2);

};

#endif
