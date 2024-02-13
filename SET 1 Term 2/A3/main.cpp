#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <random>

std::vector<std::string> ans;
std::unordered_set<std::string> set;
std::ofstream fout;

const int p = 31;

long long hash(const std::string &str) {
  long long hash = 0, pPow = 1;
  for (auto i = 0; i < str.size(); ++i) { // NOLINT
    hash += (str[i] - 'a' + 1) * pPow;
    pPow *= p;
  }
  return hash;
}

void writeAns() {
  for (auto &el : ans) {
    fout << el << '\n';
  }
}

void checkEqualHash() {
  long long initialHash = hash(ans[0]);
  for (auto i = 1; i < ans.size(); ++i) {
    if (hash(ans[i]) != initialHash) {
      fout << "Different hashes!" << '\n';
      return;
    }
  }

  fout << "All hashes are equal!" << '\n';
}

void generate(std::string &str, std::string &curr, long long currHash) { // NOLINT
  if (curr.size() == str.size() - 1) {
    curr.push_back(static_cast<char>(currHash - 1 + 'a'));
    if (curr != str) {
      ans.emplace_back(curr);
      set.insert(curr);
    }
    curr.pop_back();
    return;
  }
  for (auto i = -48; i != -38; ++i) {
    if ((currHash - i) % p == 0) {
      char sym = static_cast<char>(i - 1 + 'a');
      curr.push_back(sym);
      generate(str, curr, (currHash - i) / p);
      curr.pop_back();
    }
  }
  for (auto i = -p; i != -5; ++i) {
    if ((currHash - i) % p == 0) {
      char sym = static_cast<char>(i - 1 + 'a');
      curr.push_back(sym);
      generate(str, curr, (currHash - i) / p);
      curr.pop_back();
    }
  }

  for (auto i = 1; i != 27; ++i) {
    if ((currHash - i) % p == 0) {
      char sym = static_cast<char>(i - 1 + 'a');
      curr.push_back(sym);
      generate(str, curr, (currHash - i) / p);
      curr.pop_back();
    }
  }

}

void browseAllVariants() {
  std::string digits = "0123456789";
  std::string lower = "qwertyuiopasdfghjklzxcvbnm";
  std::string upper = lower;

  for (auto i = 0; i < lower.size(); ++i) {
    upper[i] -= 32;
  }

  std::vector<int> nums;

  for (auto i = 0; i < lower.size(); ++i) {
    nums.emplace_back(lower[i] - 'a' + 1);
    nums.emplace_back(upper[i] - 'a' + 1);
  }

  for (auto i = 0; i < digits.size(); ++i) { // NOLINT
    nums.emplace_back(digits[i] - 'a' + 1);
  }

  std::sort(nums.begin(), nums.end());

  for (auto &el : nums) {
    std::cout << el << '\n';
  }
}

int main() {
  auto startTime = std::chrono::high_resolution_clock::now();
  fout.open("hacked.txt");
  std::unordered_set<std::string> processedStrings;
  std::string initial = "0123456789"; // length = 12 abcdefghijkl
  int count = 0;
  unsigned int seed = 1;
  while (count != 100) {
    auto rnd = std::default_random_engine{seed};
    auto tmp = initial;
    std::shuffle(tmp.begin(), tmp.end(), rnd);
    if (processedStrings.contains(tmp)) {
      ++seed;
      continue;
    }
    std::string starter;
    generate(tmp, starter, hash(tmp));
    ++count;
    processedStrings.insert(tmp);
    fout << "Source string = " << tmp << '\n';
    writeAns();
    fout << "Total amount of strings = " << ans.size() << '\n';
    if (ans.size() == set.size()) {
      fout << "All strings are different!" << '\n';
    } else {
      fout << "Some strings are equal!" << '\n';
    }
    checkEqualHash();
    fout << "###################################\n";
    ans.clear();
    set.clear();
    std::cout << count << '\n';
  }
  fout.close();
  auto endTime = std::chrono::high_resolution_clock::now();
  std::cout << "Total time to hack = " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " seconds";

  return 0;
}
