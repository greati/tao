#ifndef __MAT__
#define __MAT__

#include <memory>
#include <functional>

/**
 * Represents a matrix whose elements
 * are parameterized.
 *
 * @author Vitor Greati
 * */
namespace tao {
template<typename T>
class Mat {

    protected:

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
         * Copy constructor.
         *
         * @param the mat to be copied
         * */
        Mat(const Mat<T>&);

        /**
         * Row-column read-only access operator.
         *
         * @param row the row, starting at top
         * @param col the col, starting at left
         * @return the element at row and col
         * */
        T operator()(int row, int col) const;

        /**
         * Row-column set access operator.
         *
         * @param row the row, starting at top
         * @param col the col, starting at left
         * */
        T& operator()(int row, int col);

        /**
         * Matrix element-wise sum.
         *
         * @param rhs the rhs
         * @return the sum
         * */
        Mat<T> operator+(const Mat<T>& rhs);

        /**
         * Matrix subtraction element-wise.
         *
         * @param rhs the rhs
         * @return the subtraction
         * */
        Mat<T> operator-(const Mat<T>& rhs);

        /**
         * Matrix division element-wise.
         *
         * @param rhs the rhs
         * @return the division
         * */
        Mat<T> operator/(const Mat<T>& rhs);

        /**
         * Unary matrix operator
         *
         * @return the additive inverse
         * */
        Mat<T> operator-();

        /**
         * Matrix product.
         *
         * @param rhs the rhs
         * @return the convertional matrix pruduct
         * */
        Mat<T> operator*(const Mat<T>& rhs);

        /**
         * Product between matrix and scalar.
         *
         * @param scalar the scalar rhs
         * @return the matrix multiplied by the scalar
         * */
        Mat<T> operator*(const T scalar);

        /**
         * Division between matrix and scalar.
         *
         * @param scalar the scalar rhs
         * @return the matrix multiplied by the scalar
         * */
        Mat<T> operator/(const T scalar);

        /**
         * Matrix product.
         *
         * @param rhs the rhs
         * @return true if equal
         * */
        bool operator==(const Mat<T>& rhs);

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

        /**
         * Performs an operation element-wise, producing a new matrix.
         *
         * @param operation an operation
         * @return the resulting matrix
         * */
        Mat<T> element_wise(const Mat<T>& rhs, std::function<T(T, T)> operation) const;

        /**
         * Performs an operation element-wise, modifying the current matrix.
         *
         * @param operation an operation
         * @return the resulting matrix
         * */
        Mat<T>& element_wise_inplace(const Mat<T>& rhs, std::function<T(T, T)> operation);

        /**
         * Computes the transpose of a matrix.
         *
         * @return a new matrix which is the transpose
         * */
        Mat<T> t() const;

        /**
         * Sum and assignment.
         *
         * @param other the matrix to be added
         * @return the result of adding as a reference
         * */
        Mat<T>& operator+=(const Mat<T>&);

        /**
         * Subtract and assignment.
         *
         * @param other the matrix to be added
         * @return the result of subtraction as a reference
         * */
        Mat<T>& operator-=(const Mat<T>&);

        /**
         * Divide and assignment.
         *
         * @param other the matrix to be divided
         * @return the result of division as a reference
         * */
        Mat<T>& operator/=(const Mat<T>&);

        /**
         * Multiply by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Mat<T>& operator*=(const T scalar);

        /**
         * Divide by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Mat<T>& operator/=(const T scalar);

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

        /**
         * Performs matrix multiplication.
         *
         * @param rhs the rhs
         * @return the conventional matrix pruduct
         * */
        void multiply(const Mat<T>& m1, const Mat<T>& m2, Mat<T>& m3);
};

template<typename T>
inline Mat<T> operator*(const T scalar, const Mat<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar * x; });
} 

template<typename T>
inline Mat<T> operator/(const T scalar, const Mat<T>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar / x; });
} 

};

#endif
