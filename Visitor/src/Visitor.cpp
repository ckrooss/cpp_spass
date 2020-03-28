#include <Visitor.h>
#include <iostream>

Visitor::Visitor() {
    std::cout << "Visitor::Visitor()" << std::endl;
    m_name = "el visitore";
}

Visitor::~Visitor() {
    std::cout << "Visitor::~Visitor()" << std::endl;
}

void Visitor::visit(const Gebaude* /*gebaude*/) {
    std::cout << m_name << ": visiting a gebaude" << std::endl;
}

void Visitor::visit(const Fahrzeug* /*fahrzeug*/) {
    std::cout << m_name << ": visiting a fahrzeug" << std::endl;
}
