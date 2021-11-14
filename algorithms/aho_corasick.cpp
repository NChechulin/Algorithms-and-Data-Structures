#include "trie.cpp"
#include <cstdint>
#include <map>
#include <queue>
#include <string>
#include <vector>

class AhoCorasickTrie : public Trie {
private:
  std::map<Node *, Node *> _suffixLink;
  std::map<Node *, Node *> _outputLink;
  std::map<Node *, std::string> _patterns;

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

  void buildOutputLink(Node *u) {
    Node *v = _suffixLink[u];

    if (v && v->getIsEnd())
      _outputLink[u] = v;
    else if (_outputLink[v])
      _outputLink[u] = _outputLink[v];
  }

  void buildOutputLinks() {
    std::queue<Node *> queue;
    queue.push(_root);

    while (!queue.empty()) {
      Node *current = queue.front();
      queue.pop();

      if (!current)
        continue;

      for (Node *child : current->children)
        queue.push(child);

      buildOutputLink(current);
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
      _patterns[insert(pat)] = pat;

    buildSuffixLinks();
    buildOutputLinks();
    printSuffixLinks();
  }

  typedef std::pair<std::uint32_t, std::string> occurrence;
  typedef std::vector<occurrence> find_result;

  find_result find(std::string text) {
    find_result ans;

    Node *current_node = _root;

    for (int i = 0; i < text.size(); ++i) {
      char a = text[i];

      while (!current_node->isParentOf(a) && current_node != _root)
        current_node = _suffixLink[current_node];

      if (!current_node->isParentOf(a) && current_node == _root)
        continue;

      // The currentNode will be now the child with letter a of the currentNode

      if (current_node && current_node->getIsEnd()) {
        std::string pattern = _patterns[current_node];
        ans.push_back({i - pattern.size(), pattern});
      }

      Node *v = _outputLink[current_node];

      while (v)
        v = _outputLink[v];

      if (v && v->getIsEnd()) {
        std::string pattern = _patterns[v];
        ans.push_back({i - pattern.size(), pattern});
      }
    }

    return ans;
  }
};

int main() {
  std::vector<std::string> patterns = {"i", "in", "tin", "sting"};

  AhoCorasickTrie myTrie(patterns);

  auto ans = myTrie.find("sting");

  std::cout << "FIND RESULTS\n";

  for (auto pair : ans) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }

  return 0;
}