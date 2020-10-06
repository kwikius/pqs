#ifndef PQS_SYSTEMS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED

#include <pqs/systems/imperial/units/length_unit.hpp>
#include <pqs/systems/imperial/units/time_unit.hpp>
#include <pqs/types/derived_quantity/speed.hpp>
#include <pqs/concepts/associated/unit_binary_op.hpp>

namespace pqs::imperial::speed_unit{

   struct ft_per_s : 
      decltype( length_unit::ft() / time_unit::s() ) // to output "ft/s"
   {};

   struct yd_per_s :
      decltype( length_unit::yd() / time_unit::s() )  // to output "yd/s"
   {};

   struct mi_per_hr : 
      decltype( length_unit::mi() / time_unit::hr() ) // to output "mi/hr"
   {};

   // since the unit has a name we don't want to use the operators here
   // to output "knot"
   struct knot : named<"knot"> ,
       unit_conversion<
          pqs::abstract_speed_t,
          decltype(std::ratio<1687809711, 1000000000>() ^ pqs::exponent10<0>())
       >{};

} // pqs::imperial::speed_unit

#endif // PQS_SYSTEMS_IMPERIAL_SPEED_UNIT_HPP_INCLUDED
