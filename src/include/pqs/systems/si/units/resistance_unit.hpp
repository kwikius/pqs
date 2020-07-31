#ifndef PQS_SYSTEMS_SI_UNITS_RESISTANCE_UNIT_HPP_INCLUDED
#define PQS_SYSTEMS_SI_UNITS_RESISTANCE_UNIT_HPP_INCLUDED

#include <pqs/types/derived_quantity/resistance.hpp>

#include <pqs/concepts/associated/get_derived_quantity_symbol.hpp>
#include <pqs/systems/si/unit.hpp>

namespace pqs{

  /**
   * @brief specialise symbol for resistance in si measurement system
   */
   template <typename CharSet>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_resistance_t, 
      si_measurement_system,
      CharSet
   > = "R";

   template <>
   inline constexpr 
   basic_fixed_string get_derived_quantity_symbol<
      abstract_resistance_t, 
      si_measurement_system,
      charset_utf8
   > = "\u2126"; // Ω 

}

namespace pqs::si::resistance_unit{

   struct MR : normative_unit<abstract_resistance_t, exponent10<6> >{};
   struct kR : normative_unit<abstract_resistance_t, exponent10<3> >{};
   struct R  : normative_unit<abstract_resistance_t>{};
   struct mR : normative_unit<abstract_resistance_t, exponent10<-3> >{};
  
} // pqs::si::force_unit

#endif // PQS_SYSTEMS_SI_UNITS_RESISTANCE_UNIT_HPP_INCLUDED
