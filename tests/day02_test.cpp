#include <stdexcept>
#define main day02_solution_main
#include "../2025/day02/cpp/main.cpp"
#undef main

void expect(const std::string& range, long long first, long long second) {
  const std::vector<std::string> input{range};
  if (part1(input) != first || optimizedPart1(input) != first || part2(input) != second) {
    throw std::runtime_error("Unexpected repeated-number result for " + range);
  }
}

int main() {
  expect("1-9", 0, 0);
  expect("11-22", 33, 33);
  expect("99-111", 99, 210);
  expect("111-111", 0, 111);
  expect("1000-1000", 0, 0);
  expect("1234-1234", 0, 0);
  expect("123123-123123", 123123, 123123);
  expect("111111-111111", 111111, 111111);
  for (long long start = 1; start <= 20000; start += 137) {
    const std::vector<std::string> input{
        std::to_string(start) + "-" + std::to_string(start + 300)};
    if (part1(input) != optimizedPart1(input)) {
      throw std::runtime_error("Optimized sum disagrees with enumeration");
    }
  }
  const std::vector<std::string> ranges{"9-12", "98-112", "999-1012", "9999-10102"};
  if (part1(ranges) != optimizedPart1(ranges)) {
    throw std::runtime_error("Decimal-boundary or multi-range regression");
  }
  std::cout << "Day 2: expected sums, decimal boundaries and differential checks passed\n";
}
