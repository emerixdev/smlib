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
  // smlib::mvec<int, 4> vec1=smlib::cast<float, int>(vec);
  smlib::cast<float, int>(vec);
  

  return 0;
}
