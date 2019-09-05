#include "MyClass.h"

class MyClass::MyClass_p {
  public:
    MyClass_p(int x) {
        m_x = x;
    }

    void fn() {
        std::cout << "Ahoy = " << std::to_string(m_x) << std::endl;
    }

  private:
    int m_x;
};

MyClass::MyClass(int x) {
    d = new MyClass_p(x);
}

void MyClass::fn() {
    return d->fn();
}
