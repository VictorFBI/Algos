#pragma once

#include <iostream>
#include <vector>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int left(int i) {
  return 2 * (i + 1) - 1;
}

int right(int i) {
  return 2 * (i + 1);
}

void max_heapify(std::vector<int> &vec, int i, int size, int start) { // NOLINT
  int l = left(i - start) + start;
  int r = right(i - start) + start;
  int max = i;
  if (r < start + size && vec[r] > vec[i]) {
    max = r;
  }
  if (l < start + size && vec[l] > vec[max]) {
    max = l;
  }

  if (i != max) {
    std::swap(vec[i], vec[max]);
    max_heapify(vec, max, size, start);
  }
}

void build_heap(std::vector<int> &vec, int start, int end) {
  int size = static_cast<int>(end - start) + 1;
  for (int i = start + size / 2; i != start - 1; --i) {
    max_heapify(vec, i, size, start);
  }
}

void heap_sort(std::vector<int> &vec, int start, int end) {
  if (end == start) return;
  build_heap(vec, start, end);
  int size = static_cast<int>(end - start) + 1;
  for (auto i = end; i != start; --i) {
    std::swap(vec[i], vec[start]);
    --size;
    max_heapify(vec, start, size, start);
  }
}

