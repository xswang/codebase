#include <iostream>
#include <map>
#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <unordered_map>


const size_t BUF_SIZE = 1e7;
std::unordered_map<int,int> m_; 
std::vector<int> vec_;
void init() {
  for (int i = 0; i < BUF_SIZE; ++i) {
    m_[i] = i;
    vec_.push_back(i);
  }   
}
int main() {
  init();
  std::vector<int> vec(BUF_SIZE, 0); 
  time_t start = clock();
  for (int i = 0; i < BUF_SIZE; ++i) {
    vec[i] = vec_[i]; 
  }
  time_t end = clock();
  std::cout << "for vector: " << (double)(end - start) * 1.0 / CLOCKS_PER_SEC << std::endl;

  std::unordered_map<int, int>::iterator iter;
  time_t ss = clock();
  for (iter = m_.begin(); iter != m_.end(); ++iter) {
    vec[iter->first] = iter->second;
  }
  time_t ee = clock();
  std::cout << "hashmap: " << (double)(ee - ss) * 1.0 / CLOCKS_PER_SEC << std::endl;
}

