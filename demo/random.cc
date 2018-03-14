/*
 * random.h
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include "/root/xiaoshu/opensource/code-base/demo/random.h"
#define MAX_NUM 127

int main() {
  float sum = 0.0;
  for (int i = 0; i < MAX_NUM; ++i) {
    //std::cout << " === " << local_random_engine() << std::endl;
    auto val = local_normal_real_distribution<double>(0.0, .1)(local_random_engine());
    sum += val;
    //std::cout << val << std::endl;
  }
  std::cout << sum << std::endl;

  return 0;
}

