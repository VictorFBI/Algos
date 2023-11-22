#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>


long long fast_dijkstra(long long cities, std::unordered_map<long long, std::unordered_map<long long, long long>>& map, long long from, long long to) {
  long long INF = INT64_MAX;

  std::vector<long long> value(cities + 1, INF);
  value[from] = 0;
  std::set<std::pair<long long,long long>> set;
  set.emplace(0, from);

  for (auto i = 0; i < cities; ++i) {
    long long curr_index = set.begin()->second;
    set.erase(*set.begin());

    for (auto& el : map[curr_index]) {
      if (value[el.first] > value[curr_index] + el.second) {
        set.erase(std::pair<long long, long long>(value[el.first], el.first));
        value[el.first] = value[curr_index] + el.second;
        set.emplace(value[el.first], el.first);
      }
    }
  }

  return value[to] == INF ? -1 : value[to];
}

int main() {
  long long n, k;
  std::cin >> n >> k;
  std::unordered_map<long long, std::unordered_map<long long, long long>> map;

  for (auto i = 0; i < k; ++i) {
    long long left, right, road;
    std::cin >> left >> right >> road;
    map[left][right] = road;
    map[right][left] = road;
  }

  long long from, to;
  std::cin >> from >> to;

  std::cout << fast_dijkstra(n, map, from, to);

  return 0;
}
