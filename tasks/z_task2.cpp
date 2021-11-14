// Exercise #2: Code a program that finds all distinct words in a file.
// Then, sort all the words in ascendant order according to their frequency by
// using ONLY some of the sorting algorithms we coded in previous seminars. You
// cannot use ordered containers to save distinct words. You can use unordered
// containers such as std::unordered_map, std::unordered_set, std::vector.

#include "minheap.cpp"
#include "z_algorithm.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>


std::unordered_map<std::string, int> freqs;
ZFinder *finder;

bool metWordBefore(const std::string &word) {
  return freqs.find(word) != freqs.end();
}

std::ifstream &fillFrequencies(std::ifstream &file) {
  std::string token;

  while (file >> token) {
    if (metWordBefore(token))
      freqs[token]++;
    else
      freqs[token] = 1;
  }

  return file;
}

template <typename K, typename V>
std::vector<std::pair<V, K>>
mapToVec(const std::unordered_map<K, V> &some_map) {
  std::vector<std::pair<V, K>> result;

  for (auto pair : some_map)
    result.push_back({pair.second, pair.first});

  return result;
}

int main() {
  std::ifstream infile = std::ifstream("z_task2_files/alice.txt");
  fillFrequencies(infile);

  auto freqs_vec = mapToVec(freqs);
  MinHeap<std::pair<int, std::string>>::heapSort(freqs_vec);

  for (auto pair : freqs) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }
}
