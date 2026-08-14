#include "smlib.h"
#include <assert.h>
#include <cmath>
#include <format>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mvec<float, 2> a;
  smlib::mvec<float, 3> b(1.2, 4.7, 4.33);
  std::cout << "a: " << a << "\n";
  std::cout << "b: " << b << "\n";
  constexpr smlib::mvec<double, 3> v{3.0, 4.0, 0.0};
  static_assert(std::sqrt(9.0) == 3.0);
  return 0;
}
