#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

template <typename T> class Graph {
public:
  class Node {
  public:
    T data;
    Node(const T &data = T()) : data(data) {}
  };

  ~Graph() {
    for (Node *node : _nodes)
      delete node;
  }

  Node *addNode(const T &data = T()) {
    Node *node = new Node(data);

    _nodes.push_back(node);

    return node;
  }

  bool nodeIsPresent(const T &data) { return find(data) != nullptr; }

  bool edgeIsPresent(Node *from, Node *to) {
    if (!from || !to)
      return false;

    auto ret = _adjList.equal_range(from);
    for (auto it = ret.first; it != ret.second; ++it) {
      if (it->second == to)
        return true;
    }

    return false;
  }

  Node *find(const T &data) {
    for (Node *node : _nodes)
      if (node->data == data)
        return node;
    return nullptr;
  }

  Node *findNodeOrInsert(const T &data) {
    Node *res = find(data);
    if (!res)
      res = addNode(data);

    return res;
  }

  void addEdge(Node *nodeSource, Node *nodeDest) {
    bool existsNodeSource =
        std::find(_nodes.begin(), _nodes.end(), nodeSource) != _nodes.end();
    bool existsNodeDest =
        std::find(_nodes.begin(), _nodes.end(), nodeDest) != _nodes.end();

    if (existsNodeSource && existsNodeDest)
      _adjList.insert({nodeSource, nodeDest});
  }

private:
  std::multimap<Node *, Node *> _adjList;

  std::vector<Node *> _nodes;
};

Graph<std::string> readGraph() {
  Graph<std::string> result;

  int n;
  std::cout << "Input the number of edges:\n";
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::string from, to;
    std::cin >> from >> to;

    Graph<std::string>::Node *nfrom, *nto;
    nfrom = result.findNodeOrInsert(from);
    nto = result.findNodeOrInsert(to);

    result.addEdge(nfrom, nto);
  }

  return result;
}

int main() {
  auto graph = readGraph();

  int n;
  std::cout << "Input the number of edges to check:\n";
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::string from, to;
    std::cin >> from >> to;

    Graph<std::string>::Node *nfrom, *nto;
    nfrom = graph.find(from);
    nto = graph.find(to);

    if (!nfrom || !nto)
      std::cout << "NO\n";

    if (graph.edgeIsPresent(nfrom, nto))
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }
}
