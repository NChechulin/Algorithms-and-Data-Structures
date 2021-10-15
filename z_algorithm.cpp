#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Exercise #1: Create a class "ZFinder" with a constructor that receives the
// pattern to search in a text An integer function "find" in class "ZFinder"
// must return the index of the next occurrence of the pattern in the text. A
// function "freq" that returns the number of occurrences of the pattern in the
// text.

class ZFinder {
public:
  ZFinder(std::string text, std::string pattern) {
    _text = text;
    _pattern = pattern;
    _joined = pattern + '$' + text;
    _cur = 0;
    computeZ();
  }

  int freq() const {
    return std::count(_z_arr.begin(), _z_arr.end(), _pattern.size());
  }

  int find() {
    const int start = std::max(_pattern.size() + 1, _cur + 1);
    for (int i = start; i < _joined.size(); i++) {
      if (_z_arr[i] == _pattern.size()) {
        _cur = i;
        return i - _pattern.size() - 1;
      }
    }

    return -1;
  }

private:
  unsigned long _cur;
  std::string _text;
  std::string _pattern;
  std::string _joined;
  std::vector<int> _z_arr;

  void computeZ() {
    _z_arr = std::vector<int>(_joined.size(), 0);

    int L = 0, R = 0;

    for (int k = 1; k < _joined.size(); k++) {
      if (k > R) {
        int cnt = compareParts(k, 0);
        _z_arr[k] = cnt;
        L = k;
        R = k + cnt - 1;
      } else {
        if (_z_arr[k - L] < R - k + 1) {
          _z_arr[k] = _z_arr[k - L];
        } else {
          int cnt = compareParts(R + 1, R - L + 1);
          _z_arr[k] = (R - k + 1) + cnt;
          L = k;
          R = R + _z_arr[k] - 1;
        }
      }
    }
  }

  int compareParts(const int first, const int second) const {
    int cnt = 0;
    int max = std::max(first, second);

    while (max + cnt < _joined.size() &&
           _joined[first + cnt] == _joined[second + cnt])
      cnt++;

    return cnt;
  }
};

// int main() {
//   std::string text = "If a dog chews shoes, whose shoes does he choose?";
//   std::string pattern = "oes";

//   ZFinder zFinder(text, pattern);

//   std::cout << "Number of ocurrences: " << zFinder.freq() << std::endl;

//   int pos = zFinder.find();

//   while (pos != -1) {
//     std::cout << pos << std::endl;
//     pos = zFinder.find();
//   }

//   return 0;
// }