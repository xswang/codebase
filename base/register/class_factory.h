#ifndef _CLASS_FACTORY_H
#define _CLASS_FACTORY_H

#include <iostream>
#include <map>
#include <string>

// typedef void *(*fun_ptr) ();

class ClassFactory {
 public:
  static void* get_instance(const char*);
  static void register_class(const char*, void*);

  // typedef std::map<std::string, fun_ptr> register_m;
  typedef std::map<std::string, void*> register_m;
  static register_m m_register;
};

#endif
