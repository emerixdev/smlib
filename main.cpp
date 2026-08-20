#include "matrix.hpp"
#include "smlib.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<float, 2, 2> a{{{1.f, 2.f}, {4.f, 5.f}}};
  smlib::mmat<float, 2, 2> b{{{0.1, 0.2}, {0.3, 0.4}}};
  std::cout << a << "\n";
  std::cout << b << "\n\n";
  a *= 2;
  std::cout << a << "\n";
  a /= 2;
  std::cout << a << "\n";
  return 0;
}
