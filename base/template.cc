/*
 * template.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <string>

template<typename T1, int N = 0>
void RecurPrint(const T1& t1) {
  std::cout << "N: " << N << std::endl;
}
template<class T, class ...Args, int N = 0>
void RecurPrint(const T& t1, Args... args) {
  std::cout << "Args size: " << sizeof...(args) << std::endl;
  RecurPrint(args...);
}

template <typename T, int N = 2>
void print(const T& t) {
  std::cout << " print(const T& t) " << std::endl;
}
template <typename First, typename... Rest, int N = 0>
void print(const First& first, const Rest&... rest) {
  std::cout << "sizeof...(Rest): " << sizeof...(Rest) << std::endl;
  std::cout << first << ", ";
  print(rest...); // recursive call using pack expansion syntax
}

int main() {
  RecurPrint("1.1", "2.2");
  RecurPrint("1.1", "2.2", "3.3");
  print(10, 20);
  print(10, 20, 30, 40);
  return 0;
}
