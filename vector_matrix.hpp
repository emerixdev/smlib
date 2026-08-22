#pragma once
#include "matrix.hpp"

namespace smlib {
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
constexpr mmat<T, 1, N> mvec<T, N>::to_row_mat() const noexcept {
  mmat<T, 1, N> out;
  for (std::size_t i = 0; i < N; ++i) {
    out(0, i) = data_[i];
  }
  return out;
}
template <FloatingPoint T, std::size_t N>
  requires(N > 0)
constexpr mmat<T, N, 1> mvec<T, N>::to_col_mat() const noexcept {
  mmat<T, N, 1> out;
  for (std::size_t i = 0; i < N; ++i) {
    out(i, 0) = data_[i];
  }
  return out;
}
template <FloatingPoint T, std::size_t M, std::size_t N>
  requires(M > 0 && N > 0)
constexpr mvec<T, M> mmat<T, M, N>::to_vec() const noexcept
  requires(N == 1)
{
  mvec<T, M> out;
  for (std::size_t i = 0; i < M; ++i) {
    out[i] = (*this)(0, i);
  }
  return out;
}

} // namespace smlib
