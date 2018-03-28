#ifndef _REGISTER_H
#define _REGISTER_H

class Register {
 public:
   // zhangyule
  Register(const char*, void*);
};


#define REGISTER(class_name) \
    class Register##class_name { \
     public:                    \
      static void* instance() { \
        return new class_name;   \
      }                      \
     private:                         \
      static const Register _static_register; \
    };                     \
  const Register Register##class_name::_static_register(#class_name, Register##class_name::instance());
#endif
