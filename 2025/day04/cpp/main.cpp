#include <iostream>
#include "../../common/cpp/utils.hpp"

int part1(const std::vector<std::vector<char>> &grid){
  int count = 0;
  int rows = grid.size();
  int cols = grid.empty() ? 0 : grid[0].size();

  for (int r = 0; r < rows; ++r){
    for (int c = 0; c < cols; ++c){
      int neighbors = 0;
      if (grid[r][c] == '@'){
        if (r > 0 && c > 0 && grid[r-1][c-1] == '@') ++neighbors;
        if (r > 0 && grid[r-1][c] == '@') ++neighbors;
        if (r > 0 && c + 1 < cols && grid[r-1][c+1] == '@') ++neighbors;
        if (c > 0 && grid[r][c-1] == '@') ++neighbors;
        if (c + 1 < cols && grid[r][c+1] == '@') ++neighbors;
        if (r + 1 < rows && c > 0 && grid[r+1][c-1] == '@') ++neighbors;
        if (r + 1 < rows && grid[r+1][c] == '@') ++neighbors;
        if (r + 1 < rows && c + 1 < cols && grid[r+1][c+1] == '@') ++neighbors;
        if (neighbors < 4) ++count;
      }
    }
  }

  return count;
}

int part2(std::vector<std::vector<char>> &grid){
  int count = 0;
  int rows = grid.size();
  int cols = grid.empty() ? 0 : grid[0].size();

  while(true){
    std::vector<std::pair<int, int>> to_remove;
    // Scan the current grid but don't modify it during this scan
    for (int r = 0; r < rows; ++r){
      for (int c = 0; c < cols; ++c){
        int neighbors = 0;
        if (grid[r][c] == '@'){
          if (r > 0 && c > 0 && grid[r-1][c-1] == '@') ++neighbors;
          if (r > 0 && grid[r-1][c] == '@') ++neighbors;
          if (r > 0 && c + 1 < cols && grid[r-1][c+1] == '@') ++neighbors;
          if (c > 0 && grid[r][c-1] == '@') ++neighbors;
          if (c + 1 < cols && grid[r][c+1] == '@') ++neighbors;
          if (r + 1 < rows && c > 0 && grid[r+1][c-1] == '@') ++neighbors;
          if (r + 1 < rows && grid[r+1][c] == '@') ++neighbors;
          if (r + 1 < rows && c + 1 < cols && grid[r+1][c+1] == '@') ++neighbors;
          if (neighbors < 4) {
            to_remove.emplace_back(r, c);
          }
        }
      }
    }
    
    if (to_remove.empty()) break;
    count += to_remove.size();
    for (const auto &[r, c] : to_remove) {
      grid[r][c] = '.';
    }
  }

  return count;
}


int main() {
  try {
    auto input = readLines("input.txt");
    auto grid = buildGrid(input);
    std::cout << "Part 1: " << part1(grid) << '\n';
    std::cout << "Part 2: " << part2(grid) << '\n';
  } catch (const std::exception &ex){
    std::cerr << "Exception: " << ex.what() << '\n';
    return 1;
  }
  return 0;
}