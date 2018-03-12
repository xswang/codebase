/*
 * random.h
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include "/root/xiaoshu/opensource/code-base/demo/random.h"

int main() {
  for (int i = 0; i < 10; ++i) {
    std::cout << " === " << local_random_engine() << std::endl;
    auto val = local_normal_real_distribution<double>(0.0, 1.0)(local_random_engine());
    std::cout << val << std::endl;
  }

  return 0;
}

