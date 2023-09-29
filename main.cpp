#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int algorithm1(vector<int> a) {
  int c = 0;
  int ind = -1;
  for (auto i = 0; i < a.size(); ++i) {
    int c1 = 0;
    for (int j = 0; j < a.size(); ++j) {
      if (a[i] == a[j]) c1++;
    }
    if (c1 > c) {
      c = c1;
      ind = i;
    }
  }
  if (c > a.size() / 2) return a[ind];
}

int algorithm2(vector<int> a) {
  int c = 1;
  int ind = 0;
  for (auto i = 1; i < a.size(); ++i) {
    if (a[ind] == a[i]) c++;
    else c--;
    if (c == 0) {
      ind = i;
      c = 1;
    }
  }

  int count = 0;
  for(auto i = 0; i < a.size(); ++i) {
    if (a[i] == a[ind]) ++count;
    if (count > a.size() / 2) return a[ind];
  }
}
int algorithm3(vector<int> a) {
  if (a.size() == 1) return a[0];
  auto c = 1;
  std::sort(a.begin(), a.end());
  auto i = 1;
  for (; i < a.size(); ++i) {
    if (a[i - 1] == a[i]) c++;
    else {
      if (c > a.size() / 2) return a[i - 1];
      c = 1;
    }
  }
  if (c > a.size() / 2) return a[i - 1];
}

int main() {
  vector<int> a{1, 5, 3, 4, 5, 5, 5, 6, 5};
  std::cout << algorithm1(a) << "\n";
  std::cout << algorithm2(a) << "\n";
  std::cout << algorithm3(a) << "\n";
  return 0;
}