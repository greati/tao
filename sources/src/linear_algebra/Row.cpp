#include "linear_algebra/Row.h"

template<typename T>
tao::Row<T>::Row(const std::initializer_list<T> & components) : Mat<T>(1, components.size()) { 
    auto i = 0;
    for (auto it = components.begin(); it != components.end(); ++it)
        this->data[i++] = *it;
}

template<typename T>
tao::Row<T>::Row(const Mat<T>& rowmat) : Mat<T>(rowmat) { /*empty*/ }

template<typename T>
T tao::Row<T>::operator()(int i) const {
    return Mat<T>::operator()(0, i);
}

template<typename T>
T& tao::Row<T>::operator()(int i) {
    return Mat<T>::operator()(0, i);
}

template<typename T>
tao::Row<T> tao::Row<T>::operator*(const tao::Row<T>& c2) {
    return this->element_wise(c2, [](T x, T y){return x * y; });
}

template<typename T>
T tao::Row<T>::dot(const tao::Row<T>& c2) {
    return ((*this) * c2.t())(0, 0); 
}

template class tao::Row<double>;
template class tao::Row<float>;
template class tao::Row<int>;
