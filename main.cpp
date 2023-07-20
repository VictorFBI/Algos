#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    auto curr = new ListNode();
    auto ans = curr;
    int is_ten = 0;
    while (true) {
      curr->val = (l1->val + l2->val + is_ten) % 10;
      is_ten = (l1->val + l2->val + is_ten) / 10;

      if (l1->next == nullptr && l2->next == nullptr) {
        if (is_ten > 0) {
          curr->next = new ListNode();
          curr = curr->next;
          curr->val = is_ten;
        }
        break;
      }

      if (l1->next != nullptr) {
        l1 = l1->next;
      } else {
        l1->val = 0;
      }

      if (l2->next != nullptr) {
        l2 = l2->next;
      } else {
        l2->val = 0;
      }

      curr->next = new ListNode();
      curr = curr->next;
    }
    return ans;
  }
};
int main() {

}