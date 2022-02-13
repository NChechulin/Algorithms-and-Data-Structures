#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

typedef std::pair<int, int> coordinate;
typedef std::vector<coordinate> path;

#define int long long

int w, h;

void print_matrix(const std::vector<std::vector<int>> &matrix) {
  for (auto row : matrix) {
    for (auto e : row)
      std::cout << e << ' ';
    std::cout << '\n';
  }
}

int min3(int a, int b, int c) { return std::min(a, std::min(b, c)); }

void update_weights(std::vector<std::vector<int>> &matrix) {
  for (int r = 1; r < h; ++r) {
    for (int c = 1; c < w + 1; ++c)
      matrix[r][c] +=
          min3(matrix[r - 1][c - 1], matrix[r - 1][c], matrix[r - 1][c + 1]);
  }
}

int min_element_pos(const std::vector<int> &vec, int from, int to) {
  auto from_it = std::next(vec.begin(), from);
  auto to_it = std::next(vec.begin(), to);
  auto it = std::min_element(from_it, to_it);
  return std::distance(vec.begin(), it);
}

int min_element_pos(const std::vector<int> &vec) {
  auto it = std::min_element(vec.begin(), vec.end());
  return std::distance(vec.begin(), it);
}

path restore_path(const std::vector<std::vector<int>> &matrix) {
  path result;

  int start_pos = min_element_pos(matrix.back());
  result.push_back({matrix.size() - 1, start_pos - 1});

  for (int i = matrix.size() - 1; i > 0; --i) {
    auto prev_row = matrix[i - 1];
    int new_pos = min_element_pos(prev_row, start_pos - 1, start_pos + 2);
    start_pos = new_pos;
    result.push_back({i - 1, new_pos - 1});
  }

  std::reverse(result.begin(), result.end());
  return result;
}

signed main() {
  std::cin >> h >> w;

  std::vector<std::vector<int>> matrix(h, std::vector<int>(w + 2, INT32_MAX));

  for (int r = 0; r < h; ++r)
    for (int c = 1; c < w + 1; ++c)
      std::cin >> matrix[r][c];

  update_weights(matrix);
  auto res = restore_path(matrix);

  auto final_pos = res.back();
  int res_weight = matrix[final_pos.first][final_pos.second + 1];

  std::cout << res_weight << '\n';

  for (auto e : res)
    std::cout << '(' << e.first + 1 << "," << e.second + 1 << ") ";

  return 0;
}