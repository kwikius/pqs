
#include <pqs/systems/si/capacitance.hpp>
#include <pqs/systems/si/resistance.hpp>
#include <pqs/systems/si/time.hpp>
#include <pqs/systems/si/voltage.hpp>
#include <cmath>

using namespace pqs::si;
using namespace pqs::si::literals;

int main()
{
    std::cout << "Pqs capacitor time curve example\n";
    std::cout.setf(std::ios_base::fixed,std::ios_base::floatfield);
    std::cout.precision(3);

    #define let auto constexpr

    let C = 0.47q_uF;
    let V0 = 5.0q_V;
    let R = 4.7q_kR;

    for ( auto t = 0.0q_ms ; t <= 50.0q_ms; ++t ){
        auto const Vt = V0 * std::exp(-t / (R * C));
        std::cout << "at " << t << " voltage is " ;
        if     ( Vt >= 1q_V )    std::cout << Vt ;
        else if( Vt >= 1q_mV )   std::cout << voltage::mV<>{Vt};
        else if( Vt >= 1q_uV )   std::cout << voltage::uV<>{Vt};
        else if( Vt >= 1q_nV )   std::cout << voltage::nV<>{Vt};
        else                     std::cout << voltage::pV<>{Vt};
        std::cout << "\n";
    }
}

