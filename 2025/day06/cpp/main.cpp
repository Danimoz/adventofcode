#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "../../common/cpp/utils.hpp"

long long part1(const std::string &input)
{
  const std::vector<std::string> inputLines = splitString(input, "\n");
  std::vector<std::vector<std::string>> inputArr;

  for (const auto &line : inputLines)
  {
    const std::vector<std::string> arr = splitString(line, " ");
    std::vector<std::string> row;
    for (const auto &i : arr)
    {
      if (i.empty())
        continue;
      row.push_back(i);
    }
    inputArr.push_back(row);
  }

  const int colSize = inputArr[0].size();
  const int rowSize = inputArr.size() - 1;

  long long result = 0;

  for (int c = 0; c < colSize; ++c)
  {
    const std::string operand = inputArr[rowSize - 1][c];
    long long rowTotal = operand == "+" ? 0 : 1;

    for (int r = 0; r < rowSize - 1; ++r)
    {
      rowTotal = operand == "+" ? rowTotal + std::stoi(inputArr[r][c]) : rowTotal * std::stoi(inputArr[r][c]);
    }
    result += rowTotal;
  }

  return result;
}

/**
 * @brief Splits the input string into a grid of characters, handling lines.
 * This function is equivalent to the Python: G = [list(row) for row in D.splitlines()]
 * @param input The raw input string containing the worksheet.
 * @return std::vector<std::string> A grid where each string is a row.
 */
std::vector<std::string> getCharacterGrid(const std::string &input){
  std::vector<std::string> grid;
  std::stringstream ss(input);
  std::string row;
  while (std::getline(ss, row)){
    // Remove '\r' from Windows input if present, ensuring consistent length
    if (!row.empty() && row.back() == '\r'){
      row.pop_back();
    }
    grid.push_back(row);
  }
  return grid;
}

/**
 * @brief Solves Part 2 of the Cephalopod Math problem using the correct vertical number reading.
 * This logic directly translates the functionality of the Python 'p2' calculation.
 * @param input The raw worksheet input.
 * @return long long The final grand total.
 */
long long part2(const std::string &input){
  // 1. Create the grid
  std::vector<std::string> grid = getCharacterGrid(input);
  if (grid.empty())
    return 0;

  const int rowCount = grid.size();

  // Find the maximum column width across all rows
  int maxColWidth = 0;
  for (const auto &row : grid)
  {
    maxColWidth = std::max(maxColWidth, (int)row.length());
  }

  // 2. Main logic loop (iterates through columns to find separators)
  long long totalScore = 0;
  int startCol = 0; // The starting column index of the current problem

  // Loop through all columns + 1 (to catch the final problem)
  for (int currentCol = 0; currentCol <= maxColWidth; ++currentCol){
    bool isBlank = true;

    // Check if the current column 'currentCol' is entirely blank
    if (currentCol < maxColWidth){
      for (int row = 0; row < rowCount; ++row){
        // Check if the character at grid[row][currentCol] exists and is not a space
        if (currentCol < grid[row].length() && grid[row][currentCol] != ' '){
          isBlank = false;
          break;
        }
      }
    }

    // If we hit a blank column or the end of the grid, process the problem block
    if (isBlank && currentCol > startCol){
      // Found problem block between [startCol, currentCol - 1]
      // The operator is in the last row, at the start of the block
      // NOTE: The operator is read from the last non-space column *before* the separator
      char operatorChar = grid[rowCount - 1][startCol];
      if (operatorChar != '+' && operatorChar != '*'){
        // Fallback: search for the operator in the operator row of the block
        for (int col = startCol; col < currentCol; ++col){
          if (col < grid[rowCount - 1].length() && (grid[rowCount - 1][col] == '+' || grid[rowCount - 1][col] == '*')){
            operatorChar = grid[rowCount - 1][col];
            break;
          }
        }
      }

      // Fallback: If no operator is found, this is an error or skip.
      if (operatorChar != '+' && operatorChar != '*'){
        startCol = currentCol + 1;
        continue;
      }

      long long score = (operatorChar == '+') ? 0 : 1;

      // Cephalopod Math Logic (p2): Iterate columns RIGHT-to-LEFT within the problem block
      for (int col = currentCol - 1; col >= startCol; --col) {

        // Read the number vertically (top-to-bottom) for the current column 'col'
        long long number = 0;
        bool isValidNumber = false;

        // Rows 0 to rowCount-2 are the digit rows
        for (int row = 0; row < rowCount - 1; ++row){
          if (col < grid[row].length() && grid[row][col] >= '0' && grid[row][col] <= '9'){
            // Vertical read is M.S.D to L.S.D
            number = number * 10 + (grid[row][col] - '0');
            isValidNumber = true;
          }
        }

        // Only process if a number was actually found in this column
        if (isValidNumber){
          if (operatorChar == '+'){
            score += number;
          }
          else{
            score *= number;
          }
        }
      }

      // Add the problem's score to the grand total
      totalScore += score;

      // Set the start of the next problem to the column AFTER the separator
      startCol = currentCol + 1;
    }
    else if (isBlank){
      // This handles multiple blank columns in a row
      startCol = currentCol + 1;
    }
  }

  return totalScore;
}

int main()
{
  try
  {
    std::cout << "Running Day 6 C++ Solutions\n";
    const std::string input = readFileIntoString("input.txt");

    std::cout << "Part 1:" << part1(input) << '\n';
    std::cout << "Part 2:" << part2(input) << '\n';
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}