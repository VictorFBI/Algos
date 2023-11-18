#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int count_palindromes_brute(std::string &str) {
  int n = static_cast<int>(str.size());
  std::vector<int> d1(n);
  std::vector<int> d2(n);
  int cnt = 0;
  for (auto i = 0; i < n; ++i) {
    while (i - d1[i] >= 0 && i + d1[i] < n && str[i - d1[i]] == str[i + d1[i]]) {
      ++d1[i];
    }
    while (i - d2[i] - 1 >= 0 && i + d2[i] < n && str[i - d2[i] - 1] == str[i + d2[i]]) {
      ++d2[i];
    }
    cnt += d1[i] + d2[i];
  }
  return cnt;
  // abba
}

int count_palindromes_odd(std::string &str) {
  int n = static_cast<int>(str.size());
  int l = 0, r = -1;
  std::vector<int> d1(n);
  int cnt = 0;

  for (auto i = 0; i < n; ++i) {
    if (i > r) {
      while (i - d1[i] >= 0 && i + d1[i] < n && str[i - d1[i]] == str[i + d1[i]]) {
        ++d1[i];
      }
      r = i + d1[i] - 1;
      l = i - d1[i] + 1;
    } else {
      int adj = l + (r - i);
      if (adj - d1[adj] + 1 > l) d1[i] = d1[adj];
      else {
        d1[i] = r - i;
        while (i - d1[i] >= 0 && i + d1[i] < n && str[i - d1[i]] == str[i + d1[i]]) {
          ++d1[i];
        }
        r = i + d1[i] - 1;
        l = i - d1[i] + 1;
      }
    }

    cnt += d1[i];
  }

  return cnt;
}

int count_palindromes_even(std::string &str) {
  int n = static_cast<int>(str.size());
  int l = 0, r = -1;
  std::vector<int> d2(n);
  int cnt = 0;

  for (auto i = 0; i < n; ++i) {
    if (i > r) {
      while (i - d2[i] - 1 >= 0 && i + d2[i] < n && str[i - d2[i] - 1] == str[i + d2[i]]) {
        ++d2[i];
      }
      r = i + d2[i] - 1;
      l = i - d2[i] + 1;
    } else {
      int adj = l + (r - i);
      if (adj - d2[adj] + 1 > l) d2[i] = d2[adj];
      else {
        d2[i] = r - i;
        while (i - d2[i] - 1 >= 0 && i + d2[i] < n && str[i - d2[i] - 1] == str[i + d2[i]]) {
          ++d2[i];
        }
        r = i + d2[i] - 1;
        l = i - d2[i] + 1;
      }
    }

    cnt += d2[i];
  }

  return cnt;
}

void stress_palindromes() {
  for (auto i = 0; i < 100000; ++i) {
    std::string test;
    int size = rand() % 1000;
    for (auto j = 0; j < size; ++j) {
      test += static_cast<char>(rand() % 5 + 97);
    }
    int ans1 = count_palindromes_brute(test);
    int ans2 = count_palindromes_even(test) + count_palindromes_odd(test);
    if (ans1 != ans2) {
      std::cout << test << '\n';
      std::cout << ans1 << ' ' << ans2 << '\n';
      return;
    }
  }
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << count_palindromes_even(s) + count_palindromes_odd(s);

  //stress_palindromes();
  return 0;
}
