#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


bool operator==(std::vector<int> &vec, std::vector<int> &other) {
  if (vec.size() != other.size()) return false;

  for (auto i = 0; i < vec.size(); ++i) {
    if (vec[i] != other[i]) return false;
  }

  return true;
}

void print_vector(std::vector<int>& vec) {
  for (auto& el : vec) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}


void counting_sort(std::vector<int>& vec) {
  std::vector<int> stats(2000001);
  for (auto& el : vec) {
    ++stats[el + 1000000];
  }
  int i = 0;
  for (auto k = 0; k < stats.size(); ++k) {
    while (stats[k]-- != 0) {
      vec[i++] = k - 1000000;
    }
  }
}

void stress_counting() {
  for (auto i = 0; i < 10000; ++i) {
    int size = rand() % 100;
    std::vector<int> first;
    first.reserve(size);
    for (auto j = 0; j < size; ++j) {
      int k = rand() % 2;
      if (k == 0) k = -1;
      first.push_back(k * rand() % 1000000);
    }
    auto src = first;
    auto second = first;

    std::sort(first.begin(), first.end());
    counting_sort(second);
    if (first == second) continue;

    print_vector(src);
    print_vector(first);
    print_vector(second);
  }
}
int main() {
  int n;
  std::vector<int> vec;
  std::cin >> n;
  vec.reserve(n);

  for (auto i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    vec.push_back(a);
  }

  counting_sort(vec);

  for (auto &el : vec) {
    std::cout << el << ' ';
  }

  //stress_counting();
  return 0;
}
