#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
 public:
  int compress(std::vector<char> &chars) { // NOLINT
    int count = 1;
    for (auto i = 0; i < chars.size() - 1; ++i) {
      if (chars[i] == chars[i + 1]) {
        chars.erase(chars.begin() + i + 1);
        ++count;
        --i;
      } else {
        if (count > 1) {
          while (count != 0) {
            chars.insert(chars.begin() + i + 1, (count % 10) + 48); // NOLINT
            count /= 10;
          }
          ++count;
          ++i;
        }
      }
    }

    size_t last_index = chars.size();
    if (count > 1) {
      while (count != 0) {
        chars.insert(chars.begin() + last_index, (count % 10) + 48); // NOLINT
        count /= 10;
      }
    }

    return static_cast<int>(chars.size());
  }
};

int main() {
  std::vector<char> vec{'a', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'd', 'd', 'h'};
  Solution s;
  s.compress(vec);
  std::for_each(vec.begin(), vec.end(), [](char &val) { std::cout << val << " "; });
  return 0;
}