#include <iostream>
#include <queue>
#include <set>
#include <sstream>

const char NULLCHAR = '\0';

class HuffmanNode {
public:
  char letter;
  int freq;

  HuffmanNode *leftChild;
  HuffmanNode *rightChild;

  HuffmanNode(char letter, int freq, HuffmanNode *leftChild = nullptr,
              HuffmanNode *rightChild = nullptr)
      : letter(letter), freq(freq), leftChild(leftChild),
        rightChild(rightChild) {}

  HuffmanNode(const HuffmanNode &node)
      : letter(node.letter), freq(node.freq), leftChild(node.leftChild),
        rightChild(node.rightChild) {}

  bool operator<(const HuffmanNode &node) const {
    return this->freq <= node.freq;
  }
};

std::ostream &operator<<(std::ostream &out, const HuffmanNode &node) {
  out << "Letter: " << node.letter << " Freq: " << node.freq;
  return out;
}

class HuffmanTree {
private:
  HuffmanNode *_root;

public:
  HuffmanTree(std::multiset<HuffmanNode> &nodes) {
    while (nodes.size() > 1) {
      HuffmanNode *left = new HuffmanNode(*nodes.begin());
      nodes.erase(nodes.begin());

      HuffmanNode *right = new HuffmanNode(*nodes.begin());
      nodes.erase(nodes.begin());

      nodes.insert(
          HuffmanNode(NULLCHAR, left->freq + right->freq, left, right));
    }

    _root = new HuffmanNode(*nodes.begin());
  }

  void print() {
    std::queue<std::pair<HuffmanNode *, std::string>> q;
    q.push({_root, ""});

    while (!q.empty()) {
      auto p = q.front();
      q.pop();

      HuffmanNode *node = p.first;
      std::string buf = p.second;

      if (!node)
        continue;

      if (node->letter != NULLCHAR)
        std::cout << *node << ":\t" << buf << '\n';

      q.push({node->leftChild, buf + "0"});
      q.push({node->rightChild, buf + "1"});
    }
  }
};

int main() {
  std::multiset<HuffmanNode> s = {
      {'D', 1}, {'C', 1}, {'R', 2}, {'B', 2}, {'A', 5}};

  HuffmanTree tree(s);
  tree.print();

  return 0;
}