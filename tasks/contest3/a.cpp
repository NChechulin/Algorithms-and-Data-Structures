#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int solveRow(const std::vector<int> &row) {
  int ans = 0;
  int boundary = *std::max_element(row.cbegin(), row.cend());

  for (int j = 1; j <= boundary; j++) {
    int counter = 0;
    int max_cntr = 0;

    for (int i = 0; i < row.size(); i++) {
      if (row[i] && j <= row[i])
        counter++;
      else {
        max_cntr = std::max(max_cntr, counter);
        counter = 0;
      }
    }

    max_cntr = std::max(max_cntr, counter);
    ans = std::max(ans, max_cntr * j);
  }

  return ans;
}

int solve(std::vector<std::vector<int>> &dp, int n, int m) {
  int ans = solveRow(dp[0]);

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++)
      if (dp[i][j])
        dp[i][j] += dp[i - 1][j];
    ans = std::max(ans, solveRow(dp[i]));
  }

  return ans;
}

int main() {
  std::ifstream infile("input.txt");

  int n, m;
  infile >> n >> m;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

  for (int i = 0; i < n; ++i) {
    std::string temp;
    infile >> temp;

    for (int j = 0; j < m; ++j)
      matrix[i][j] = (temp[j] - '0') ^ 1;
  }

  std::cout << solve(matrix, n, m) << '\n';

  return 0;
}