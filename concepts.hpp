#pragma once
#include <concepts>
namespace smlib {
template <typename T>
concept FloatingPoint = std::floating_point<T>;
}
