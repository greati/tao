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
         * Vector access operator.
         *
         * @param pos component position
         * @return component value
         * */
        T operator()(int i);
};
};

#endif
