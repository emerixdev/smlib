#include "vector.hpp"
#include "vector_matrix.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<float, 3, 2> a{{{1.f, 2.f}, {3, 4}, {5.f, 6.f}}};
  smlib::mvec<float, 2> b({2.2, 4.7});
  std::cout << a << "\n";
  std::cout << b << "\n";
  std::cout << a * b << "\n";
  return 0;
}
