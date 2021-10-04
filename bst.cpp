#include "iostream"
#include "node.cpp"
#include "vector"
#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T> class BST {
private:
  Node<T> *_root;
  int _size = 0;

public:
  void insert(T key) {
    Node<T> *new_node = new Node<T>(key);
    Node<T> *parent = nullptr;
    Node<T> *it = _root;

    while (it != nullptr) {
      parent = it;
      it = new_node->key < it->key ? it->left : it->right;
    }

    if (!parent)
      _root = new_node;
    else if (new_node->key < parent->key)
      parent->left = new_node;
    else
      parent->right = new_node;

    _size++;
  }

  Node<T> *find(T key) const {
    if (!_root)
      throw std::out_of_range("Cannot find element in an empty tree");

    Node<T> *it = _root;
    while (it != nullptr && it->key != key) {
      if (key < it->key)
        it = it->left;
      else
        it = it->right;
    }

    if (!it)
      throw std::out_of_range("Element is not present in the tree");

    return it;
  }

  int getSize() const { return _size; }
};

int main() {
  BST<int> tree = BST<int>();

  std::vector<int> data = {8, 3, 10, 1, 6, 14, 4, 7, 13};

  for (int e : data)
    tree.insert(e);

  for (int e : data)
    tree.find(e);

  try {
    tree.find(-1);
  } catch (std::out_of_range) {
    std::cout << "\n-1 is not present in the tree\n";
  }

  std::cout << tree.getSize() << '\n';
}