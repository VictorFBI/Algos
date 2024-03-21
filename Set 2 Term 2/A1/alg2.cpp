#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>

using namespace std;

struct Edge {
  int from, to, weight;

  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

struct CompareEdges {
  bool operator()(const Edge &e1, const Edge &e2) {
    return e1.weight > e2.weight;
  }
};

vector<int> parent;

int find(int u) { // find root of the tree
  if (parent[u] == u) {
    return u;
  }
  return find(parent[u]);
}

bool unite(int u, int v) { // unite two trees (true if they were different, false if they were the same)
  int pu = find(u), pv = find(v);
  if (pu != pv) {
    parent[pu] = pv;
    return true;
  }
  return false;
}

vector<Edge> ALG_2(vector<Edge> &edges, int n) {
  vector<Edge> result;
  parent.resize(n);
  for (int i = 0; i < n; ++i) { // O(V)
    parent[i] = i;
  }
  random_device rd;
  mt19937 gen(rd());
  shuffle(edges.begin(), edges.end(), gen); // O(E)

  for (auto &e : edges) { // O(E)
    cout << e.from << " " << e.to << " " << e.weight << endl;
    if (unite(e.from, e.to)) { // O(a(E)), a - inverse Ackermann function (grows very slowly)
      result.push_back(e); // O(1)
    }
  }
  return result;
} // total: O(E*a(E))

int main() {
  int n, m;
  cin >> n >> m;

  vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    edges.emplace_back(from, to, weight);
  }

  cout << "#######################\n";

  vector<Edge> MST = ALG_2(edges, n);

  cout << "#######################\n";

  int sum = 0;
  for (const auto &edge : MST) {
    cout << edge.from << " " << edge.to << " " << edge.weight << endl;
    sum += edge.weight;
  }

  cout << "Total weight: " << sum << endl;

  return 0;
}
