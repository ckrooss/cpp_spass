#include <Bilanzposten.h>
#include <Visitor.h>
#include <iostream>
#include <memory>

int main() {
    Fahrzeug a = Fahrzeug(50.0, 3);
    Fahrzeug b = Fahrzeug(30.0, 4);
    Gebaude c = Gebaude(120, 2);

    //auto v = std::make_shared<Visitor>();
    auto v = std::shared_ptr<Visitor>(new Visitor[2](), [](Visitor* v) { delete[] v; });
    a.accept(v);
    b.accept(v);
    c.accept(v);
    v.reset();
}
