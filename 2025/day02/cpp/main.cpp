#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../../common/cpp/utils.hpp"

bool isInvalid(const std::string &password){
  bool is_valid = false;
  auto half = password.size() / 2;
  std::string firstHalf = password.substr(0, half);
  std::string secondHalf = password.substr(half);
  if (firstHalf == secondHalf){
    is_valid = true;
  }
  return is_valid;
}

long long part1(const std::vector<std::string> &input){
  long long total = 0;

  for (const auto &range : input){
    auto parts = splitString(range, '-');
    long long start = std::stoll(parts[0]);
    long long end = std::stoll(parts[1]);

    for (long long i = start; i <= end; ++i){
      const std::string numStr = std::to_string(i);
      if ((numStr.size() % 2) != 0)
        continue;
      if (isInvalid(numStr)){
        total += i;
      }
    }
  }
  return total;
}

/*
  The brute-force version looped over every integer from L to R, converted it to a string, checked the length and halves, and summed valid numbers. This is inefficient for large ranges.
  The optimized version avoids iteration by mathematically generating and summing only the valid N using the formula N = M * (10^k + 1), where k is the half length, M is  the first half.
  The code loops over possible k values (1 to 9), calculates the valid range for M based on L and R, and sums the valid N directly.
  e.g. for 1212, M=12, k=2, N=12*(10^2+1)=1212
*/
long long optimizedPart1(const std::vector<std::string> &input){
  long long total = 0;

  for (const auto &range : input){
    auto parts = splitString(range, '-');
    long long start = std::stoll(parts[0]);
    long long end = std::stoll(parts[1]);
    /*
    Why loop L from 1 to 9?
     - This covers full number lengths from 2 to 18 digits (since N has even length 2k).
     - long long can hold up to 19 digits, so k=9 (18 digits) is the max valid half-length to avoid overflow.
     - for each round, we find all valid N = M * (10^k + 1) within [start, end].
    */
    for (int L = 1; L <= 9; ++L){
      long long powerOf10L = 1LL;

      /*
       Why a Loop instead of std::pow?
        - std::pow returns double, which loses precision for large integers.
      */
      for (int k = 0; k < L; ++k){
        powerOf10L *= 10;
      }

      long long multiplier = powerOf10L + 1; //(10^L + 1)
      /*
        Compute Base Minimum and Maximum for M
         - M must be L digits, so min is 10^(L-1) and max is 10^L - 1 (e.g. for L=2, M in [10, 99])
      */
      long long min_X = powerOf10L / 10;
      long long max_X = powerOf10L - 1;

      /*
        Compute ceiling of L
        Purpose: Finds the smallest integer M such that N = M * (10^L + 1) >= start
        - Ensures we start from the first valid N >= start
      */
      long long lower_bound_X = (start + multiplier - 1) / multiplier;
      long long upper_bound_X = end / multiplier;

      long long actual_min = std::max(min_X, lower_bound_X);
      long long actual_max = std::min(max_X, upper_bound_X);

      if (actual_min <= actual_max) {
        long long count = actual_max - actual_min + 1;
        long long sum_X = (actual_min + actual_max) * count / 2;
        total += sum_X * multiplier;
      }
    }
  }
  return total;
}

long long part2(const std::vector<std::string> &input){
  long long total = 0;
  for (const auto &range : input){
    auto parts = splitString(range, '-');
    long long start = std::stoll(parts[0]);
    long long end = std::stoll(parts[1]);

    for (long long i = start; i <= end; ++i){
      const std::string numStr = std::to_string(i);
      if (!numStr.empty() && numStr.front() != '0'){
        int n = numStr.size();
        bool isRepeated = false;

        for (int d = 1; d * 2 <= n && !isRepeated; ++d){
          if (n % d != 0) continue;
          int k = n / d;
          if (k < 2) continue;

          bool ok = true;
          for (int i = 1; i < k && ok; ++i){
            for (int j = 0; j < d; ++j){
              if (numStr[j] != numStr[i * d + j]){
                ok = false;
                break;
              }
            }
          }
          if (ok) isRepeated = true;
        }
        if (isRepeated) total += i;
      }
    }
  }
  return total;
}

int main(){
  try{
    std::cout << "Running Day 2 C++ Solutions\n";
    auto input = readFileIntoString("input.txt");
    auto ranges = splitString(input, ',');

    std::cout << "Part 1: " << part1(ranges) << '\n';
    std::cout << "Optimized Part 1: " << optimizedPart1(ranges) << '\n';
    std::cout << "Part 2: " << part2(ranges) << '\n';
  } catch (const std::exception &ex)
  {
    std::cerr << "Exception: " << ex.what() << '\n';
    return 1;
  }
  return 0;
}