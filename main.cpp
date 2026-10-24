#include "matrix.hpp"
#include "vector.hpp"
#include "vector_matrix.hpp"
#include <assert.h>
#include <iostream>
#include <numbers>
int main(int argc, char *argv[]) {
  smlib::mvec<float, 4> vec({1, 2, 4, 1});
  vec*=1.7144;
  std::cout<<vec<<"\n";
  std::cout<<vec.to_string(2)<<"\n";
  std::cout<<vec.to_string(1)<<"\n";
  std::cout<<vec.to_string(0)<<"\n";
  std::cout<<vec.to_string(-1)<<"\n";
  std::cout<<vec.to_string(-2)<<"\n";
  std::cout<<vec.to_string()<<"\n";


  return 0;
}
