#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../../common/cpp/utils.hpp"

long long part1(const std::vector<std::string> &input) {
  long long total = 0;

  for (const auto &bank : input) {
    int max_joltage = 0;

    for (int i = 0; i< bank.size() - 1; ++i){
      for(int j = i+1; j < bank.size(); ++j){
        if ( i != j) {
          int joltage = 10 * (bank[i] - '0') + (bank[j] - '0');
          max_joltage = std::max(max_joltage, joltage);
        }
      }
    }
    total += max_joltage;
  }
    
  return total;
}


long long part2(const std::vector<std::string> &input) {
  long long total = 0;
  const int D = 12;

  for (const auto &bank : input) {
    std::string result = "";
    int current_search_start = 0;

    for (int digits_selected = 0; digits_selected < D; ++digits_selected){
      int digits_remaining = D - digits_selected;
      int max_search_end = bank.size() - digits_remaining;
      char max_digit = '0' - 1; // Initialize to SLASH '/' which will be overwritten later
      int max_digit_index = -1;

      for (int i = current_search_start; i <= max_search_end; ++i){
        if (bank[i] > max_digit){
          max_digit = bank[i];
          max_digit_index = i;
        }
      }
      result += max_digit;
      current_search_start = max_digit_index + 1;
    }
    total += std::stoll(result);
  }

  return total;
}

int main() {
  try {
    std::cout << "Running Day 3 C++ Solutions\n";
    auto input = readLines("input.txt");
    std::cout << "Part 1: " << part1(input) << '\n';
    std::cout << "Part 2: " << part2(input) << '\n';
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
  return 0;
}