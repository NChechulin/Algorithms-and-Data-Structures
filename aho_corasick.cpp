#include "trie.cpp"
#include <map>
#include <queue>
#include <string>
#include <vector>

class AhoCorasickTrie : public Trie {
private:
  std::map<Node *, Node *> _suffixLink;
  std::map<Node *, Node *> _outputLink;
  // std::map<Node *, std::string> _patterns;

  void buildSuffixLinks() {
    _suffixLink[_root] = nullptr;

    for (Node *child : _root->children)
      _suffixLink[child] = _root;

    // level order (BFS)
    std::queue<Node *> queue;
    queue.push(_root);

    while (!queue.empty()) {
      Node *w = queue.front();
      queue.pop();

      for (Node *child : w->children)
        queue.push(child);

      if (w == _root)
        continue;

      for (Node *a : w->children) {
        if (!a)
          continue;

        Node *x = _suffixLink[w];

        while (x && !x->isParentOf(a->key))
          x = _suffixLink[x];

        if (x)
          _suffixLink[a] = x->find(a->key);
        else
          _suffixLink[a] = _root;
      }
    }
  }

  void printSuffixLinks() {
    std::queue<Node *> q;
    q.push(_root);
    int row_index = 1;

    while (!q.empty()) {
      Node *current = q.front();
      q.pop();

      if (!current)
        continue;

      for (Node *child : current->children)
        if (child)
          q.push(child);

      if (current == _root)
        continue;

      Node *suff_link = _suffixLink[current];

      std::cout << row_index << ": " << current->key << '(' << current << ')'
                << " -> ";

      if (!suff_link)
        std::cout << "nullptr\n";
      else if (suff_link == _root)
        std::cout << "root\n";
      else
        std::cout << suff_link->key << '(' << suff_link << ')' << '\n';

      row_index++;
    }
  }

public:
  AhoCorasickTrie(std::vector<std::string> &patterns) {
    for (auto pat : patterns)
      insert(pat);
    buildSuffixLinks();
    printSuffixLinks();
  }
};

int main() {
  std::vector<std::string> patterns = {"he", "his", "hers", "she"};

  AhoCorasickTrie myTrie(patterns);

  return 0;
}