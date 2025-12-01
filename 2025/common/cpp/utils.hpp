#pragma once
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readInput(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open file: " + filename);
  }
  std::vector<std::string> lines;
  std::string line;

  while(std::getline(file, line)) {
    lines.emplace_back(std::move(line));
  }

  return lines;
}