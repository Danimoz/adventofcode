#include <iostream>
#include "../../common/cpp/utils.hpp"

int mod(int a, int m) {
  int remainder = a % m;
  return remainder < 0 ? remainder + m : remainder;
}

int part1(const std::vector<std::string>& input) {
  int dial = 50;
  int hits = 0;

  for (const auto& line : input) {
    const char direction = line[0];
    const int amount = std::stoi(line.substr(1));

    if (direction == 'L'){
      dial = mod(dial - amount, 100);
    } else if (direction == 'R'){
      dial = mod(dial + amount, 100);
    }

    if (dial == 0){
      ++hits;
    }
  }

  return hits;
}

int part2(const std::vector<std::string> &input){
  // Initial state
  int dial = 50;
  long long hits = 0; // Use long long for hits just in case rotations are huge

  for (const auto &line : input){
    const char direction = line[0];
    const int amount = std::stoi(line.substr(1));

    // --- Core Fix: Separate Full Cycles from Remainder ---

    // 1. Count guaranteed hits from full 100-click revolutions
    hits += amount / 100;
    int remainder = amount % 100;

    if (direction == 'R'){
      // 2. Check if the remainder causes one additional hit by crossing 99 -> 0
      if (dial + remainder >= 100){
        hits++;
      }
      dial = mod(dial + amount, 100);
    } else if (direction == 'L'){
      // 2. Check if the remainder causes one additional hit by crossing 0
      // A hit occurs if the movement crosses/lands on 0 (dial - remainder <= 0),  BUT ONLY if the dial didn't start at 0 (0 -> 99 is not a hit).
      if (dial != 0 && dial - remainder <= 0){
        hits++;
      }
      dial = mod(dial - amount, 100);
    }
  }

  return (int)hits;
}


int main() {
  auto input = readLines("input.txt");
  std::cout << "Part 1: " << part1(input) << '\n';
  std::cout << "Part 2: " << part2(input) << '\n';
  return 0;
}