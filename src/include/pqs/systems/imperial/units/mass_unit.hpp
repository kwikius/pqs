#ifndef PQS_SYSTEMS_IMPERIAL_MASS_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_MASS_UNIT_HPP_INCLUDED

#include <pqs/types/charset.hpp>
#include <pqs/systems/imperial/unit.hpp>
#include <pqs/types/base_quantity/mass.hpp>
#include <pqs/bits/named.hpp>

namespace pqs::imperial::mass_unit{

   struct lb: named<"lb">, pqs::base_unit<
      base_mass,imperial_measurement_system
   >{};

   struct kg : named<"kg"> ,
      decltype( lb() * std::ratio<2500000,1133981>())
   {};

   struct ton : named<"ton"> ,
      decltype( lb() * std::ratio<2'000>())
   {};

} // pqs::si::mass_unit


#endif // PQS_SYSTEMS_IMPERIAL_MASS_UNIT_HPP_INCLUDED
