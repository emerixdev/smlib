#include "smlib.h"
#include <assert.h>
#include <format>
#include <iostream>
int main(int argc, char *argv[]) {
  smlib::mvec<float> a({1.2, 3.7, 4.2});
  smlib::mvec<float> b({7.1, 0.1, -3.0});
  std::cout << std::format("a: {}\nb: {}\n", a, b);
  std::cout << std::format("a-b: {}\na+b: {}\na/2: {}\nb/0: {}\n", a - b, a + b, a / 2, b / 0);
  std::cout << std::format("smlib::dot(a,b): {}\nsmlib::dot(b, a):{}\n", smlib::dot(a, b), smlib::dot(b, a));
  std::cout << std::format("smlib::cross(a,b): {}\nsmlib::cross(b, a):{}\n", smlib::cross(a, b), smlib::cross(b, a));

  return 0;
}
