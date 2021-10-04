#include "iostream"
#include "vector"
#include <stdexcept>
#include <vector>

template <typename T> class Node {
public:
  T key;
  Node<T> *left;
  Node<T> *right;

  Node<T>() {}
  Node<T>(T key) : key(key) {}
};
