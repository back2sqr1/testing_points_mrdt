#include "Solver.hpp"
#include <iostream>

void print_answer(N *g) {
  while (g != nullptr && !g->neighbors.empty()) {
    std::cout << std::get<0>(g->value) << " ";
    g = g->neighbors.front();
  }
  std::cout << std::get<0>(g->value) << "\n";
}

int main() {
  Point a(-1, 0);
  Point b(1, 0);
  Point c(0, -1);
  Solver solver;
  Point s(1, 1);
  Point arbi(0, 0); // arbitruary node
  // t = 0.5, 1.2, 3 // to test all points
  double t = 1.2;
  auto [ff, d_ff] = solver.forward_function(s, a, b, t);
  auto [ffs, d_ffs] = solver.forward_function_sampling(s, a, b, t);
  std::cout << ff << " " << ffs << std::endl;

  Graph::Graph<Val> g;
  N *s_node = g.addNode({s, 1.2});
  N *a_node = g.addNode({a, 0});
  N *b_node = g.addNode({b, 0});
  N *d_node = g.addNode({arbi, 2});
  N *c_node = g.addNode({c, 0});

  g.addEdge(d_node, a_node);
  g.addEdge(d_node, b_node);
  g.addEdge(s_node, d_node);
  g.addEdge(s_node, c_node);

  Graph::Graph<std::tuple<Point, double>> sol_g;
  N *ans = solver.solve_ff_tree(*s_node, sol_g);
  auto [pt, dist] = ans->value;
  std::cout << "ANSWER\n";
  print_answer(ans);
  std::cout << dist << "\n";
}
