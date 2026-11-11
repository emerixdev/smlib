#include "matrix.hpp"
#include "vector.hpp"
#include "vector_matrix.hpp"
#include <assert.h>
#include <iostream>
#include <numbers>
int main(int argc, char *argv[]) {
  smlib::mvec<float, 4> vec({1, 2, 4, 1});
  vec *= 1.714445;
  std::cout << vec << "\n";
  std::cout << vec+2 << "\n";
  std::cout << vec-4.154 << "\n";
  vec-=2;
  std::cout << vec << "\n";

  

  return 0;
}
