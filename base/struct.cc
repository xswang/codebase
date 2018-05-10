/*
 * struct.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <iostream>
#include <string.h>
#include <unordered_map>

struct Summary {
  Summary() {
    memset(values, 0, sizeof(float) * 10);
  }
  float values[10];
};

int main() {
  std::unordered_map<uint64_t, struct Summary> test_map;

  struct Summary tempstruct;
  // std::cout << tempstruct.values[2] << std::endl;

  struct Summary &S = (test_map[0] = tempstruct);

  uint64_t posS = ((uint64_t)(&S) - sizeof(uint64_t));
  posS = (uint64_t)(&S);
  std::cout << posS << std::endl;
}
