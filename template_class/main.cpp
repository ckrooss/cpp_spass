#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <class T>
struct Container {
    Container(T content) {
        m_content = content;
    }

    T m_content;
};

int main() {
    Container<double> a{2.0};
    Container<string> b{"Peter"};
    cout << a.m_content << b.m_content << endl;
}
