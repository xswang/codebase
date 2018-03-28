/*
 * vector_assign.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <vector>
#include <iostream>

int main() {
  for (int k = 0; k < 100; ++k) {
    std::vector<double> a;
    a.assign(2, 0.0);
    std::vector<std::vector<double>> b;
    b.assign(3, a);
    double* bb = &b[0][0];

    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 3; ++j) {
        std::cout << bb[i * 2 + j] << std::endl;
      }
    }
  } 
}
