#pragma once
#include <fstream>
#include <string_view>
#include <string>
#include <vector>

std::vector<std::string> readLines(const std::string& filename) {
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


std::string readFileIntoString(const std::string& filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if(!in) throw std::runtime_error("Could not open file: " + filename);
  
  // seekg/tellg ask the OS for the file size
  in.seekg(0, std::ios::end);
  std::size_t size = static_cast<std::size_t>(in.tellg());
  in.seekg(0, std::ios::beg);

  std::string result;
  // this allocates exactly the amount of memory we need, so subsequent copy never triggers reallocation
  result.resize(size);

  // read directly from the file's buffer into the string's memory
  result.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  return result;
}


std::vector<std::string> splitString(const std::string_view& str, char delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;

  while (true) {
    size_t pos = str.find(delimiter, start);
    if (pos == std::string_view::npos){
      tokens.emplace_back(str.substr(start));
      break;
    }
    tokens.emplace_back(str.substr(start, pos - start));
    start = pos + 1;
  }

  return tokens;
}