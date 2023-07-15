#include <iostream>
#include <string>
class Solution {
 public:
  int reverse(int x) {
    std::string num = std::to_string(x);
    int ans;
    try {
      ans = std::stoi(reverseString(num));
      return x >= 0 ? ans : -ans;
    } catch (std::out_of_range &) {
      return 0;
    }
  }
  std::string &reverseString(std::string &str) {
    int left = 0;
    int right = static_cast<int>(str.size() - 1);
    while (left - right < 0) {
      std::swap(str[left], str[right]);
      ++left;
      --right;
    }
    return str;
  }
};
int main() {
  int input = 0;
  Solution s;
  std::cin >> input;
  std::cout << s.reverse(input);
  return 0;

}