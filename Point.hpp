#include <bits/std_thread.h>
#include <cmath>
#include <iostream>
class Point {
public:
  double x;
  double y;
  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double dist(const Point &z) {
    return std::sqrt((z.x - x) * (z.x - x) + (z.y - y) * (z.y - y));
  }
  Point midpoint(const Point &z) { return Point((x + z.x) / 2, (y + z.y) / 2); }
};
// --- Add this operator overload function here ---
inline std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}
