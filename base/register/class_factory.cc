#include "class_factory.h"

// zhangyule
ClassFactory::register_m ClassFactory::m_register = ClassFactory::register_m();

void* ClassFactory::get_instance(const char* class_name) {
  if (ClassFactory::m_register.find(class_name) 
      == ClassFactory::m_register.end()) {
    return NULL;
  }
  std::cout << "found" << std::endl;
  // zhangyule
  return ClassFactory::m_register[class_name];
}

// zhangyule
void ClassFactory::register_class(const char* class_name, void* class_obj) {
  // zhangyule
  ClassFactory::m_register[class_name] = class_obj;
  std::cout << "insert class name: " << class_name << std::endl;
}
