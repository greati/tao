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

        std::unique_ptr<T[]> data;      /** Matrix data */
        int rows {0};                   /** Number of rows */
        int cols {0};                   /** Number of cols */

    public:

        /**
         * Constructor of square matrices based on size only.
         *
         * @param rows number of rows and cols
         * */
        Mat(int dim);

        /**
         * Constructor based on size only.
         *
         * @param rows number of rows
         * @param cols number of cols
         * */
        Mat(int rows, int cols);

        /**
         * Constructor based on size and a fill value.
         *
         * @param rows number of rows
         * @param cols number of cols
         * @param fill value to fill
         * */
        Mat(int rows, int cols, T val);

        /**
         * Construtor based on an initializer list.
         *
         * @param elements the elements
         * */
        Mat(const std::initializer_list<std::initializer_list<T>>& elements);

        /**
         * Row-column access operator.
         *
         * @param row the row, starting at top
         * @param col the col, starting at left
         * */
        T operator()(int row, int col);

        /**
         * The number of rows.
         *
         * @return the number of rows
         * */
        inline int nrows() const { return rows; };

        /**
         * The number of cols.
         *
         * @return the number of cols
         * */
        inline int ncols() const { return cols; };

        /**
         * Reset matrix with a value.
         *
         * @param value the value to fill the matrix
         * */
        void reset(const T& val);

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
