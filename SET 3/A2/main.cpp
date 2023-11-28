#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "sort_algorithms.h"
#include "random_vec.h"

enum sort_type {
  merge,
  hybrid
};

long long mark_time(std::vector<int> &vec, sort_type value) {
  long long millisec;
  if (value == merge) {
    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(vec, 0, static_cast<int>(vec.size()));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  } else {
    auto start = std::chrono::high_resolution_clock::now();
    hybrid_sort(vec, 0, static_cast<int>(vec.size()));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }

  return millisec;
}

std::ofstream fout_abs(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\abs_random_merge.txt)");
std::ofstream fout_rev(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\reversed_merge.txt)");
std::ofstream fout_sor(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\alm_sorted_merge.txt)");

void test_sort(sort_type value) {
  for (auto size = 500; size <= 4000; size += 100) {
    long long total_time = 0;
    for (auto i = 0; i < 100; ++i) {
      auto vec = get_random_vector();
      auto sub_vec = get_random_subvector(vec, size);
      total_time += mark_time(sub_vec, value);
    }
    fout_abs << "(" << size << ", " << static_cast<double>(total_time) / 100 << ") ";

    total_time = 0;
    for (auto i = 0; i < 100; ++i) {
      auto vec = get_reversed_vector();
      auto sub_vec = get_random_subvector(vec, size);
      total_time += mark_time(sub_vec, value);
    }
    fout_rev << "(" << size << ", " << static_cast<double>(total_time) / 100 << ") ";

    total_time = 0;
    for (auto i = 0; i < 100; ++i) {
      auto vec = get_random_vector();
      auto sub_vec = get_random_subvector(vec, size);
      make_almost_sorted_vector(sub_vec);
      total_time += mark_time(sub_vec, value);
    }
    fout_sor << "(" << size << ", " << static_cast<double>(total_time) / 100 << ") ";
  }
}

int main() {

  fout_abs.close();
  fout_rev.close();
  fout_sor.close();

  fout_abs.open(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\abs_random_hybrid20.txt)");
  fout_rev.open(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\reversed_hybrid20.txt)");
  fout_sor.open(R"(C:\Users\frolo\CLionProjects\assemblyTestProgram\alm_sorted_hybrid20.txt)");

  test_sort(hybrid);

  return 0;
}
