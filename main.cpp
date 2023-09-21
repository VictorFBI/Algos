#include <iostream>
#include <string>
#include <stack>

std::string unpack(std::string& str) {
  std::string ans;
  std::stack<int> digits;
  std::stack<std::string> records;
  for (auto &el : str) {
    if (el == '[') continue;
    if (el == ']' || isdigit(el)) {
      if(!ans.empty()) records.push(ans);
      ans.clear();
      if (isdigit(el)) {
        digits.push(el - 48);
      }
      continue;
    }

    ans += el;
  }

  while(digits.size() != 1) {
    auto size = digits.top();
    auto record = records.top();
    for(auto i = 0; i < size - 1; ++i) record += records.top();
    digits.pop();
    records.pop();
    records.top() += record;
  }

  auto size = digits.top();
  for(auto i = 0; i < size; ++i) ans += records.top();
  return ans;
}



int main() {
  std::string str = "1[a2[bbb3[c]]]";
  std::cout << unpack(str);
  return 0;
}