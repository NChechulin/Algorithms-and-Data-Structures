// UNDIRECTED WEIGHTED GRAPH

#ifndef GRAPH_H
#define GRAPH_H

#include "dot_writer.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename T> class Graph {
public:
  class Node {
  public:
    T data;
    Node(const T &data = T()) : data(data) {}
    // A utility variable used for graphviz
    bool isSpecial = false;
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

  bool existsNode(T &x) const {
    // Check if exists a node with data = x
    for (Node *node : _nodes)
      if (node->data == x)
        return true;
    return false;
  }

  void addEdge(Node *nodeSource, Node *nodeDest, int weight) {
    bool existsNodeSource =
        std::find(_nodes.begin(), _nodes.end(), nodeSource) != _nodes.end();
    bool existsNodeDest =
        std::find(_nodes.begin(), _nodes.end(), nodeDest) != _nodes.end();

    if (existsNodeSource && existsNodeDest) {
      // Create two edges (A,B) and (A,B) which represent a bi-directional link
      // A<--->B
      _adjList.insert({nodeSource, nodeDest});
      _adjList.insert({nodeDest, nodeSource});

      _edgeWeights.insert({{nodeSource, nodeDest}, weight});
      _edgeWeights.insert({{nodeDest, nodeSource}, weight});

      _edgesByWeight.insert({weight, {nodeSource, nodeDest}});
      _edgesByWeight.insert({weight, {nodeDest, nodeSource}});
    }
  }

  Node *getNode(const T &data) const {
    for (Node *node : _nodes)
      if (node->data == data)
        return node;
    return nullptr;
  }

  bool existsEdge(Node *x, Node *y) const {
    auto ret = _adjList.equal_range(x);

    // all pairs whose first component is equal to x are in the range
    // [ret->first, ret->second)
    for (auto it = ret.first; it != ret.second; ++it)
      if (it->second == y)
        return true;
    return false;
  }

  std::vector<Node *> getNeighbors(Node *x) const {
    std::vector<Node *> neighbors;

    auto ret = _adjList.equal_range(x);

    for (auto it = ret.first; it != ret.second; ++it)
      neighbors.push_back(it->second);

    // for every node "y" in the vector "neighbors", there exists an edge
    // "(x,y)" in the graph.
    return neighbors;
  }

  int getNodeOutDegree(Node *x) const { return this->getNeighbors(x).size(); }

  int getNodeInDegree(Node *x) const {
    int cnt = 0;

    for (auto pair : _adjList)
      if (pair.second == x)
        cnt++;
    return cnt;
  }

  const std::vector<Node *> &getNodes() const { return _nodes; }

  const std::map<std::pair<Node *, Node *>, int> getEdgeWeights() const {
    return _edgeWeights;
  }

  const std::multimap<int, std::pair<Node *, Node *>> getEdgesByWeight() const {
    return _edgesByWeight;
  }

  int getEdgeWeight(Node *nodeSource, Node *nodeDest) {
    return _edgeWeights[{nodeSource, nodeDest}];
  }

  std::string getDotRepresentation() {
    DotWriter writer;

    for (Node *node : _nodes)
      writer.addNode(node->data, node->data, node->isSpecial);

    for (auto &edge : _adjList) {
      Node *from = edge.first;
      Node *to = edge.second;
      writer.addEdge(from->data, to->data, getEdgeWeight(from, to), false);
    }

    return writer.getDotRepresentation("test");
  }

private:
  std::multimap<Node *, Node *> _adjList;

  std::map<std::pair<Node *, Node *>, int> _edgeWeights;

  std::multimap<int, std::pair<Node *, Node *>> _edgesByWeight;

  std::vector<Node *> _nodes;
};

template <typename T> // OVERLOADING THE OPERATOR << for the class Graph
std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
  using Node = typename Graph<T>::Node;

  for (Node *node : graph.getNodes())
    os << node->data << std::endl;

  bool skip = true;

  for (auto edge : graph.getEdgesByWeight()) {
    if ((skip = !skip)) // only for undirected graphs
      continue;

    int weight = edge.second;

    Node *u = edge.first.first;
    Node *v = edge.first.second;

    os << u->data << ' ' << v->data << ' ' << weight
       << std::endl; // printing the weight
  }

  return os;
}

#endif
