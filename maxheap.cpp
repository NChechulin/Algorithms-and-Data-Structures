#include "iostream"
#include "vector"
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T> class MaxHeap {
private:
  std::vector<T> _data;
  int _size;

  int getParentIndex(int child_index) const {
    if (child_index == 0)
      throw std::out_of_range("Root node does not have a parent");
    return (child_index - 1) / 2;
  }

  // returns index of left child of given parent or throws an exception
  int getLeftChildIndex(int parent_index) const {
    int ans = 2 * parent_index + 1;
    if (ans >= _data.size())
      throw std::out_of_range("Element doesn't have a left child");
    return ans;
  }

  // returns index of right child of given parent or throws an exception
  int getRightChildIndex(int parent_index) const {
    int ans = 2 * parent_index + 2;
    if (ans >= _data.size())
      throw std::out_of_range("Element doesn't have a right child");
    return ans;
  }

  // raises smaller element up
  void bubbleUp(int node_index) {
    int parent_index;

    try {
      parent_index = getParentIndex(node_index);
    } catch (std::out_of_range) {
      return;
    }

    if (_data[parent_index] < _data[node_index]) {
      std::swap(_data[parent_index], _data[node_index]);
      bubbleUp(parent_index);
    }
  }

  // lowers bigger element
  void bubbleDown(int node_index) {
    T node = _data[node_index];
    int left_index, right_index;

    try {
      left_index = getLeftChildIndex(node_index);
    } catch (std::out_of_range) {
      left_index = node_index;
    }

    try {
      right_index = getRightChildIndex(node_index);
    } catch (std::out_of_range) {
      right_index = node_index;
    }

    int min_index = node_index;

    if (_data[min_index] < _data[left_index])
      min_index = left_index;
    if (_data[min_index] < _data[right_index])
      min_index = right_index;

    if (min_index != node_index) {
      std::swap(_data[min_index], _data[node_index]);
      bubbleDown(min_index);
    }
  }

  // rearrange a heap to ensure it's properties
  void heapify() {
    for (int i = _size; i >= 0; --i)
      bubbleDown(i);
  }

public:
  MaxHeap<T>(std::vector<T> data) {
    _data = data;
    _size = data.size();

    heapify();
  }

  // sorts the given vector
  static void heapSort(std::vector<T> &data) {
    MaxHeap<T> heap = MaxHeap<T>(data);

    for (int i = 0; i < data.size(); ++i)
      data[i] = heap.pop();
    
    std::reverse(data.begin(), data.end());
  }

  // inerts new element into the heap
  void insert(T value) {
    _data.push_back(value);
    _size++;
    bubbleUp(_size - 1);
  }

  // returns the root (max element) and deletes it from the heap
  T pop() {
    if (_size == 0)
      throw std::out_of_range("Cannot delete element out of empty heap");

    T ans = _data[0];
    _data[0] = _data.back();
    _data.pop_back();
    _size--;
    bubbleDown(0);
    return ans;
  }

  // returns the root of the heap
  T &getRoot() const {
    if (_size == 0)
      throw std::out_of_range("Cannot return element out of empty heap");

    return _data[0];
  }

  // returns number of elements present in heap
  int size() const { return _size; }
};

// int main() {
//   std::vector<int> data = {3, 7, 12, 5, 3, 0, 96};
//   MaxHeap<int> heap = MaxHeap<int>(data);

//   for (int i = 0; i < data.size(); ++i)
//     std::cout << heap.pop() << ' ';

//   std::cout << "\nHEAPSORT:\n";
//   MaxHeap<int>::heapSort(data);

//   for (auto e : data)
//     std::cout << e << ' ';

//   return 0;
// }