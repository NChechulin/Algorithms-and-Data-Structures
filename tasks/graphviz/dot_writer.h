#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class GraphvizNode {
public:
  std::string name, label;
  bool isSpecial;

  GraphvizNode(const std::string &name, const std::string &label,
               bool isSpecial)
      : name(name), label(label), isSpecial(isSpecial) {}

  std::string getStyle() const {
    return isSpecial ? "[shape = oval, color = red]" : "[shape = box]";
  }

  std::string getDotRepresentation() const {
    return "\t\"" + name + "\" " + getStyle() + '\n';
  }
};

class GraphvizEdge {
public:
  std::string from, to;
  int weight;
  bool isSpecial;

  GraphvizEdge(const std::string &from, const std::string &to, int weight,
               bool isSpecial)
      : from(from), to(to), weight(weight), isSpecial(isSpecial) {}

  std::string getStyle() const {
    std::string default_style =
        "[dir = none, label = " + std::to_string(weight);
    return default_style + (isSpecial ? ", penwidth = 2]" : "]");
  }

  std::string getDotRepresentation() const {
    return "\t\"" + from + "\"" + " -> " + "\"" + to + "\"" + " " + getStyle() +
           '\n';
  }

  bool operator==(const GraphvizEdge &rhs) {
    return rhs.from == from && rhs.to == to && rhs.weight == weight;
  }
};

class DotWriter {
public:
  void addNode(const std::string &name, const std::string &label,
               bool isSpecial) {
    _nodes.push_back(GraphvizNode(name, label, isSpecial));
  }

  void addEdge(const std::string &from, const std::string &to, int weight,
               bool isSpecial) {
    const GraphvizEdge backwards = GraphvizEdge(to, from, weight, isSpecial);
    const GraphvizEdge edge = GraphvizEdge(from, to, weight, isSpecial);
    // check if edge in other direction is not in the vec
    if (std::find(_edges.begin(), _edges.end(), backwards) == _edges.end())
      _edges.push_back(edge);
  }

  std::string getDotRepresentation(const std::string &graphName) const {
    std::string result;
    result += "digraph " + graphName + " {\n";

    for (auto &n : _nodes)
      result += n.getDotRepresentation();

    for (auto &e : _edges)
      result += e.getDotRepresentation();

    result += "}\n";

    return result;
  }

private:
  std::vector<GraphvizNode> _nodes;
  std::vector<GraphvizEdge> _edges;
};
