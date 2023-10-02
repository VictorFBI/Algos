#include <iostream>
#include <vector>

int HammingDistance(std::vector<int> &a, std::vector<int> &b) {
  int count = 0;
  for (auto i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) ++count;
  }
  return count;
}

bool operator==(std::vector<int> &a, std::vector<int> &b) {
  if (a.size() != b.size()) return false;

  for (auto i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return false;
  }

  return true;
}

bool checkIn(std::vector<std::vector<int>> &set, std::vector<int> &vec) {
  if (set.empty()) return false;
  for (auto &el : set) {
    if (el == vec) return true;
  }

  return false;

}

int CountArrayRotations(std::vector<int> &vec) {
  auto source = vec;
  auto n = vec.size();
  auto max_dist = 0;
  auto count = 0;
  std::vector<std::vector<int>> set;

  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < n - 1; ++j) {
      std::swap(vec[j], vec[j + 1]);
    }
    if (checkIn(set, vec)) continue;
    set.push_back(vec);

    auto dist = HammingDistance(source, vec);
    if (max_dist < dist) {
      count = 0;
      max_dist = dist;
    }
    if (max_dist == dist) ++count;
  }

  return count;
}

int main() {
  int n;
  std::vector<int> vec;
  std::cin >> n;

  for (auto i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    vec.push_back(a);
  }
  std::cout << CountArrayRotations(vec);
  return 0;
}