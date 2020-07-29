
#if 1



#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/length_unit.hpp>

namespace pqs::si {

  // PQS_SI_QUANTITY_LITERAL(length,m)

 namespace length{ 
      template <typename ValueType = double> 
      using m = make_quantity< length_unit::m ,ValueType>; 
   } 
    namespace literals{  
      constexpr auto operator""q_m (unsigned long long v) 
      { 
         return pqs::si::length::m<std::int64_t>(static_cast<std::int64_t>(v)); 
      } 
      constexpr auto operator""q_m(long double v) 
      { 
         return pqs::si:: length :: m<pqs::real_type>{static_cast<pqs::real_type>(v)} ; 
      } 
   }

} // pqs::si
#else
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/area.hpp>

using namespace pqs::si::literals;

int main()
{
   auto constexpr q1 = 1.0q_m;
   auto constexpr q2 = -1q_m;
   auto constexpr q3 = 1.0q_cm;
   auto constexpr q4 = -1q_cm;
   auto constexpr q5 = 1.0q_mm;
   auto constexpr q6 = -1q_mm;
   auto constexpr q7 = 1.0q_km;
   auto constexpr q8 = -1q_km;
   auto constexpr q10 = 1.0q_mm2;
  
}
#endif