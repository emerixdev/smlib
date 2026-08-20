#include "matrix.hpp"
#include "smlib.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<float, 2, 2> a{{{1.f, 2.f}, {4.f, 5.f}}};
  std::cout << a << "\n";
  std::cout << "row(0): " << a.row(0) << "\nrow(1): " << a.row(1) << "\ncol(0): " << a.col(0)
            << "\ncol(1): " << a.col(1) << "\n";
  return 0;
}
