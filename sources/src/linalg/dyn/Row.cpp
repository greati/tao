#include "tao/linalg/dyn/Row.h"
#include "tao/linalg/dyn/Col.h"
#include <cmath>

template<typename T>
tao::deprecated::Row<T>::Row(const std::initializer_list<T> & components) : Mat<T>(1, components.size()) { 
    auto i = 0;
    for (auto it = components.begin(); it != components.end(); ++it)
        this->data[i++] = *it;
}

template<typename T>
tao::deprecated::Row<T>::Row(const Mat<T>& rowmat) : Mat<T>(rowmat) { /*empty*/ }

template<typename T>
T tao::deprecated::Row<T>::operator()(int i) const {
    return Mat<T>::operator()(0, i);
}

template<typename T>
T& tao::deprecated::Row<T>::operator()(int i) {
    return Mat<T>::operator()(0, i);
}

template<typename T>
tao::deprecated::Row<T> tao::deprecated::Row<T>::operator*(const tao::deprecated::Row<T>& c2) {
    return this->element_wise(c2, [](T x, T y){return x * y; });
}

template<typename T>
tao::deprecated::Row<T>& tao::deprecated::Row<T>::operator*=(const tao::deprecated::Row<T>& c2) {
    this->element_wise_inplace(c2, [](T x, T y){return x * y; });
    return (*this);
}

template<typename T>
tao::deprecated::Row<T>& tao::deprecated::Row<T>::operator/=(const tao::deprecated::Row<T>& c2) {
    this->element_wise_inplace(c2, [](T x, T y){return x / y; });
    return (*this);
}

template<typename T>
T tao::deprecated::Row<T>::dot(const tao::deprecated::Row<T>& c2) {
    return Mat<T>::operator*(c2.t())(0, 0);
}

template<typename T>
T tao::deprecated::Row<T>::norm() const {
    Col<T> t = (*this).t();
    Row<T> r = (*this);
    return std::sqrt(r.dot(t));
}

template<typename T>
std::optional<tao::deprecated::Row<T>> tao::deprecated::Row<T>::unit(bool inplace) {
    if (!inplace)
        return (*this) / (*this).norm();
    (*this) /= (*this).norm();
    return std::nullopt;
}

template<typename T>
tao::deprecated::Row<T>& tao::deprecated::Row<T>::operator*=(const T scalar) {
    this->element_wise_inplace((*this), [&](T x, T y) { return scalar * x; });
    return (*this);
}

template<typename T>
tao::deprecated::Row<T>& tao::deprecated::Row<T>::operator/=(const T scalar) {
    this->element_wise_inplace((*this), [&](T x, T y) { return x / scalar; });
    return (*this);
}

template class tao::deprecated::Row<double>;
template class tao::deprecated::Row<float>;
template class tao::deprecated::Row<int>;
