#include <iostream>
#include "../../common/cpp/utils.hpp"

struct ManualData {
  std::string lights;
  std::vector<std::vector<int>> buttons;
  std::vector<int> joltage;
};

ManualData parseManual(std::string line) {
  ManualData data;

  const size_t startBracket = line.find("[");
  const size_t endBracket = line.find("]");
  data.lights = line.substr(startBracket + 1, endBracket - startBracket - 1);

  // -- Parse Buttons
  size_t pos = endBracket + 1;

  while (true) {
    size_t openParen = line.find("(", pos);
    size_t curlyBrace = line.find("{", pos);

    if (openParen == std::string::npos || (curlyBrace != std::string::npos && openParen > curlyBrace)) {
      break;
    }

    size_t closeParen = line.find(')', openParen);
    std::string content = line.substr(openParen + 1, closeParen - openParen - 1);
    std::vector<std::string> currentButton = splitString(content, ",");
    std::vector<int> buttonIndices;
    for (const auto& button : currentButton) {
      buttonIndices.push_back(std::stoi(button));
    }
    data.buttons.push_back(buttonIndices);
    pos = closeParen + 1;
  }

  // -- Parse Joltage
  size_t startCurlyBrace = line.find("{", pos);
  size_t endCurlyBrace = line.find("}", pos);
  if (startCurlyBrace != std::string::npos && endCurlyBrace != std::string::npos) {
    std::string joltageStr = line.substr(startCurlyBrace + 1, endCurlyBrace - startCurlyBrace - 1);
    std::vector<std::string> joltageStrArr = splitString(joltageStr, ",");
    for (const auto& joltage : joltageStrArr) {
      data.joltage.push_back(std::stoi(joltage));
    }
  }

  return data;
}

int solution( const ManualData& data) {
  int targetMask = 0;
  for (int i = 0; i < data.lights.length(); ++i) {
    if (data.lights[i] == '#') {
      targetMask |= (1 << i);
    }
  }

  std::vector<int> buttonMasks;
  for (const auto &btnIndices : data.buttons) {
    int mask = 0;
    for (int idx: btnIndices) {
      mask |= (1 << idx);
    }
    buttonMasks.push_back(mask);
  }

  int numButtons = buttonMasks.size();
  int minPresses = INT_MAX;

  for (int i = 0; i < (1 << numButtons); ++i) {
    int currentResult = 0;
    for (int j = 0; j < numButtons; ++j) {
      if ((i >> j) & 1) {
        currentResult ^= buttonMasks[j];
      }
    }

    if (currentResult == targetMask) {
      minPresses = std::min(minPresses, __builtin_popcount(i));
    }
  }

  return (minPresses == INT_MAX) ? 0 : minPresses;
}

int main() {
  std::vector<std::string> inputLines = readLines("input.txt");
  long long totalPresses = 0;

  for (const auto& line : inputLines) {
    ManualData data = parseManual(line);
    totalPresses += solution(data);
  }

  std::cout << "Part 1: " << totalPresses << std::endl;
  return 0;
}