#pragma once
#include <Bilanzposten.h>
#include <iostream>
#include <string>

struct Gebaude;
struct Fahrzeug;

class Visitor {
  public:
    Visitor();
    ~Visitor();
    void visit(const Gebaude* gebaude);
    void visit(const Fahrzeug* fahrzeug);
    std::string m_name;
};
