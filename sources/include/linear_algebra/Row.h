#ifndef __ROW__
#define __ROW__

#include "Mat.h"

namespace tao {
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
        Row(const tao::Mat<T> & colmat);

        /**
         * Construct a row by size.
         *
         * @param size the number of cols
         * */
        Row(int cols) : Mat<T>{1, cols} {/*empty*/}

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
        Row<T> operator*(const Col<T>& c2);

        /**
         * Vector dot product
         *
         * @param c2 the rhs
         * */
        T dot(const Row<T>& c2);
};
};

#endif
