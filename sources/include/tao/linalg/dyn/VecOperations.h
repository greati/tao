#ifndef __VECOPERATIONS__
#define __VECOPERATIONS__

#include "tao/linalg/dyn/Col.h"

namespace tao {
namespace deprecated {

/**
 * Computes the cross product between 
 * two 3D vectors.
 *
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the cross product
 * */
template<typename T>
Col<T> cross(const Col<T>& v1, const Col<T>& v2) {
    if (v1.nrows() != 3 or v2.nrows() != 3)
        throw std::invalid_argument("cross product is defined only for 3d vectors");
    return tao::deprecated::Col<T>{
        (v1(1) * v2(2) - v1(2) * v2(1)), 
        (-(v1(0) * v2(2) - v1(2) * v2(0))), 
        (v1(0) * v2(1) - v1(1) * v2(0))
    };
}

};
};

#endif
