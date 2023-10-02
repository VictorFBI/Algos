#include <iostream>
#include <string>

std::string Decode(std::string s) {
  std::string ans;
  for (std::size_t i = 0; i < s.size(); ++i) {
    if (isdigit(s[i])) {
      std::size_t num = 0;
      while (isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        ++i;
      }
      std::string tmp;
      std::size_t open = 1;
      std::size_t close = 0;
      std::size_t j = i + 1;
      while (open != close) {
        if (s[j] == '[') {
          ++open;
        }
        if (s[j] == ']') {
          ++close;
        }
        if (open == close) break;
        tmp += s[j];
        ++j;
      }
      auto pre_ans = Decode(tmp);
      for (auto k = 0; k < num; ++k) {
        ans += pre_ans;
      }
      i = j;
    } else {
      ans += s[i];
    }
  }

  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string input;
  getline(std::cin, input);

  std::cout << Decode(input);
  return 0;
}