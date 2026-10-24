#pragma once
#include "concepts.hpp"
#include "vector.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
namespace smlib {

template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
class mmat {
private:
  std::array<T, M * N> data_{};

public:
  using value_type = T;
  using size_type = std::size_t;
  using iterator = typename std::array<T, M * N>::iterator;
  using const_iterator = typename std::array<T, M * N>::const_iterator;
  constexpr mmat() noexcept = default;
  constexpr explicit mmat(T value) noexcept { std::fill(data_.begin(), data_.end(), value); }
  constexpr mmat(std::initializer_list<std::initializer_list<T>> list) : data_{} {
    if (list.size() != M)
      throw std::invalid_argument("Incorrect number of rows!");
    std::size_t row = 0;
    for (const auto &r : list) {
      if (r.size() != N)
        throw std::invalid_argument("Incorrect number of cols!");
      std::size_t col = 0;
      for (auto c : r) {
        data_[row * N + (col++)] = c;
      }
      row++;
    }
  }
  static constexpr std::size_t rows = M;
  static constexpr std::size_t cols = N;
  constexpr T *data() noexcept { return data_.data(); }
  constexpr const T *data() const noexcept { return data_.data(); }
  constexpr std::array<T, M * N> &array() noexcept { return data_; }
  constexpr const std::array<T, M * N> &array() const noexcept { return data_; }
  constexpr T &operator[](std::size_t index) noexcept { return data_[index]; }
  constexpr const T &operator[](std::size_t index) const noexcept { return data_[index]; }
  constexpr T &at(std::size_t index) { return data_.at(index); }
  constexpr const T &at(std::size_t index) const { return data_.at(index); }
  constexpr T &at(std::size_t row, std::size_t col);
  constexpr const T &at(std::size_t row, std::size_t col) const;
  constexpr T &operator()(std::size_t row, std::size_t col) noexcept { return data_[row * N + col]; }
  constexpr const T &operator()(std::size_t row, std::size_t col) const noexcept { return data_[row * N + col]; }
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
  constexpr T &front() noexcept { return data_.front(); }
  constexpr const T &front() const noexcept { return data_.front(); }
  constexpr T &back() noexcept { return data_.back(); }
  constexpr const T &back() const noexcept { return data_.back(); }
  constexpr void swap(mmat &a) noexcept { data_.swap(a.data_); }
  constexpr mvec<T, N> row(std::size_t row) const;
  constexpr mvec<T, M> col(std::size_t column) const;
  constexpr mmat<T, M, N> &operator+=(const mmat<T, M, N> &a) noexcept;
  constexpr mmat<T, M, N> &operator-=(const mmat<T, M, N> &a) noexcept;
  constexpr mmat<T, M, N> &operator*=(T scalar) noexcept;
  constexpr mmat<T, M, N> &operator/=(T scalar);
  constexpr mmat<T, M, N> operator+(const mmat<T, M, N> &a) const noexcept;
  constexpr mmat<T, M, N> operator-(const mmat<T, M, N> &a) const noexcept;
  constexpr mmat<T, M, N> operator*(T scalar) const noexcept;
  constexpr mmat<T, M, N> operator/(T scalar) const;
  constexpr mmat<T, M, N> operator+() const noexcept { return *this; }
  constexpr mmat<T, M, N> operator-() const noexcept { return *this * T{-1}; }
  constexpr bool operator==(const mmat<T, M, N> &a) const noexcept { return data_ == a.data_; }
  constexpr bool operator!=(const mmat<T, M, N> &a) const noexcept { return data_ != a.data_; }
  template <std::size_t P> constexpr mmat<T, M, P> operator*(const mmat<T, N, P> &a) const noexcept;
  // constexpr mvec<T, M> operator*(const mvec<T, N> &a) const noexcept;
  template <Arithmetic U> constexpr mvec<std::common_type_t<T, U>, M> operator*(const mvec<U, N> &a) const noexcept;
  constexpr std::size_t size() const noexcept { return data_.size(); }
  constexpr void fill(T value) noexcept { std::fill(begin(), end(), value); }
  bool approx_equal(const mmat<T, M, N> &a, T epsilon) const
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
  constexpr mmat<T, N, M> transpose() const noexcept;
  constexpr mvec<T, M> to_vec() const noexcept
    requires(N == 1);
};
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr T &mmat<T, M, N>::at(std::size_t row, std::size_t col) {
  if (row >= M || col >= N)
    throw std::out_of_range("row or col out of range: mmat::at(row, col)!");
  return data_[row * N + col];
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr const T &mmat<T, M, N>::at(std::size_t row, std::size_t col) const {
  if (row >= M || col >= N)
    throw std::out_of_range("row or col out of range: mmat::at(row, col)!");
  return data_[row * N + col];
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mvec<T, N> mmat<T, M, N>::row(std::size_t row) const {
  if (row >= M)
    throw std::out_of_range("row out of range: mmat::row(row)!");
  mvec<T, N> out;
  for (std::size_t col = 0; col < N; col++) {
    out[col] = (*this)(row, col);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mvec<T, M> mmat<T, M, N>::col(std::size_t col) const {
  if (col >= N)
    throw std::out_of_range("col out of range: mmat::col(col)!");
  mvec<T, M> out;
  for (std::size_t row = 0; row < M; row++) {
    out[row] = (*this)(row, col);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator+=(const mmat<T, M, N> &a) noexcept {
  for (std::size_t i = 0; i < size(); ++i) {
    data_[i] += a.data_[i];
  }
  return *this;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator-=(const mmat<T, M, N> &a) noexcept {
  for (std::size_t i = 0; i < size(); ++i) {
    data_[i] -= a.data_[i];
  }
  return *this;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator*=(T scalar) noexcept {
  for (auto &it : (*this)) {
    it *= scalar;
  }
  return *this;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator/=(T scalar) {
  for (auto &it : (*this)) {
    it /= scalar;
  }
  return *this;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator+(const mmat<T, M, N> &a) const noexcept {
  mmat<T, M, N> out = *this;
  out += a;
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator-(const mmat<T, M, N> &a) const noexcept {
  mmat<T, M, N> out = *this;
  out -= a;
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator*(T scalar) const noexcept {
  mmat<T, M, N> out = *this;
  out *= scalar;
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator/(T scalar) const {
  mmat<T, M, N> out = *this;
  out /= scalar;
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
template <std::size_t P>
constexpr mmat<T, M, P> mmat<T, M, N>::operator*(const mmat<T, N, P> &a) const noexcept {
  mmat<T, M, P> out;
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t k = 0; k < N; ++k) {
      for (std::size_t j = 0; j < P; ++j) {
        out(i, j) += (*this)(i, k) * a(k, j);
      }
    }
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
template <Arithmetic U>
constexpr mvec<std::common_type_t<T, U>, M> mmat<T, M, N>::operator*(const mvec<U, N> &a) const noexcept {
  using R = std::common_type_t<T, U>;

  mvec<R, M> out;
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t k = 0; k < N; ++k) {
      out[i] += static_cast<R>((*this)(i, k)) * static_cast<R>(a[k]);
    }
  }
  return out;
}
// template <Arithmetic T, std::size_t M, std::size_t N>
//   requires(M > 0 && N > 0)
// constexpr mvec<T, M> mmat<T, M, N>::operator*(const mvec<T, N> &a) const noexcept {
//   mvec<T, M> out;
//   for (std::size_t i = 0; i < M; ++i) {
//     for (std::size_t k = 0; k < N; ++k) {
//       out[i] += (*this)(i, k) * a[k];
//     }
//   }
//   return out;
// }
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
bool mmat<T, M, N>::approx_equal(const mmat<T, M, N> &a, T epsilon) const
  requires std::floating_point<T>
{
  if (epsilon < T{0} || std::isnan(epsilon))
    throw std::invalid_argument("Invalid epsilon!");
  for (std::size_t i = 0; i < size(); ++i) {
    T lhs = (*this)[i];
    T rhs = a[i];
    if (lhs == rhs)
      continue;
    if (!std::isfinite(lhs) || !std::isfinite(rhs))
      return false;
    if (std::abs(lhs - rhs) > epsilon * std::max(T{1}, std::max(std::abs(lhs), std::abs(rhs))))
      return false;
  }
  return true;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
bool mmat<T, M, N>::has_nan() const noexcept
  requires std::floating_point<T>
{
  return std::any_of(begin(), end(), [](T x) { return std::isnan(x); });
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
bool mmat<T, M, N>::has_infinity() const noexcept
  requires std::floating_point<T>
{
  return std::any_of(begin(), end(), [](T x) { return std::isinf(x); });
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
bool mmat<T, M, N>::is_finite() const noexcept
  requires std::floating_point<T>
{
  return std::all_of(begin(), end(), [](T x) { return std::isfinite(x); });
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr bool mmat<T, M, N>::is_zero() const noexcept {
  return std::all_of(begin(), end(), [](T x) { return x == 0; });
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
bool mmat<T, M, N>::is_near_zero(T epsilon) const
  requires std::floating_point<T>
{
  if (epsilon < T{0} || std::isnan(epsilon))
    throw std::invalid_argument("Invalid epsilon!");
  return std::all_of(begin(), end(), [epsilon](T x) { return std::abs(x) <= epsilon; });
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, N, M> mmat<T, M, N>::transpose() const noexcept {
  mmat<T, N, M> out;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < M; j++) {
      out(i, j) = (*this)(j, i);
    }
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
std::ostream &operator<<(std::ostream &os, const mmat<T, M, N> &a) {
  os << "{";
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < N; j++) {
      os << a(i, j);
      if (j < N - 1)
        os << ", ";
    }
    if (i < M - 1)
      os << ",\n";
  }
  os << "}";
  return os;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> operator*(T scalar, const mmat<T, M, N> &a) {
  return a * scalar;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> abs_ew(const mmat<T, M, N> &a) {
  mmat<T, M, N> out = a;
  for (auto &it : out) {
    it = std::abs(it);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> floor_ew(const mmat<T, M, N> &a)
  requires std::floating_point<T>
{
  mmat<T, M, N> out = a;
  for (auto &it : out) {
    it = std::floor(it);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> ceil_ew(const mmat<T, M, N> &a)
  requires std::floating_point<T>
{
  mmat<T, M, N> out = a;
  for (auto &it : out) {
    it = std::ceil(it);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> round_ew(const mmat<T, M, N> &a)
  requires std::floating_point<T>
{
  mmat<T, M, N> out = a;
  for (auto &it : out) {
    it = std::round(it);
  }
  return out;
}
template <Arithmetic T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> sqrt_ew(const mmat<T, M, N> &a)
  requires std::floating_point<T>
{
  mmat<T, M, N> out = a;
  for (auto &it : out) {
    it = std::sqrt(it);
  }
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 1)
mmat<T, N, N> gen_identity_mat() {
  mmat<T, N, N> out(0);
  for (std::size_t i = 0; i < N; ++i)
    out(i, i) = 1;
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 1)
mmat<T, N, N> gen_translation_mat(mvec<T, N - 1> vec) {
  mmat<T, N, N> out = gen_identity_mat<T, N>();
  for (std::size_t i = 0; i < N - 1; ++i)
    out(i, N - 1) = vec[i];
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 1)
mmat<T, N, N> gen_scaling_mat(mvec<T, N - 1> vec) {
  mmat<T, N, N> out = gen_identity_mat<T, N>();
  for (std::size_t i = 0; i < N - 1; ++i)
    out(i, i) = vec[i];
  return out;
}
template <Arithmetic T, std::size_t N>
  requires(N > 1)
mmat<T, N, N> gen_rotation_mat(float theta, mvec<T, N - 1> rotation_axis) {
  mmat<T, N, N> out = gen_identity_mat<T, N>();
  //R_x
  mmat<T, N, N> rot_x = gen_identity_mat<T, N>();
  rot_x(1, 1)=cos(theta);
  rot_x(2, 1)=sin(theta);
  rot_x(1, 2)=-sin(theta);
  rot_x(2, 2)=cos(theta);
  return rot_x;
}
} // namespace smlib
