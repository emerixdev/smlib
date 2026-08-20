#pragma once
#include "concepts.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>
namespace smlib {

template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
class mmat {
private:
  std::array<T, M * N> data_{};

public:
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
  constexpr T &operator[](std::size_t index) noexcept { return data_[index]; }
  constexpr const T &operator[](std::size_t index) const noexcept { return data_[index]; }
  constexpr T &at(std::size_t index) { return data_.at(index); }
  constexpr const T &at(std::size_t index) const { return data_.at(index); }
  constexpr T &at(std::size_t row, std::size_t col) { return data_.at(row * N + col); }
  constexpr const T &at(std::size_t row, std::size_t col) const { return data_.at(row * N + col); }
  constexpr T &operator()(std::size_t row, std::size_t col) noexcept { return data_[row * N + col]; }
  constexpr const T &operator()(std::size_t m, std::size_t n) const noexcept { return data_[m * N + n]; }
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
  constexpr mmat<T, M, N> &operator+=(const mmat<T, M, N> &a) noexcept;
  constexpr mmat<T, M, N> &operator-=(const mmat<T, M, N> &a) noexcept;
  constexpr mmat<T, M, N> &operator*=(T scalar) noexcept;
  constexpr mmat<T, M, N> &operator/=(T scalar) noexcept;
  constexpr mmat<T, M, N> operator+(const mmat<T, M, N> &a) const noexcept;
  constexpr mmat<T, M, N> operator-(const mmat<T, M, N> &a) const noexcept;
  constexpr mmat<T, M, N> operator*(T scalar) const noexcept;
  constexpr mmat<T, M, N> operator/(T scalar) const noexcept;
  constexpr mmat<T, M, N> operator+() const noexcept { return *this; }
  constexpr mmat<T, M, N> operator-() const noexcept { return *this * T{-1}; }
  constexpr bool operator==(const mmat<T, M, N> &a) const noexcept { return data_ == a.data_; }
  constexpr bool operator!=(const mmat<T, M, N> &a) const noexcept { return data_ != a.data_; }
  constexpr std::size_t size() const noexcept { return N * M; }
  constexpr void fill(T value) noexcept { std::fill(begin(), end(), value); }
  mmat<T, M, N> abs() const noexcept;
  mmat<T, M, N> floor() const noexcept;
  mmat<T, M, N> ceil() const noexcept;
  mmat<T, M, N> round() const noexcept;
  mmat<T, M, N> sqrt() const noexcept;
  bool approx_equal(const mmat<T, M, N> &a, T epsilon) const;
  bool has_nan() const noexcept;
  bool has_infinity() const noexcept;
  bool is_finite() const noexcept;
  constexpr bool is_zero() const noexcept;
  bool is_near_zero(T epsilon) const;
};
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator+=(const mmat<T, M, N> &a) noexcept {
  for (std::size_t i = 0; i < size(); ++i) {
    data_[i] += data_[i];
  }
  return *this;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator-=(const mmat<T, M, N> &a) noexcept {
  for (std::size_t i = 0; i < size(); ++i) {
    data_[i] -= data_[i];
  }
  return *this;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator*=(T scalar) noexcept {
  for (auto &it : (*this)) {
    it *= scalar;
  }
  return *this;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator/=(T scalar) noexcept {
  for (auto &it : (*this)) {
    it /= scalar;
  }
  return *this;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator+(const mmat<T, M, N> &a) const noexcept {
  mmat<T, M, N> out = *this;
  out += a;
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator-(const mmat<T, M, N> &a) const noexcept {
  mmat<T, M, N> out = *this;
  out -= a;
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator*(T scalar) const noexcept {
  mmat<T, M, N> out = *this;
  out *= scalar;
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> mmat<T, M, N>::operator/(T scalar) const noexcept {
  mmat<T, M, N> out = *this;
  out /= scalar;
  return out;
}

template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> mmat<T, M, N>::abs() const noexcept {
  mmat<T, M, N> out = (*this);
  for (auto &it : out) {
    it = std::abs(it);
  }
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> mmat<T, M, N>::floor() const noexcept {
  mmat<T, M, N> out = (*this);
  for (auto &it : out) {
    it = std::floor(it);
  }
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> mmat<T, M, N>::ceil() const noexcept {
  mmat<T, M, N> out = (*this);
  for (auto &it : out) {
    it = std::ceil(it);
  }
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> mmat<T, M, N>::round() const noexcept {
  mmat<T, M, N> out = (*this);
  for (auto &it : out) {
    it = std::round(it);
  }
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
mmat<T, M, N> mmat<T, M, N>::sqrt() const noexcept {
  mmat<T, M, N> out = (*this);
  for (auto &it : out) {
    it = std::sqrt(it);
  }
  return out;
}

template <FloatingPoint T, std::size_t M, std::size_t N>
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

template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> operator*(T scalar, mmat<T, M, N> &a) {
  return a * scalar;
}
} // namespace smlib
