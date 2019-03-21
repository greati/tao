#include "linear_algebra/Mat.h"

template<typename T>
tao::Mat<T>::Mat(const std::initializer_list<std::initializer_list<T>>& elements) {
    auto [rows, cols] = validate(elements);
    this->rows = rows;
    this->cols = cols;
    this->data = std::move(std::make_unique<T[]>(this->rows * this->cols));
    populate(elements);
}


template<typename T>
void tao::Mat<T>::populate(const std::initializer_list<std::initializer_list<T>>& elements) {
    auto elements_row_it = elements.begin();
    for (auto i = 0; i < rows; ++i) {
        auto elements_col_it = elements_row_it->begin();
        for (auto j = 0; j < cols; ++j) {
            this->data[i * cols + j] = *elements_col_it;
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

template class tao::Mat<float>;
template class tao::Mat<double>;
