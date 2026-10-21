#include <cmath>
#include <iostream>
class Vector {
public:
  double x;
  double y;
  Vector(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double magnitude() { return std::sqrt(x * x + y * y); }
  void resize(double mag) {
    double original_mag = magnitude();
    x /= original_mag / mag;
    y /= original_mag / mag;
  }
};
inline std::ostream &operator<<(std::ostream &os, const Vector &v) {
  os << "[" << v.x << ", " << v.y << " ]";
  return os;
}
