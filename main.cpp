#include <iostream>
#include <stack>

template<typename T>
class Queue {
 public:
  Queue() = default;
  ~Queue() = default;

  Queue(const Queue &other) : pushStack(other.pushStack), popStack(other.popStack), _size(other._size) {
  }

  Queue(Queue &&other) noexcept
      : pushStack(std::move(other.pushStack)), popStack(std::move(other.popStack)), _size(std::move(other._size)) {
  }

  Queue &operator=(const Queue &other) {
    if (this != &other) {
      pushStack = other.pushStack;
      popStack = other.popStack;
      _size = other._size;
    }

    return *this;
  }

  Queue &operator=(Queue &&other) noexcept {
    if (this != &other) {
      pushStack = std::move(other.pushStack);
      popStack = std::move(other.popStack);
      _size = other._size;
      other._size = 0;
    }

    return *this;
  }

  void push(T &val) {
    pushStack.push(val);
    if (increasing.empty() || val <= increasing.top()) increasing.push(val);
    else {
      while (!increasing.empty()) {
        decreasing.push(increasing.top());
        increasing.pop();
      }

      while (!decreasing.empty() && val < decreasing.top()) {
        decreasing.pop();
      }
      decreasing.push(val);

      while (!decreasing.empty()) {
        increasing.push(decreasing.top());
        decreasing.pop();
      }
    }
    ++_size;
  }

  void push(T &&val) {
    pushStack.push(val);
    if (increasing.empty() || val <= increasing.top()) increasing.push(val);
    else {
      while (!increasing.empty()) {
        decreasing.push(increasing.top());
        increasing.pop();
      }

      while (!decreasing.empty() && val < decreasing.top()) {
        decreasing.pop();
      }
      decreasing.push(val);

      while (!decreasing.empty()) {
        increasing.push(decreasing.top());
        decreasing.pop();
      }
    }
    ++_size;
  }

  void pop() {
    if (empty()) throw std::runtime_error("Queue is empty");

    if (popStack.empty()) {
      int count = 0;
      while (!pushStack.empty()) {
        popStack.push(pushStack.top());
        if (count == 0) _back = pushStack.top();
        ++count;
        pushStack.pop();
      }
    }

    if (increasing.top() == popStack.top()) {
      increasing.pop();
    }

    popStack.pop();
    --_size;
  }

  T &front() {
    if (empty()) throw std::runtime_error("Stack is empty");

    if (popStack.empty()) {
      int count = 0;
      while (!pushStack.empty()) {
        popStack.push(pushStack.top());
        if (count == 0) _back = pushStack.top();
        ++count;
        pushStack.pop();
      }
    }

    return popStack.top();
  }

  T &back() {
    if (empty()) throw std::runtime_error("Stack is empty");

    if (pushStack.empty()) return _back;
    else return pushStack.top();
  }

  T &min() {
    return increasing.top();
  }

  void swap(Queue &other) {
    std::swap(*this, other);
  }

  size_t size() {
    return _size;
  }

  bool empty() {
    return _size == 0;
  }

 private:
  T _back{};
  std::stack<T> pushStack;
  std::stack<T> popStack;
  std::stack<T> increasing;
  std::stack<T> decreasing;
  size_t _size = 0;
};

int main() {
  Queue<int> q;
  q.push(3);
  q.push(4);
  q.push(5);
  q.push(6);
  q.push(7);
  std::cout << q.min() << "\n";
  q.pop();
  std::cout << q.min() << "\n";
  q.pop();
  std::cout << q.min() << "\n";
  q.pop();
  std::cout << q.min() << "\n";
  q.pop();
  std::cout << q.min() << "\n";
  q.pop();

  return 0;
}
