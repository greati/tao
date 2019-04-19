#include "linalg/Mat.h"

template<typename T>
tao::Mat<T>::Mat(const Mat<T>& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
    for (int i = 0; i < this->rows * this->cols; ++i)
        this->data[i] = other.data[i];
}

template<typename T>
tao::Mat<T>::Mat(int dim) : tao::Mat<T>::Mat(dim, dim) { /* empty */}

template<typename T>
tao::Mat<T>::Mat(int rows, int cols) {
    if (rows <= 0)
        throw std::invalid_argument("negative rows number " + std::to_string(rows));
    if (cols <= 0)
        throw std::invalid_argument("negative cols number " + std::to_string(cols));
    this->rows = rows;
    this->cols = cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
}

template<typename T>
tao::Mat<T>::Mat(int rows, int cols, T val) {
    if (rows <= 0)
        throw std::invalid_argument("negative rows number " + std::to_string(rows));
    if (cols <= 0)
        throw std::invalid_argument("negative cols number " + std::to_string(cols));
    this->rows = rows;
    this->cols = cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
    this->reset(val);
}

template<typename T>
tao::Mat<T>::Mat(const std::initializer_list<std::initializer_list<T>>& elements) {
    auto [rows, cols] = validate(elements);
    this->rows = rows;
    this->cols = cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
    populate(elements);
}

template<typename T>
T& tao::Mat<T>::operator()(int row, int col) {
    if (row < 0 || row >= rows)
        throw std::invalid_argument("invalid row access, when rows are " + std::to_string(rows)
                + " and row is " + std::to_string(row));
    if (col < 0 || col >= cols)
        throw std::invalid_argument("invalid col access, when cols are " + std::to_string(cols)
                + " and col is " + std::to_string(col));
    return this->data[row * cols + col];
}

template<typename T>
T tao::Mat<T>::operator()(int row, int col) const {
    if (row < 0 || row >= rows)
        throw std::invalid_argument("invalid row access, when rows are " + std::to_string(rows)
                + " and row is " + std::to_string(row));
    if (col < 0 || col >= cols)
        throw std::invalid_argument("invalid col access, when cols are " + std::to_string(cols)
                + " and col is " + std::to_string(col));
    return this->data[row * cols + col];
}

template<typename T>
void tao::Mat<T>::reset(const T& val) {
    for (int i = 0; i < rows * cols; ++i) {
        this->data[i] = val;
    }
}

template<typename T>
void tao::Mat<T>::populate(const std::initializer_list<std::initializer_list<T>>& elements) {
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

template<typename T>
std::pair<int, int> tao::Mat<T>::validate(const std::initializer_list<std::initializer_list<T>>& elements) {

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


template<typename T>
tao::Mat<T> tao::Mat<T>::element_wise(const tao::Mat<T>& rhs, std::function<T(T, T)> operation) const {
    if (rhs.ncols() != this->ncols() || rhs.nrows() != this->nrows())
        throw std::invalid_argument("can't operate element-wise on matrices with different dimensions");
    tao::Mat<T> mat {rhs.nrows(), rhs.ncols()};
    for (auto i = 0; i < rhs.nrows(); ++i) {
        for (auto j = 0; j < rhs.ncols(); ++j) {
            mat(i, j) = operation((*this)(i, j), rhs(i, j));
        }
    }
    return mat;
}


template<typename T>
tao::Mat<T>& tao::Mat<T>::element_wise_inplace(const tao::Mat<T>& rhs, std::function<T(T, T)> operation) {
    if (rhs.ncols() != this->ncols() || rhs.nrows() != this->nrows())
        throw std::invalid_argument("can't operate element-wise on matrices with different dimensions");
    for (auto i = 0; i < rhs.nrows(); ++i) {
        for (auto j = 0; j < rhs.ncols(); ++j) {
            (*this)(i, j) = operation((*this)(i, j), rhs(i, j));
        }
    }
    return (*this);
}


template<typename T>
tao::Mat<T> & tao::Mat<T>::operator=(const tao::Mat<T>& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
    for (int i = 0; i < this->rows * this->cols; ++i)
        this->data[i] = other.data[i];
    return (*this);
}

template<typename T>
bool tao::Mat<T>::operator==(const tao::Mat<T>& rhs) {
    if (rhs.ncols() != this->ncols() || rhs.nrows() != this->nrows())
        return false;
    for (auto i = 0; i < rhs.nrows(); ++i) {
        for (auto j = 0; j < rhs.ncols(); ++j) {
            if ((*this)(i, j) != rhs(i, j))
                return false;
        }
    }
    return true;
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator*(const T scalar) {
    return scalar * (*this);
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator/(const T scalar) {
    return (*this).element_wise((*this), [&](T x, T y) { return x / scalar; });
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator+(const tao::Mat<T>& rhs) const {
    return this->element_wise(rhs, [](T x, T y) { return x + y; });
}

template<typename T>
tao::Mat<T>& tao::Mat<T>::operator+=(const tao::Mat<T>& rhs) {
    return this->element_wise_inplace(rhs, [](T x, T y) { return x + y; });
}

template<typename T>
tao::Mat<T>& tao::Mat<T>::operator-=(const tao::Mat<T>& rhs) {
    return this->element_wise_inplace(rhs, [](T x, T y) { return x - y; });
}

template<typename T>
tao::Mat<T>& tao::Mat<T>::operator/=(const tao::Mat<T>& rhs) {
    return this->element_wise_inplace(rhs, [](T x, T y) { return x / y; });
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator-(const tao::Mat<T>& rhs) {
    return this->element_wise(rhs, [](T x, T y) { return x - y; });
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator-() {
    return this->element_wise((*this), [](T x, T y) { return -x; });
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator/(const tao::Mat<T>& rhs) {
    return this->element_wise(rhs, [](T x, T y) { return x / y; });
}

template<typename T>
tao::Mat<T>& tao::Mat<T>::operator*=(const T scalar) {
    return this->element_wise_inplace((*this), [&](T x, T y) { return scalar * x; });
}

template<typename T>
tao::Mat<T>& tao::Mat<T>::operator/=(const T scalar) {
    return this->element_wise_inplace((*this), [&](T x, T y) { return x / scalar; });
}

template<typename T>
void tao::Mat<T>::multiply(const tao::Mat<T>& m1, const tao::Mat<T>& m2, tao::Mat<T>& m3) {
    if (m1.ncols() != m2.nrows())
        throw std::invalid_argument("can't multiply m x n and p x k, with n neq p");
    for (auto i = 0; i < m1.nrows(); ++i) {
        for (auto j = 0; j < m2.ncols(); ++j) {
            T vm3 = m3(i, j);
            for (auto k = 0; k < m2.nrows(); ++k) {
                auto vm1 = m1(i, k);
                auto vm2 = m2(k, j);
                m3(i, j) += (vm1 * vm2);//m1(i, k) * m2(k, j); 
            }
            m3(i, j) -= vm3;
        }
    }
}

template<typename T>
tao::Mat<T> tao::Mat<T>::operator*(const tao::Mat<T>& rhs) {
    if (this->ncols() != rhs.nrows())
        throw std::invalid_argument("can't multiply m x n and p x k, with n neq p");
    tao::Mat<T> mat {this->nrows(), rhs.ncols()};
    this->multiply((*this), rhs, mat);
    return mat;
}

template<typename T>
tao::Mat<T> tao::Mat<T>::t() const {
    Mat<T> transp {cols, rows};
    for (auto i = 0; i < cols; ++i) {
        for (auto j = 0; j < rows; ++j) {
            transp(i, j) = (*this)(j, i);        
        }
    }
    return transp;
}

template<typename T>
bool tao::Mat<T>::eq(const Mat<T>& rhs, float precision) const {
    if ((*this).ncols() != rhs.ncols() || (*this).nrows() != rhs.nrows())
        return false;
    for (auto i = 0; i < rhs.nrows(); ++i) {
        for (auto j = 0; j < rhs.ncols(); ++j) {
            if (std::abs((*this)(i, j) - rhs(i, j)) >= precision)
                return false;
        }
    }
    return true;   
}

template class tao::Mat<float>;
template class tao::Mat<double>;
template class tao::Mat<int>;
