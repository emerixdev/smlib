#ifndef SMLIB_H
#define SMLIB_H
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace smlib {
template <typename T>
concept FloatingPoint = std::floating_point<T>;

template <FloatingPoint T, std::size_t N> class mvec {
private:
  std::array<T, N> data_{};

public:
  constexpr mvec() noexcept = default;
  constexpr explicit mvec(T value) noexcept { std::fill(data_.begin(), data_.end(), value); }
  template <typename... U>
  // variadic constructor, no idea how it works but it works
    requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
  constexpr mvec(U &&...values) noexcept : data_{static_cast<T>(std::forward<U>(values))...} {}

  constexpr T *data() noexcept { return data_.data(); };
  constexpr const T *data() const noexcept { return data_.data(); };
  constexpr T &operator[](std::size_t index) noexcept { return data_[index]; };
  constexpr const T &operator[](std::size_t index) const noexcept { return data_[index]; };
  mvec<T, N> &operator+=(const mvec<T, N> &a);
  mvec<T, N> &operator-=(const mvec<T, N> &a);
  mvec<T, N> &operator*=(T scalar);
  mvec<T, N> &operator/=(T scalar);
  mvec<T, N> operator+(const mvec<T, N> &a) const;
  mvec<T, N> operator-(const mvec<T, N> &a) const;
  mvec<T, N> operator*(T scalar) const;
  mvec<T, N> operator/(T scalar) const;
  mvec<T, N> operator+() const;
  mvec<T, N> operator-() const;
  bool operator==(const mvec<T, N> &a) const;
  bool operator!=(const mvec<T, N> &a) const;
  void fill(T value);
  bool empty() const;
  T &at(std::size_t index);
  const T &at(std::size_t index) const;
  T &x();
  const T &x() const;
  T &y()
    requires(N > 1);
  const T &y() const
    requires(N > 1);
  T &z()
    requires(N > 2);
  const T &z() const
    requires(N > 2);
  constexpr auto begin() noexcept { return data_.begin(); };
  constexpr auto end() noexcept { return data_.end(); };
  constexpr auto begin() const noexcept { return data_.begin(); };
  constexpr auto end() const noexcept { return data_.begin(); };
  constexpr auto cbegin() const noexcept { return data_.cbegin(); };
  constexpr auto cend() const noexcept { return data_.cend(); };
  T dot(const mvec<T, N> &a) const;
  T magnitude() const;
  T magnitude_squared() const;
  T sum() const;
  T min() const;
  T max() const;
  mvec<T, N> unit() const;
  void normalize();
  mvec<T, N> cross(const mvec<T, N> &a) const
    requires(N == 3);
  mvec<T, N> abs() const;
  mvec<T, N> floor() const;
  mvec<T, N> ceil() const;
  mvec<T, N> round() const;
  mvec<T, N> sqrt() const;
  bool approx_equal_absolute(const mvec<T, N> &a, T epsilon) const;
  bool approx_equal_relative(const mvec<T, N> &a, T epsilon) const;
  bool has_nan() const;
  bool has_infinity() const;
  bool is_finite() const;
  bool is_zero() const;
  bool is_near_zero(T epsilon) const;
};
/*
template <FloatingPoint T, std::size_t N> class mmat {
private:
  const std::size_t rows_;
  const std::size_t cols_;
  std::vector<T> data_;

public:
  mmat(std::size_t rows, std::size_t cols);
  mmat(std::size_t rows, std::size_t cols, const T &value);
  mmat(std::initializer_list<std::initializer_list<T>> list);
  T *data();
  const T *data() const;
  T &operator()(std::size_t row, std::size_t col);
  const T &operator()(std::size_t row, std::size_t col) const;
  mmat<T> &operator+=(const mmat<T> &a);
  mmat<T> &operator-=(const mmat<T> &a);
  mmat<T> &operator*=(T scalar);
  mmat<T> &operator/=(T scalar);
  mmat<T> operator+(const mmat<T> &a) const;
  mmat<T> operator-(const mmat<T> &a) const;
  mmat<T> operator*(T scalar) const;
  mmat<T> operator/(T scalar) const;
  mmat<T> operator+() const;
  mmat<T> operator-() const;
  bool operator==(const mmat<T> &a) const;
  bool operator!=(const mmat<T> &a) const;
};*/
template <FloatingPoint T, std::size_t N> mvec<T, N> &mvec<T, N>::operator+=(const mvec<T, N> &a) {
  for (std::size_t i = 0; i < N; ++i) {
    (*this)[i] += a[i];
  }
  return *this;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> &mvec<T, N>::operator-=(const mvec<T, N> &a) {
  for (std::size_t i = 0; i < N; ++i) {
    (*this)[i] -= a[i];
  }
  return *this;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> &mvec<T, N>::operator*=(T scalar) {
  for (auto &it : *this) {
    it *= scalar;
  }
  return *this;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> &mvec<T, N>::operator/=(T scalar) {
  for (auto &it : *this) {
    it /= scalar;
  }
  return *this;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator+(const mvec<T, N> &a) const {
  mvec<T, N> out(*this);
  out += a;
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator-(const mvec<T, N> &a) const {
  mvec<T, N> out(*this);
  out -= a;
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator*(T scalar) const {
  mvec<T, N> out(*this);
  out *= scalar;
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator/(T scalar) const {
  mvec<T, N> out(*this);
  out /= scalar;
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator+() const { return *this; }
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::operator-() const { return (*this) * -1; }
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::operator==(const mvec<T, N> &a) const {
  return data_ == a.data_;
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::operator!=(const mvec<T, N> &a) const {
  return !(*this == a);
}
template <FloatingPoint T, std::size_t N> void mvec<T, N>::fill(T value) { std::fill(begin(), end(), value); }
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::empty() const { return data_.empty(); }
template <FloatingPoint T, std::size_t N> T &mvec<T, N>::at(std::size_t index) { return data_.at(index); }
template <FloatingPoint T, std::size_t N> const T &mvec<T, N>::at(std::size_t index) const { return data_.at(index); }
template <FloatingPoint T, std::size_t N> T &mvec<T, N>::x() { return at(0); }
template <FloatingPoint T, std::size_t N> const T &mvec<T, N>::x() const { return at(0); }
template <FloatingPoint T, std::size_t N>
T &mvec<T, N>::y()
  requires(N > 1)
{
  return at(1);
}
template <FloatingPoint T, std::size_t N>
const T &mvec<T, N>::y() const
  requires(N > 1)
{
  return at(1);
}
template <FloatingPoint T, std::size_t N>
T &mvec<T, N>::z()
  requires(N > 2)
{
  return at(2);
}
template <FloatingPoint T, std::size_t N>
const T &mvec<T, N>::z() const
  requires(N > 2)
{
  return at(2);
}
template <FloatingPoint T, std::size_t N> T mvec<T, N>::dot(const mvec<T, N> &a) const {
  T out = T{0};
  for (std::size_t i = 0; i < N; ++i) {
    out += (*this)[i] * a[i];
  }
  return out;
}
template <FloatingPoint T, std::size_t N> T mvec<T, N>::magnitude() const {
  T out = T{0};
  for (auto x : *this) {
    out = std::hypot(out, x);
  }
  return out;
}
template <FloatingPoint T, std::size_t N> T mvec<T, N>::magnitude_squared() const { return dot(*this); }
template <FloatingPoint T, std::size_t N> T mvec<T, N>::sum() const {
  T out = T{0};
  for (auto x : *this) {
    out += x;
  }
  return out;
}
template <FloatingPoint T, std::size_t N> T mvec<T, N>::min() const {
  if (empty())
    throw std::domain_error("Cannot find minimum of an empty vector!");
  return *std::min_element(begin(), end());
}
template <FloatingPoint T, std::size_t N> T mvec<T, N>::max() const {
  if (empty())
    throw std::domain_error("Cannot find maximum of an empty vector!");
  return *std::max_element(begin(), end());
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::unit() const {
  T mag = magnitude();
  if (mag == T{})
    throw std::domain_error("Cannot normalize a zero vector!");
  return *this / mag;
}
template <FloatingPoint T, std::size_t N> void mvec<T, N>::normalize() { *this = this->unit(); }
template <FloatingPoint T, std::size_t N>
mvec<T, N> mvec<T, N>::cross(const mvec<T, N> &a) const
  requires(N == 3)
{
  mvec<T, N> out;
  out.x() = y() * a.z() - z() * a.y();
  out.y() = z() * a.x() - x() * a.z();
  out.z() = x() * a.y() - y() * a.x();
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::abs() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::abs(at(i));
  }
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::floor() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::floor(at(i));
  }
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::ceil() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::ceil(at(i));
  }
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::round() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::round(at(i));
  }
  return out;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> mvec<T, N>::sqrt() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::sqrt(at(i));
  }
  return out;
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::approx_equal_absolute(const mvec<T, N> &a, T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");
  for (std::size_t i = 0; i < N; ++i) {
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
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::approx_equal_relative(const mvec<T, N> &a, T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");
  for (std::size_t i = 0; i < N; ++i) {
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
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::has_nan() const {
  return std::any_of(begin(), end(), [](T x) { return std::isnan(x); });
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::has_infinity() const {
  return std::any_of(begin(), end(), [](T x) { return std::isinf(x); });
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::is_finite() const {
  return std::all_of(begin(), end(), [](T x) { return std::isfinite(x); });
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::is_zero() const {
  return std::all_of(begin(), end(), [](T x) { return x == 0; });
}
template <FloatingPoint T, std::size_t N> bool mvec<T, N>::is_near_zero(T epsilon) const {
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");

  return std::all_of(begin(), end(), [epsilon](T x) { return std::abs(x) <= epsilon; });
}

template <FloatingPoint T, std::size_t N> std::ostream &operator<<(std::ostream &os, const mvec<T, N> &a) {
  os << "{";
  for (std::size_t i = 0; i < N; ++i) {
    os << a[i];
    if (i < N - 1)
      os << ", ";
  }
  os << "}";
  return os;
}
template <FloatingPoint T, std::size_t N> mvec<T, N> operator*(T scalar, const mvec<T, N> &a) { return a * scalar; }
template <FloatingPoint T, std::size_t N> T dot(const mvec<T, N> &a, const mvec<T, N> &b) { return a.dot(b); }
template <FloatingPoint T, std::size_t N> T sum(const mvec<T, N> &a) { return a.sum(); }
template <FloatingPoint T, std::size_t N> T min(const mvec<T, N> &a) { return a.min(); }
template <FloatingPoint T, std::size_t N> T max(const mvec<T, N> &a) { return a.max(); }
template <FloatingPoint T, std::size_t N> mvec<T, N> cross(const mvec<T, N> &a, const mvec<T, N> &b) {
  return a.cross(b);
}
template <FloatingPoint T, std::size_t N> mvec<T, N> abs(const mvec<T, N> &a) { return a.abs(); }
template <FloatingPoint T, std::size_t N> mvec<T, N> floor(const mvec<T, N> &a) { return a.floor(); }
template <FloatingPoint T, std::size_t N> mvec<T, N> ceil(const mvec<T, N> &a) { return a.ceil(); }
template <FloatingPoint T, std::size_t N> mvec<T, N> round(const mvec<T, N> &a) { return a.round(); }
template <FloatingPoint T, std::size_t N> mvec<T, N> sqrt(const mvec<T, N> &a) { return a.sqrt(); }
template <FloatingPoint T, std::size_t N>
bool approx_equal_absolute(const mvec<T, N> &a, const mvec<T, N> &b, T epsilon) {
  return a.approx_equal_absolute(b, epsilon);
}
template <FloatingPoint T, std::size_t N>
bool approx_equal_relative(const mvec<T, N> &a, const mvec<T, N> &b, T epsilon) {
  return a.approx_equal_relative(b, epsilon);
}
template <FloatingPoint T> bool is_nan(T value) { return std::isnan(value); }
template <FloatingPoint T> bool is_infinite(T value) { return std::isinf(value); }
template <FloatingPoint T> bool is_finite(T value) { return std::isfinite(value); }
template <FloatingPoint T, std::size_t N> bool has_nan(const mvec<T, N> &a) { return a.has_nan(); }
template <FloatingPoint T, std::size_t N> bool has_infinity(const mvec<T, N> &a) { return a.has_infinity(); }
template <FloatingPoint T, std::size_t N> bool is_finite(const mvec<T, N> &a) { return a.is_finite(); }
template <FloatingPoint T, std::size_t N> bool is_zero(const mvec<T, N> &a) { return a.is_zero(); }
template <FloatingPoint T, std::size_t N> bool is_near_zero(const mvec<T, N> &a, T epsilon) {
  return a.is_near_zero(epsilon);
}
} // namespace smlib

#endif
