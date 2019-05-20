#ifndef __VECOPERATIONS__
#define __VECOPERATIONS__

#include "tao/core.h"
#include <cmath>

namespace tao {


/**
 * Computes the norm of a vector.
 *
 * @param v1 the first vector
 * @return the cross product
 * */
template<typename T, int N>
T norm(const Mat<T, N, 1>& v1) {
    return std::sqrt((v1.t() * v1)(0));
}

/**
 * Computes the unit version of a vector.
 *
 * @param v1 the first vector
 * @return the unit version of a vector.
 * */
template<typename T, int N>
Mat<T, N, 1> unitize(const Mat<T, N, 1>& v1) {
    return v1 / tao::norm(v1);
}

/**
 * Computes the dot product between vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the cross product
 * */
template<typename T, int N>
T dot(const Mat<T, N, 1>& v1, const Mat<T, N, 1>& v2) {
    T r { 0.0 };
    for (auto i {0}; i < N; ++i)
        r += v1(i) * v2(i);
    return r;
}

/**
 * Computes the cross product between 
 * two 3D vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the cross product
 * */
template<typename T>
Mat<T, 3, 1> cross(const Mat<T, 3, 1>& v1, const Mat<T, 3, 1>& v2) {
    return tao::Mat<T, 3, 1>{
        (v1(1) * v2(2) - v1(2) * v2(1)), 
        (-(v1(0) * v2(2) - v1(2) * v2(0))), 
        (v1(0) * v2(1) - v1(1) * v2(0))
    };
}

};

#endif
