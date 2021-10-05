#include "iostream"
#include "node.cpp"
#include "vector"
#include <algorithm>
#include <queue>
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

  // BFS
  void levelOrder(void(f)(Node<T> *)) {
    if (!_root)
      return;

    std::queue<Node<T> *> queue;
    queue.push(_root);

    while (!queue.empty()) {
      Node<T> *node = queue.front();
      queue.pop();

      f(node);

      if (node->hasLeftChild())
        queue.push(node->left);
      if (node->hasRightChild())
        queue.push(node->right);
    }
  }

  // DFS: left subtree, node itself, right subtree
  void inOrder(Node<T> *current, void(f)(Node<T> *)) {
    if (!current)
      return;

    if (current->hasLeftChild())
      inOrder(current->left, f);

    f(current);

    if (current->hasRightChild())
      inOrder(current->right, f);
  }

  // DFS: node itself, left subtree, right subtree
  void preOrder(Node<T> *current, void(f)(Node<T> *)) {
    if (!current)
      return;

    f(current);

    if (current->hasLeftChild())
      preOrder(current->left, f);

    if (current->hasRightChild())
      preOrder(current->right, f);
  }

  // DFS: left subtree, right subtree, node itself
  void postOrder(Node<T> *current, void(f)(Node<T> *)) {
    if (!current)
      return;

    if (current->hasLeftChild())
      postOrder(current->left, f);

    if (current->hasRightChild())
      postOrder(current->right, f);

    f(current);
  }

  int getSize() const { return _size; }

  Node<T> *getRoot() const { return _root; }
};

template <typename T> void myfunc(Node<T> *node) {
  if (node)
    std::cout << node->key << '\n';
  else
    std::cout << "reached leaf\n";
}

template <typename T> void f(Node<T> *node) {
  std::cout << "NODE: " << node->key << '\n';
}

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

  Node<int> *root = tree.getRoot();

  std::cout << "Level order\n";
  tree.levelOrder(&f);
  std::cout << "In order\n";
  tree.inOrder(root, &f);
  std::cout << "PreOrder\n";
  tree.preOrder(root, &f);
  std::cout << "PostOrder\n";
  tree.postOrder(root, &f);
}