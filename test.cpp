#include "smlib.h"
#include <assert.h>
#include <format>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mvec<float> a({1.2, 3.7, 4.2});
  smlib::mvec<float> b({7.1, 0.1, -3.0});
  std::cout << std::format("a: {}\nb: {}\n", a, b);
  std::cout << std::format("b.abs(): {}\na.floor(): {}\na.ceil(): {}\na.round(): {}\n b.sqrt(): {}\n", b.abs(),
                           a.floor(), a.ceil(), a.round(), b.sqrt());

  return 0;
}
