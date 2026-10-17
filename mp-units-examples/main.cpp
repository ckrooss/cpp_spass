#include <mp-units/systems/si.h>
#include <mp-units/systems/usc.h>
#include <mp-units/systems/isq.h>
#include <mp-units/core.h>
#include <mp-units/utility/uncertain.h>
#include <print>
//import mp_units;

using namespace mp_units;
using namespace mp_units::si::unit_symbols;
using mp_units::usc::unit_symbols::deg_F;
using mp_units::isq::thermodynamic_temperature;
using mp_units::utility::uncertain;


void controller(QuantityPointOf<thermodynamic_temperature> auto gtIst,
                QuantityPointOf<thermodynamic_temperature> auto gtSoll,
                QuantityOf<thermodynamic_temperature> auto gtDelta) {
    std::println("gtIst = {} ({})", gtIst, gtIst.in(deg_F));
    std::println("gtSoll = {} ({})", gtSoll, gtSoll.in(deg_F));
    std::println("delta = {} ({})", gtDelta, gtDelta.in(deg_F));

    auto avg = midpoint(gtIst, gtSoll);
    std::println("Average temperature: {} ({})", avg, avg.in(deg_F));

    quantity length = uncertain{12.0, 0.1} * cm;
    quantity k_local = uncertain{401.0, 1.0} * W / (m * K);
    quantity power = k_local * gtDelta * length;
    std::println("conductivity: {} at {} -> {}", k_local, gtIst, power.in(W));
}

int main() {
    auto gtIst = point<deg_C>(19.0);
    auto gtSoll = point<deg_C>(250.0);
    auto gtDelta = gtSoll - gtIst;

    controller(gtIst, gtSoll, gtDelta);
    //controller(point<si::pascal>(0.0), point<si::pascal>(100.0), delta<si::pascal>(5.0));
}
