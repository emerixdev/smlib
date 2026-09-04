#pragma once
#include <concepts>
namespace smlib {
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;
template <typename T>
concept FloatingPoint = std::floating_point<T>;
}
