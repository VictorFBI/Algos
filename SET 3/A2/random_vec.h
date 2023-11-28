#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> get_random_vector() {
  std::vector<int> vec;
  vec.reserve(4000);
  for (auto i = 0; i < 4000; ++i) {
    vec.push_back(rand() % 3001); // NOLINT
  }

  return vec;
}

std::vector<int> get_random_subvector(std::vector<int>& src, int size) {
  std::vector<int> vec;
  vec.reserve(size);
  if (size == 4000) {
    vec = src;
    return vec;
  }
  int start = rand() % (4000 - size); // NOLINT

  for (auto i = start; i < start + size; ++i) {
    vec.push_back(src[i]);
  }

  return vec;
}

std::vector<int> get_reversed_vector() {
  auto vec = get_random_vector();
  std::sort(vec.begin(), vec.end(), std::greater());
  return vec;
}

void make_almost_sorted_vector(std::vector<int>& src) {
  std::sort(src.begin(), src.end());
  int size = static_cast<int>(src.size());
  int pairs_to_swap = rand() % 4 + 1; // NOLINT
  for (auto i = 0; i < pairs_to_swap; ++i) {
    std::swap(src[rand() % size], src[rand() % size]); // NOLINT
  }
}