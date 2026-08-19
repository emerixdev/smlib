#pragma once
#include "concepts.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
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
  constexpr T *data() noexcept { return data_.data(); }
  constexpr const T *data() const noexcept { return data_.data(); }
  constexpr T &operator[](std::size_t index) noexcept { return data_[index]; }
  constexpr const T &operator[](std::size_t index) const noexcept { return data_[index]; }
  constexpr T &at(std::size_t index) noexcept { return data_.at(index); }
  constexpr const T &at(std::size_t index) const noexcept { return data_.at(index); }
  constexpr T &at(std::size_t row, std::size_t col) noexcept { return data_.at(row * N + col); }
  constexpr const T &at(std::size_t row, std::size_t col) const noexcept { return data_.at(row * N + col); }
  constexpr T &operator()(std::size_t row, std::size_t col) noexcept { return data_[row * N + col]; }
  constexpr const T &operator()(std::size_t m, std::size_t n) const noexcept { return data_[m * N + n]; }
  /* constexpr mmat<T, M, N> &operator+=(const mmat<T, M, N> &a) noexcept;
   constexpr mmat<T, M, N> &operator-=(const mmat<T, M, N> &a) noexcept;
   */
};
/*
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mmat<T, M, N> &mmat<T, M, N>::operator+=(const mmat<T, M, N> &a) noexcept {
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
    }
  }
}
*/
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

} // namespace smlib
