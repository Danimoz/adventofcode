#pragma once
#include <fstream>
#include <string_view>
#include <string>
#include <vector>

inline std::vector<std::string> readLines(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("Could not open file: " + filename);
  }
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line))
  {
    lines.emplace_back(std::move(line));
  }

  return lines;
}

inline std::string readFileIntoString(const std::string &filename){
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (!in)
    throw std::runtime_error("Could not open file: " + filename);

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

inline std::vector<std::string> splitString(const std::string_view &str, const std::string &delimiter){
  std::vector<std::string> tokens;
  size_t start = 0;

  while (true){
    size_t pos = str.find(delimiter, start);
    if (pos == std::string_view::npos){
      tokens.emplace_back(str.substr(start));
      break;
    }
    tokens.emplace_back(str.substr(start, pos - start));
    start = pos + delimiter.length();
  }

  return tokens;
}

inline std::string trim(const std::string &s){
  size_t start = s.find_first_not_of(" \t\n\r");
  if (start == std::string::npos)
    return "";

  size_t end = s.find_last_not_of(" \t\n\r");
  return s.substr(start, end - start + 1);
}

inline std::vector<std::vector<char>> buildGrid(const std::vector<std::string> &input){
  std::vector<std::vector<char>> grid;
  for (const auto &line : input){
    std::vector<char> row;
    for (char ch : line){
      row.emplace_back(ch);
    }
    grid.emplace_back(std::move(row));
  }

  return grid;
}