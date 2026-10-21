#include <memory>
#include <utility>
#include <vector>

namespace Graph {
template <typename T> struct Node {
  T value;
  std::vector<Node<T> *> neighbors;
  explicit Node(T v) : value(std::move(v)) {}
};

template <typename T> class Graph {
  std::vector<std::unique_ptr<Node<T>>> nodes;

public:
  Node<T> *root;
  Graph() {}

  Node<T> *addNode(T value) {
    nodes.push_back(std::make_unique<Node<T>>(std::move(value)));
    return nodes.back().get();
  }
  Node<T> *addNode(std::unique_ptr<Node<T>> node) {
    nodes.push_back(std::move(node));
    return nodes.back().get();
  }

  // directed edge a -> b
  void addEdge(Node<T> *a, Node<T> *b) { a->neighbors.push_back(b); }

  // for undirected, also: b->neighbors.push_back(a);
};
} // namespace Graph
