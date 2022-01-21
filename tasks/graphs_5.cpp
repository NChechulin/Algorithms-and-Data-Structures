#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stack>
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

  bool nodeIsPresent(const T &data) const { return find(data) != nullptr; }

  bool edgeIsPresent(Node *from, Node *to) const {
    if (!from || !to)
      return false;

    auto ret = _adjList.equal_range(from);
    for (auto it = ret.first; it != ret.second; ++it) {
      if (it->second == to)
        return true;
    }

    return false;
  }

  Node *find(const T &data) const {
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

  std::vector<Node *> getAllFollowsBy(Node *node) const {
    if (!node)
      return {};
    std::vector<Node *> result;

    auto ret = _adjList.equal_range(node);
    for (auto it = ret.first; it != ret.second; ++it)
      result.push_back(it->second);

    return result;
  }

  std::vector<Node *> getAllFollowsBy(const T &data) const {
    Node *node = find(data);

    if (!node)
      return {};

    return getAllFollowsBy(node);
  }

  Node *getNodeWithMaxFollows() const {
    int maxlen = 0;
    Node *ans = nullptr;

    for (Node *node : _nodes) {
      if (!node)
        continue;

      std::vector<Node *> res = getAllFollowsBy(node);

      if (maxlen < res.size()) {
        maxlen = res.size();
        ans = node;
      }
    }

    return ans;
  }

  Node *getNodeWithMaxFollowers() const {
    std::map<Node *, int> counts;

    for (auto edge_it = _adjList.begin(); edge_it != _adjList.end();
         ++edge_it) {
      if (counts.find(edge_it->second) == counts.end())
        counts[edge_it->second] = 0;

      counts[edge_it->second]++;
    }

    int max = -1;
    Node *ans = nullptr;

    for (auto it = counts.begin(); it != counts.end(); ++it) {
      if (it->second > max) {
        max = it->second;
        ans = it->first;
      }
    }

    return ans;
  }

  void dfs() {
    std::set<Node *> visited;
    std::stack<Node *> stack;
    stack.push(_nodes[0]);

    while (!stack.empty()) {
      Node *curr = stack.top();
      stack.pop();

      if (visited.find(curr) != visited.end())
        continue;

      visited.insert(curr);

      std::cout << curr->data << '\n';

      auto ret = _adjList.equal_range(curr);
      for (auto it = ret.first; it != ret.second; ++it)
        stack.push(it->second);
    }
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
  graph.dfs();
}
