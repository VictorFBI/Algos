#include <iostream>
#include <vector>
#include <unordered_map>

struct Node {
  Node(int _val, Node *_prev, Node *_next) : val(_val), prev(_prev), next(_next) {
  }
  int val;
  Node *prev;
  Node *next;
};

class DoublyLinkedList {
 public:
  DoublyLinkedList() : size(0), head(nullptr), tail(nullptr) {
  }
  DoublyLinkedList(const DoublyLinkedList &other) : DoublyLinkedList() {
    auto iter = other.head;
    while (iter != nullptr) {
      pushBack(iter->val);
      iter = iter->prev;
    }
  }
  explicit DoublyLinkedList(std::vector<int>& vec) : DoublyLinkedList() {
    for (auto& el : vec) {
      pushBack(el);
    }
  }
  void pushBack(int el) {
    if (size == 0) {
      head = new Node(el, nullptr, nullptr);
      tail = head;
    } else {
      tail->prev = new Node(el, nullptr, tail);
      tail = tail->prev;
    }
    ++size;
  }
  void pushFront(int el) {
    if (size == 0) {
      head = new Node(el, nullptr, nullptr);
      tail = head;
    } else {
      head->next = new Node(el, head, nullptr);
      head = head->next;
    }
    ++size;
  }
  void insert(Node *prev, int data) {
    if (prev == nullptr || !contains(prev)) {
      throw std::runtime_error("Wrong position for insertion!");
    }
    if (prev->next == nullptr) {
      pushFront(data);
      return;
    }
    auto to_insert = new Node(data, prev, prev->next);
    prev->next = to_insert;
    prev->next->prev = to_insert;
    ++size;
  }
  void popFront() {
    if (size == 0) {
      throw std::runtime_error("Deletion error!");
    }
    head = head->prev;
    delete head->next;
    head->next = nullptr;
    --size;
  }
  void popBack() {
    if (size == 0) {
      throw std::runtime_error("Deletion error!");
    }
    tail = tail->next;
    delete tail->prev;
    tail->prev = nullptr;
    --size;
  }
  void pop(Node *pos) {
    if (pos == nullptr || !contains(pos)) {
      throw std::runtime_error("Wrong position for deletion!");
    }
    if (pos->next == nullptr) {
      popFront();
      return;
    }
    if (pos->prev == nullptr) {
      popBack();
      return;
    }

    pos->next->prev = pos->prev;
    pos->prev->next = pos->next;
    delete pos;
    --size;
  }
  void erase() {
    if (size == 0) return;
    while (size != 1) {
      popBack();
    }
    delete head;
    head = nullptr;
    tail = nullptr;
    size = 0;
  }
  void reverse() {
    auto forward = head;
    auto back = tail;
    for (auto i = 1; i <= size / 2; ++i) {
      std::swap(forward->val, back->val);
      forward = forward->prev;
      back = back->next;
    }
  }
  void removeDuplicates() {
    std::unordered_map<int, int> map;
    auto iter = head;
    auto tmp = new DoublyLinkedList();
    while (iter != nullptr) {
      if (map.count(iter->val) == 0) {
        tmp->pushBack(iter->val);
        map[iter->val] = 1;
      }
      iter = iter->prev;
    }
    erase();
    head = tmp->head;
    tail = tmp->tail;
    size = tmp->size;
  }
  void replace(int el, int new_el) {
    auto iter = head;
    while (iter != nullptr) {
      if (iter->val == el) iter->val = new_el;
      iter = iter->prev;
    }
  }

  // delete this method in the final answer
  void print() {
    auto iter = head;
    while (iter != nullptr) {
      std::cout << iter->val << " ";
      iter = iter->prev;
    }
    std::cout << "\n";
  }

 private:
  std::size_t size;
  Node *head;
  Node *tail;
  bool contains(Node *pos) {
    auto iter = head;
    while (iter != nullptr) {
      if (iter == pos) return true;
      iter = iter->prev;
    }
    return false;
  }
};

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5};
  auto list = DoublyLinkedList(vec);
  list.print();
  list.popBack();
  list.print();
  list.popFront();
  list.print();
  list.pushBack(3);
  list.pushBack(5);
  list.pushBack(3);
  list.pushBack(4);
  list.pushBack(5);
  list.print();
  list.removeDuplicates();
  list.print();
  list.reverse();
  list.print();
  list.pushBack(1);
  list.reverse();
  list.print();
  list.erase();
  list.print();
  list.pushBack(1);
  list.pushFront(7);
  list.print();
  list.reverse();
  list.print();
  list.pushFront(7);
  list.print();
  list.removeDuplicates();
  list.print();
  list.pushBack(3);
  list.reverse();
  list.print();
  return 0;
}
