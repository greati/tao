#ifndef __ROW__
#define __ROW__

#include "Mat.h"

namespace tao {
namespace deprecated {
template<typename T>
class Row : public Mat<T> {

    public:

        /**
         * Construct a row vector from its components.
         *
         * @param components the components
         * */
        Row(const std::initializer_list<T> & components);

        /**
         * Construct a column vector from an Nx1 matrix.
         * */
        Row(const tao::deprecated::Mat<T> & rowmat);

        /**
         * Vector access operator.
         *
         * @param pos component position
         * @return component value
         * */
        T operator()(int i) const;

        /**
         * Vector reference access operator.
         *
         * @param pos component position
         * @return component value
         * */
        T& operator()(int i);

        /**
         * Vector element-wise multiplication
         *
         * @param c2 the rhs
         * */
        Row<T> operator*(const Row<T>& c2);

        /**
         * Vector element-wise multiplication with assignment
         *
         * @param c2 the rhs
         * @return a reference to the modified version
         * */
        Row<T>& operator*=(const Row<T>& c2);

        /**
         * Vector element-wise division with assignment
         *
         * @param c2 the rhs
         * @return a reference to the modified version
         * */
        Row<T>& operator/=(const Row<T>& c2);

        /**
         * Euclidean norm of the vector
         *
         * @return the euclidean norm
         * */
        T norm() const;

        /**
         * The corresponding unit vector
         *
         * @param inplace if the vector should be modified
         * @return a new vector or nothing, depending on the inplace value
         * */
        std::optional<Row<T>> unit(bool inplace = false);

        /**
         * Vector dot product
         *
         * @param c2 the rhs
         * */
        T dot(const Row<T>& c2);

        /**
         * Multiply by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Row<T>& operator*=(const T scalar);

        /**
         * Divide by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Row<T>& operator/=(const T scalar);
};

template<typename T>
inline Row<T> operator*(const T scalar, const Row<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar * x; });
} 

template<typename T>
inline Row<T> operator/(const T scalar, const Row<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar / x; });
}
};
};
#endif
