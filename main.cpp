#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> result;
    set<vector<int>> triplets;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; ++i) {
      int left = i + 1;
      int right = nums.size() - 1;
      while (left != right) {
        if (nums[i] + nums[left] + nums[right] > 0) {
          --right;
          continue;
        }
        if (nums[i] + nums[left] + nums[right] < 0) {
          ++left;
          continue;
        }
        vector<int> triplet{nums[i], nums[left], nums[right]};
        triplets.insert(triplet);
        ++left;
      }
    }
    for (auto &el : triplets) {
      result.push_back(el);
    }

    return result;
  }
};
int main() {
  vector<int> vec{-2, 0, 1, 1, 2};
  Solution s;
  for (auto &triplet : s.threeSum(vec)) {
    for (auto &el : triplet) {
      cout << el << " ";
    }
    cout << endl;
  }

  return 0;
}
