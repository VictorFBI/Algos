#include <iostream>
#include <vector>

template<typename T>
class HashLPTable {
 public:

  explicit HashLPTable(size_t par_capacity) {
    capacity_ = par_capacity;
    size_ = 0;
    table = std::vector<T>(capacity_);
    isErased = std::vector<bool>(capacity_, false);
    isNull = std::vector<bool>(capacity_, true);
  }

  ~HashLPTable() = default;

  void insert(T key) {
    auto ind = std::hash<T>{}(key) % capacity_;

    while (!isNull[ind] && !isErased[ind]) {
      if (table[ind] == key) return;
      ind = (ind + 1) % capacity_;
    }
    table[ind] = key;
    isNull[ind] = false;
    isErased[ind] = false;
    ++size_;

    if (static_cast<double>(size_) / static_cast<double>(capacity_) >= 0.5) rehash();
  }

  void remove(T key) {
    auto ind = std::hash<T>{}(key) % capacity_;

    while (!isNull[ind]) {
      if (table[ind] == key) {
        isErased[ind] = true;
        isNull[ind] = false;
        --size_;
        return;
      }

      ind = (ind + 1) % capacity_;
    }
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

  [[nodiscard]] size_t capacity() const {
    return capacity_;
  }

  bool search(T key) {
    auto ind = std::hash<T>{}(key) % capacity_;

    while (!isNull[ind]) {
      if (table[ind] == key && !isErased[ind]) return true;
      ind = (ind + 1) % capacity_;
    }
    return false;
  }

 private:
  size_t capacity_;
  size_t size_;
  std::vector<T> table;
  std::vector<bool> isNull;
  std::vector<bool> isErased;

  void rehash() {
    std::vector<T> tmpTable(2 * capacity_);
    std::vector<bool> tmpIsNull(2 * capacity_, true);
    std::vector<bool> tmpIsErased(2 * capacity_, false);

    for (auto i = 0; i < capacity_; ++i) {
      if (isNull[i] || isErased[i]) continue;
      auto ind = std::hash<T>{}(table[i]) % (2 * capacity_);

      while (!tmpIsNull[ind] && !tmpIsErased[ind]) {
        ind = (ind + 1) % (2 * capacity_);
      }
      tmpTable[ind] = table[i];
      tmpIsNull[ind] = false;
      tmpIsErased[ind] = false;
    }

    table = tmpTable;
    isNull = tmpIsNull;
    isErased = tmpIsErased;
    capacity_ *= 2;
  }
};

int main() {
  HashLPTable<int> set(4);

  for (auto i = 0; i <= 10000; ++i) {
    set.insert(i);
  }

  for (auto i = 0; i <= 10000; i += 2) {
    set.remove(i);
  }

  for (auto i = 0; i <= 10000; i += 2) {
    if (set.search(i)) {
      std::cout << "Wrong realisation!";
    }
  }

  std::cout << "Nice realisation\n";
  std::cout << "Size = " << set.size();

  return 0;
}
