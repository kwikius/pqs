

#include <pqs/systems/si/inductance.hpp>
#include <pqs/systems/si/resistance.hpp>
#include <pqs/systems/si/voltage.hpp>
#include <pqs/systems/si/current.hpp>
#include <pqs/systems/si/time.hpp>

#define let constexpr auto

/*
Lm is inductance of motor
Rm is resistance of motor windings
Em is emf due to motor velocity
Im is current through motor
Vm is voltage across motor

Vlm = Lm * DIm/Dt
Vrm = Im * Rm

Em = Vm - ( Vlm + Vrm) 

Vm = 0 or Vm = Vmax
*/

using namespace pqs::si;
using namespace pqs::si::literals;

int main()
{
   //Lm is inductance of motor
   let Lm = 1.0q_mH;
   // Rm is motor winding resistance
   let Rm = 0.1q_R;
   // current at now and prev
   let Im0 = 0.1q_A;
   let Im1 = 0.2q_A;

   let dt = 0.05q_s;

   let Vlm = Lm * (Im1 - Im0) / dt;
   let Vrm = Im1 * Rm;
   
   let Vm = 5.0q_V;

   pqs::si::voltage::V<> Em = Vm - ( Vlm + Vrm);
   std::cout << "back emf = " << Em <<'\n';
}