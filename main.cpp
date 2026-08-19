#include "smlib.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<float, 2, 3> a{{{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}}};
  std::cout << a << "\n";
  a(1, 1) = 6.9;
  std::cout << a << "\n";
  a(0, 1) = 4.20;
  std::cout << a << "\n";
  return 0;
}
