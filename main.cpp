#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

int HoarePartition(std::vector<int> &vec, int left, int right);
int LomutoPartition(std::vector<int> &vec, int left, int right);



int LomutoPartition(std::vector<int> &vec, int left, int right) {
  int j = left;
  for (auto i = j + 1; i < right + 1; ++i) {
    if (vec[i] >= vec[0]) continue;
    ++j;
    std::swap(vec[i], vec[j]);
  }
  std::swap(vec[j], vec[0]);
  return j;
}

bool checkPartition(std::vector<int> &vec, int j) {
  for (auto i = 0; i < j; ++i) {
    if (vec[i] >= vec[j]) return false;
  }
  for (auto i = j + 1; i < vec.size(); ++i) {
    if (vec[i] < vec[j]) return false;
  }
  return true;
}


class Solution {
 public:
  std::vector<int> sortArray(std::vector<int>& nums) {
    bool needToSort = false;
    for(auto i = 0; i < nums.size() - 1; ++i) {
      if(nums[i] > nums[i+1]) {
        needToSort = true;
        break;
      }
    }
    if(!needToSort) return nums;
    quickSort(nums, 0, nums.size() - 1);
    return nums;
  }
  void quickSort(std::vector<int> &vec, int start, int end) {
    if (start >= end) return;
    auto index = HoarePartition(vec, start, end);
    quickSort(vec, start, index - 1);
    quickSort(vec, index + 1, end);
  }
  int LomutoPartition(std::vector<int> &vec, int left, int right) {
    int pivotIndex = choosePivot(vec, left, right);
    std::swap(vec[left], vec[pivotIndex]);
    int j = left;
    for (auto i = j + 1; i < right + 1; ++i) {
      if (vec[i] >= vec[0]) continue;
      ++j;
      std::swap(vec[i], vec[j]);
    }
    std::swap(vec[j], vec[0]);
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
  int choosePivot(std::vector<int> &vec, int left, int right) {
    int mid = left + (right - left) / 2;
    if (vec[left] > vec[mid]) std::swap(vec[left], vec[mid]);
    if (vec[left] > vec[right]) std::swap(vec[left], vec[right]);
    if (vec[mid] > vec[right]) std::swap(vec[mid], vec[right]);
    return mid;
  }
};
int main() {
  std::vector<int> vec{};
  std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "\n";
  std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });

  return 0;
}

//std::vector<int> vec;
//std::vector<int> tmp;
//int size = 4;
//for (auto times = 0; times < 10000; ++times) {
//if (times == 0) {
//for (auto i = 0; i < size; ++i) {
//srand(i);
//vec.push_back(rand()); // NOLINT
//}
//} else {
//for (auto i = 0; i < size; ++i) {
//srand(vec[i]);
//vec[i] = rand(); // NOLINT
//}
//}
//tmp = vec;
//auto index = LomutoPartition(vec, 0, vec.size() - 1);
//if (!checkPartition(vec, index)) {
//std::for_each(tmp.begin(), tmp.end(), [](int &val) { std::cout << val << " "; });
//std::cout << "\n";
//std::cout << index << "\n";
//std::for_each(vec.begin(), vec.end(), [](int &val) { std::cout << val << " "; });
//break;
//}
//}
