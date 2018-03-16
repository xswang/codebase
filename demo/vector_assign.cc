/*
 * vector_assign.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <vector>
#include <iostream>

int main() {
  std::vector<int> a(2, 0);
  std::vector<std::vector<int>> b;
  b.assign(3, a);

  std::cout << b.size() << std::endl;
  std::cout << b[1].size() << std::endl;
  std::cout << b[0][0] << std::endl;
  
}
