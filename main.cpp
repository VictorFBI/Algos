#include <vector>
#include <iostream>
#include <cstdint>

int dijkstra(std::vector<std::vector<int>>& matrix, int s, int f) {
  --s;
  --f;
  int INF = INT32_MAX;
  std::vector<bool> visited(matrix.size(), false);
  std::vector<int> value(matrix.size(), INF);
  value[s] = 0;

  for (auto i = 0; i < matrix.size(); ++i) {
    int min = INF;
    int curr_index = 0;
    // Поиск минимальной непосещённой вершины
    for (auto j = 0; j < matrix.size(); ++j) {
      if (!visited[j] && value[j] < min) {
        min = value[j];
        curr_index = j;
      }
    }

    // Помечаем эту вершину посещённой
    visited[curr_index] = true;

    // Обновляем стоимости соседей текущей вершины, если это необходимо
    for (auto j = 0; j < matrix[curr_index].size(); ++j) {
      if (matrix[curr_index][j] != -1 && !visited[j] && value[j] > value[curr_index] + matrix[curr_index][j]) {
        value[j] = value[curr_index] + matrix[curr_index][j];
      }
    }
  }

  // Если расстояние = бесконечности, то значит, что мы эту вершину никогда не посетили
  // => выводим -1, иначе выводим искомое расстояние
  return value[f] == INF ? -1 : value[f];
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

  std::cout << dijkstra(matrix, s, f);

  return 0;
}
