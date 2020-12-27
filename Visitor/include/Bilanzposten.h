#pragma once
#include <Visitor.h>
#include <memory>

class Visitor;

class Bilanzposten {
  public:
    Bilanzposten(double wert, int abschreibungsdauer);

    double m_wert;
    int m_abschreibungsdauer;

    virtual void accept(std::shared_ptr<Visitor> visitor) const = 0;
};

class Gebaude : public Bilanzposten {
  public:
    Gebaude(double wert, int abschreibungsdauer);
    void accept(std::shared_ptr<Visitor> visitor) const;
};

class Fahrzeug : public Bilanzposten {
  public:
    Fahrzeug(double wert, int abschreibungsdauer);
    void accept(std::shared_ptr<Visitor> visitor) const;
};
