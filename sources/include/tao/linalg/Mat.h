#ifndef _COMP_MAT_
#define _COMP_MAT_

#include <memory>
#include <functional>
#include <array>
#include <type_traits>

enum StorageType {
    Dynamic = 0
};

namespace tao {

/**
 * Traits to define the matrix storage type
 * at compile time.
 * */
template<int M, int N, typename T>
struct mat_storage_type_traits {
    using matrix_storage_type = 
        typename std::conditional<
            (M==Dynamic && N==Dynamic),
            typename std::unique_ptr<T[]>,
            typename std::conditional<
                (M != Dynamic && N != Dynamic),
                std::array<T, M*N>,
                std::array<T, M*N>
            >::type
        >::type;
};

template<int M, int N, typename T>
struct mat_storage_initializer {
    void initialize(typename mat_storage_type_traits<M, N, T>::matrix_storage_type& data, int _M, int _N) {}  
};

template<typename T>
struct mat_storage_initializer<Dynamic, Dynamic, T> {
    void initialize(typename mat_storage_type_traits<Dynamic, Dynamic, T>::matrix_storage_type& data, 
            int _M, int _N) {
        data = std::move(std::make_unique<T[]>(_M*_N)); 
    }  
};

/**
 * Represents a matrix whose elements
 * are parameterized.
 *
 * @author Vitor Greati
 * */
template<typename T, int NumberRows, int NumberCols>
class Mat {

    protected:

        typename mat_storage_type_traits<NumberRows, NumberCols, T>::matrix_storage_type data;
        mat_storage_initializer<NumberRows, NumberCols, T> storage_initializer;

        int rows {NumberRows};                  /** Number of rows */
        int cols {NumberCols};                  /** Number of cols */

    public:

        Mat() {/* empty */}

        /**
         * Constructor which initializes the matrix
         * with an specified value.
         *
         * @param initial the initial value
         * */
        Mat(T initial) {
            for (auto i {0}; i < rows * cols; ++i)
                data[i] = initial;
        }


        /**
         * Construtor based on an initializer list.
         *
         * @param elements the elements
         * */
        Mat(const std::initializer_list<T>& elements) {
            auto [r, c] = validate(elements);
            this->rows = r;
            this->cols = c;

            storage_initializer.initialize(data, rows, cols);

            if (r != this->rows || c != this->cols)
                throw std::invalid_argument("invalid matrix initialization, expected: (" 
                        + std::to_string(this->rows)
                        + "," + std::to_string(this->cols) + "), got (" + std::to_string(r) 
                        + "," + std::to_string(c) + ")");
            populate(elements);
        }

        /**
         * Construtor based on an initializer list.
         *
         * @param elements the elements
         * */
        Mat(const std::initializer_list<std::initializer_list<T>>& elements) {
            auto [r, c] = validate(elements);
            this->rows = r;
            this->cols = c;

            storage_initializer.initialize(data, rows, cols);

            if (r != this->rows || c != this->cols)
                throw std::invalid_argument("invalid matrix initialization, expected: (" 
                        + std::to_string(this->rows)
                        + "," + std::to_string(this->cols) + "), got (" + std::to_string(r) 
                        + "," + std::to_string(c) + ")");
            populate(elements);
        }

        /**
         * Row-column read-only access operator.
         *
         * @param row the row, starting at top
         * @param col the col, starting at left
         * @return the element at row and col
         * */
        T operator()(int row, int col=0) const {
            if (row < 0 || row >= rows)
                throw std::invalid_argument("invalid row access, when rows are " + std::to_string(rows)
                        + " and row is " + std::to_string(row));
            if (col < 0 || col >= cols)
                throw std::invalid_argument("invalid col access, when cols are " + std::to_string(cols)
                        + " and col is " + std::to_string(col));
            return this->data[row * cols + col]; 
        }

        /**
         * Row-column set access operator.
         *
         * @param row the row, starting at top
         * @param col the col, starting at left
         * */
        T& operator()(int row, int col=0) {
            if (row < 0 || row >= rows)
                throw std::invalid_argument("invalid row access, when rows are " + std::to_string(rows)
                        + " and row is " + std::to_string(row));
            if (col < 0 || col >= cols)
                throw std::invalid_argument("invalid col access, when cols are " + std::to_string(cols)
                        + " and col is " + std::to_string(col));
            return this->data[row * cols + col];
        }

        /**
         * Matrix element-wise sum.
         *
         * @param rhs the rhs
         * @return the sum
         * */
        Mat<T, NumberRows, NumberCols> operator+(const Mat<T, NumberRows, NumberCols>& rhs) const {
            return this->element_wise(rhs, [](T x, T y) { return x + y; });
        }

        /**
         * Matrix subtraction element-wise.
         *
         * @param rhs the rhs
         * @return the subtraction
         * */
        Mat<T, NumberRows, NumberCols> operator-(const Mat<T, NumberRows, NumberCols>& rhs) const {
            return this->element_wise(rhs, [](T x, T y) { return x - y; });
        }

        /**
         * Matrix division element-wise.
         *
         * @param rhs the rhs
         * @return the division
         * */
        Mat<T, NumberRows, NumberCols> operator/(const Mat<T, NumberRows, NumberCols>& rhs) const {
            return this->element_wise(rhs, [](T x, T y) { return x / y; });
        }

        /**
         * Unary matrix operator
         *
         * @return the additive inverse
         * */
        Mat<T, NumberRows, NumberCols> operator-() const {
            return this->element_wise((*this), [](T x, T y) { return -x; });
        }

        /**
         * Product between matrix and scalar.
         *
         * @param scalar the scalar rhs
         * @return the matrix multiplied by the scalar
         * */
        Mat<T, NumberRows, NumberCols> operator*(const T scalar) {
            return scalar * (*this);
        }

        /**
         * Division between matrix and scalar.
         *
         * @param scalar the scalar rhs
         * @return the matrix multiplied by the scalar
         * */
        Mat<T, NumberRows, NumberCols> operator/(const T scalar) {
            return (*this).element_wise((*this), [&](T x, T y) { return x / scalar; });
        }

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
        void reset(const T& val) {
            for (int i = 0; i < rows * cols; ++i) {
                this->data[i] = val;
            }
        }

        /**
         * Performs an operation element-wise, producing a new matrix.
         *
         * @param operation an operation
         * @return the resulting matrix
         * */
        Mat<T, NumberRows, NumberCols> element_wise(const Mat<T, NumberRows, NumberCols>& rhs, 
                std::function<T(T, T)> operation) const {
            tao::Mat<T, NumberRows, NumberCols> mat;
            for (auto i = 0; i < rhs.nrows(); ++i) {
                for (auto j = 0; j < rhs.ncols(); ++j) {
                    mat(i, j) = operation((*this)(i, j), rhs(i, j));
                }
            }
            return mat;
        }

        /**
         * Performs an operation element-wise, modifying the current matrix.
         *
         * @param operation an operation
         * @return the resulting matrix
         * */
        Mat<T, NumberRows, NumberCols>& element_wise_inplace(const Mat<T, NumberRows, NumberCols>& rhs, 
                std::function<T(T, T)> operation) {
            for (auto i = 0; i < rhs.nrows(); ++i) {
                for (auto j = 0; j < rhs.ncols(); ++j) {
                    (*this)(i, j) = operation((*this)(i, j), rhs(i, j));
                }
            }
            return (*this);
        }

        /**
         * Computes the transpose of a matrix.
         *
         * @return a new matrix which is the transpose
         * */
        Mat<T, NumberCols, NumberRows> t() const {
            Mat<T, NumberCols, NumberRows> transp;
            for (auto i = 0; i < cols; ++i) {
                for (auto j = 0; j < rows; ++j) {
                    transp(i, j) = (*this)(j, i);        
                }
            }
            return transp;
        }

        /**
         * Sum and assignment.
         *
         * @param other the matrix to be added
         * @return the result of adding as a reference
         * */
        Mat<T, NumberRows, NumberCols>& operator+=(const Mat<T, NumberRows, NumberCols>& rhs) {
            return this->element_wise_inplace(rhs, [](T x, T y) { return x + y; });
        }

        /**
         * Subtract and assignment.
         *
         * @param other the matrix to be added
         * @return the result of subtraction as a reference
         * */
        Mat<T, NumberRows, NumberCols>& operator-=(const Mat<T, NumberRows, NumberCols>& rhs) {
            return this->element_wise_inplace(rhs, [](T x, T y) { return x - y; });
        }

        /**
         * Divide and assignment.
         *
         * @param other the matrix to be divided
         * @return the result of division as a reference
         * */
        Mat<T, NumberRows, NumberCols>& operator/=(const Mat<T, NumberRows, NumberCols>& rhs) {
            return this->element_wise_inplace(rhs, [](T x, T y) { return x / y; });
        }

        /**
         * Multiply by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Mat<T, NumberRows, NumberCols>& operator*=(const T scalar) {
            return this->element_wise_inplace((*this), [&](T x, T y) { return scalar * x; });
        }

        /**
         * Divide by scalar and assignment.
         *
         * @param other the matrix to be added
         * @return the result of multiplication as a reference
         * */
        Mat<T, NumberRows, NumberCols>& operator/=(const T scalar) {
            return this->element_wise_inplace((*this), [&](T x, T y) { return x / scalar; });
        }

        /**
         * Equality comparison with precision indication.
         *
         * @param m1 a matrix
         * @param m2 another matrix
         * @param the precision
         * @return if m1 == m2 according to the precision
         * */
        template<int O, int P>
        bool eq(const Mat<T, O, P>& rhs, float precision = 0.0001) const {
            if (O != NumberRows || P != NumberCols)
                return false;
            for (auto i = 0; i < rhs.nrows(); ++i) {
                for (auto j = 0; j < rhs.ncols(); ++j) {
                    if (std::abs((*this)(i, j) - rhs(i, j)) >= precision)
                        return false;
                }
            }
            return true;
        }

    private:

        /**
         * Populate the data member given an initializer list.
         *
         * @param elements the elements
         * */
        void populate(const std::initializer_list<std::initializer_list<T>>& elements) {
            auto elements_row_it = elements.begin();
            for (auto i = 0; i < rows; ++i) {
                auto elements_col_it = elements_row_it->begin();
                for (auto j = 0; j < cols; ++j) {
                    this->data[i * cols + j] = *elements_col_it;
                    elements_col_it++;
                }
                elements_row_it++;
                if (elements_row_it == elements.end())
                    break;
            }
        }

        /**
         * Populate the data member given an initializer list.
         *
         * @param elements the elements
         * */
        void populate(const std::initializer_list<T>& elements) {
            auto elements_row_it = elements.begin();

            auto i {0};

            for (auto e : elements) {
                this->data[i] = e;
                i++;
            }
/*
            for (auto i = 0; i < rows; ++i) {
                auto elements_col_it = elements_row_it->begin();
                for (auto j = 0; j < cols; ++j) {
                    this->data[i * cols + j] = *elements_col_it;
                    elements_col_it++;
                }
                elements_row_it++;
                if (elements_row_it == elements.end())
                    break;
            }*/
        }

        /**
         * Validate an initializer list to become a valid matrix.
         *
         * @param elements the list
         * @return the size of the future matrix
         * */
        std::pair<int, int> validate(const std::initializer_list<std::initializer_list<T>>& elements) {
            if (elements.size() == 0)
                throw std::invalid_argument("empty column found");

            auto rows = 0, cols = 0, cols_temp = 0;
            
            for (auto itrow = elements.begin(); itrow != elements.end(); ++itrow) {
                rows++;
                cols_temp = 0;
                for (auto itcol = itrow->begin(); itcol != itrow->end(); ++itcol) {
                    cols_temp++;
                }
                if (cols_temp == 0) {
                    throw std::invalid_argument("empty column found");
                }
                if (cols == 0) {
                    cols = cols_temp;
                } else if (cols != cols_temp) {
                    throw std::invalid_argument("different number of elements in columns");
                }
            }
            return {rows, cols}; 
        }

        /**
         * Validate an initializer list to become a valid matrix.
         *
         * @param elements the list
         * @return the size of the future matrix
         * */
        std::pair<int, int> validate(const std::initializer_list<T>& elements) {
            if (elements.size() == 0)
                throw std::invalid_argument("empty column found");

            if (NumberRows != Dynamic && NumberCols != Dynamic
                    && elements.size() != NumberRows * NumberCols) {
                throw std::invalid_argument("invalid number of elements in initializer: " +
                        std::to_string(elements.size()));
            }

            if (NumberRows == Dynamic || NumberCols == Dynamic)
                return {elements.size(), 1};

            return {NumberRows, NumberCols}; 
        }

};

/**
 * Performs matrix multiplication.
 *
 * @param rhs the rhs
 * @return the conventional matrix pruduct
 * */
template<typename T, int M, int N, int P>
void multiply(const Mat<T, M, N>& m1, const Mat<T, N, P>& m2, 
        Mat<T, M, P>& m3) {
    for (auto i = 0; i < m1.nrows(); ++i) {
        for (auto j = 0; j < m2.ncols(); ++j) {
            T vm3 = m3(i, j);
            for (auto k = 0; k < m2.nrows(); ++k) {
                auto vm1 = m1(i, k);
                auto vm2 = m2(k, j);
                m3(i, j) += (vm1 * vm2);
            }
            m3(i, j) -= vm3;
        }
    }
}

/**
 * Matrix product.
 *
 * @param rhs the rhs
 * @return the convertional matrix pruduct
 * */
template<typename T, int M, int N, int P>
Mat<T, M, P> operator*(const Mat<T, M, N>& lhs, 
                       const Mat<T, N, P>& rhs) {
    Mat<T, M, P> result ( T(0) );
    multiply(lhs, rhs, result);
    return result;
}

template<typename T, int M, int N>
inline Mat<T, M, N> operator*(const T scalar, const Mat<T, M, N>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar * x; });
} 

template<typename T, int M, int N>
inline Mat<T, M, N> operator/(const T scalar, const Mat<T, M, N>& m) {
    return m.element_wise(m, [&](T x, T y) { return scalar / x; });
} 

/**
 * Equality comparison.
 *
 * @param rhs the rhs
 * @return true if equal
 * */
template<typename T, int M, int N, int O, int P>
bool operator==(const Mat<T, M, N>& lhs, const Mat<T, O, P>& rhs) {
    if (O != M || P != N)
        return false;
    for (auto i = 0; i < rhs.nrows(); ++i) {
        for (auto j = 0; j < rhs.ncols(); ++j) {
            if (lhs(i, j) != rhs(i, j))
                return false;
        }
    }
    return true;
}


};
#endif
