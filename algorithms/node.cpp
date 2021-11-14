#include "iostream"
#include "vector"
#include <stdexcept>
#include <vector>

template <typename T> class Node {
public:
  T key;
  Node<T> *left = nullptr;
  Node<T> *right = nullptr;

  Node<T>() {}
  Node<T>(T key) : key(key) {}

  bool hasLeftChild() const { return left != nullptr; }

  bool hasRightChild() const { return right != nullptr; }

  bool isLeaf() const { return (!hasLeftChild()) && (!hasRightChild()); }
};
