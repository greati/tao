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
};
};

#endif
