#include "matrix.hpp"
#include "smlib.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<float, 3, 2> a{{{1.f, 2.f}, {3, 4}, {5.f, 6.f}}};
  smlib::mmat<float, 2, 4> b{{{4, 7, 2, 9}, {-3, 3, 0.5, 9.2}}};
  std::cout << a << "\n";
  std::cout << b << "\n";
  std::cout << a * b << "\n";
  return 0;
}
