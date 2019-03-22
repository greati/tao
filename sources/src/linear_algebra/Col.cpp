#include "linear_algebra/Col.h"

template<typename T>
tao::Col<T>::Col(const std::initializer_list<T> & components) : Mat<T>(components.size(), 1) { 
    auto i = 0;
    for (auto it = components.begin(); it != components.end(); ++it)
        this->data[i++] = *it;
}

template<typename T>
T tao::Col<T>::operator()(int i) {
    return Mat<T>::operator()(i, 0);
}

template class tao::Col<double>;
template class tao::Col<float>;
template class tao::Col<int>;
