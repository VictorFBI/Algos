#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int parent(int i) {
  return (i + 1) / 2 - 1;
}

int left(int i) {
  return 2 * (i + 1) - 1;
}

int right(int i) {
  return 2 * (i + 1);
}

void max_heapify(std::vector<int> &vec, int i, int size) { // NOLINT
  int l = left(i);
  int r = right(i);
  int max = i;
  if (r < size && vec[r] > vec[i]) {
    max = r;
  }
  if (l < size && vec[l] > vec[max]) {
    max = l;
  }

  if (i != max) {
    std::swap(vec[i], vec[max]);
    max_heapify(vec, max, size);
  }
}

void build_heap(std::vector<int> &vec) {
  int size = static_cast<int>(vec.size());
  for (int i = static_cast<int>(vec.size()) / 2; i != -1; --i) {
    max_heapify(vec, i, size);
  }
}

void heap_sort(std::vector<int> &vec) {
  if (vec.empty()) return;
  build_heap(vec);
  int size = static_cast<int>(vec.size());
  for (auto i = static_cast<int>(vec.size()) - 1; i != 0; --i) {
    std::swap(vec[i], vec[0]);
    --size;
    max_heapify(vec, 0, size);
  }
}

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

void stress_heap() {
  for (auto i = 0; i < 1000000; ++i) {
    int size = rand() % 100;
    std::vector<int> first;
    first.reserve(size);
    first.clear();
    for (auto j = 0; j < size; ++j) {
      first.push_back(rand() % 1000000000);
    }
    auto src = first;
    auto second = first;

    std::sort(first.begin(), first.end());
    heap_sort(second);
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

  heap_sort(vec);

  for (auto &el : vec) {
    std::cout << el << ' ';
  }

  //stress_heap();
  return 0;
}
