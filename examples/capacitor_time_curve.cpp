
#include <pqs/systems/si/capacitance.hpp>
#include <pqs/systems/si/current.hpp>
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

   let C = 0.47_q_uF;
   let V0 = 5.0_q_V;
   let R = 4.7_q_kR;

   for ( auto t = 0.0_q_ms ; t <= 50.0_q_ms; ++t ){
      auto const Vt = V0 * std::exp(-t / (R * C));
      std::cout << "at " << t << " voltage is " ;
      if     ( Vt >= 1_q_V )
         std::cout << Vt ;
      else if( Vt >= 1_q_mV )
         std::cout << implicit_cast<voltage::mV<> >(Vt);
      else if( Vt >= 1_q_uV )
         std::cout << implicit_cast<voltage::uV<> >(Vt);
      else if( Vt >= 1_q_nV )
         std::cout << implicit_cast<voltage::nV<> >(Vt);
      else
         std::cout << implicit_cast<voltage::pV<> >(Vt);

      std::cout << "\n";
   }
}

