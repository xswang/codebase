/*
 * make_shared.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <iostream>
#include <vector>
#include <memory>

class Test {
 public:
  int* value() {
    return p_;
  }
  std::vector<int> vec_value() {
    return vec_;
  }
  int* p_;
  std::vector<int> vec_;
};
int main() {
  std::shared_ptr<Test> test = std::make_shared<Test>();
  int a = 10;
  int* point = test->value();
  point = &a;
  std::cout  << *point << std::endl;
  std::vector<int> vec = test->vec_value();
  std::cout << "vec size:" << vec.size() << std::endl;
  vec.resize(10);
  std::cout << "vec size: " << vec.size() << std::endl;
  return 0;
}
