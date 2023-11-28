#pragma once

#include <iostream>
#include <vector>

void insertion_sort(std::vector<int> &vec, int start, int end) {
  int i, j, key;
  for (i = start + 1; i < end; i++) {
    key = vec[i];
    j = i - 1;
    while (j >= 0 && vec[j] > key) {
      vec[j + 1] = vec[j];
      j = j - 1;
    }
    vec[j + 1] = key;
  }
}

void merge_sort(std::vector<int> &vec, int start, int end) { // NOLINT
  if (end - start <= 1) return;

  if (end - start == 2) {
    if (vec[start] > vec[start + 1]) {
      std::swap(vec[start], vec[start + 1]);
      return;
    }
  }

  merge_sort(vec, start, start + (end - start) / 2);
  merge_sort(vec, start + (end - start) / 2, end);

  std::vector<int> tmp;
  int i = start, j = start + (end - start) / 2;

  while (i < start + (end - start) / 2 && j < end) {
    if (vec[i] < vec[j]) {
      tmp.push_back(vec[i]);
      ++i;
    } else {
      tmp.push_back(vec[j]);
      ++j;
    }
  }

  if (i == start + (end - start) / 2) {
    for (auto t = j; t < end; ++t) tmp.push_back(vec[t]);
  } else {
    for (auto t = i; t < start + (end - start) / 2; ++t) tmp.push_back(vec[t]);
  }

  for (auto t = start; t < end; ++t) {
    vec[t] = tmp[t - start];
  }
}

void hybrid_sort(std::vector<int> &vec, int start, int end) { // NOLINT
  if (end - start <= 20) {
    insertion_sort(vec, start, end);
    return;
  }

  merge_sort(vec, start, start + (end - start) / 2);
  merge_sort(vec, start + (end - start) / 2, end);

  std::vector<int> tmp;
  int i = start, j = start + (end - start) / 2;

  while (i < start + (end - start) / 2 && j < end) {
    if (vec[i] < vec[j]) {
      tmp.push_back(vec[i]);
      ++i;
    } else {
      tmp.push_back(vec[j]);
      ++j;
    }
  }

  if (i == start + (end - start) / 2) {
    for (auto t = j; t < end; ++t) tmp.push_back(vec[t]);
  } else {
    for (auto t = i; t < start + (end - start) / 2; ++t) tmp.push_back(vec[t]);
  }

  for (auto t = start; t < end; ++t) {
    vec[t] = tmp[t - start];
  }
}