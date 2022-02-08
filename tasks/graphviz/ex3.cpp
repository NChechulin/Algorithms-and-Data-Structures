#include "graph.h"
#include "priorityqueue.h"
#include <algorithm>
#include <climits>
#include <map>
#include <string>

const int oo = INT_MAX; // infinite

using Node = Graph<std::string>::Node;
using MyGraph = Graph<std::string>;

void buildGraph(MyGraph &graph) {
  Node *frankfurt = graph.addNode("Frankfurt");
  Node *stuttgart = graph.addNode("Stuttgart");
  Node *mannheim = graph.addNode("Mannheim");
  Node *karlsruhe = graph.addNode("Karlsruhe");
  Node *augsburg = graph.addNode("Augsburg");
  Node *munchen = graph.addNode("Munchen");
  Node *wurzburg = graph.addNode("Wurzburg");
  Node *erfurt = graph.addNode("Erfurt");
  Node *nurnberg = graph.addNode("Nurnberg");
  Node *kassel = graph.addNode("Kassel");

  graph.addEdge(frankfurt, mannheim, 85);
  graph.addEdge(frankfurt, wurzburg, 217);
  graph.addEdge(frankfurt, kassel, 173);
  graph.addEdge(mannheim, karlsruhe, 80);
  graph.addEdge(karlsruhe, augsburg, 250);
  graph.addEdge(augsburg, munchen, 84);
  graph.addEdge(kassel, munchen, 502);
  graph.addEdge(wurzburg, erfurt, 186);
  graph.addEdge(wurzburg, nurnberg, 103);
  graph.addEdge(nurnberg, stuttgart, 183);
  graph.addEdge(nurnberg, munchen, 167);
}

/// Dijkstra algorithm which returns distances from startNode to all of the
/// others
std::map<Node *, int> dijkstra(MyGraph &graph, Node *startNode) {
  PriorityQueue<Node *> queue;
  std::map<Node *, int> distance;
  std::map<Node *, bool> visited;

  for (auto node : graph.getNodes()) {
    distance[node] = oo;
    visited[node] = false;
    queue.insert(node, distance[node]);
  }

  distance[startNode] = 0;
  queue.insert(startNode, 0);

  while (!queue.empty()) {
    Node *node = queue.getMin();
    for (auto el : graph.getNeighbors(node)) {
      if (visited[el] == false) {
        if (distance[el] > distance[node] + graph.getEdgeWeight(node, el)) {
          queue.update(el, distance[el],
                       distance[node] + graph.getEdgeWeight(node, el));
          distance[el] = distance[node] + graph.getEdgeWeight(node, el);
        }
      }
    }
    visited[node] = true;
    queue.removeMin();
  }

  return distance;
}

/// Algorithm based on Dijkstra which returns the shortest path from a given
/// start node to the end node
std::vector<Node *> restorePath(MyGraph &graph, Node *startNode,
                                Node *endNode) {
  PriorityQueue<Node *> queue;
  std::map<Node *, int> distance;
  std::map<Node *, bool> visited;
  std::map<Node *, Node *> parent;

  for (auto node : graph.getNodes()) {
    distance[node] = oo;
    visited[node] = false;
    queue.insert(node, distance[node]);
    parent[node] = nullptr;
  }

  distance[startNode] = 0;
  queue.update(startNode, oo, 0);

  while (!queue.empty()) {
    Node *node = queue.getMin();
    for (auto el : graph.getNeighbors(node)) {
      if (visited[el] == false) {
        if (distance[el] > distance[node] + graph.getEdgeWeight(node, el)) {
          queue.update(el, distance[el],
                       distance[node] + graph.getEdgeWeight(node, el));
          parent[el] = node;
          distance[el] = distance[node] + graph.getEdgeWeight(node, el);
        }
      }
    }
    visited[node] = true;
    queue.removeMin();
  }

  std::vector<Node *> path;
  Node *curNode = endNode;

  while (curNode != nullptr) {
    path.push_back(curNode);
    curNode = parent[curNode];
  }

  std::reverse(path.begin(), path.end());
  return path;
}

int main() {
  MyGraph graph;

  buildGraph(graph);
  Node *startNode = graph.getNode("Frankfurt");
  Node *endNode = graph.getNode("Munchen");

  std::map<Node *, int> distances = dijkstra(graph, startNode);
  std::vector<Node *> path = restorePath(graph, startNode, endNode);
  // Mark all cities on path from Frankfurt to Munchen as special
  for (Node *node : path)
    node->isSpecial = true;

  // Set labels with distance
  for (Node *node : graph.getNodes()) {
    std::string dist_label = " (" + std::to_string(distances[node]) + ")";
    node->data += dist_label;
  }

  std::cout << graph.getDotRepresentation() << '\n';

  return 0;
}