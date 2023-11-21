#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>

std::vector<int> find_dijkstra_path(std::vector<std::vector<int>>& matrix, int s, int f) {
  // если начало совпадает с концом, то алгоритм можно не применять и сказать сразу ответ
  if (s == f) return std::vector<int>{s};
  --s;
  --f;
  int INF = INT32_MAX;
  auto n = matrix.size();
  std::vector<bool> visited(n, false);
  std::vector<int> value(n, INF);
  std::vector<int> prev(n, -1);
  value[s] = 0;

  for (auto i = 0; i < n; ++i) {
    int curr_index = 0;
    int min = INF;
    // Поиск наименьшей непосещённой вершины
    for (auto j = 0; j < matrix.size(); ++j) {
      if (!visited[j] && value[j] < min) {
        min = value[j];
        curr_index = j;
      }
    }

    // Помечаем эту вершину посещённой
    visited[curr_index] = true;

    // Обновляем стоимости соседей текущего узла, если это необходимо, параллельно
    // запоминая, из какой вершины мы пришли
    for (auto j = 0; j < matrix[curr_index].size(); ++j) {
      if (matrix[curr_index][j] != -1 && !visited[j] && value[j] > value[curr_index] + matrix[curr_index][j]) {
        value[j] = value[curr_index] + matrix[curr_index][j];
        prev[j] = curr_index;
      }
    }
  }
  
  
  // Собираем путь
  std::vector<int> path;
  path.push_back(f + 1);

  while (prev[f] != -1) { // пока есть откуда приезжать
    path.push_back(prev[f] + 1);
    f = prev[f];
  }
  std::reverse(path.begin(), path.end()); // разворачиваем путь

  return path.size() == 1 ? std::vector<int>{-1} : path;
}


int main() {
  int n, s, f;
  std::cin >> n >> s >> f;
  std::vector<std::vector<int>> matrix(n);

  for (auto i = 0; i < n; ++i) {
    std::vector<int> str;
    str.reserve(n);
    for (auto j = 0; j < n; ++j) {
      int a;
      std::cin >> a;
      str.push_back(a);
    }
    matrix[i] = str;
  }

  auto ans = find_dijkstra_path(matrix, s, f);

  for (auto& el : ans) {
    std::cout << el << ' ';
  }

  return 0;
}
