#ifndef PQS_SI_DENSITY_HPP_INCLUDED
#define PQS_SI_DENSITY_HPP_INCLUDED

#include <pqs/systems/si/quantity.hpp>
#include <pqs/systems/si/units/mass_unit.hpp>
#include <pqs/systems/si/units/volume_unit.hpp>

namespace pqs::si { 

   namespace density{

      template <typename ValueType = double> 
      using kg_per_m3 = make_v_quantity< pqs::si::mass_unit::kg() / pqs::si::volume_unit::m3() ,ValueType>; 
   }

   namespace literals{
  
      constexpr auto operator""q_kg_per_m3(unsigned long long v) 
      { 
         return pqs::si::density::kg_per_m3<std::int64_t>{static_cast<std::int64_t>(v)}; 
      }

      constexpr auto operator""q_kg_per_m3(long double v) 
      { 
         return pqs::si::density::kg_per_m3<pqs::real_type>{static_cast<pqs::real_type>(v)} ; 
      } 
   }

}// pqs::si

#endif // PQS_SI_DENSITY_HPP_INCLUDED
