#include <iostream>

class MyClass {
public:
    MyClass(int x);
    void fn();
private:
    class MyClass_p;
    MyClass_p* d;
};
