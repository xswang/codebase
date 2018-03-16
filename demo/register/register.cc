#include "register.h"
#include "class_factory.h"

// zhangyule
Register::Register(const char* class_name, void* fp) {
  ClassFactory::register_class(class_name, fp);
}
