#include <iostream>
#include <vector>

template<typename T>
class HashCuckooTable {
 public:
  explicit HashCuckooTable(size_t capacity_, size_t maxCountAttempts_) {
    maxCountAttempts = maxCountAttempts_;
    size_ = 0;
    this->capacity_ = capacity_;
    first = std::vector<T *>(capacity_, nullptr);
    second = std::vector<T *>(capacity_, nullptr);
  }

  void insert(T key) {
    insertHelper(key, first, second);
    isDone = false;
    if (static_cast<double>(size_) / static_cast<double>(capacity_) >= 0.5) rehash();
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

  [[nodiscard]] size_t capacity() const {
    return capacity_;
  }

  bool search(T key) {
    auto ind1 = hash1(key);
    if (first[ind1] && *first[ind1] == key) return true;
    auto ind2 = hash2(key);
    if (second[ind2] && *second[ind2] == key) return true;
    return false;
  }

 private:
  std::vector<T *> first;
  std::vector<T *> second;
  size_t maxCountAttempts;
  size_t currCountAttempts = 0;
  size_t capacity_;
  size_t size_;
  size_t salt1 = 1;
  size_t salt2 = 2;
  bool isDone = false;
  bool isFirst = true;

  size_t hash1(T key) {
    return std::hash<std::string>{}(std::to_string(key) + std::to_string(salt1)) % capacity_;
  }

  size_t hash2(T key) {
    return std::hash<std::string>{}(std::to_string(key) + std::to_string(salt2)) % capacity_;
  }

  void insertHelper(T key, std::vector<T *> &vec1, std::vector<T *> &vec2) { // NOLINT
    if (currCountAttempts == maxCountAttempts) {
      salt1 += 2;
      salt2 += 2;
      currCountAttempts = 0;
      rebuild();
      insertHelper(key, vec1, vec2);
      return;
    }

    auto ind1 = hash1(key);
    if (!vec1[ind1]) {
      vec1[ind1] = new T(key);
      if (&vec1 == &first) ++size_;
      return;
    }

    if (*vec1[ind1] == key) return;
    auto ind2 = hash2(key);

    if (!vec2[ind2]) {
      vec2[ind2] = new T(key);
      if (&vec2 == &second) ++size_;
      return;
    }

    if (*vec2[ind2] == key) return;

    T tmp;
    if (isFirst) {
      tmp = *vec1[ind1];
      delete vec1[ind1];
      vec1[ind1] = new T(key);
      isFirst = false;
    } else {
      tmp = *vec2[ind2];
      delete vec2[ind2];
      vec2[ind2] = new T(key);
      isFirst = true;
    }
    ++currCountAttempts;
    insertHelper(tmp, vec1, vec2);
    currCountAttempts = 0;
  }

  void rebuild() { // NOLINT
    std::vector<T *> tmp1(capacity_, nullptr);
    std::vector<T *> tmp2(capacity_, nullptr);
    for (auto i = 0; i < capacity_; ++i) {
      if (!first[i]) continue;
      insertHelper(*first[i], tmp1, tmp2);
    }
    for (auto i = 0; i < capacity_; ++i) {
      if (!second[i]) continue;
      insertHelper(*second[i], tmp1, tmp2);
    }
    if (isDone) return;
    first = tmp1;
    second = tmp2;
    isDone = true;
  }

  void rehash() {
    capacity_ *= 2;
    std::vector<T*> tmp1(capacity_, nullptr);
    std::vector<T*> tmp2(capacity_, nullptr);
    for (auto i = 0; i < capacity_ / 2; ++i) {
      if (!first[i]) continue;
      insertHelper(*first[i], tmp1, tmp2);
    }

    for (auto i = 0; i < capacity_ / 2; ++i) {
      if (!second[i]) continue;
      insertHelper(*second[i], tmp1, tmp2);
    }
    first = tmp1;
    second = tmp2;
  }

};

int main() {
  HashCuckooTable<int> set(100, 100);
  for (auto i = 0; i < 1000000; ++i) {
    set.insert(i);
  }

  for (auto i = 0; i < 1000000; ++i) {
    if (!set.search(i)) {
      std::cout << "Wrong realisation!";
      return 0;
    }
  }

  std::cout << set.size() << '\n';
  std::cout << set.capacity() << '\n';

  std::cout << "Nice realisation!";

  return 0;
}
