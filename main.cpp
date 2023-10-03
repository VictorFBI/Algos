#include <iostream>
#include <vector>
#include <unordered_set>

struct Node {
  Node() = default;
  explicit Node(int value) : next(nullptr), previous(nullptr), data(value) {
  }
  Node *next;
  Node *previous;
  int data;
};

class DoublyLinkedList {
 public:
  Node *head;
  Node *tail;
  DoublyLinkedList() : head(nullptr), tail(nullptr) {
  }
  DoublyLinkedList(const DoublyLinkedList &other) : DoublyLinkedList() {
    auto iter = other.head;
    while (iter != nullptr) {
      pushBack(iter->data);
      iter = iter->next;
    }
  }
  explicit DoublyLinkedList(std::vector<int> &vec) : DoublyLinkedList() {
    for (auto &el : vec) {
      pushBack(el);
    }
  }
  ~DoublyLinkedList() {
    erase();
  }
  void pushBack(int el) {
    auto tmp = new Node(el);
    if (head == nullptr) {
      head = tmp;
      tail = head;
    } else {
      tmp->previous = tail;
      tail->next = tmp;
      tail = tmp;
    }
  }
  void pushFront(int el) {
    auto tmp = new Node(el);
    if (head == nullptr) {
      head = tmp;
      tail = head;
    } else {
      tmp->next = head;
      head->previous = tmp;
      head = tmp;
    }
  }
  void insert(Node *prev, int data) {
    if (prev == nullptr) throw std::runtime_error("Wrong position for insertion!");
    if (prev == tail) {
      pushBack(data);
      return;
    }
    auto tmp = head;
    bool isBreak = false;
    while (tmp != nullptr) {
      if (prev == tmp) {
        auto to_insert = new Node(data);
        to_insert->previous = tmp;
        to_insert->next = tmp->next;
        tmp->next->previous = to_insert;
        tmp->next = to_insert;
        isBreak = true;
        break;
      }
      tmp = tmp->next;
    }

    if (!isBreak) throw std::runtime_error("Wrong position for insertion!");
  }
  void popFront() {
    if (head == nullptr) {
      throw std::runtime_error("Deletion error!");
    }
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
      return;
    }
    head = head->next;
    delete head->previous;
    head->previous = nullptr;
  }
  void popBack() {
    if (head == nullptr) {
      throw std::runtime_error("Deletion error!");
    }
    if (head == tail) {
      delete tail;
      head = nullptr;
      tail = nullptr;
      return;
    }
    tail = tail->previous;
    delete tail->next;
    tail->next = nullptr;
  }
  void pop(Node *pos) {
    if (pos == nullptr || head == nullptr) throw std::runtime_error("Wrong position for deletion!");
    if (pos == tail) {
      popBack();
      return;
    }
    if (pos == head) {
      popFront();
      return;
    }
    auto tmp = head;
    bool isBreak = false;
    while (tmp != nullptr) {
      if (pos == tmp) {
        pos->previous->next = pos->next;
        pos->next->previous = pos->previous;
        delete pos;
        isBreak = true;
        break;
      }
      tmp = tmp->next;
    }
    if (!isBreak) throw std::runtime_error("Wrong position for deletion!");
  }
  void erase() {
    if (head == nullptr) return;
    while (head != tail) {
      popBack();
    }
    delete head;
    head = nullptr;
    tail = nullptr;
  }
  void reverse() {
    auto tmp = head;
    auto oldHead = head;
    while (tmp != nullptr) {
      auto previous = tmp->previous;
      auto next = tmp->next;
      tmp->previous = next;
      tmp->next = previous;
      tmp = next;
    }
    head = tail;
    tail = oldHead;
  }
  void removeDuplicates() {
    std::unordered_set<int> set;
    auto iter = head;
    while (iter != nullptr) {
      if (set.count(iter->data) == 0) {
        set.insert(iter->data);
      } else {
        auto tmp = iter;

        pop(tmp);
      }
      iter = iter->next;
    }
  }
  void replace(int oldElem, int newElem) const {
    auto iter = head;
    while (iter != nullptr) {
      if (iter->data == oldElem) iter->data = newElem;
      iter = iter->next;
    }
  }

  void print() const {
    auto iter = head;
    while (iter != nullptr) {
      std::cout << iter->data << " ";
      iter = iter->next;
    }
    std::cout << "\n";
  }
};

int main() {
  DoublyLinkedList l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushBack(3);
  l.print();
  l.insert(l.head->next, 5);
  l.print();
  return 0;
}