/*
 *Disjoint Set Union (Union-Find) with
 * - Path compression in find()
 * - Union by size
 */

#include <vector>

class DSU {
private:
  int n;
  vector<int> parent;
  vector<int> rank;
  int count;

public:
  //Constructor
  DSU(int _n) {
    n = _n;
    parent.resize(n);
    rank.assign(n, 0);
    for (int i = 0; i < n; ++i) parent[i] = i;
    count = n;
  }

  int find(int x) {
    if (parent[x] != x)
      // Path Compression: Make parent point to root
      parent[x] = find(parent[x]);
    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(a);
    int rootY = find(y);
    if (rootX == rootY) return false;

    //Attach smaller rank tree under larger rank tree
    if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
    else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }

    count--;
    return true;
  }

  bool connected(int x, int y) {
    return find(x) == find(y);
  }
};

