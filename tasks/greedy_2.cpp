#include <algorithm>
#include <iostream>
#include <vector>

#define all(x) x.begin(), x.end()

int main() {
  std::vector<int> production_times = {1, 6, 4};

  std::vector<std::pair<int, int>> schedule;
  for (int time : production_times)
    schedule.push_back({time, schedule.size()});

  std::sort(all(schedule));

  for (auto p : schedule)
    std::cout << p.second + 1 << ' ';
  std::cout << '\n';
}