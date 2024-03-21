#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
  int from, to, weight;
  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
  bool operator<(const Edge &other) const {
    return weight > other.weight;
  }

  bool operator==(const Edge &other) const {
    return from == other.from && to == other.to && weight == other.weight;
  }
};

// Функция DFS для обхода графа
void DFS(int node, vector<vector<int>> &adj_list, vector<bool> &visited) {
  visited[node] = true; // Помечаем текущую вершину как посещенную
  for (int neighbor : adj_list[node]) { // Проходим по всем соседям текущей вершины
    if (!visited[neighbor]) { // Если сосед еще не посещен
      DFS(neighbor, adj_list, visited); // Рекурсивно вызываем DFS для него
    }
  }
}

// Функция для проверки связности графа
bool isConnectedGraph(vector<vector<int>> &adj_list, int num_vertices) {
  vector<bool> visited(num_vertices, false); // Массив для отслеживания посещенных вершин
  DFS(0, adj_list, visited); // Запускаем DFS с любой стартовой вершины
  for (bool visit_status : visited) { // Проверяем, были ли посещены все вершины
    if (!visit_status) {
      return false; // Если есть непосещенные вершины, граф не связен
    }
  }
  return true; // Если все вершины посещены, граф связен
}

vector<Edge> ALG_1(vector<vector<int>> &adj_list, vector<Edge> &edges) {
  int num_vertices = static_cast<int>(adj_list.size());
  std::sort(edges.begin(), edges.end()); // O(E logE)
  vector<Edge> T = edges;
  for (auto &el : edges) { // O(E)
    cout << el.from + 1 << " " << el.to + 1 << " " << el.weight << endl;
    adj_list[el.from].erase(find(adj_list[el.from].begin(), adj_list[el.from].end(), el.to)); // O(V)
    adj_list[el.to].erase(find(adj_list[el.to].begin(), adj_list[el.to].end(), el.from)); // O(V)
    if (!isConnectedGraph(adj_list, num_vertices)) { // O(V + E)
      adj_list[el.from].push_back(el.to);
      adj_list[el.to].push_back(el.from);
    } else {
      T.erase(find(T.begin(), T.end(), el));
    }
  }

  return T;
} // total: O(E(V + E))

int main() {
  int num_vertices, num_edges;
  cin >> num_vertices >> num_edges;

  vector<vector<int>> adj_list(num_vertices); // Список смежности для графа
  vector<Edge> edges; // Список ребер графа

  // Считываем ребра графа и строим список смежности + список ребер
  for (int i = 0; i < num_edges; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    --from;
    --to;
    adj_list[from].push_back(to);
    adj_list[to].push_back(from);
    edges.emplace_back(from, to, weight);
  }

  cout << "##########################\n";

  auto mst = ALG_1(adj_list, edges);

  cout << "##########################\n";

  int sum = 0;

  for (auto &el : mst) {
    cout << el.from + 1 << " " << el.to + 1 << " " << el.weight << endl;
    sum += el.weight;
  }

  cout << "Total weight: " << sum << endl;

  return 0;
}
