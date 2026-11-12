#include <random>
#include <stdexcept>
#define main day01_solution_main
#include "../2025/day01/cpp/main.cpp"
#undef main

std::pair<int, int> simulate(const std::vector<std::string>& rotations) {
  int dial = 50;
  int landings = 0;
  int crossings = 0;
  for (const auto& rotation : rotations) {
    const int step = rotation.front() == 'L' ? -1 : 1;
    for (int click = 0; click < std::stoi(rotation.substr(1)); ++click) {
      dial = (dial + step + 100) % 100;
      if (dial == 0) ++crossings;
    }
    if (dial == 0) ++landings;
  }
  return {landings, crossings};
}

void check(const std::vector<std::string>& rotations) {
  const auto expected = simulate(rotations);
  if (part1(rotations) != expected.first || part2(rotations) != expected.second) {
    throw std::runtime_error("Dial solution disagrees with click-by-click simulation");
  }
}

int main() {
  check({});
  check({"L50"});
  check({"R50", "L1", "R1"});
  check({"L50", "L100", "R200", "L1", "R1"});
  check({"L49", "L2", "R101", "L350", "R400"});
  std::mt19937 random(2025);
  for (int trial = 0; trial < 200; ++trial) {
    std::vector<std::string> rotations;
    for (int move = 0; move < 64; ++move) {
      rotations.push_back(std::string(random() % 2 ? "L" : "R") +
                          std::to_string(1 + random() % 400));
    }
    check(rotations);
  }
  std::cout << "Day 1: boundary cases and 200 generated sequences passed\n";
}
