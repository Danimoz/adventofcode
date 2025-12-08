#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "../../common/cpp/utils.hpp"

long long part1(const std::vector<std::vector<char>> &tokens) {
  long long count = 0;
  size_t rowSize = tokens.size();
  size_t colSize = tokens[0].size();
  int startCol = 0;

  for (int s = 0; s < tokens.size(); ++s) {
    if (tokens[0][s] == 'S') {
      startCol = s;
    }
  }

  std::unordered_set<int> curr;
  curr.insert(startCol);

  // We're starting at startingRow + 1, starting Row is 0. The S is always at 0
  for (int r = 1; r < rowSize && !curr.empty(); ++r) {
    std::unordered_set<int> next;
    for (int c: curr) {
      if (c < 0 || c >= colSize) continue;
      if (const char cell = tokens[r][c]; cell == '^') {
        ++count;
        int left = c - 1;
        int right = c + 1;
        if (left >= 0) next.insert(left);
        if (right < colSize) next.insert(right);
      } else {
        next.insert(c);
      }
    }
    curr.swap(next);
  }

  return count;
}

long long part2(const std::vector<std::vector<char>> &tokens) {
  size_t rowSize = tokens.size();
  size_t colSize = tokens[0].size();

  int startCol = 0;
  for (int s = 0; s < tokens.size(); ++s) {
    if (tokens[0][s] == 'S') {
      startCol = s;
    }
  }

  std::unordered_map<int, long long> curr;
  curr[startCol] = 1;

  long long exited = 0;
  for (int r = 1; r < rowSize && !curr.empty(); ++r) {
    std::unordered_map<int, long long> next;

    for (auto &p : curr) {
      int col = p.first;
      const long long count = p.second;

      if (col < 0 || col >= colSize) {
        exited += count;
        continue;
      }

      char cell = (col < static_cast<int>(tokens[r].size())) ? tokens[r][col] : '.';
      if (cell == '^') {
        int left = col - 1;
        int right = col + 1;
        if (left >= 0) next[left] += count;
        else exited += count;
        if (right < colSize) next[right] += count;
        else exited += count;
      } else {
        next[col] += count;
      }
    }
    curr.swap(next);
  }

  for (auto &p : curr) {
    exited += p.second;
  }

  return exited;
}

int main() {
  std::cout << "Day 7 Solutions" << '\n';
  const std::vector<std::string> input = readLines("input.txt");
  const auto grid = buildGrid(input);
  std::cout << "Part 1: "  << part1(grid) << '\n';
  std::cout << "Part 2: " << part2(grid) << '\n';

  return 0;
}