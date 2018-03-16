#include <iostream>
#include <cstdio>
#include "register.h"
#include "class_factory.h"
#include "foo_reg.h"

int main() {
  std::cout << "start main************************" << std::endl;
  Foo* foo = static_cast<Foo*>(ClassFactory::get_instance("Foo"));
  //printf("foo:%p\n", foo);
  std::cout << foo->name_ << std::endl;
  Foo1* foo1 = static_cast<Foo1*>(ClassFactory::get_instance("Foo1"));
  //printf("foo1:%p\n", foo1);
  std::cout << foo1->name_ << std::endl;
  return 0;
}
