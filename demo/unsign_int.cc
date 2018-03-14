/*
 * unsign_int.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <cstdint>

int main() {
  for (int i = 0; i < 127; ++i) {
    auto a = (uint64_t)(i);
    bool b = a < (uint64_t)(0);
    std::cout << b << std::endl;
  }

}


