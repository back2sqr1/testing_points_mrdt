#include "Solver.hpp"
#include <iostream>

int main() {
  Point a(-1, 0);
  Point b(1, 0);
  Solver solver;
  Point s(1, 1);
  // t = 0.5, 1.2, 3 // to test all points
  double t = 1.2;
  Point ff = solver.forward_function(s, a, b, t);
  Point ffs = solver.forward_function_sampling(s, a, b, t);
  std::cout << ff.max_of_dists(a, b) << " " << ffs.max_of_dists(a, b)
            << std::endl;
  std::cout << ff << " " << ffs << std::endl;
}
