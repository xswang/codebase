/*
 * random.h
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include "/root/xiaoshu/opensource/code_base/demo/random.h"
#define MAX_NUM 127

int main() {
  float ss = 1.0;
  for (int k = 0; k < 1; ++k) {
    float sum = 0.0;
    for (int i = 0; i < MAX_NUM; ++i) {
      //std::cout << " === " << local_random_engine() << std::endl;
      //auto val = local_normal_real_distribution<double>(0.0, .9)(local_random_engine());
      auto val = local_uniform_real_distribution<double>()(local_random_engine());
      sum += val;
      if (val >= 0.98) std::cout << val << std::endl;
    }
    // std::cout << "sum = " << sum << std::endl;
    ss *= sum;
    // std::cout << "xxx = " << ss << std::endl;
  }
  // std::cout << "ss = " << ss << std::endl;

  return 0;
}

