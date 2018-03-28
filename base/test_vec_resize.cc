/*
 * test_vec_resize.cc
 * Copyright (C) 2017 root <root@izt4ngd9bowt8sik34geskz>
 *
 * Distributed under terms of the MIT license.
 */
#include <iostream>
#include <vector>


int main() {
  std::vector<int> vec = {1, 2, 3};
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << std::endl;
  }
  std::cout << "==========" << std::endl;
  vec.resize(5, 0);
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << std::endl;
  }
  std::cout << "ٍ==========" << std::endl;
  int* a = vec.data();
  std::cout << *a << std::endl;

  vec.clear();
  std::cout << vec.size() << std::endl;
  return 0;
}
