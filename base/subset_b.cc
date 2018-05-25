/*
 * subset.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

template<typename T>
bool CheckSubSet(std::vector<T>& x, std::vector<T>& y) {
  std::sort(x.begin(), x.end()); // sort x first
  std::sort(y.begin(), y.end()); // sort y first
  int x_pos = 0; // the element in x which be searched in y now.
  //
  // traverse x, check whether x element in y
  //
  for (int y_index = 0; y_index < y.size() && x_pos < x.size(); ++y_index) {
    if (x[x_pos] == y[y_index]) {  // if x[x_pos] equal y[y_index], it means can check next element in x
      ++x_pos;
    }
  }
  if (x_pos == x.size()) return true; // if x_pos equal x.size(), it means all elements of x in y
  else return false;
}

int main() {
  std::vector<int> x = {1,3,4,2};
  std::vector<int> y = {1,4, 2,3};
  bool res = CheckSubSet<int>(x, y);
  std::cout << res << std::endl;
}
