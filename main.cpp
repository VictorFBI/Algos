#include <iostream>
#include <stack>

class Queue {
 public:
  Queue() = default;
  ~Queue() = default;

  Queue(const Queue &other) = default;

  Queue(Queue &&other) noexcept
      : min(other.min),
        _back(std::move(other._back)),
        pushStack(std::move(other.pushStack)),
        popStack(std::move(other.popStack)),
        _size(other._size) {
  }

  Queue &operator=(const Queue &other) {
    if (this != &other) {
      pushStack = other.pushStack;
      popStack = other.popStack;
      _size = other._size;
      min = other.min;
      _back = other._back;
    }

    return *this;
  }

  Queue &operator=(Queue &&other) noexcept {
    if (this != &other) {
      pushStack = std::move(other.pushStack);
      popStack = std::move(other.popStack);
      _size = other._size;
      min = other.min;
      _back = std::move(other._back);
      other._size = 0;
      other.min = 0;
    }

    return *this;
  }

  void push(int &val) {
    if (pushStack.empty()) {
      min = val;
    } else {
      if (val < min) min = val;
    }
    _back = std::make_pair(val, min);
    pushStack.emplace(val, min);
    ++_size;
  }

  void push(int &&val) {
    if (pushStack.empty()) {
      min = val;
    } else {
      if (val < min) min = val;
    }
    _back = std::make_pair(val, min);
    pushStack.emplace(val, min);
    ++_size;
  }

  void pop() {
    if (empty()) throw std::runtime_error("Queue is empty");
    if (popStack.empty()) {
      _back = pushStack.top();
      int tmp_min;
      while (!pushStack.empty()) {
        if (popStack.empty()) tmp_min = pushStack.top().second;
        else {
          if (pushStack.top().second < tmp_min) tmp_min = pushStack.top().second;
        }
        popStack.emplace(pushStack.top().first, tmp_min);
        pushStack.pop();
      }
    }
    if (popStack.top().first == popStack.top().second) {
      popStack.pop();
      std::stack<std::pair<int, int>> tmp;
      int tmp_min;
      while (!popStack.empty()) {
        if (tmp.empty()) tmp_min = popStack.top().first;
        else {
          if (popStack.top().first < tmp_min) tmp_min = popStack.top().first;
        }
        tmp.emplace(popStack.top().first, tmp_min);
        popStack.pop();
      }
      while (!tmp.empty()) {
        popStack.emplace(tmp.top().first, tmp_min);
        tmp.pop();
      }
    } else {
      popStack.pop();
    }
    --_size;
  }

  int &front() {
    if (empty()) throw std::runtime_error("Queue is empty");
    if (popStack.empty()) {
      _back = pushStack.top();
      int tmp_min;
      while (!pushStack.empty()) {
        if (popStack.empty()) tmp_min = pushStack.top().second;
        else {
          if (pushStack.top().second < tmp_min) tmp_min = pushStack.top().second;
        }
        popStack.emplace(pushStack.top().first, tmp_min);
        pushStack.pop();
      }
    }
    return popStack.top().first;
  }

  int &back() {
    if (empty()) throw std::runtime_error("Queue is empty");
    return _back.first;
  }

  const int &getMin() {
    if (empty()) throw std::runtime_error("Queue is empty");
    if (!popStack.empty() && !pushStack.empty()) return std::min(pushStack.top().second, popStack.top().second);
    if (!popStack.empty()) return popStack.top().second;
    return pushStack.top().second;
  }

  void swap(Queue &other) {
    std::swap(*this, other);
  }

  [[nodiscard]] size_t size() const {
    return _size;
  }

  [[nodiscard]] bool empty() const {
    return _size == 0;
  }

 private:
  int min{};
  std::pair<int, int> _back{};
  std::stack<std::pair<int, int>> pushStack;
  std::stack<std::pair<int, int>> popStack;
  size_t _size = 0;
};

int main() {
  Queue q;
  q.push(1);
  q.push(-1);
  q.push(0);
  q.push(5);
  q.push(3);
  std::cout << "Front: " << q.front() << "\n";
  std::cout << "Back: " << q.back() << " \n";
  std::cout << "Min: " << q.getMin() << "\n";
  std::cout << "\n";
  q.pop();
  std::cout << "Front: " << q.front() << "\n";
  std::cout << "Back: " << q.back() << " \n";
  std::cout << "Min: " << q.getMin() << "\n";
  std::cout << "\n";
  q.pop();
  std::cout << "Front: " << q.front() << "\n";
  std::cout << "Back: " << q.back() << " \n";
  std::cout << "Min: " << q.getMin() << "\n";
  std::cout << "\n";
  q.pop();
  std::cout << "Front: " << q.front() << "\n";
  std::cout << "Back: " << q.back() << " \n";
  std::cout << "Min: " << q.getMin() << "\n";
  std::cout << "\n";
  q.pop();
  std::cout << "Front: " << q.front() << "\n";
  std::cout << "Back: " << q.back() << " \n";
  std::cout << "Min: " << q.getMin() << "\n";
  std::cout << "\n";
  q.pop();
  return 0;
}