#include "smlib.h"
#include <assert.h>
#include <format>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mvec<float, 2> a;
  smlib::mvec<float, 3> b(1.2, 4.7, 4.33);
  std::cout << "a: " << a << "\n";
  std::cout << "b: " << b << "\n";
  return 0;
}
