#include "smlib.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

using smlib::mvec;

void test_construction() {
  mvec<float> a;
  assert(a.empty());
  assert(a.size() == 0);

  mvec<float> b(3);
  assert(b.size() == 3);
  assert(b[0] == 0.0f);
  assert(b[1] == 0.0f);
  assert(b[2] == 0.0f);

  mvec<float> c(3, 5.0f);
  assert(c == mvec<float>{5.0f, 5.0f, 5.0f});

  mvec<float> d{1.0f, 2.0f, 3.0f};
  assert(d.size() == 3);
  assert(d.x() == 1.0f);
  assert(d.y() == 2.0f);
  assert(d.z() == 3.0f);
}

void test_access() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  assert(a[0] == 1.0f);
  assert(a.at(1) == 2.0f);
  assert(a.x() == 1.0f);
  assert(a.y() == 2.0f);
  assert(a.z() == 3.0f);

  a.x() = 10.0f;
  a.y() = 20.0f;
  a.z() = 30.0f;

  assert(a == mvec<float>{10.0f, 20.0f, 30.0f});

  bool threw = false;

  try {
    a.at(100);
  } catch (const std::out_of_range &) {
    threw = true;
  }

  assert(threw);
}

void test_const_access() {
  const mvec<float> a{1.0f, 2.0f, 3.0f};

  assert(a[0] == 1.0f);
  assert(a.at(1) == 2.0f);
  assert(a.x() == 1.0f);
  assert(a.y() == 2.0f);
  assert(a.z() == 3.0f);

  assert(a.data()[0] == 1.0f);
  assert(a.data()[1] == 2.0f);
  assert(a.data()[2] == 3.0f);

  float sum = 0.0f;

  for (float x : a)
    sum += x;

  assert(sum == 6.0f);
}

void test_data() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  float *data = a.data();

  assert(data != nullptr);
  assert(data[0] == 1.0f);
  assert(data[1] == 2.0f);
  assert(data[2] == 3.0f);

  data[1] = 20.0f;

  assert(a[1] == 20.0f);
}

void test_arithmetic() {
  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{4.0f, 5.0f, 6.0f};

  assert(a + b == mvec<float>{5.0f, 7.0f, 9.0f});
  assert(a - b == mvec<float>{-3.0f, -3.0f, -3.0f});

  assert(a * 2.0f == mvec<float>{2.0f, 4.0f, 6.0f});
  assert(2.0f * a == mvec<float>{2.0f, 4.0f, 6.0f});

  assert(a / 2.0f == mvec<float>{0.5f, 1.0f, 1.5f});

  assert(+a == a);
  assert(-a == mvec<float>{-1.0f, -2.0f, -3.0f});

  mvec<float> c = a;
  c += b;
  assert(c == mvec<float>{5.0f, 7.0f, 9.0f});

  c = a;
  c -= b;
  assert(c == mvec<float>{-3.0f, -3.0f, -3.0f});

  c = a;
  c *= 2.0f;
  assert(c == mvec<float>{2.0f, 4.0f, 6.0f});

  c = a;
  c /= 2.0f;
  assert(c == mvec<float>{0.5f, 1.0f, 1.5f});
}

void test_copy_move() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  mvec<float> b = a;

  assert(b == a);

  b[0] = 100.0f;

  assert(a[0] == 1.0f);
  assert(b[0] == 100.0f);

  mvec<float> c = std::move(b);

  assert(c == mvec<float>{100.0f, 2.0f, 3.0f});
}

void test_size_errors() {
  mvec<float> a{1.0f, 2.0f};
  mvec<float> b{1.0f, 2.0f, 3.0f};

  bool threw = false;

  try {
    a += b;
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    a -= b;
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    a.dot(b);
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);

  assert(!a.approx_equal_absolute(b, 1.0f));
  assert(!a.approx_equal_relative(b, 1.0f));
}

void test_dot() {
  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{4.0f, 5.0f, 6.0f};

  assert(smlib::dot(a, b) == 32.0f);
  assert(smlib::dot(b, a) == 32.0f);

  mvec<float> perpendicular_a{1.0f, 0.0f, 0.0f};
  mvec<float> perpendicular_b{0.0f, 1.0f, 0.0f};

  assert(smlib::dot(perpendicular_a, perpendicular_b) == 0.0f);
}

void test_magnitude() {
  mvec<float> a{3.0f, 4.0f};

  assert(a.magnitude() == 5.0f);

  mvec<float> b{0.0f, 0.0f, 0.0f};

  assert(b.magnitude() == 0.0f);
}

void test_reductions() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  assert(a.sum() == 6.0f);
  assert(a.magnitude_squared() == 14.0f);

  mvec<float> empty;

  assert(empty.sum() == 0.0f);
  assert(empty.magnitude_squared() == 0.0f);
}

void test_min_max() {
  mvec<float> a{3.0f, -1.0f, 5.0f, 2.0f};

  assert(a.min() == -1.0f);
  assert(a.max() == 5.0f);

  mvec<float> positive{2.0f, 4.0f, 6.0f};

  assert(positive.min() == 2.0f);
  assert(positive.max() == 6.0f);

  mvec<float> negative{-6.0f, -4.0f, -2.0f};

  assert(negative.min() == -6.0f);
  assert(negative.max() == -2.0f);

  mvec<float> single{42.0f};

  assert(single.min() == 42.0f);
  assert(single.max() == 42.0f);

  mvec<float> empty;

  bool threw = false;

  try {
    empty.min();
  } catch (const std::domain_error &) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    empty.max();
  } catch (const std::domain_error &) {
    threw = true;
  }

  assert(threw);
}

void test_unit() {
  mvec<float> a{3.0f, 4.0f};

  auto u = a.unit();

  assert(std::abs(u.magnitude() - 1.0f) < 0.0001f);
  assert(std::abs(u.x() - 0.6f) < 0.0001f);
  assert(std::abs(u.y() - 0.8f) < 0.0001f);

  mvec<float> zero{0.0f, 0.0f, 0.0f};

  bool threw = false;

  try {
    zero.unit();
  } catch (const std::domain_error &) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    zero.normalize();
  } catch (const std::domain_error &) {
    threw = true;
  }

  assert(threw);
}

void test_cross() {
  mvec<float> x{1.0f, 0.0f, 0.0f};
  mvec<float> y{0.0f, 1.0f, 0.0f};
  mvec<float> z{0.0f, 0.0f, 1.0f};

  assert(smlib::cross(x, y) == z);
  assert(smlib::cross(y, x) == -z);

  assert(smlib::cross(x, z) == -y);

  mvec<float> invalid{1.0f, 2.0f};

  bool threw = false;

  try {
    x.cross(invalid);
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);
}

void test_elementwise_math() {
  mvec<float> a{-1.5f, 2.2f, 9.0f};

  assert(a.abs() == mvec<float>{1.5f, 2.2f, 9.0f});
  assert(a.floor() == mvec<float>{-2.0f, 2.0f, 9.0f});
  assert(a.ceil() == mvec<float>{-1.0f, 3.0f, 9.0f});
  assert(a.round() == mvec<float>{-2.0f, 2.0f, 9.0f});

  mvec<float> b{1.0f, 4.0f, 9.0f};

  assert(b.sqrt() == mvec<float>{1.0f, 2.0f, 3.0f});
}

void test_fill_resize() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  a.fill(5.0f);

  assert(a == mvec<float>{5.0f, 5.0f, 5.0f});

  a.resize(5);

  assert(a.size() == 5);
  assert(a[0] == 5.0f);
  assert(a[1] == 5.0f);
  assert(a[2] == 5.0f);
  assert(a[3] == 0.0f);
  assert(a[4] == 0.0f);

  a.resize(2);

  assert(a.size() == 2);
  assert(a == mvec<float>{5.0f, 5.0f});
}

void test_iterators() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  float sum = 0.0f;

  for (float x : a)
    sum += x;

  assert(sum == 6.0f);

  assert(a.cbegin() != a.cend());
}

void test_zero_checks() {
  mvec<float> zero{0.0f, 0.0f, 0.0f};
  mvec<float> a{0.0f, 0.0001f, 0.0f};

  assert(zero.is_zero());
  assert(!a.is_zero());

  assert(zero.is_near_zero(0.001f));
  assert(a.is_near_zero(0.001f));
  assert(!a.is_near_zero(0.00001f));

  bool threw = false;

  try {
    zero.is_near_zero(-1.0f);
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);
}

void test_approx_equal_absolute() {
  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{1.001f, 2.001f, 3.001f};

  assert(a.approx_equal_absolute(b, 0.01f));
  assert(!a.approx_equal_absolute(b, 0.0001f));

  bool threw = false;

  try {
    a.approx_equal_absolute(b, -1.0f);
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);
}

void test_approx_equal_relative() {
  mvec<float> a{100.0f, 200.0f, 300.0f};
  mvec<float> b{101.0f, 202.0f, 303.0f};

  assert(a.approx_equal_relative(b, 0.01f));
  assert(a.approx_equal_relative(b, 0.011f));

  assert(!a.approx_equal_relative(b, 0.001f));

  bool threw = false;

  try {
    a.approx_equal_relative(b, -1.0f);
  } catch (const std::invalid_argument &) {
    threw = true;
  }

  assert(threw);
}

void test_nan() {
  const float nan = std::numeric_limits<float>::quiet_NaN();

  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{1.0f, nan, 3.0f};

  assert(!a.has_nan());
  assert(b.has_nan());

  assert(a.is_finite());
  assert(!b.is_finite());

  assert(smlib::is_nan(nan));
  assert(!smlib::is_nan(1.0f));

  assert(!a.approx_equal_absolute(b, 1.0f));
  assert(!a.approx_equal_relative(b, 1.0f));
}

void test_infinity() {
  const float inf = std::numeric_limits<float>::infinity();

  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{1.0f, inf, 3.0f};

  assert(!a.has_infinity());
  assert(b.has_infinity());

  assert(a.is_finite());
  assert(!b.is_finite());

  assert(smlib::is_infinite(inf));
  assert(!smlib::is_infinite(1.0f));

  mvec<float> positive_inf{inf};
  mvec<float> another_positive_inf{inf};

  assert(positive_inf.approx_equal_relative(another_positive_inf, 0.001f));

  mvec<float> negative_inf{-inf};

  assert(!positive_inf.approx_equal_relative(negative_inf, 0.001f));
}

void test_division_by_zero() {
  mvec<float> a{1.0f, -2.0f, 0.0f};

  auto result = a / 0.0f;

  assert(std::isinf(result[0]));
  assert(std::isinf(result[1]));
  assert(std::isnan(result[2]));

  assert(result[0] > 0.0f);
  assert(result[1] < 0.0f);
}

void test_free_functions() {
  mvec<float> a{1.0f, 2.0f, 3.0f};
  mvec<float> b{1.001f, 2.001f, 3.001f};

  assert(smlib::approx_equal_absolute(a, b, 0.01f));
  assert(smlib::approx_equal_relative(a, b, 0.01f));

  assert(!smlib::has_nan(a));
  assert(!smlib::has_infinity(a));
  assert(smlib::is_finite(a));

  assert(smlib::is_finite(1.0f));
  assert(!smlib::is_finite(std::numeric_limits<float>::infinity()));
}

template <typename T> void test_type() {
  mvec<T> a{T{1}, T{2}, T{3}};
  mvec<T> b{T{4}, T{5}, T{6}};

  assert(a + b == mvec<T>{T{5}, T{7}, T{9}});
  assert(a.dot(b) == T{32});
  assert(a.sum() == T{6});
}

void test_output() {
  mvec<float> a{1.0f, 2.0f, 3.0f};

  std::cout << "Vector: " << a << '\n';
}

int main() {
  std::cout << "Running smlib tests...\n\n";

  test_construction();
  std::cout << "[PASS] construction\n";

  test_access();
  std::cout << "[PASS] access\n";

  test_const_access();
  std::cout << "[PASS] const access\n";

  test_data();
  std::cout << "[PASS] data\n";

  test_arithmetic();
  std::cout << "[PASS] arithmetic\n";

  test_copy_move();
  std::cout << "[PASS] copy/move\n";

  test_size_errors();
  std::cout << "[PASS] size errors\n";

  test_dot();
  std::cout << "[PASS] dot\n";

  test_magnitude();
  std::cout << "[PASS] magnitude\n";

  test_reductions();
  std::cout << "[PASS] reductions\n";

  test_min_max();
  std::cout << "[PASS] min/max\n";

  test_unit();
  std::cout << "[PASS] unit\n";

  test_cross();
  std::cout << "[PASS] cross\n";

  test_elementwise_math();
  std::cout << "[PASS] elementwise math\n";

  test_fill_resize();
  std::cout << "[PASS] fill/resize\n";

  test_iterators();
  std::cout << "[PASS] iterators\n";

  test_zero_checks();
  std::cout << "[PASS] zero checks\n";

  test_approx_equal_absolute();
  std::cout << "[PASS] absolute comparison\n";

  test_approx_equal_relative();
  std::cout << "[PASS] relative comparison\n";

  test_nan();
  std::cout << "[PASS] NaN\n";

  test_infinity();
  std::cout << "[PASS] infinity\n";

  test_division_by_zero();
  std::cout << "[PASS] division by zero\n";

  test_free_functions();
  std::cout << "[PASS] free functions\n";

  test_type<float>();
  std::cout << "[PASS] float\n";

  test_type<double>();
  std::cout << "[PASS] double\n";

  test_output();

  std::cout << "\nAll tests passed!\n";

  return 0;
}
