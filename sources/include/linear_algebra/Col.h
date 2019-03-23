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
         * Vector access operator.
         *
         * @param pos component position
         * @return component value
         * */
        T operator()(int i);

        /**
         * Returns the corresponding row vector.
         *
         * @return the row vector
         * */
        Row<T> t();

};
};

#endif
