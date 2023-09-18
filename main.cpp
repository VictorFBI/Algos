#include <iostream>
#include <vector>
#include <algorithm>

int choosePivot(std::vector<int> &vec, int left, int right) {
  int mid = left + (right - left) / 2;
  if (vec[left] > vec[mid]) std::swap(vec[left], vec[mid]);
  if (vec[left] > vec[right]) std::swap(vec[left], vec[right]);
  if (vec[mid] > vec[right]) std::swap(vec[mid], vec[right]);
  return mid;
}

int LomutoPartition(std::vector<int> &vec, int left, int right) {
  int pivotIndex = choosePivot(vec, left, right);
  std::swap(vec[left], vec[pivotIndex]);
  int j = left;
  for (auto i = j + 1; i < right + 1; ++i) {
    if (vec[i] >= vec[left]) continue;
    ++j;
    std::swap(vec[i], vec[j]);
  }
  std::swap(vec[j], vec[left]);
  return j;
}

int HoarePartition(std::vector<int> &vec, int left, int right) {
  int pivotIndex = choosePivot(vec, left, right);
  std::swap(vec[left], vec[pivotIndex]);
  int j = left + 1, i = right;
  while (j < i) {
    if (vec[j] < vec[left]) {
      ++j;
      continue;
    }
    if (vec[i] >= vec[left]) {
      --i;
      continue;
    }
    std::swap(vec[i], vec[j]);
    ++j;
    --i;
  }
  if (i == j && vec[j] < vec[left]) ++j;
  --j;
  std::swap(vec[j], vec[left]);
  return j;
}

void quickSort(std::vector<int> &vec, int start, int end) { // NOLINT
  if (start >= end) return;
  auto index = HoarePartition(vec, start, end);
  // or
  // auto index = LomutoPartition(vec, start, end);
  quickSort(vec, start, index - 1);
  quickSort(vec, index + 1, end);
}

int main() {
  std::vector<int> vec{5, 3, 1, 4, 6, 1, 1, 0, -1, 65, 56, 90, -11, 12, 7, 77};
  std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });
  quickSort(vec, 0, static_cast<int>(vec.size()) - 1);
  std::cout << "\n";
  std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });

  return 0;
}
