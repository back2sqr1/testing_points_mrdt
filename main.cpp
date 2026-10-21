#include "Solver.hpp"
#include <iostream>

int main() {
  Point a(-10, 0);
  Point b(10, 0);
  Solver solver;
  Point s(5, 10);
  double t = 9;
  std::cout << solver.forward_function(s, a, b, t) << std::endl;
}
