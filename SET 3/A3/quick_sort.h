#pragma once

#include <iostream>
#include <random>
#include <vector>
#include "heap_sort.h"

// A function to return a seeded random number generator.
inline std::mt19937& generator() {
  // the generator will only be seeded once (per thread) since it's static
  static thread_local std::mt19937 gen(std::random_device{}());
  return gen;
}

// A function to generate integers in the range [min, max]
template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
T my_rand(T min, T max) {
  std::uniform_int_distribution<T> dist(min, max);
  return dist(generator());
}

// A function to generate floats in the range [min, max)
template<typename T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
T my_rand(T min, T max) {
  std::uniform_real_distribution<T> dist(min, max);
  return dist(generator());
}


std::pair<int, int> partition(std::vector<int>& vec, int left, int right, int pivot) {
  int e = left, g = left;
  for (int i = left; i <= right; i++) {
    if (vec[i] > pivot) continue;
    if (vec[i] < pivot) {
      std::swap(vec[e], vec[i]);
      if (e != g) {
        std::swap(vec[g], vec[i]);
      }
      ++e;
      ++g;
      continue;
    }
    std::swap(vec[g], vec[i]);
    ++g;
  }

  return std::make_pair(e, g);
}

void quick_sort(std::vector<int>& vec, int left, int right) { // NOLINT
  if (left < right) {
    if (right - left == 1 && vec[left] > vec[right]) {
      std::swap(vec[left], vec[right]);
      return;
    }
    int pvt = vec[my_rand(left, right)];
    auto pair = partition(vec, left, right, pvt);
    quick_sort(vec, left, pair.first - 1);
    quick_sort(vec, pair.second, right);
  }
}

void hybrid_sort(std::vector<int>& vec, int left, int right) { // NOLINT
  if (left < right) {
    if (right - left <= 50) {
      heap_sort(vec, left, right);
      return;
    }
    int pvt = vec[my_rand(left, right)];
    auto pair = partition(vec, left, right, pvt);
    hybrid_sort(vec, left, pair.first - 1);
    hybrid_sort(vec, pair.second, right);
  }
}


