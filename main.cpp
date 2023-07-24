#include <iostream>
#include <string>
class Solution {
 public:
  bool isDigit(char sym) {
    return (int) sym >= 48 && (int) sym <= 57;
  }
  int charToInteger(char sym) {
    return (int) sym - 48;
  }
  int myAtoi(std::string s) {
    int sign = 1;
    int i = 0;
    while (s[i] == ' ') ++i;
    if (s[i] == '-') {
      sign = -1;
      ++i;
    } else {
      if(s[i] == '+') ++i;
    }
    int64_t res = 0;
    while (i < s.size() && isDigit(s[i])) {
      res = res * 10 + charToInteger(s[i]);
      res *= sign;
      if (res > INT32_MAX) {
        return INT32_MAX;
      }
      if (res < INT32_MIN) {
        return INT32_MIN;
      }
      res *= sign;
      ++i;
    }
    return static_cast<int>(res) * sign;
  }
};
int main() {
  Solution s;
  std::cout << s.myAtoi("+1") << std::endl;
  std::cout << s.myAtoi("f7dsa-42") << std::endl;
  std::cout << s.myAtoi("  42-1") << std::endl;
  std::cout << s.myAtoi("  -42g") << std::endl;
  std::cout << s.myAtoi("   +0 123") << std::endl;
  std::cout << s.myAtoi("+-12") << std::endl;
  std::cout << s.myAtoi("214748364325252460909") << std::endl;
  return 0;
}
