#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void mergeSort(std::vector<int> &vec, int start, int end) {
  if (end - start <= 1) return;

  if (end - start == 2) {
    if (vec[start] > vec[start + 1]) {
      std::swap(vec[start], vec[start + 1]);
      return;
    }
  }

  mergeSort(vec, start, start + (end - start) / 2);
  mergeSort(vec, start + (end - start) / 2, end);

  std::vector<int> tmp;
  int i = start, j = start + (end - start) / 2;

  while (i < start + (end - start) / 2 && j < end) {
    if (vec[i] < vec[j]) {
      tmp.push_back(vec[i]);
      ++i;
    } else {
      tmp.push_back(vec[j]);
      ++j;
    }
  }

  if (i == start + (end - start) / 2) {
    for (auto t = j; t < end; ++t) tmp.push_back(vec[t]);
  } else {
    for (auto t = i; t < start + (end - start) / 2; ++t) tmp.push_back(vec[t]);
  }

  for (auto t = start; t < end; ++t) {
    vec[t] = tmp[t - start];
  }
}

int main() {
  std::vector<int> vec{5, 3, 1, 4, -1, 90, 65, 77, -70, 11, -1, 256};
  mergeSort(vec, 0, static_cast<int>(vec.size()));
  std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });
  return 0;
}