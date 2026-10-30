#pragma once
#include "concepts.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <format>
#include <iomanip>
#include <ios>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace smlib {
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
class mmat;
template <Arithmetic T, std::size_t N>
  requires(N > 0)
class mvec {
private:
  std::array<T, N> data_{};

public:
  constexpr mvec() noexcept = default;
  constexpr explicit mvec(T value) noexcept { std::fill(data_.begin(), data_.end(), value); }
  // variadic constructor, no idea how it works but it works
  template <typename... U>
    requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
  constexpr mvec(U &&...values) noexcept : data_{static_cast<T>(std::forward<U>(values))...} {}

  constexpr T *data() noexcept { return data_.data(); }
  constexpr const T *data() const noexcept { return data_.data(); }
  constexpr T &operator[](std::size_t index) noexcept { return data_[index]; }
  constexpr const T &operator[](std::size_t index) const noexcept { return data_[index]; }
  constexpr T &at(std::size_t index) { return data_.at(index); }
  constexpr const T &at(std::size_t index) const { return data_.at(index); };
  constexpr auto begin() noexcept { return data_.begin(); }
  constexpr auto end() noexcept { return data_.end(); }
  constexpr auto begin() const noexcept { return data_.begin(); }
  constexpr auto end() const noexcept { return data_.end(); }
  constexpr auto cbegin() const noexcept { return data_.cbegin(); }
  constexpr auto cend() const noexcept { return data_.cend(); }
  constexpr auto rbegin() noexcept { return data_.rbegin(); }
  constexpr auto rend() noexcept { return data_.rend(); }
  constexpr auto rbegin() const noexcept { return data_.rbegin(); }
  constexpr auto rend() const noexcept { return data_.rend(); }
  constexpr auto crbegin() const noexcept { return data_.crbegin(); }
  constexpr auto crend() const noexcept { return data_.crend(); }
  constexpr mvec<T, N> &operator+=(const mvec<T, N> &a) noexcept;
  constexpr mvec<T, N> &operator-=(const mvec<T, N> &a) noexcept;
  constexpr mvec<T, N> &operator*=(T scalar) noexcept;
  constexpr mvec<T, N> &operator/=(T scalar) noexcept;
  constexpr mvec<T, N> operator+(const mvec<T, N> &a) const noexcept;
  constexpr mvec<T, N> operator-(const mvec<T, N> &a) const noexcept;
  constexpr mvec<T, N> operator*(T scalar) const noexcept;
  constexpr mvec<T, N> operator/(T scalar) const noexcept;
  constexpr mvec<T, N> operator+() const noexcept { return *this; }
  constexpr mvec<T, N> operator-() const noexcept { return *this * T{-1}; }
  constexpr bool operator==(const mvec<T, N> &a) const noexcept { return data_ == a.data_; }
  constexpr bool operator!=(const mvec<T, N> &a) const noexcept { return data_ != a.data_; }
  constexpr std::size_t size() const noexcept { return N; }
  constexpr void fill(T value) noexcept { std::fill(begin(), end(), value); }
  constexpr T &x() noexcept { return data_[0]; }
  constexpr const T &x() const noexcept { return data_[0]; }
  constexpr T &y() noexcept
    requires(N >= 2)
  {
    return data_[1];
  }
  constexpr const T &y() const noexcept
    requires(N >= 2)
  {
    return data_[1];
  }
  constexpr T &z() noexcept
    requires(N >= 3)
  {
    return data_[2];
  }
  constexpr const T &z() const noexcept
    requires(N >= 3)
  {
    return data_[2];
  }
  constexpr T &w() noexcept
    requires(N >= 4)
  {
    return data_[3];
  }
  constexpr const T &w() const noexcept
    requires(N >= 4)
  {
    return data_[3];
  }
  constexpr T dot(const mvec<T, N> &a) const noexcept;
  T magnitude() const noexcept
    requires std::floating_point<T>;
  constexpr T magnitude_squared() const noexcept { return dot(*this); };
  constexpr T sum() const noexcept;
  constexpr T min() const noexcept { return *std::min_element(begin(), end()); }
  constexpr T max() const noexcept { return *std::max_element(begin(), end()); }
  mvec<T, N> unit() const
    requires std::floating_point<T>;
  void normalize()
    requires std::floating_point<T>
  {
    *this = unit();
  }
  constexpr mvec<T, N> cross(const mvec<T, N> &a) const noexcept
    requires(N == 3);
  mvec<T, N> abs() const;
  mvec<T, N> floor() const noexcept
    requires std::floating_point<T>;
  mvec<T, N> ceil() const noexcept
    requires std::floating_point<T>;
  mvec<T, N> round() const noexcept
    requires std::floating_point<T>;
  mvec<T, N> sqrt() const noexcept
    requires std::floating_point<T>;
  bool approx_equal(const mvec<T, N> &a, T epsilon) const
    requires std::floating_point<T>;
  bool has_nan() const noexcept
    requires std::floating_point<T>;
  bool has_infinity() const noexcept
    requires std::floating_point<T>;
  bool is_finite() const noexcept
    requires std::floating_point<T>;
  constexpr bool is_zero() const noexcept;
  bool is_near_zero(T epsilon) const
    requires std::floating_point<T>;
  constexpr mmat<T, 1, N> to_row_mat() const noexcept;
  constexpr mmat<T, N, 1> to_col_mat() const noexcept;
  std::string to_string(bool pretty = 1, int floating_points = -1) const noexcept;
};

template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> &mvec<T, N>::operator+=(const mvec<T, N> &a) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    (*this)[i] += a[i];
  }
  return *this;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> &mvec<T, N>::operator-=(const mvec<T, N> &a) noexcept {
  for (std::size_t i = 0; i < N; ++i) {
    (*this)[i] -= a[i];
  }
  return *this;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> &mvec<T, N>::operator*=(T scalar) noexcept {
  for (auto &it : *this) {
    it *= scalar;
  }
  return *this;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> &mvec<T, N>::operator/=(T scalar) noexcept {
  for (auto &it : *this) {
    it /= scalar;
  }
  return *this;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> mvec<T, N>::operator+(const mvec<T, N> &a) const noexcept {
  mvec<T, N> out(*this);
  out += a;
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> mvec<T, N>::operator-(const mvec<T, N> &a) const noexcept {
  mvec<T, N> out(*this);
  out -= a;
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> mvec<T, N>::operator*(T scalar) const noexcept {
  mvec<T, N> out(*this);
  out *= scalar;
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> mvec<T, N>::operator/(T scalar) const noexcept {
  mvec<T, N> out(*this);
  out /= scalar;
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T mvec<T, N>::dot(const mvec<T, N> &a) const noexcept {
  T out = T{0};
  for (std::size_t i = 0; i < N; ++i) {
    out += (*this)[i] * a[i];
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
T mvec<T, N>::magnitude() const noexcept
  requires std::floating_point<T>
{
  T out = T{0};
  for (auto x : *this) {
    out = std::hypot(out, x);
  }
  return out;
}

template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T mvec<T, N>::sum() const noexcept {
  T out = T{0};
  for (auto x : *this) {
    out += x;
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::unit() const
  requires std::floating_point<T>
{
  T mag = magnitude();
  if (mag == 0)
    throw std::domain_error("Cannot normalize a zero vector!");
  if (!std::isfinite(mag))
    throw std::domain_error("Cannot normalize a non-finite vector!");
  return *this / mag;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> mvec<T, N>::cross(const mvec<T, N> &a) const noexcept
  requires(N == 3)
{
  mvec<T, N> out;
  out.x() = y() * a.z() - z() * a.y();
  out.y() = z() * a.x() - x() * a.z();
  out.z() = x() * a.y() - y() * a.x();
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::abs() const {
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::abs(data_[i]);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::floor() const noexcept
  requires std::floating_point<T>
{
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::floor(data_[i]);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::ceil() const noexcept
  requires std::floating_point<T>
{
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::ceil(data_[i]);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::round() const noexcept
  requires std::floating_point<T>
{
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::round(data_[i]);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> mvec<T, N>::sqrt() const noexcept
  requires std::floating_point<T>
{
  mvec<T, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out[i] = std::sqrt(data_[i]);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
bool mvec<T, N>::approx_equal(const mvec<T, N> &a, T epsilon) const
  requires std::floating_point<T>
{
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
template <Arithmetic T, std::size_t N>
  requires(N > 0)
bool mvec<T, N>::has_nan() const noexcept
  requires std::floating_point<T>
{
  return std::any_of(begin(), end(), [](T x) { return std::isnan(x); });
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
bool mvec<T, N>::has_infinity() const noexcept
  requires std::floating_point<T>
{
  return std::any_of(begin(), end(), [](T x) { return std::isinf(x); });
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
bool mvec<T, N>::is_finite() const noexcept
  requires std::floating_point<T>
{
  return std::all_of(begin(), end(), [](T x) { return std::isfinite(x); });
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr bool mvec<T, N>::is_zero() const noexcept {
  return std::all_of(begin(), end(), [](T x) { return x == 0; });
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
bool mvec<T, N>::is_near_zero(T epsilon) const
  requires std::floating_point<T>
{
  if (epsilon < T{0})
    throw std::invalid_argument("Epsilon cannot be negative!");
  return std::all_of(begin(), end(), [epsilon](T x) { return std::abs(x) <= epsilon; });
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
std::string mvec<T, N>::to_string(bool pretty, int floating_points) const noexcept {
  std::stringstream ss;
  if (pretty) {
    ss << "{";
    for (std::size_t i = 0; i < N; ++i) {
      if (floating_points >= 0)
        ss << std::fixed << std::setprecision(floating_points) << (*this)[i];
      else
        ss << (*this)[i];
      if (i < N - 1)
        ss << ", ";
    }
    ss << "}";
  } else {
    for (std::size_t i = 0; i < N; ++i) {
      if (floating_points >= 0)
        ss << std::fixed << std::setprecision(floating_points) << (*this)[i];
      else
        ss << (*this)[i];
      if (i < N - 1)
        ss << " ";
    }
  }
  return ss.str();
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
std::ostream &operator<<(std::ostream &os, const mvec<T, N> &a) {
  os << "{";
  for (std::size_t i = 0; i < N; ++i) {
    os << a[i];
    if (i < N - 1)
      os << ", ";
  }
  os << "}";
  return os;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> operator*(T scalar, const mvec<T, N> &a) {
  return a * scalar;
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T dot(const mvec<T, N> &a, const mvec<T, N> &b) {
  return a.dot(b);
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T sum(const mvec<T, N> &a) {
  return a.sum();
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T min(const mvec<T, N> &a) {
  return a.min();
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr T max(const mvec<T, N> &a) {
  return a.max();
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr mvec<T, N> cross(const mvec<T, N> &a, const mvec<T, N> &b) {
  return a.cross(b);
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
mvec<T, N> abs(const mvec<T, N> &a) {
  return a.abs();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
mvec<T, N> floor(const mvec<T, N> &a) {
  return a.floor();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
mvec<T, N> ceil(const mvec<T, N> &a) {
  return a.ceil();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
mvec<T, N> round(const mvec<T, N> &a) {
  return a.round();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
mvec<T, N> sqrt(const mvec<T, N> &a) {
  return a.sqrt();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
bool approx_equal(const mvec<T, N> &a, const mvec<T, N> &b, T epsilon) {
  return a.approx_equal(b, epsilon);
}
template <FloatingPoint T> bool is_nan(T value) { return std::isnan(value); }
template <FloatingPoint T> bool is_infinite(T value) { return std::isinf(value); }
template <FloatingPoint T> bool is_finite(T value) { return std::isfinite(value); }
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
bool has_nan(const mvec<T, N> &a) {
  return a.has_nan();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
bool has_infinity(const mvec<T, N> &a) {
  return a.has_infinity();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
bool is_finite(const mvec<T, N> &a) {
  return a.is_finite();
}
template <Arithmetic T, std::size_t N>
  requires(N > 0)
constexpr bool is_zero(const mvec<T, N> &a) {
  return a.is_zero();
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
bool is_near_zero(const mvec<T, N> &a, T epsilon) {
  return a.is_near_zero(epsilon);
}
} // namespace smlib
