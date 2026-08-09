#include "smlib.h"
#include <assert.h>
#include <format>
#include <iostream>
int main(int argc, char *argv[]) {
  std::cout << "Meow Meow\n";
  smlib::mvec<float> x({1.2, 4.3});
  smlib::mvec<float> y({4, 7.3});
  smlib::mvec<double> u(4);
  std::cout << "x: " << x << "\n";
  std::cout << "y: " << y << "\n";
  std::cout << "x.mag(): " << x.magnitude() << "\n";
  std::cout << "x.unit(): " << x.unit() << "\n";
  std::cout << "y.unit(): " << y.unit() << "\n";
  y.normalize();
  std::cout << "y: " << y << "\n";
  smlib::mvec<double> a({1.2, 4.7, -7.1});
  smlib::mvec<double> b({2.5, -1.5, 3.2});
  std::cout << "a: " << a << "\n";
  std::cout << "b: " << b << "\n";
  std::cout << "a.cross(b): " << a.cross(b) << "\n";
  std::cout << "b.cross(a): " << b.cross(a) << "\n";
  std::cout << "a.cross(b).dot(a): " << a.cross(b).dot(a) << "\n";
  std::cout << "a.cross(b).dot(b): " << a.cross(b).dot(b) << "\n";
  std::cout << "b.cross(a).dot(b): " << b.cross(a).dot(b) << "\n";
  std::cout << "b.cross(a).dot(a): " << b.cross(a).dot(a) << "\n";
  std::cout << "a/0: " << a / 0 << "\n";
  return 0;
}
