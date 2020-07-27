#ifndef PQS_SYSTEMS_SI_QUANTITY_NAMED_DIMENSION_SYMBOL_HPP_INCLUDED
#define PQS_SYSTEMS_SI_QUANTITY_NAMED_DIMENSION_SYMBOL_HPP_INCLUDED

#include <pqs/types/derived_quantity/force.hpp>
#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/quantity/measurement_system_def.hpp>

namespace pqs{

   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_force_t, 
      si_measurement_system,
      CharSet
   > = "N";

}
#endif // PQS_SYSTEMS_SI_QUANTITY_NAMED_DIMENSION_SYMBOL_HPP_INCLUDED
