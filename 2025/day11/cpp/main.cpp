#include <iostream>
#include <unordered_map>
#include "../../common/cpp/utils.hpp"

struct State {
  std::string node;
  int mask;

  bool operator==(const State& other) const {
    return node == other.node && mask == other.mask;
  }
};

//Custom has for the State struct
struct StateHash {
  std::size_t operator()(const State& state) const {
    return std::hash<std::string>{}(state.node) ^ (std::hash<int>{}(state.mask) << 1);
  }
};

std::unordered_map<std::string, std::vector<std::string>> buildGraph(const std::vector<std::string>& inputLines) {
  std::unordered_map<std::string, std::vector<std::string>> graph;

  for (const auto& line : inputLines) {
    if (line.empty()) continue;

    const auto kv = splitString(line, ":");
    const std::string key = kv[0];

    std::vector<std::string> neighbors;
    const auto vals = splitString(kv[1], " ");
    for (const auto& val : vals) {
      if (!val.empty()) {
        neighbors.push_back(val);
      }
    }
    graph[key] = neighbors;
  }
  return graph;
}

long long countP2(const std::string& current,
                  int mask,
                  const std::unordered_map<std::string, std::vector<std::string>>& graph,
                  std::unordered_map<State, long long, StateHash>& memo) {

  int nextMask = mask;
  if (current == "dac") nextMask |= 1;
  if (current == "fft") nextMask |= 2;

  if (current == "out") {
    return (nextMask == 3) ? 1 : 0;
  }

  State currentState = {current, nextMask};
  if (memo.count(currentState)) return memo[currentState];

  long long totalPaths = 0;
  if (graph.count(current)) {
    for (const std::string & neighbor :graph.at(current)) {
      totalPaths += countP2(neighbor, nextMask, graph, memo);
    }
  }
  return memo[currentState] = totalPaths;
}

long long countP1(const std::string& current,
                      const std::unordered_map<std::string, std::vector<std::string>>& graph,
                      std::unordered_map<std::string, long long>& memo
                      ) {

  // Base case - reached the exit node
  if (current == "out") {
    return 1;
  }

  if (const auto it = memo.find(current); it != memo.end()) {
    return it->second;
  }

  long long totalPaths = 0;

  if (const auto graphIt = graph.find(current); graphIt != graph.end()) {
    for (const std::string& neighbor : graphIt->second) {
      totalPaths += countP1(neighbor, graph, memo);
    }
  }

  return memo[current] = totalPaths;
}

long long solve(const std::unordered_map<std::string, std::vector<std::string>>& graph) {
  std::unordered_map<std::string, long long> memo1;
  return countP1("you", graph, memo1);
}


int main() {
  const auto lines = readLines("input.txt");
  const auto graph = buildGraph(lines);
  long long p1 = solve(graph);
  std::cout << "Part 1:" << p1 << "\n";

  std::unordered_map<State, long long, StateHash> memo2;
  long long p2 = countP2("svr", 0, graph, memo2);
  std::cout << "Part 2:" << p2 << "\n";
  return 0;
}