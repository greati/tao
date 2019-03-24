#include "linear_algebra/Col.h"

template<typename T>
tao::Col<T>::Col(const std::initializer_list<T> & components) : Mat<T>(components.size(), 1) { 
    auto i = 0;
    for (auto it = components.begin(); it != components.end(); ++it)
        this->data[i++] = *it;
}

template<typename T>
tao::Col<T>::Col(const Mat<T>& colmat) : Mat<T>(colmat) { /*empty*/ }

template<typename T>
T tao::Col<T>::operator()(int i) const {
    return Mat<T>::operator()(i, 0);
}

template<typename T>
T& tao::Col<T>::operator()(int i) {
    return Mat<T>::operator()(i, 0);
}

template<typename T>
tao::Col<T> tao::Col<T>::operator*(const tao::Col<T>& c2) {
    return this->element_wise(c2, [](T x, T y){return x * y; });
}

template<typename T>
T tao::Col<T>::dot(const tao::Col<T>& c2) {
    return ((*this).t() * c2)(0, 0); 
}

template class tao::Col<double>;
template class tao::Col<float>;
template class tao::Col<int>;
