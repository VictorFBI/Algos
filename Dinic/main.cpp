#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Edge {
  int v;
  int flow;
  int C;
  int rev;
};

void addEdge(vector<vector<Edge>>& adj, int u, int v, int C) {
  Edge a{v, 0, C, static_cast<int>(adj[v].size())};
  Edge b{u, 0, 0, static_cast<int>(adj[u].size())};
  adj[u].push_back(a);
  adj[v].push_back(b); // reverse edge
}

bool BFS(vector<vector<Edge>>& adj, int s, int t, vector<int>& level) {
  fill(level.begin(), level.end(), -1);
  level[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const auto& e : adj[u]) {
      if (level[e.v] < 0 && e.flow < e.C) {
        level[e.v] = level[u] + 1;
        q.push(e.v);
      }
    }
  }
  return level[t] >= 0;
}

int sendFlow(vector<vector<Edge>>& adj, int u, int flow, int t, vector<int>& start, vector<int>& level) { // NOLINT
  if (u == t) return flow;

  for (; start[u] < adj[u].size(); ++start[u]) {
    Edge& e = adj[u][start[u]];
    if (level[e.v] == level[u] + 1 && e.flow < e.C) {
      int currFlow = min(flow, e.C - e.flow);
      int tempFlow = sendFlow(adj, e.v, currFlow, t, start, level);
      if (tempFlow > 0) {
        e.flow += tempFlow;
        adj[e.v][e.rev].flow -= tempFlow;
        return tempFlow;
      }
    }
  }
  return 0;
}

int DinicMaxflow(vector<vector<Edge>>& adj, int s, int t) { // O(V^2 * E)
  int V = static_cast<int>(adj.size());
  if (s == t) return 0;

  int total = 0;
  vector<int> level(V);
  while (BFS(adj, s, t, level)) {
    vector<int> start(V, 0);
    while (int flow = sendFlow(adj, s, INT32_MAX, t, start, level)) {
      total += flow;
    }
  }
  return total;
}

int main() {
  int V, E;
  cin >> V >> E;

  vector<vector<Edge>> adj(V + 1);

  for (int i = 0; i < E; ++i) {
    int u, v, C;
    cin >> u >> v >> C;
    addEdge(adj, u, v, C);
  }


  cout << "Maximum flow " << DinicMaxflow(adj, 1, V);
  return 0;
}
