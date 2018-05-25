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

template<typename T1, typename T2>
bool CheckSubSet(std::vector<T1>& x, std::vector<T1>& y) {
  std::unordered_map<T1, T2> hash_table;
  for (int y_index = 0; y_index < y.size(); ++y_index) {
    hash_table.insert({y[y_index], 1}); // we first insert all elements of y into hash_table
  }
  int check_num = 0; // check counter
  for (int x_index = 0; x_index < x.size(); ++x_index) {
    typename std::unordered_map<T1, T2>::iterator iter;
    iter = hash_table.find(x[x_index]); // then we check whether elements of x in the hash_table
    if (iter != hash_table.end()) ++check_num; // if we find, increase the counter
  }
  if (check_num == x.size()) return true; // if check_num equal x.size(), means we found all, reutrn true
  else return false;
}

int main() {
  std::vector<int> x = {1,3,4,2};
  std::vector<int> y = {1,4, 2,3};
  bool res = CheckSubSet<int, int>(x, y);
  std::cout << res << std::endl;
}
