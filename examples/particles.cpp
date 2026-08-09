#include "../smlib.h"
#include <iostream>

constexpr double dt = 0.01;

struct Particle {
  smlib::mvec<double> position;
  smlib::mvec<double> velocity;
  smlib::mvec<double> acceleration;

  Particle() : position(2), velocity(2), acceleration(2) {}

  Particle(const smlib::mvec<double> &pos, const smlib::mvec<double> &vel, const smlib::mvec<double> &acc)
      : position(pos), velocity(vel), acceleration(acc) {}

  void print() const {
    std::cout << "Position: " << position << "\nVelocity: " << velocity << "\nAcceleration: " << acceleration << '\n';
  }

  void update() {
    position += velocity * dt;
    velocity += acceleration * dt;
  }
};

int main() {
  Particle a({3.0, 4.0}, {1.0, 2.3}, {7.5, 6.9});

  a.print();

  std::cout << "Update\n";

  a.update();
  a.print();

  return 0;
}
