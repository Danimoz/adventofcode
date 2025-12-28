#include <iostream>
#include "../../common/cpp/utils.hpp"

struct Point {
  int x;
  int y;
};

// --- GEOMETRY UTILITIES FOR PART 2 ---
bool edgeCutsInterior(const Point p1, const Point p2, const long long minX, const long long maxX, const long long minY, const long long maxY) {
  long long x1 = std::min(p1.x, p2.x), x2 = std::max(p1.x, p2.x);
  long long y1 = std::min(p1.y, p2.y), y2 = std::max(p1.y, p2.y);

  if (x1 == x2) {
    if (x1 > minX && x1 < maxX && y1 < maxY && y2 > minY) return true;
  } else {
    if (y1 > minY && y1 < maxY && x1 < maxX && x2 > minX) return true;
  }
  return false;
}

bool isInside(double px, double py, const std::vector<Point> &poly) {
  bool inside = false;
  for (size_t i = 0, j = poly.size() - 1; i < poly.size(); j = i++) {
    if (((poly[i].y > py) != (poly[j].y > py)) &&
      (px < (poly[j].x - poly[i].x) * (py - poly[i].y) /(double)(poly[j].y - poly[i].y) + poly[i].x)) {
      inside = !inside;
    }
  }
  return inside;
}

void solve(const std::vector<std::string> &lines) {
  std::vector<Point> redTiles;

  for (const std::string &line : lines) {
    const std::vector<std::string> parts = splitString(line, ",");
    redTiles.push_back({std::stoi(parts[0]), std::stoi(parts[1])});
  }

  long long maxPart1 = 0;
  long long maxPart2 = 0;
  size_t n = redTiles.size();

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      long long x1 = redTiles[i].x, y1 = redTiles[i].y;
      long long x2 = redTiles[j].x, y2 = redTiles[j].y;

      long long minX = std::min(x1, x2), maxX = std::max(x1, x2);
      long long minY = std::min(y1, y2), maxY = std::max(y1, y2);
      long long area = (maxX - minX + 1) * (maxY - minY + 1);

      // Part 1: No constraints, just find the biggest possible rectangle
      if (area > maxPart1) maxPart1 = area;

      // Part 2 : Geometric Constraints
      if (area > maxPart2) {
        bool wallInWay = false;
        for (size_t k = 0; k < n; ++k) {
          if (edgeCutsInterior(redTiles[k], redTiles[(k+1) % n], minX, maxX, minY, maxY)) {
            wallInWay = true;
            break;
          }
        }
        if (!wallInWay) {
          double midX = (minX + maxX) / 2.0;
          double midY = (minY + maxY) / 2.0;
          if (isInside(midX, midY, redTiles)) {
            maxPart2 = area;
          }
        }
      }
    }
  }
  std::cout << "Part 1: " << maxPart1 << std::endl;
  std::cout << "Part 2: " << maxPart2 << std::endl;
}

int main() {
  std::cout << "Day 09 Solution\n";
  const std::vector<std::string> inputLines = readLines("input.txt");
  solve(inputLines);
  return 0;
}