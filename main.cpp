#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

class Solution {
 public:
  std::queue<std::string> ans;
  std::queue<int> open;
  std::queue<int> close;
  std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::string> res;
    ans.emplace("(");
    open.push(1);
    close.push(0);

    while (!ans.empty()) {
      if (open.front() == n && close.front() == n) {
        res.push_back(ans.front());
        ans.pop();
        open.pop();
        close.pop();
        continue;
      }

      if (open.front() == close.front()) {
        ans.push(ans.front() + "(");
        ans.pop();
        open.push(open.front() + 1);
        open.pop();
        close.push(close.front());
        close.pop();
        continue;
      }

      if(open.front() != n) {
        ans.push(ans.front() + "(");
        open.push(open.front() + 1);
        close.push(close.front());
      }
      ans.push(ans.front() + ")");
      open.push(open.front());
      close.push(close.front() + 1);

      ans.pop();
      open.pop();
      close.pop();
    }

    return res;
  }
};

int main() {
  Solution s;
  auto ans = s.generateParenthesis(3);

  for (auto &el : ans) {
    std::cout << el << "\n";
  }

  return 0;
}