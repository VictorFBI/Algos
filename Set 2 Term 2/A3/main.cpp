#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_set>

bool findPathDFS(const std::vector<std::vector<size_t>> &graph, // NOLINT
                 short source,
                 short destination,
                 std::vector<bool> &visited,
                 std::vector<short> &path, bool toDelete) {
  visited[source] = true;
  path.push_back(source);

  if (source == destination) {
    return true;
  }

  for (int i = 0; i < graph.size(); ++i) {
    if (graph[source][i] != 0 && !visited[i]) {
      if (findPathDFS(graph, i, destination, visited, path, toDelete)) {
        return true;
      }
    }
  }

  if (toDelete) path.pop_back();
  return false;
}

bool findPath(const std::vector<std::vector<size_t>> &graph,
              short source,
              short destination,
              std::vector<short> &path, bool toDelete = true) {
  std::vector<bool> visited(graph.size(), false);

  return findPathDFS(graph, source, destination, visited, path, toDelete);
}

std::vector<short> fordFalkersonMinVerticesToDelete(std::vector<std::vector<size_t>> &graph,
                                                    std::vector<std::vector<short>> &adjList,
                                                    short from,
                                                    short to) {
  size_t maxFlow = 0;
  std::vector<short> path;

  while (findPath(graph, from, to, path)) { // O((V + E)*V*C), C - max weight of the edge
    size_t minCapacity = UINT64_MAX;

    for (auto i = 0; i < path.size() - 1; ++i) { // O(V)
      short start = path[i];
      short end = path[i + 1];
      minCapacity = std::min(minCapacity, graph[start][end]);
    }

    for (auto i = 0; i < path.size() - 1; ++i) { // O(V)
      short start = path[i];
      short end = path[i + 1];

      graph[start][end] -= minCapacity;
      graph[end][start] += minCapacity;
    }

    maxFlow += minCapacity;
    path.clear();
  }

  std::cout << "Residual network at the end:\n";
  for (auto i = 1; i < graph.size(); ++i) {
    for (auto j = 1; j < graph.size(); ++j) {
      std::cout << graph[i][j] << ' ';
    }
    std::cout << '\n';
  }

  // сложность оставшегося кода асимптотически меньше O((V + E)*V*C),
  // так что не будем подсчитывать её, так как она все равно не влияет на общую сложность

  findPath(graph, from, to, path, false); // path содержит вершины, достижимые из истока
  std::unordered_set<short> reachable;
  std::unordered_set<short> containsInPath;
  for (auto &el : path) {
    containsInPath.insert(el);
  }
  std::vector<short> ans;

  for (auto &adj : path) {
    for (auto &el : adjList[adj]) {
      if (!containsInPath.contains(el)) reachable.insert(el);
    }
  }

  for (auto &el : path) {
    if (el == from) continue;
    if (adjList[el].size() > 1) {
      for (auto &adj : adjList[el]) {
        reachable.erase(adj);
        ans.push_back(el);
      }
    }
  }

  for (auto &el : reachable) {
    if (el == to) continue;
    ans.push_back(el);
  }

  return ans;
} // total: // O((V + E)*V*C) (то есть сложность алгоритма Форда-Фалкерсона)

int main() {
  short n, m;
  std::cin >> n >> m;

  std::vector<std::vector<size_t>> graph(n + 1, std::vector<size_t>(n + 1, 0));
  std::vector<std::vector<short>> adjList(n + 1);

  for (auto i = 0; i < m; ++i) {
    short start, end;
    size_t weight;
    std::cin >> start >> end >> weight;
    graph[start][end] = weight;
    adjList[start].push_back(end);
  }

  auto verticesToDelete = fordFalkersonMinVerticesToDelete(graph, adjList, 1, n);

  std::cout << "Vertices to delete: ";
  for (auto &el : verticesToDelete) {
    std::cout << el << ' ';
  }

  return 0;
}
