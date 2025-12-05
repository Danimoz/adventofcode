#include <iostream>
#include <algorithm>
#include "../../common/cpp/utils.hpp"

struct Range {
  long long start;
  long long end;
};

// Time Complexity O(M * N)
int part1(const std::vector<std::string> &ranges, const std::vector<std::string> &ingredients){
  int count = 0;

  for (const auto &ingredient : ingredients){
    std::string trimmedIngredient = trim(ingredient);
    if (trimmedIngredient.empty()) continue;

    const long long ingredientValue = std::stoll(trimmedIngredient);

    for (const auto &range : ranges){
      std::string trimmedRange = trim(range);
      if (trimmedRange.empty()) continue;

      const std::vector<std::string> rangeArray = splitString(trimmedRange, "-");
      if (rangeArray.size() < 2) continue;

      const long long start = std::stoll(trim(rangeArray[0]));
      const long long end = std::stoll(trim(rangeArray[1]));

      if (ingredientValue >= start && ingredientValue <= end){
        ++count;
        break;
      }
    }
  }

  return count;
}

// Time Complexity O(N log N + M log N)
int optimizedPart1(const std::vector<std::string> &ranges, const std::vector<std::string> &ingredients){
  std::vector<Range> parsedRanges;
  parsedRanges.reserve(ranges.size());

  for (const auto &range : ranges){
    std::string trimmedRange = trim(range);
    if (trimmedRange.empty()) continue;

    const std::vector<std::string> rangeArray = splitString(trimmedRange, "-");
    if (rangeArray.size() < 2) continue;

    const long long start = std::stoll(trim(rangeArray[0]));
    const long long end = std::stoll(trim(rangeArray[1]));
    parsedRanges.push_back({start, end});
  }

  if (parsedRanges.empty())
    return 0;

  // Sort ranges by start time
  std::sort(parsedRanges.begin(), parsedRanges.end(), [](const Range &a, const Range &b)
            { return a.start < b.start; });

  // Merge overlapping or adjacent ranges
  std::vector<Range> mergedRanges;
  mergedRanges.push_back(parsedRanges[0]);

  for (size_t i = 1; i < parsedRanges.size(); ++i){
    if (parsedRanges[i].start <= mergedRanges.back().end + 1){
      mergedRanges.back().end = std::max(mergedRanges.back().end, parsedRanges[i].end);
    }
    else{
      mergedRanges.push_back(parsedRanges[i]);
    }
  }

  int count = 0;
  for (const auto &ingredient : ingredients){
    std::string trimmedIngredient = trim(ingredient);
    if (trimmedIngredient.empty()) continue;

    long long val = std::stoll(trimmedIngredient);

    // Binary search for the range
    auto it = std::upper_bound(mergedRanges.begin(), mergedRanges.end(), val, [](long long value, const Range &r)
                               { return value < r.start; });

    if (it != mergedRanges.begin()){
      auto prev = std::prev(it);
      if (val >= prev->start && val <= prev->end){
        count++;
      }
    }
  }
  return count;
}

long long part2(const std::vector<std::string> &ranges)
{
  std::vector<Range> parsedRanges;

  for (const auto &range : ranges)
  {
    std::string trimmedRange = trim(range);
    if (trimmedRange.empty())
      continue;

    const std::vector<std::string> rangeArray = splitString(trimmedRange, "-");
    if (rangeArray.size() < 2)
      continue;

    const long long start = std::stoll(trim(rangeArray[0]));
    const long long end = std::stoll(trim(rangeArray[1]));
    parsedRanges.push_back(Range{start, end});
  }

  std::sort(parsedRanges.begin(), parsedRanges.end(), [](const Range &a, const Range &b)
            { return a.start < b.start; });

  long long count = 0;
  long long currentStart = parsedRanges[0].start;
  long long currentEnd = parsedRanges[0].end;

  // Merge overlapping ranges and count total coverage
  for (size_t i = 1; i < parsedRanges.size(); ++i)
  {
    // Check for Overlap
    if (parsedRanges[i].start <= currentEnd)
    {
      // Extend the current end if the new range goes further
      currentEnd = std::max(currentEnd, parsedRanges[i].end);
    }
    else
    {
      // No overlap, add the current range length to count
      count += (currentEnd - currentStart) + 1;
      // Reset current pointers to the new range
      currentStart = parsedRanges[i].start;
      currentEnd = parsedRanges[i].end;
    }
  }
  // Add the last range
  count += (currentEnd - currentStart) + 1;
  return count;
}

int main()
{
  try
  {
    std::cout << "Running Day 5 C++ Solutions\n";
    std::string input = readFileIntoString("input.txt");

    // Remove carriage returns to handle Windows line endings consistently
    input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
    const std::vector<std::string> parts = splitString(input, "\n\n");

    if (parts.size() < 2)
    {
      std::cerr << "Error: Input does not contain two sections separated by double newline.\n";
      return 1;
    }

    const std::string &ranges = parts[0];
    const std::vector<std::string> rangesArray = splitString(ranges, "\n");
    const std::string &availableIngredients = parts[1];
    const std::vector<std::string> ingredientsArray = splitString(availableIngredients, "\n");

    std::cout << "Part 1:" << part1(rangesArray, ingredientsArray) << "\n";
    std::cout << "Optimized Part 1: " << optimizedPart1(rangesArray, ingredientsArray) << "\n";
    std::cout << "Part 2: " << part2(rangesArray) << "\n";
  }
  catch (const std::exception &e){
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}