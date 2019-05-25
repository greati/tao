#ifndef _FIXED_TAO_OPERATIONS_
#define _FIXED_TAO_OPERATIONS_

#include <cmath>
#include "tao/linalg/Mat.h"

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

template<typename T, int M, int N>
Mat<T, M, N> abs(const Mat<T, M, N>& m1) {
    Mat<T, M, N> res;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            res(i, j) = std::abs(m1(i,j));
        } 
    }
    return res;
}

template<typename T, int N>
T distance(const Mat<T, N, 1>& v1, const Mat<T, N, 1>& v2) {
    return norm(v1-v2);
}

template<typename T>
T lerp(float t, const Mat<T, 3, 1>& p0, const tao::Mat<T, 3, 1>& p1) {
    return (1 - t) * p0 + t * p1;
}

/*float lerp(float t, float v1, float v2) {
    return (1 - t) * v1+ t * v2;
}*/

};

#endif
