#include "iostream"
#include "vector"
#include <algorithm>
#include <assert.h>
#include <queue>
#include <stdexcept>
#include <vector>

const char NOCHAR = '\0';

class Node {
private:
  bool _is_end = false;

public:
  char key;
  std::vector<Node *> children;

  Node() : key(NOCHAR) {}

  Node(char key) : key(key) {}

  ~Node() {
    for (Node *child : children)
      delete child;
  }

  /// returns a pointer to a child with given key or nullptr
  Node *find(char c) {
    for (Node *current : children) {
      if (current->key == c)
        return current;
    }
    return nullptr;
  }

  /// returns true if `x` is a direct child of current node
  bool isParentOf(Node *x) {
    for (Node *child : children) {
      if (child == x)
        return true;
    }

    return false;
  }

  /// returns true if one of the children has key `c`
  bool isParentOf(char c) { return find(c) != nullptr; }

  /// sets a flag of the end of the word to true
  void setIsEnd() { _is_end = true; }
  /// sets a flag of the end of the word to anything
  void setIsEnd(bool new_value) { _is_end = new_value; }
  /// returns a flag of the end of the word
  bool getIsEnd() { return _is_end; }

  /// Returns pointer to found or created node
  Node *insert(char c) {
    Node *find_result = find(c);
    if (find_result)
      return find_result;

    Node *new_node = new Node(c);
    children.push_back(new_node);
    return new_node;
  }

  /// Returns true if the node has no real children
  bool isLeaf() const {
    int ans = 0;
    for (Node *current : children) {
      if (current)
        ans += 1;
    }

    return ans == 0;
  }
};

class Trie {
protected:
  Node *_root;

  void recursive_retrieve(std::string current_prefix, Node *current_node) {
    if (current_node->getIsEnd())
      std::cout << current_prefix << '\n';

    for (Node *child : current_node->children)
      recursive_retrieve(current_prefix + child->key, child);
  }

  Node *recursive_erase(std::string &key, Node *current_node, int depth) {
    if (current_node == nullptr)
      return nullptr;

    if (depth == key.length()) {
      current_node->setIsEnd(false);
      if (current_node->isLeaf()) {
        Node *tmp = current_node;
        delete current_node;
        return tmp;
      }
    }

    Node *child = current_node->find(key[depth]);
    child = recursive_erase(key, child, depth + 1);

    if (current_node->isLeaf() && !current_node->getIsEnd())
      current_node = nullptr;

    return current_node;
  }

public:
  Trie() : _root(new Node()) {}

  /// constructs a trie from vector of keys
  Trie(std::vector<std::string> &keys) {
    _root = new Node();

    for (std::string key : keys)
      insert(key);
  }

  ~Trie() { delete _root; }

  /// inserts a new key into the trie
  void insert(std::string &key) {
    Node *current = _root;

    for (int i = 0; i < key.size(); ++i)
      current = current->insert(key[i]);
    current->setIsEnd();
  }

  /// returns true if the item is present in the tree
  bool search(std::string &key) const {
    Node *current = _root;

    for (int i = 0; i < key.size(); ++i) {
      current = current->find(key[i]);

      if (!current)
        return false;
    }

    return current->getIsEnd();
  }

  /// prints all of the words with a given prefix
  void retrieve(std::string &prefix) {
    Node *last_prefix_char = _root;

    for (int i = 0; i < prefix.size(); ++i) {
      last_prefix_char = last_prefix_char->find(prefix[i]);
      if (!last_prefix_char)
        return;
    }

    // at this point we have a pointer to the last char of prefix
    recursive_retrieve(prefix, last_prefix_char);
  }

  /// erases a node with a given key
  void erase(std::string &key) { _root = recursive_erase(key, _root, 0); }
};

bool itemInVector(std::string &item, std::vector<std::string> &items) {
  return std::find(items.begin(), items.end(), item) != items.end();
}

// int main() {
//   std::vector<std::string> data = {"any",      "ant",   "anna",  "anger",
//                                    "angelina", "angie", "angry", "angel"};

//   Trie *trie = new Trie(data);

//   std::vector<std::string> items_to_search_for = {
//       "antalya", "angelina", "anna",   "angel", "betty",
//       "alabama", "abobus",   "amogus", "an"};

//   for (std::string &key : items_to_search_for)
//     assert(trie->search(key) == itemInVector(key, data));

//   std::cout << "PASSED ALL TESTS\n";

//   trie->erase(items_to_search_for[0]);
//   assert(trie->search(items_to_search_for[0]) == 0);

//   delete trie;

//   std::cout << "DELETED THE TRIE SUCCESFULLY\n";
// }