#pragma once
#include <Bilanzposten.h>
#include <iostream>
#include <string>

class Gebaude;
class Fahrzeug;

class Visitor {
  public:
    Visitor();
    ~Visitor();
    void visit(const Gebaude* gebaude);
    void visit(const Fahrzeug* fahrzeug);
    std::string m_name;
};
