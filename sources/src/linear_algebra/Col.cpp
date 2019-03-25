#include "linear_algebra/Col.h"
#include <cmath>

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
tao::Col<T>& tao::Col<T>::operator*=(const tao::Col<T>& c2) {
    this->element_wise_inplace(c2, [](T x, T y){return x * y; });
    return (*this);
}

template<typename T>
T tao::Col<T>::dot(const tao::Col<T>& c2) {
    return ((*this).t() * c2)(0, 0); 
}

template<typename T>
T tao::Col<T>::norm() const {
    Row<T> t = (*this).t();
    return std::sqrt(t.dot((*this)));
}

template<typename T>
std::optional<tao::Col<T>> tao::Col<T>::unit(bool inplace) {
    if (!inplace)
        return (*this) / (*this).norm();
    (*this) /= (*this).norm();
    return std::nullopt;
}

template<typename T>
tao::Col<T>& tao::Col<T>::operator*=(const T scalar) {
    this->element_wise_inplace((*this), [&](T x, T y) { return scalar * x; });
    return (*this);
}

template<typename T>
tao::Col<T>& tao::Col<T>::operator/=(const T scalar) {
    this->element_wise_inplace((*this), [&](T x, T y) { return x / scalar; });
    return (*this);
}

template class tao::Col<double>;
template class tao::Col<float>;
template class tao::Col<int>;
