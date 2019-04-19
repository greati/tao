#ifndef __COL__
#define __COL__

#include "Mat.h"
#include "Row.h"
#include <optional>

namespace tao {
template<typename T>
class Col : public Mat<T> {

    public:

        Col() : Mat<T>{3, 1} {/* empty */}

        /**
         * Construct a column vector from its components.
         *
         * @param components the components
         * */
        Col(const std::initializer_list<T> & components);

        /**
         * Construct a column vector from an Nx1 matrix.
         * */
        Col(const tao::Mat<T> & colmat);

        /**
         * Vector read-only access operator.
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
         * Vector difference
         *
         * @param c2 the other vector
         * @return the difference
         * */
        inline Col<T> operator-(const Col<T>& c2) { return Mat<T>::operator-(c2); }

        /**
         * Vector element-wise multiplication
         *
         * @param c2 the rhs
         * */
        Col<T> operator*(const Col<T>& c2);

        /**
         * Vector element-wise multiplication with assignment
         *
         * @param c2 the rhs
         * @return a reference to the modified version
         * */
        Col<T>& operator*=(const Col<T>& c2);

        /**
         * Vector element-wise division with assignment
         *
         * @param c2 the rhs
         * @return a reference to the modified version
         * */
        Col<T>& operator/=(const Col<T>& c2);

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
        std::optional<Col<T>> unit(bool inplace = false);

        /**
         * Vector dot product
         *
         * @param c2 the rhs
         * */
        T dot(const Col<T>& c2);

        /**
         * Multiply by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Col<T>& operator*=(const T scalar);

        /**
         * Divide by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Col<T>& operator/=(const T scalar);

        /**
         * Product between vector and scalar.
         *
         * @param scalar the scalar rhs
         * @return the matrix multiplied by the scalar
         * */
        Col<T> operator*(const T scalar) const;
};

template<typename T>
inline Col<T> operator*(const T scalar, const Col<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar * x; });
} 

template<typename T>
inline Col<T> operator/(const T scalar, const Col<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar / x; });
}

};

#endif
