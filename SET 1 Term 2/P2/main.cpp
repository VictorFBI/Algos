#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class BloomFilter {
 public:
  BloomFilter(size_t hashes, size_t bits) {
    hashes_ = hashes;
    bits_ = bits;
    totalVerifies = 0;
    fpVerifies = 0;
    filter = std::vector<bool>(bits, false);
  }

  ~BloomFilter() = default;

  void add(const std::string &obj) {
    set.insert(obj);
    for (size_t i = 0; i < hashes_; ++i) {
      filter[hash(obj, i) % bits_] = true;
    }
  }

  bool verify(const std::string &obj) {
    ++totalVerifies;
    for (size_t i = 0; i < hashes_; ++i) {
      if (!filter[hash(obj, i) % bits_]) return false;
    }
    if (!set.count(obj)) ++fpVerifies;
    return true;
  }

  double getFPRate() const {
    if (totalVerifies == 0) return 0;
    return fpVerifies / totalVerifies;
  }

  size_t numberOfHashFunctions() const {
    return hashes_;
  }
  size_t numberOfBits() const {
    return bits_;
  }

 private:
  std::vector<bool> filter;
  std::unordered_set<std::string> set;
  size_t hashes_;
  size_t bits_;
  double totalVerifies;
  double fpVerifies;
  static size_t hash(const std::string &str, size_t index) {
    if (index) return std::hash<std::string>{}(str + std::to_string(index));
    else return std::hash<std::string>{}(str);
  }
};
