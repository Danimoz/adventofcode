//
// Created by dflat on 10/12/2025.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include "../../common/cpp/utils.hpp"

// 1. Structure to hold 3d information
struct Point {
  long long x, y, z;
};

// 2 . Structure to hold Edge Information
struct Edge {
  int u;
  int v;
  long long distSq;

  // Comparator for Sorting
  bool operator<(const Edge& other) const {
    return distSq < other.distSq;
  }
};

// 3. The DSU Class (with Size)
class UnionFind {
public:
  std::vector<int> parent;
  std::vector<int> size; // Tracks the size of each component (For Part 1)
  int count; // Tracks Number of disjoint  components (For Part 2)

  UnionFind(int n) {
    parent.resize(n);
    size.assign(n, 1); // Initially every node is a component of size 1
    count = n;
    for (int i = 0; i < n; i++) parent[i] = i;
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(x), rootY = find(y);
    if (rootX != rootY) {
      // Merge smaller into larger
      if (size[rootX] < size[rootY]) {
        std::swap(rootX, rootY);
      }
      parent[rootY] = rootX;
      size[rootX] += size[rootY];
      count--;
      return true;
    }
    return false;
  }

  // Helper for Part 1
  std::vector<int> getComponentSizes(int n) {
    std::vector<int> sizes;
    std::vector<bool> seen(n, false);
    for (int i = 0; i < n; i++) {
      int root = find(i);
      if (!seen[root]) {
        seen[root] = true;
        sizes.push_back(size[root]);
      }
    }
    return sizes;
  }
};

long long distSquared(const Point& p1, const Point& p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y) +
          (p1.z - p2.z)*(p1.z - p2.z);
}

int main(){
  std::vector<Point> points;
  std::string line;

  const std::vector<std::string> lines = readLines("input.txt");
  for (const auto& nline : lines){
    auto parts = splitString(nline, ",");
    points.push_back(Point{
      std::stoll(parts[0]),
      std::stoll(parts[1]),
      std::stoll(parts[2])
    });
  }

  int n = points.size();
  if (n == 0) return 0;

  std::vector<Edge> edges;
  edges.reserve(n * (n - 1) / 2);

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      edges.push_back({ i, j, distSquared(points[i], points[j])});
    }
  }

  std::sort(edges.begin(), edges.end());

  // --- Part 1 ---
  UnionFind dsu1(n);
  int limit = std::min((int)edges.size(), 1000);

  for (int i = 0; i < limit; i++) {
    dsu1.unite(edges[i].u, edges[i].v);
  }

  std::vector<int> sizes = dsu1.getComponentSizes(n);
  std::sort(sizes.rbegin(), sizes.rend());

  long long part1 = 1;
  for (int i = 0; i<3 && i < sizes.size(); i++) {
    part1 *= sizes[i];
  }

  // --- Part 2 ---
  UnionFind dsu2(n);
  long long part2 = 0;
  for (const auto& edge : edges) {
    if (dsu2.unite(edge.u, edge.v)) {
      if (dsu2.count == 1) {
        part2 = points[edge.u].x * points[edge.v].x;
        break;
      }
    }
  }

  std::cout << "Day 8 Solutions\n";
  std::cout << "Part 1: " << part1 << '\n';
  std::cout << "Part 2: " << part2 << '\n';
  return 0;
}



