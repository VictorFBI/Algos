#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

void radix256_sort(std::vector<int>&);

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

void stress_radix256() {
  for (auto i = 0; i < 10000; ++i) {
    int size = rand() % 100;
    std::vector<int> first;
    first.reserve(size);
    for (auto j = 0; j < size; ++j) {
      int k = rand() % 2;
      if (k == 0) k = -1;
      first.push_back(k * rand() % 1000000001);
    }
    auto src = first;
    auto second = first;

    std::sort(first.begin(), first.end());
    radix256_sort(second);
    if (first == second) continue;

    print_vector(src);
    print_vector(first);
    print_vector(second);
  }
}

int give_nth_digit(int number, int n) {
  for (auto i = 0; i < n; ++i) {
    number /= 256;
  }

  return number % 256;
}

void sort_by_nth_digit(std::vector<int>& vec, int n) {
  std::vector<std::queue<int>> buckets(256);

  for (int i : vec) {
    buckets[give_nth_digit(i, n)].push(i);
  }

  int i = 0;
  for (auto& bucket : buckets) {
    while (!bucket.empty()) {
      vec[i++] = bucket.front();
      bucket.pop();
    }
  }
}

void radix256_sort(std::vector<int>& vec) {
  std::vector<int> positives;
  std::vector<int> negatives;
  positives.reserve(vec.size());
  for (auto& el : vec) {
    if (el >= 0) positives.push_back(el);
  }

  negatives.reserve(vec.size() - positives.size());
  for (auto& el : vec) {
    if (el < 0) negatives.push_back(-el);
  }

  for (auto i = 0; i < 5; ++i) { // because 1 + 256 + 256^2 + 256^3 + 256^4 > 10^9
    sort_by_nth_digit(positives, i);
  }

  for(auto i = 0; i < 5; ++i) {
    sort_by_nth_digit(negatives, i);
  }

  int i = 0;
  for (auto it = negatives.crbegin(); it != negatives.crend(); ++it) {
    vec[i++] = -(*it);
  }

  for (auto& el : positives) {
    vec[i++] = el;
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

  radix256_sort(vec);

  for (auto &el : vec) {
    std::cout << el << ' ';
  }

  //stress_radix256();
  return 0;
}
