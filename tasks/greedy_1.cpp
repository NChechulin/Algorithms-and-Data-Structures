#include <iostream>
#include <vector>

int main() {
  std::vector<int> house_positions = {1, 3, 7, 12, 15, 16};
  std::vector<int> ans;

  int repeater_range = 1;

  int last_covered_pos = -1e9;

  for (int pos : house_positions) {
    if (pos <= last_covered_pos + repeater_range)
      continue;

    last_covered_pos = pos + 3 * repeater_range;
    ans.push_back(pos + 2 * repeater_range);
  }

  for (int pos : ans)
    std::cout << pos << ' ';
  std::cout << '\n';

  // TODO: fix positions from ans

  return 0;
}