#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdint>

using namespace std;

struct Edge {
  int from, to, weight;

  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}

  bool operator==(const Edge &other) const {
    return from == other.from && to == other.to && weight == other.weight;
  }
};

bool hasCycleDFS(int current, int parent, vector<vector<Edge>> &adj_list, vector<bool> &visited, Edge &max_edge) {
  visited[current] = true;
  for (const auto &edge : adj_list[current]) {
    int neighbor = edge.to;
    if (!visited[neighbor]) {
      if (hasCycleDFS(neighbor, current, adj_list, visited, max_edge)) {
        // Найден цикл
        if (edge.weight > max_edge.weight) {
          max_edge = edge; // Обновляем максимальное ребро
        }
        return true;
      }
    } else if (neighbor != parent) {
      // Найден цикл
      if (edge.weight > max_edge.weight) {
        max_edge = edge; // Обновляем максимальное ребро
      }
      return true;
    }
  }
  return false;
}

bool hasCycle(vector<vector<Edge>> &adj_list, Edge &max_edge) {
  int num_vertices = static_cast<int>(adj_list.size());
  vector<bool> visited(num_vertices, false);

  for (int i = 0; i < num_vertices; ++i) {
    if (!visited[i] && hasCycleDFS(i, -1, adj_list, visited, max_edge)) {
      return true; // Найден цикл и максимальное ребро
    }
  }

  return false; // Цикл не найден
}

vector<Edge> ALG_3(vector<Edge> &edges, int num_vertices) {
  vector<vector<Edge>> result(num_vertices);
  vector<Edge> edgesResult;
  random_device rd;
  mt19937 gen(rd());
  shuffle(edges.begin(), edges.end(), gen); // O(E)

  for (auto &edge : edges) { // O(E)
    cout << edge.from + 1 << " " << edge.to + 1 << " " << edge.weight << endl;
    result[edge.from].emplace_back(edge.from, edge.to, edge.weight);
    result[edge.to].emplace_back(edge.to, edge.from, edge.weight);
    if (edge.from > edge.to) {
      swap(edge.from, edge.to);
    }
    edgesResult.emplace_back(edge);
    Edge max_edge(-1, -1, INT32_MIN);
    if (hasCycle(result, max_edge)) { // O(V + E)
      cout << "------------------\n";
      cout << "max edge " << max_edge.from + 1 << " " << max_edge.to + 1 << " " << max_edge.weight << endl;
      cout << "------------------\n";

      result[max_edge.from].erase(find(result[max_edge.from].begin(), result[max_edge.from].end(), max_edge)); // O(V)
      result[max_edge.to].erase(find(result[max_edge.to].begin(),
                                     result[max_edge.to].end(),
                                     Edge(max_edge.to, max_edge.from, max_edge.weight))); // O(V)
      if (max_edge.from > max_edge.to) {
        swap(max_edge.from, max_edge.to);
      }
      edgesResult.erase(find(edgesResult.begin(), edgesResult.end(), max_edge)); // O(E)
    }
  }

  return edgesResult;
} // total O(E(V + E))

int main() {
  int num_vertices, num_edges;
  cin >> num_vertices >> num_edges;

  vector<Edge> edges;
  for (int i = 0; i < num_edges; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    edges.emplace_back(from, to, weight);
  }

  cout << "#######################\n";

  auto MST = ALG_3(edges, num_vertices);

  cout << "#######################\n";

  int sum = 0;
  for(const auto &edge : MST) {
    cout << edge.from + 1 << " " << edge.to + 1 << " " << edge.weight << endl;
    sum += edge.weight;
  }

  cout << "Total weight: " << sum << endl;

  return 0;
}
