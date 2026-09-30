#include <iostream>
#include <vector>
#include <map>
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

void doPushBack23(auto&& container, auto&& value)
requires requires { container.push_back(value); }
{
    container.push_back(value);
}

auto doPushBack11(auto&& container, auto&& value) -> std::void_t<decltype(container.push_back(value))>
{
    container.push_back(value);
}

void doPushBackPlain(auto&& container, auto&& value)
{
    container.push_back(value);
}

int main() {
    Container<double> a{2.0};
    Container<string> b{"Peter"};
    cout << a.m_content << b.m_content << endl;

    std::vector<int> v;
    doPushBack11(v, 3);
    doPushBack23(v, 3);
    doPushBackPlain(v, 3);

    std::map<int, int> m;
    //doPushBack11(m, 3);
    //doPushBack23(m, 3);
    doPushBackPlain(m, 3);


}
