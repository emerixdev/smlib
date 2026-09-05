#include "matrix.hpp"
#include "vector.hpp"
#include "vector_matrix.hpp"
#include <assert.h>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mmat<int, 4, 4> trans(0);
  smlib::mvec<float, 4> vec({1, 2, 4, 1});
  trans=smlib::gen_identity_mat<int, 4>();
  trans(0, 3)=4;
  trans(1, 3)=2;
  trans(2, 3)=3;
  std::cout<<"trans matrix: \n"<<trans<<"\n\n";
  std::cout<<"trans*vec:\n"<<trans*vec<<"\n";
  

  return 0;
}
