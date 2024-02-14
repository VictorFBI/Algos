#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <set>

// Элемент хеш-таблицы - список объектов с одним хешем
template<class KeyType, class ValueType>
struct Node {
  KeyType key_;
  ValueType value_;
  Node *next_;

  Node() = default;

  Node(KeyType key, ValueType value) {
    this->key_ = key;
    this->value_ = value;
    next_ = nullptr;
  }
};

// Хеш-таблица
template<class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
 public:
  HashTable() {
    capacity_ = 100;
    array = new Node<KeyType, ValueType> *[capacity_]();
    coeff = 0.5;
    size_ = 0;
  }
  explicit HashTable(Func func) : HashTable() { // NOLINT
    hasher = func;
  }
  HashTable(size_t max_capacity, double lambda, Func func = std::hash<KeyType>()) {
    capacity_ = max_capacity;
    if (0 < lambda && lambda <= 1) coeff = lambda;
    else coeff = 0.5;
    hasher = func;
    size_ = 0;
    array = new Node<KeyType, ValueType> *[capacity_]();
  }

  ~HashTable() {
    for (auto i = 0; i < capacity_; ++i) {
      auto curr = array[i];
      while (curr) {
        auto tmp = curr;
        curr = curr->next_;
        delete tmp;
      }
    }
    delete[] array;
  }

  void insert(KeyType key, ValueType value) {
    auto bucket = hasher(key) % capacity_;

    auto curr = array[bucket];

    while (curr) {
      if (curr->key_ == key) {
        curr->value_ = value;
        return;
      }
      curr = curr->next_;
    }

    auto tail = array[bucket];
    array[bucket] = new Node<KeyType, ValueType>(key, value);
    array[bucket]->next_ = tail;
    ++size_;
    if (static_cast<double>(size_) / static_cast<double>(capacity_) > coeff) rehash();
  }

  ValueType *find(KeyType key) {
    auto bucket = hasher(key) % capacity_;

    auto curr = array[bucket];

    while (curr) {
      if (curr->key_ == key) {
        return &curr->value_;
      }
      curr = curr->next_;
    }

    return nullptr;
  }
  void erase(KeyType key) {
    auto bucket = hasher(key) % capacity_;

    auto curr = array[bucket];
    Node<KeyType, ValueType> *prev = nullptr;

    while (curr) {
      if (curr->key_ == key) {
        if (!prev) {
          array[bucket] = curr->next_;
        } else {
          prev->next_ = curr->next_;
        }
        --size_;
        delete curr;
        return;
      }

      prev = curr;
      curr = curr->next_;
    }
  }

  Node<KeyType, ValueType> &operator[](uint64_t hash) {
    if (hash >= capacity_) throw std::out_of_range("Hash is out of range");
    if (!array[hash]) throw std::runtime_error("Bucket is empty");
    return *array[hash];
  }
  Node<KeyType, ValueType> at(uint64_t hash) {
    if (hash >= capacity_) throw std::out_of_range("Hash is out of range");
    if (!array[hash]) throw std::runtime_error("Bucket is empty");
    return *array[hash];
  }

  size_t size() const {
    return size_;
  }
  size_t capacity() const {
    return capacity_;
  }
 private:
  size_t size_;
  size_t capacity_;
  double coeff;
  Func hasher;
  Node<KeyType, ValueType> **array;

  void rehash() {
    size_t newCapacity = capacity_ * 2;
    Node<KeyType, ValueType> **tmp = new Node<KeyType, ValueType> *[newCapacity]();

    for (auto i = 0; i < capacity_; ++i) {
      auto el = array[i];
      while (el) {
        auto bucket = hasher(el->key_) % (newCapacity);

        if (!tmp[bucket]) {
          tmp[bucket] = new Node<KeyType, ValueType>(el->key_, el->value_);
        } else {
          auto curr = tmp[bucket];
          bool isBreak = false;

          while (curr) {
            if (curr->key_ == el->key_) {
              curr->value_ = el->value_;
              isBreak = true;
              break;
            }
            curr = curr->next_;
          }
          if (!isBreak) {
            auto tail = tmp[bucket];
            tmp[bucket] = new Node<KeyType, ValueType>(el->key_, el->value_);
            tmp[bucket]->next_ = tail;
          }
        }
        el = el->next_;
      }
    }

    for (auto i = 0; i < capacity_; ++i) {
      auto curr = array[i];
      while (curr) {
        auto tmpNode = curr;
        curr = curr->next_;
        delete tmpNode;
      }
    }

    delete[] array;
    capacity_ = newCapacity;
    array = tmp;
  }
};
