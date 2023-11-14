#include <iostream>
#include <vector>

class Permutation {
 public:
  explicit Permutation(std::vector<int> &_perm) : perm(_perm) {}
  static Permutation inv(Permutation &other) {
    std::vector<int> vec;
    for (auto i = 0; i < 6; ++i) {
      for (auto j = 0; j < 6; ++j) {
        if (other.perm[j] == i + 1) vec.push_back(j + 1);
      }
    }
    return Permutation(vec);
  }
  Permutation operator*(Permutation &other) {
    std::vector<int> vec;

    for (auto i = 0; i < 6; ++i) {
      vec.push_back(perm[other.perm[i] - 1]);
    }

    return Permutation(vec);
  }

  void print() const {
    for (auto &el : perm) {
      std::cout << el << " ";
    }
    std::cout << '\n';
  }
 private:
  std::vector<int> perm;
};

void read_vector(std::vector<int> &vec) {
  for (auto i = 0; i < 6; ++i) {
    int a;
    std::cin >> a;
    vec.push_back(a);
  }
}

int main() {
  std::vector<int> vec;
  std::cout << "A: ";
  read_vector(vec);
  Permutation A(vec);
  vec.clear();

  std::cout << "B: ";
  read_vector(vec);
  Permutation B(vec);
  vec.clear();

  std::cout << "C: ";
  read_vector(vec);
  Permutation C(vec);
  vec.clear();

  Permutation invA = Permutation::inv(A);
  Permutation ans = C * A * B * invA * invA * C;
  ans.print();
  return 0;
}
