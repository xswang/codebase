#include <iostream>
#include <map>

class RegisterClass {
 public:
  RegisterClass(const char* class_name, void* fp){
    register_m_[class_name] = fp;
    std::cout << "Register " << class_name << " before main" << std::endl; 
  }
  static void* getIns(const char* class_name) {
    return register_m_[class_name];
  }

  ~RegisterClass() {}
 typedef std::map<const char*, void*> register_map_type;
 static register_map_type register_m_;
};

RegisterClass::register_map_type RegisterClass::register_m_ = RegisterClass::register_map_type();

#define REGISTER(class_name)               \
    class Register##class_name {           \
     public:                               \
      static void* NewInstance() {         \
       return new class_name;              \
      }                                    \
     private:                              \
      static const RegisterClass  static_register_;     \
    };                                     \
const RegisterClass Register##class_name::static_register_(#class_name, Register##class_name::NewInstance()); 

class Conv {
 public:
  Conv() {
    name_ = "Conv";
  }
  void hi() {
    std::cout << "Conv has been Registered!" << std::endl;
  }
  std::string name_;
};
       
REGISTER(Conv)


int main() {
  std::cout << "==============main start==================" << std::endl;
  Conv* conv = static_cast<Conv*>(RegisterClass::getIns("Conv")); 
  conv->hi();
  std::cout << conv->name_ << std::endl;
  return 0;
}
