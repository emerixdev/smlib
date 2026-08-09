#ifndef SMLIB_H
#define SMLIB_H
#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <vector>

namespace smlib {
template <typename T>
concept FloatingPoint = std::floating_point<T>;

template <FloatingPoint T> class mvec {
private:
  std::vector<T> data_;

public:
  mvec() = default;
  mvec(std::size_t n) : data_(n) {}
  mvec(std::size_t n, const T &value) : data_(n, value) {}
  mvec(std::initializer_list<T> list) : data_(list) {}
  T *data();
  const T *data() const;
  T &operator[](std::size_t index);
  const T &operator[](std::size_t index) const;
  mvec<T> &operator+=(const mvec<T> &a);
  mvec<T> &operator-=(const mvec<T> &a);
  mvec<T> &operator*=(T scalar);
  mvec<T> &operator/=(T scalar);
  mvec<T> operator+(const mvec<T> &a) const;
  mvec<T> operator-(const mvec<T> &a) const;
  mvec<T> operator*(T scalar) const;
  mvec<T> operator/(T scalar) const;
  mvec<T> operator+() const;
  mvec<T> operator-() const;
  bool operator==(const mvec<T> &a) const;
  bool operator!=(const mvec<T> &a) const;
  void fill(T value);
  void resize(std::size_t size);
  std::size_t size() const;
  bool empty() const;
  T &at(std::size_t index);
  const T &at(std::size_t index) const;
  T &x();
  const T &x() const;
  T &y();
  const T &y() const;
  T &z();
  const T &z() const;
  auto begin();
  auto end();
  auto begin() const;
  auto end() const;
  auto cbegin() const;
  auto cend() const;
  T dot(const mvec<T> &a) const;
  T magnitude() const;
  T magnitude_squared() const;
  T sum() const;
  T min() const;
  T max() const;
  mvec<T> unit() const;
  void normalize();
  mvec<T> cross(const mvec<T> &a) const;
  mvec<T> abs() const;
  mvec<T> floor() const;
  mvec<T> ceil() const;
  mvec<T> round() const;
  mvec<T> sqrt() const;
  bool approx_equal_absolute(const mvec<T> &a, T epsilon) const;
  bool approx_equal_relative(const mvec<T> &a, T epsilon) const;
  bool has_nan() const;
  bool has_infinity() const;
  bool is_finite() const;
  bool is_zero() const;
  bool is_near_zero(T epsilon) const;
};
template <FloatingPoint T> T *mvec<T>::data() { return data_.data(); }
template <FloatingPoint T> const T *mvec<T>::data() const { return data_.data(); }
template <FloatingPoint T> T &mvec<T>::operator[](std::size_t index) { return data_[index]; }
template <FloatingPoint T> const T &mvec<T>::operator[](std::size_t index) const { return data_[index]; }
template <FloatingPoint T> mvec<T> &mvec<T>::operator+=(const mvec<T> &a) {
  if (size() != a.size())
    throw std::invalid_argument("Vector sizes must match! (Addition).");
  for (std::size_t i = 0; i < size(); ++i) {
    (*this)[i] += a[i];
  }
  return *this;
}
template <FloatingPoint T> mvec<T> &mvec<T>::operator-=(const mvec<T> &a) {
  if (size() != a.size())
    throw std::invalid_argument("Vector sizes must match! (Subtraction).");
  for (std::size_t i = 0; i < size(); ++i) {
    (*this)[i] -= a[i];
  }
  return *this;
}
template <FloatingPoint T> mvec<T> &mvec<T>::operator*=(T scalar) {
  for (auto &it : *this) {
    it *= scalar;
  }
  return *this;
}
template <FloatingPoint T> mvec<T> &mvec<T>::operator/=(T scalar) {
  for (auto &it : *this) {
    it /= scalar;
  }
  return *this;
}
template <FloatingPoint T> mvec<T> mvec<T>::operator+(const mvec<T> &a) const {
  mvec<T> out(*this);
  out += a;
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::operator-(const mvec<T> &a) const {
  mvec<T> out(*this);
  out -= a;
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::operator*(T scalar) const {
  mvec<T> out(*this);
  out *= scalar;
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::operator/(T scalar) const {
  mvec<T> out(*this);
  out /= scalar;
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::operator+() const { return *this; }
template <FloatingPoint T> mvec<T> mvec<T>::operator-() const { return (*this) * -1; }
template <FloatingPoint T> bool mvec<T>::operator==(const mvec<T> &a) const { return data_ == a.data_; }
template <FloatingPoint T> bool mvec<T>::operator!=(const mvec<T> &a) const { return !(*this == a); }
template <FloatingPoint T> void mvec<T>::fill(T value) { std::fill(begin(), end(), value); }
template <FloatingPoint T> void mvec<T>::resize(std::size_t size) { data_.resize(size); }
template <FloatingPoint T> std::size_t mvec<T>::size() const { return data_.size(); }
template <FloatingPoint T> bool mvec<T>::empty() const { return data_.empty(); }
template <FloatingPoint T> T &mvec<T>::at(std::size_t index) { return data_.at(index); }
template <FloatingPoint T> const T &mvec<T>::at(std::size_t index) const { return data_.at(index); }
template <FloatingPoint T> T &mvec<T>::x() { return at(0); }
template <FloatingPoint T> const T &mvec<T>::x() const { return at(0); }
template <FloatingPoint T> T &mvec<T>::y() { return at(1); }
template <FloatingPoint T> const T &mvec<T>::y() const { return at(1); }
template <FloatingPoint T> T &mvec<T>::z() { return at(2); }
template <FloatingPoint T> const T &mvec<T>::z() const { return at(2); }
template <FloatingPoint T> auto mvec<T>::begin() { return data_.begin(); }
template <FloatingPoint T> auto mvec<T>::end() { return data_.end(); }
template <FloatingPoint T> auto mvec<T>::begin() const { return data_.begin(); }
template <FloatingPoint T> auto mvec<T>::end() const { return data_.end(); }
template <FloatingPoint T> auto mvec<T>::cbegin() const { return data_.cbegin(); }
template <FloatingPoint T> auto mvec<T>::cend() const { return data_.cend(); }
template <FloatingPoint T> T mvec<T>::dot(const mvec<T> &a) const {
  if (size() != a.size())
    throw std::invalid_argument("Vector sizes must match! (Dot).");
  T out = T{0};
  for (std::size_t i = 0; i < size(); ++i) {
    out += (*this)[i] * a[i];
  }
  return out;
}
template <FloatingPoint T> T mvec<T>::magnitude() const {
  T out = T{0};
  for (auto x : *this) {
    out = std::hypot(out, x);
  }
  return out;
}
template <FloatingPoint T> T mvec<T>::magnitude_squared() const { return dot(*this); }
template <FloatingPoint T> T mvec<T>::sum() const {
  T out = T{0};
  for (auto x : *this) {
    out += x;
  }
  return out;
}
template <FloatingPoint T> T mvec<T>::min() const {
  if (empty())
    throw std::domain_error("Cannot find minimum of an empty vector!");
  return *std::min_element(begin(), end());
}
template <FloatingPoint T> T mvec<T>::max() const {
  if (empty())
    throw std::domain_error("Cannot find maximum of an empty vector!");
  return *std::max_element(begin(), end());
}
template <FloatingPoint T> mvec<T> mvec<T>::unit() const {
  T mag = magnitude();
  if (mag == T{})
    throw std::domain_error("Cannot normalize a zero vector!");
  return *this / mag;
}
template <FloatingPoint T> void mvec<T>::normalize() { *this = this->unit(); }
template <FloatingPoint T> mvec<T> mvec<T>::cross(const mvec<T> &a) const {
  if (size() != 3 || a.size() != 3)
    throw std::invalid_argument("Cannot compute cross product of non-3D vectors!");
  mvec<T> out(3);
  out.x() = y() * a.z() - z() * a.y();
  out.y() = z() * a.x() - x() * a.z();
  out.z() = x() * a.y() - y() * a.x();
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::abs() const {
  mvec<T> out(size());
  for (std::size_t i = 0; i < size(); ++i) {
    out[i] = std::abs(at(i));
  }
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::floor() const {
  mvec<T> out(size());
  for (std::size_t i = 0; i < size(); ++i) {
    out[i] = std::floor(at(i));
  }
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::ceil() const {
  mvec<T> out(size());
  for (std::size_t i = 0; i < size(); ++i) {
    out[i] = std::ceil(at(i));
  }
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::round() const {
  mvec<T> out(size());
  for (std::size_t i = 0; i < size(); ++i) {
    out[i] = std::round(at(i));
  }
  return out;
}
template <FloatingPoint T> mvec<T> mvec<T>::sqrt() const {
  mvec<T> out(size());
  for (std::size_t i = 0; i < size(); ++i) {
    out[i] = std::sqrt(at(i));
  }
  return out;
}
template <FloatingPoint T> bool mvec<T>::approx_equal_absolute(const mvec<T> &a, T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");
  if (size() != a.size())
    return false;
  for (std::size_t i = 0; i < size(); ++i) {
    T lhs = (*this)[i];
    T rhs = a[i];
    if (std::isnan(lhs) || std::isnan(rhs))
      return false;
    if (lhs == rhs)
      continue;
    if (std::abs(lhs - rhs) > epsilon)
      return false;
  }
  return true;
}
template <FloatingPoint T> bool mvec<T>::approx_equal_relative(const mvec<T> &a, T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");
  if (size() != a.size())
    return false;
  for (std::size_t i = 0; i < size(); ++i) {
    T lhs = (*this)[i];
    T rhs = a[i];
    if (std::isnan(lhs) || std::isnan(rhs))
      return false;
    if (lhs == rhs)
      continue;
    if (std::isinf(lhs) || std::isinf(rhs))
      return false;
    if (std::abs(lhs - rhs) > epsilon * std::max(std::abs(lhs), std::abs(rhs)))
      return false;
  }
  return true;
}
template <FloatingPoint T> bool mvec<T>::has_nan() const {
  return std::any_of(begin(), end(), [](T x) { return std::isnan(x); });
}
template <FloatingPoint T> bool mvec<T>::has_infinity() const {
  return std::any_of(begin(), end(), [](T x) { return std::isinf(x); });
}
template <FloatingPoint T> bool mvec<T>::is_finite() const {
  return std::all_of(begin(), end(), [](T x) { return std::isfinite(x); });
}
template <FloatingPoint T> bool mvec<T>::is_zero() const {
  return std::all_of(begin(), end(), [](T x) { return x == 0; });
}
template <FloatingPoint T> bool mvec<T>::is_near_zero(T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");

  return std::all_of(begin(), end(), [epsilon](T x) { return std::abs(x) <= epsilon; });
}

template <FloatingPoint T> std::ostream &operator<<(std::ostream &os, const mvec<T> &a) {
  os << "{";
  for (std::size_t i = 0; i < a.size(); ++i) {
    os << a[i];
    if (i < a.size() - 1)
      os << ", ";
  }
  os << "}";
  return os;
}
template <FloatingPoint T> mvec<T> operator*(T scalar, const mvec<T> &a) { return a * scalar; }
template <FloatingPoint T> T dot(const mvec<T> &a, const mvec<T> &b) { return a.dot(b); }
template <FloatingPoint T> T sum(const mvec<T> &a) { return a.sum(); }
template <FloatingPoint T> T min(const mvec<T> &a) { return a.min(); }
template <FloatingPoint T> T max(const mvec<T> &a) { return a.max(); }
template <FloatingPoint T> mvec<T> cross(const mvec<T> &a, const mvec<T> &b) { return a.cross(b); }
template <FloatingPoint T> mvec<T> abs(const mvec<T> &a) { return a.abs(); }
template <FloatingPoint T> mvec<T> floor(const mvec<T> &a) { return a.floor(); }
template <FloatingPoint T> mvec<T> ceil(const mvec<T> &a) { return a.ceil(); }
template <FloatingPoint T> mvec<T> round(const mvec<T> &a) { return a.round(); }
template <FloatingPoint T> mvec<T> sqrt(const mvec<T> &a) { return a.sqrt(); }
template <FloatingPoint T> bool approx_equal_absolute(const mvec<T> &a, const mvec<T> &b, T epsilon) {
  return a.approx_equal_absolute(b, epsilon);
}
template <FloatingPoint T> bool approx_equal_relative(const mvec<T> &a, const mvec<T> &b, T epsilon) {
  return a.approx_equal_relative(b, epsilon);
}
template <FloatingPoint T> bool is_nan(T value) { return std::isnan(value); }
template <FloatingPoint T> bool is_infinite(T value) { return std::isinf(value); }
template <FloatingPoint T> bool is_finite(T value) { return std::isfinite(value); }
template <FloatingPoint T> bool has_nan(const mvec<T> &a) { return a.has_nan(); }
template <FloatingPoint T> bool has_infinity(const mvec<T> &a) { return a.has_infinity(); }
template <FloatingPoint T> bool is_finite(const mvec<T> &a) { return a.is_finite(); }
template <FloatingPoint T> bool is_zero(const mvec<T> &a) { return a.is_zero(); }
template <FloatingPoint T> bool is_near_zero(const mvec<T> &a, T epsilon) { return a.is_near_zero(epsilon); }
} // namespace smlib

#endif
