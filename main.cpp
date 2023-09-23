#include <iostream>
#include <vector>
#include <queue>
#include <map>

std::vector<int> getNewSet(std::vector<int> &vec, std::vector<int> &nums) {
  std::map<int, int> map;
  std::vector<int> ans;
  for (auto &el : vec) {
    ++map[el];
  }

  for (auto &el : nums) {
    if (map.count(el) == 0) ans.push_back(el);
  }
  return ans;
}

std::vector<std::vector<int>> permute(std::vector<int> &nums) {
  std::queue<std::vector<int>> queue;
  std::vector<std::vector<int>> ans;
  for (auto &el : nums) {
    std::vector<int> vec{el};
    queue.push(vec);
  }

  while (!queue.empty()) {
    if (queue.front().size() == nums.size()) {
      ans.push_back(queue.front());
    } else {
      auto set = getNewSet(queue.front(), nums);
      for (auto &el : set) {
        auto tmp = queue.front();
        tmp.push_back(el);
        queue.push(tmp);
      }
    }
    queue.pop();
  }

  return ans;
}

int main() {
  auto count = 0;
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  auto ans = permute(vec);

  for (auto &record : ans) {
    for (auto &el : record) {
      std::cout << el << " ";
    }
    ++count;
    std::cout << "\n";
  }
  std::cout << "Total amount of permutations is: " << count << "\n";
  return 0;
}