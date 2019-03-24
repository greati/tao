#ifndef __COL__
#define __COL__

#include "Mat.h"
#include "Row.h"

namespace tao {
template<typename T>
class Col : public Mat<T> {

    public:

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
         * Vector element-wise multiplication
         *
         * @param c2 the rhs
         * */
        Col<T> operator*(const Col<T>& c2);

        /**
         * Vector dot product
         *
         * @param c2 the rhs
         * */
        T dot(const Col<T>& c2);
};
};

#endif
