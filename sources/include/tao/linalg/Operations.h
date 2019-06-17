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

template<typename T>
T det(const Mat<T, 4, 4>& mat) {
   T value;
   value =
   mat(0,3)*mat(1,2)*mat(2,1)*mat(3,0) - mat(0,2)*mat(1,3)*mat(2,1)*mat(3,0) - mat(0,3)*mat(1,1)*mat(2,2)*mat(3,0) + mat(0,1)*mat(1,3)*mat(2,2)*mat(3,0)+
   mat(0,2)*mat(1,1)*mat(2,3)*mat(3,0) - mat(0,1)*mat(1,2)*mat(2,3)*mat(3,0) - mat(0,3)*mat(1,2)*mat(2,0)*mat(3,1) + mat(0,2)*mat(1,3)*mat(2,0)*mat(3,1)+
   mat(0,3)*mat(1,0)*mat(2,2)*mat(3,1) - mat(0,0)*mat(1,3)*mat(2,2)*mat(3,1) - mat(0,2)*mat(1,0)*mat(2,3)*mat(3,1) + mat(0,0)*mat(1,2)*mat(2,3)*mat(3,1)+
   mat(0,3)*mat(1,1)*mat(2,0)*mat(3,2) - mat(0,1)*mat(1,3)*mat(2,0)*mat(3,2) - mat(0,3)*mat(1,0)*mat(2,1)*mat(3,2) + mat(0,0)*mat(1,3)*mat(2,1)*mat(3,2)+
   mat(0,1)*mat(1,0)*mat(2,3)*mat(3,2) - mat(0,0)*mat(1,1)*mat(2,3)*mat(3,2) - mat(0,2)*mat(1,1)*mat(2,0)*mat(3,3) + mat(0,1)*mat(1,2)*mat(2,0)*mat(3,3)+
   mat(0,2)*mat(1,0)*mat(2,1)*mat(3,3) - mat(0,0)*mat(1,2)*mat(2,1)*mat(3,3) - mat(0,1)*mat(1,0)*mat(2,2)*mat(3,3) + mat(0,0)*mat(1,1)*mat(2,2)*mat(3,3);
   return value;
}

template<typename T>
Mat<T, 4, 4> inverse(const Mat<T, 4, 4>& mat) {
   Mat<T, 4, 4> m;
   m(0,0) = mat(1,2)*mat(2,3)*mat(3,1) - mat(1,3)*mat(2,2)*mat(3,1) + mat(1,3)*mat(2,1)*mat(3,2) - mat(1,1)*mat(2,3)*mat(3,2) - mat(1,2)*mat(2,1)*mat(3,3) + mat(1,1)*mat(2,2)*mat(3,3);
   m(0,1) = mat(0,3)*mat(2,2)*mat(3,1) - mat(0,2)*mat(2,3)*mat(3,1) - mat(0,3)*mat(2,1)*mat(3,2) + mat(0,1)*mat(2,3)*mat(3,2) + mat(0,2)*mat(2,1)*mat(3,3) - mat(0,1)*mat(2,2)*mat(3,3);
   m(0,2) = mat(0,2)*mat(1,3)*mat(3,1) - mat(0,3)*mat(1,2)*mat(3,1) + mat(0,3)*mat(1,1)*mat(3,2) - mat(0,1)*mat(1,3)*mat(3,2) - mat(0,2)*mat(1,1)*mat(3,3) + mat(0,1)*mat(1,2)*mat(3,3);
   m(0,3) = mat(0,3)*mat(1,2)*mat(2,1) - mat(0,2)*mat(1,3)*mat(2,1) - mat(0,3)*mat(1,1)*mat(2,2) + mat(0,1)*mat(1,3)*mat(2,2) + mat(0,2)*mat(1,1)*mat(2,3) - mat(0,1)*mat(1,2)*mat(2,3);
   m(1,0) = mat(1,3)*mat(2,2)*mat(3,0) - mat(1,2)*mat(2,3)*mat(3,0) - mat(1,3)*mat(2,0)*mat(3,2) + mat(1,0)*mat(2,3)*mat(3,2) + mat(1,2)*mat(2,0)*mat(3,3) - mat(1,0)*mat(2,2)*mat(3,3);
   m(1,1) = mat(0,2)*mat(2,3)*mat(3,0) - mat(0,3)*mat(2,2)*mat(3,0) + mat(0,3)*mat(2,0)*mat(3,2) - mat(0,0)*mat(2,3)*mat(3,2) - mat(0,2)*mat(2,0)*mat(3,3) + mat(0,0)*mat(2,2)*mat(3,3);
   m(1,2) = mat(0,3)*mat(1,2)*mat(3,0) - mat(0,2)*mat(1,3)*mat(3,0) - mat(0,3)*mat(1,0)*mat(3,2) + mat(0,0)*mat(1,3)*mat(3,2) + mat(0,2)*mat(1,0)*mat(3,3) - mat(0,0)*mat(1,2)*mat(3,3);
   m(1,3) = mat(0,2)*mat(1,3)*mat(2,0) - mat(0,3)*mat(1,2)*mat(2,0) + mat(0,3)*mat(1,0)*mat(2,2) - mat(0,0)*mat(1,3)*mat(2,2) - mat(0,2)*mat(1,0)*mat(2,3) + mat(0,0)*mat(1,2)*mat(2,3);
   m(2,0) = mat(1,1)*mat(2,3)*mat(3,0) - mat(1,3)*mat(2,1)*mat(3,0) + mat(1,3)*mat(2,0)*mat(3,1) - mat(1,0)*mat(2,3)*mat(3,1) - mat(1,1)*mat(2,0)*mat(3,3) + mat(1,0)*mat(2,1)*mat(3,3);
   m(2,1) = mat(0,3)*mat(2,1)*mat(3,0) - mat(0,1)*mat(2,3)*mat(3,0) - mat(0,3)*mat(2,0)*mat(3,1) + mat(0,0)*mat(2,3)*mat(3,1) + mat(0,1)*mat(2,0)*mat(3,3) - mat(0,0)*mat(2,1)*mat(3,3);
   m(2,2) = mat(0,1)*mat(1,3)*mat(3,0) - mat(0,3)*mat(1,1)*mat(3,0) + mat(0,3)*mat(1,0)*mat(3,1) - mat(0,0)*mat(1,3)*mat(3,1) - mat(0,1)*mat(1,0)*mat(3,3) + mat(0,0)*mat(1,1)*mat(3,3);
   m(2,3) = mat(0,3)*mat(1,1)*mat(2,0) - mat(0,1)*mat(1,3)*mat(2,0) - mat(0,3)*mat(1,0)*mat(2,1) + mat(0,0)*mat(1,3)*mat(2,1) + mat(0,1)*mat(1,0)*mat(2,3) - mat(0,0)*mat(1,1)*mat(2,3);
   m(3,0) = mat(1,2)*mat(2,1)*mat(3,0) - mat(1,1)*mat(2,2)*mat(3,0) - mat(1,2)*mat(2,0)*mat(3,1) + mat(1,0)*mat(2,2)*mat(3,1) + mat(1,1)*mat(2,0)*mat(3,2) - mat(1,0)*mat(2,1)*mat(3,2);
   m(3,1) = mat(0,1)*mat(2,2)*mat(3,0) - mat(0,2)*mat(2,1)*mat(3,0) + mat(0,2)*mat(2,0)*mat(3,1) - mat(0,0)*mat(2,2)*mat(3,1) - mat(0,1)*mat(2,0)*mat(3,2) + mat(0,0)*mat(2,1)*mat(3,2);
   m(3,2) = mat(0,2)*mat(1,1)*mat(3,0) - mat(0,1)*mat(1,2)*mat(3,0) - mat(0,2)*mat(1,0)*mat(3,1) + mat(0,0)*mat(1,2)*mat(3,1) + mat(0,1)*mat(1,0)*mat(3,2) - mat(0,0)*mat(1,1)*mat(3,2);
   m(3,3) = mat(0,1)*mat(1,2)*mat(2,0) - mat(0,2)*mat(1,1)*mat(2,0) + mat(0,2)*mat(1,0)*mat(2,1) - mat(0,0)*mat(1,2)*mat(2,1) - mat(0,1)*mat(1,0)*mat(2,2) + mat(0,0)*mat(1,1)*mat(2,2);
   auto det = tao::det(mat);
   return m.element_wise_inplace(m, [det](T x, T) {return x * (1.0/det);});
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

template<typename T>
float spherical_theta(const Mat<T, 3, 1>& v) {
    auto norm = tao::norm(v);
    if (norm > 0.0f)
        return std::acos(v(2)/tao::norm(v)); 
    return 0.0f;
}

template<typename T>
float spherical_phi(const Mat<T, 3, 1>& v) {
    if (v(0) != 0)
        return std::atan2(v(1), v(0)); 
    else 
        return 0.0f;
}

template<typename T, int M>
bool is_identity(const Mat<T, M, M>& m) {
   for (int i = 0; i < M; ++i) {
       for (int j = 0; j < M; ++j) {
            if (i == j && m(i, j) != 1) return false;
            else if (i != j && m(i, j) != 0) return false;
       }
   } 
   return true;
}

/*float lerp(float t, float v1, float v2) {
    return (1 - t) * v1+ t * v2;
}*/

};

#endif
