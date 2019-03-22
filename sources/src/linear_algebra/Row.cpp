#include "linear_algebra/Row.h"

template<typename T>
tao::Row<T>::Row(const std::initializer_list<T> & components) : Mat<T>(1, components.size()) { 
    auto i = 0;
    for (auto it = components.begin(); it != components.end(); ++it)
        this->data[i++] = *it;
}

template<typename T>
T tao::Row<T>::operator()(int i) {
    return Mat<T>::operator()(0, i);
}

template class tao::Row<double>;
template class tao::Row<float>;
template class tao::Row<int>;
