// PRIORITY QUEUE

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <set>

template <typename T> class PriorityQueue {

public:
  const T &getMin() const // O(1)
  {
    return _pq.begin()->second;
  }

  void update(const T &x, int oldWeight, int newWeight) // O(LogN)
  {
    _pq.erase(_pq.find({oldWeight, x}));
    _pq.insert({newWeight, x});
  }

  void removeMin() // O(LogN)
  {
    _pq.erase(_pq.begin());
  }

  void insert(const T &x, int weight) { _pq.insert({weight, x}); }

  bool empty() { return !_pq.size(); }

  void print() {
    for (auto pair : _pq)
      std::cout << '(' << pair.first << ',' << pair.second << ") ";
    std::cout << std::endl;
  }

private:
  std::set<std::pair<int, T>> _pq;
};

#endif
