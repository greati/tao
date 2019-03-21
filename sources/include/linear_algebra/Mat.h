#ifndef __MAT__
#define __MAT__

#include <memory>

/**
 * Represents a matrix whose elements
 * are parameterized.
 *
 * @author Vitor Greati
 * */
namespace tao {
template<typename T>
class Mat {

    private:

        std::unique_ptr<T[]> data;        /** Matrix data */
        int rows {0};                   /** Number of rows */
        int cols {0};                   /** Number of cols */

    public:

        /**
         * Construtor based on an initializer list.
         *
         * @param elements the elements
         * */
        Mat(const std::initializer_list<std::initializer_list<T>>& elements);

    private:

        /**
         * Populate the data member given an initializer list.
         *
         * @param elements the elements
         * */
        void populate(const std::initializer_list<std::initializer_list<T>>& elements);

        /**
         * Validate an initializer list to become a valid matrix.
         *
         * @param elements the list
         * @return the size of the future matrix
         * */
        std::pair<int, int> validate(const std::initializer_list<std::initializer_list<T>>& elements);
};
};

#endif
