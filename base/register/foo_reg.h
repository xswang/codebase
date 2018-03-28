#ifndef _FOO_REG_H
#define _FOO_REG_H

#include <string>
#include "register.h"

class Foo {
 public:
  Foo() {
    id_ = 1;
    name_ = "foo ok";
  }
  int id_;
  std::string name_;
};

class Foo1 {
 public:
  Foo1() {
   id_ = 1;
   name_ = "foo1 ok";
  }
  int id_;
  std::string name_;
};

REGISTER(Foo)
REGISTER(Foo1)
#endif
