#include <iostream>
#include <vector>

int HammingDistance(std::vector<int> &a, std::vector<int> &b) {
  int count = 0;
  for (auto i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) ++count;
  }
  return count;
}

int CountArrayRotations(std::vector<int> &vec) {
  auto source = vec;
  auto n = vec.size();
  auto max_dist = 0;
  auto count = 0;

  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < n - 1; ++j) {
      std::swap(vec[j], vec[j + 1]);
    }

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
  std::vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 1, 8, 0};
  std::cout << CountArrayRotations(vec1) << std::endl;
  std::cout << CountArrayRotations(vec2) << std::endl;
  return 0;
}