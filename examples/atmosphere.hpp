#ifndef PQS_EXAMPLES_ATMOSPHERE_HPP_INCLUDED
#define PQS_EXAMPLES_ATMOSPHERE_HPP_INCLUDED

#include <pqs/systems/si/pressure.hpp>
#include <pqs/systems/si/density.hpp>
#include <pqs/systems/si/energy.hpp>
#include <pqs/systems/si/mass.hpp>
#include <pqs/systems/si/temperature.hpp>
#include <pqs/systems/si/substance.hpp>
#include <pqs/systems/si/length.hpp>
#include <pqs/systems/si/acceleration.hpp>

struct air{

   static constexpr 
   auto specific_gas_constant()
   {
      auto constexpr  J = pqs::si::energy_unit::J();
      auto constexpr kg = pqs::si::mass_unit::kg();
      auto constexpr  K = pqs::si::temperature_unit::K();
      return pqs::make_v_quantity< J/(kg * K) > {287.058};
   }

   static constexpr 
   pqs::si::pressure::Pa<> 
   get_sea_level_pressure() 
   { return pqs::si::pressure::Pa<>{101325};}

   static pqs::si::pressure::Pa<> 
   get_static_pressure(pqs::si::length::m<> const & asl);

   static pqs::si::density::kg_per_m3<> 
   get_density(pqs::si::length::m<> const & asl);
   
};


#endif // PQS_EXAMPLES_ATMOSPHERE_HPP_INCLUDED
