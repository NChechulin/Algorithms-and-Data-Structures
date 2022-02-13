#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

bool cmp(int a, int b) { return a > b; }

bool checkTriangle(int a, int b, int c) {
  // since the input is sorted (a > b > c) we can only check this part
  return (b + c) > a && a > 0;
}

double getArea(int a, int b, int c) {
  const double p = double(a + b + c) / 2;
  return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

void printvec(std::vector<int> &v) {
  for (int i : v)
    std::cout << i << ' ';
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> segments(n);
  for (int i = 0; i < n; ++i)
    std::cin >> segments[i];

  if (n < 3) {
    std::cout << "0\n";
    return 0;
  }

  std::vector<int> q;
  for (int i = 0; i < 3; ++i) {
    const auto to = std::next(segments.begin(), i);
    std::nth_element(segments.begin(), to, segments.end(), cmp);

    q.push_back(segments[i]);
  }

  double maxarea = 0;
  std::vector<int> ans;

  for (int i = 3; i < n + 1; ++i) {
    int a = q[0], b = q[1], c = q[2];

    if (checkTriangle(a, b, c) && getArea(a, b, c) > maxarea) {
      ans = q;
      maxarea = getArea(a, b, c);
    }
    const auto to = std::next(segments.begin(), i);
    std::nth_element(segments.begin(), to, segments.end(), cmp);

    q[0] = q[1];
    q[1] = q[2];
    q[2] = segments[i];
  }

  if (!ans.size())
    std::cout << 0 << '\n';
  else {
    int a = ans[0], b = ans[1], c = ans[2];

    std::cout << std::setprecision(3) << std::fixed << getArea(a, b, c) << '\n';
    std::cout << c << ' ' << b << ' ' << a << '\n';
    return 0;
  }

  return 0;
}