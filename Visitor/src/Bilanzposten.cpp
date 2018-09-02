#include <Bilanzposten.h>
#include <Visitor.h>

Bilanzposten::Bilanzposten(double wert, int abschreibungsdauer)
    : m_wert(wert), m_abschreibungsdauer(abschreibungsdauer) {}

Gebaude::Gebaude(double wert, int abschreibungsdauer)
    : Bilanzposten(wert, abschreibungsdauer) {}

void Gebaude::accept(std::shared_ptr<Visitor> visitor) const {
  std::cout << "got a visitor" << std::endl;
  visitor->visit(this);
  //delete visitor.get();
}

Fahrzeug::Fahrzeug(double wert, int abschreibungsdauer)
    : Bilanzposten(wert, abschreibungsdauer) {}

void Fahrzeug::accept(std::shared_ptr<Visitor> visitor) const {
  std::cout << "got a visitor" << std::endl;
  visitor->visit(this);
}
